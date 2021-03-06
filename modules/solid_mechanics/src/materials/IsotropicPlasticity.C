/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "IsotropicPlasticity.h"

#include "SymmIsotropicElasticityTensor.h"

#include "PiecewiseLinear.h"

template<>
InputParameters validParams<IsotropicPlasticity>()
{
  InputParameters params = validParams<ReturnMappingModel>();

  // Linear strain hardening parameters
  params.addRequiredParam<Real>("yield_stress", "The point at which plastic strain begins accumulating");
  params.addParam<Real>("hardening_constant", "Hardening slope");
  params.addParam<FunctionName>("hardening_function", "True stress as a function of plastic strain");

  return params;
}


IsotropicPlasticity::IsotropicPlasticity( const InputParameters & parameters)
  :ReturnMappingModel(parameters),
   _yield_stress(getParam<Real>("yield_stress")),
   _hardening_constant(isParamValid("hardening_constant") ? getParam<Real>("hardening_constant") : 0),
   _hardening_function(isParamValid("hardening_function") ? dynamic_cast<PiecewiseLinear*>(&getFunction("hardening_function")) : NULL),

   _plastic_strain(declareProperty<SymmTensor>("plastic_strain")),
   _plastic_strain_old(declarePropertyOld<SymmTensor>("plastic_strain")),
   _scalar_plastic_strain(_hardening_function ? &declareProperty<Real>("scalar_plastic_strain") : NULL),
   _scalar_plastic_strain_old(_hardening_function ? &declarePropertyOld<Real>("scalar_plastic_strain") : NULL),

   _hardening_variable(declareProperty<Real>("hardening_variable")),
   _hardening_variable_old(declarePropertyOld<Real>("hardening_variable"))
{
  if (_yield_stress <= 0)
  {
    mooseError("Yield stress must be greater than zero");
  }
  if ((isParamValid("hardening_constant") && isParamValid("hardening_function")) ||
      (!isParamValid("hardening_constant") && !isParamValid("hardening_function")))
  {
    mooseError("Either hardening_constant or hardening_function must be defined");
  }
  if (isParamValid("hardening_function") && !_hardening_function)
  {
    mooseError("The hardening_function must be PiecewiseLinear");
  }
}

void
IsotropicPlasticity::initStatefulProperties(unsigned n_points)
{
  for (unsigned qp(0); qp < n_points; ++qp)
  {
    _hardening_variable[qp] = 0;
    if (_scalar_plastic_strain)
    {
      (*_scalar_plastic_strain)[qp] = (*_scalar_plastic_strain_old)[qp] = 0;
    }
  }
  ReturnMappingModel::initStatefulProperties( n_points );
}

void
IsotropicPlasticity::computeStressInitialize(unsigned qp, Real effectiveTrialStress, const SymmElasticityTensor & elasticityTensor)
{
  const SymmIsotropicElasticityTensor * eT = dynamic_cast<const SymmIsotropicElasticityTensor*>(&elasticityTensor);
  if (!eT)
  {
    mooseError("IsotropicPlasticity requires a SymmIsotropicElasticityTensor");
  }
  _shear_modulus = eT->shearModulus();
  _yield_condition = effectiveTrialStress - _hardening_variable_old[qp] - _yield_stress;
  _hardening_variable[qp] = _hardening_variable_old[qp];
  _plastic_strain[qp] = _plastic_strain_old[qp];
}

void
IsotropicPlasticity::computeStressFinalize(unsigned qp, const SymmTensor & plasticStrainIncrement)
{
  _plastic_strain[qp] += plasticStrainIncrement;
}

Real
IsotropicPlasticity::computeResidual(unsigned qp, Real effectiveTrialStress, Real scalar)
{
  Real residual(0);
  _hardening_slope = 0;
  if (_yield_condition > 0)
  {
    _hardening_slope = computeHardening( qp, scalar );
    residual = effectiveTrialStress - (3. * _shear_modulus * scalar) - _hardening_variable[qp] - _yield_stress;
    _hardening_variable[qp] = _hardening_variable_old[qp] + (_hardening_slope * scalar);
  }
  return residual;
}

Real
IsotropicPlasticity::computeDerivative(unsigned /*qp*/, Real /*effectiveTrialStress*/, Real /*scalar*/)
{
  Real derivative(1);
  if (_yield_condition > 0)
  {
    derivative = -3 * _shear_modulus - _hardening_slope;
  }
  return derivative;
}

void
IsotropicPlasticity::iterationFinalize(unsigned qp, Real scalar)
{
  _hardening_variable[qp] = _hardening_variable_old[qp] + (_hardening_slope * scalar);
  if (_scalar_plastic_strain)
  {
    (*_scalar_plastic_strain)[qp] = (*_scalar_plastic_strain_old)[qp] + scalar;
  }
}

Real
IsotropicPlasticity::computeHardening( unsigned qp, Real /*scalar*/ )
{
  Real slope = _hardening_constant;
  if (_hardening_function)
  {
    const Real strain_old = (*_scalar_plastic_strain_old)[qp];
    Point p;
    slope = _hardening_function->timeDerivative( strain_old, p );
  }
  return slope;
}


// DEPRECATED CONSTRUCTOR
IsotropicPlasticity::IsotropicPlasticity(const std::string & deprecated_name, InputParameters parameters)
  :ReturnMappingModel(deprecated_name, parameters),
   _yield_stress(getParam<Real>("yield_stress")),
   _hardening_constant(isParamValid("hardening_constant") ? getParam<Real>("hardening_constant") : 0),
   _hardening_function(isParamValid("hardening_function") ? dynamic_cast<PiecewiseLinear*>(&getFunction("hardening_function")) : NULL),

   _plastic_strain(declareProperty<SymmTensor>("plastic_strain")),
   _plastic_strain_old(declarePropertyOld<SymmTensor>("plastic_strain")),
   _scalar_plastic_strain(_hardening_function ? &declareProperty<Real>("scalar_plastic_strain") : NULL),
   _scalar_plastic_strain_old(_hardening_function ? &declarePropertyOld<Real>("scalar_plastic_strain") : NULL),

   _hardening_variable(declareProperty<Real>("hardening_variable")),
   _hardening_variable_old(declarePropertyOld<Real>("hardening_variable"))
{
  if (_yield_stress <= 0)
  {
    mooseError("Yield stress must be greater than zero");
  }
  if ((isParamValid("hardening_constant") && isParamValid("hardening_function")) ||
      (!isParamValid("hardening_constant") && !isParamValid("hardening_function")))
  {
    mooseError("Either hardening_constant or hardening_function must be defined");
  }
  if (isParamValid("hardening_function") && !_hardening_function)
  {
    mooseError("The hardening_function must be PiecewiseLinear");
  }
}

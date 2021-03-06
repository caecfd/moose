/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "NSMomentumViscousBC.h"

template<>
InputParameters validParams<NSMomentumViscousBC>()
{
  InputParameters params = validParams<NSIntegratedBC>();

  // Required parameters
  params.addRequiredParam<unsigned>("component", "(0,1,2) = (x,y,z) for which momentum component this BC is applied to");

  return params;
}




NSMomentumViscousBC::NSMomentumViscousBC(const InputParameters & parameters)
    : NSIntegratedBC(parameters),

      // Parameters to be specified in input file block...
      _component(getParam<unsigned>("component")),

      // Derivative computing object
      _vst_derivs(*this)
{
}



Real NSMomentumViscousBC::computeQpResidual()
{
  // n . (-tau) . v

  // Vector-valued test function
  RealVectorValue v_test;
  v_test(_component) = _test[_i][_qp];

  // The viscous contribution: n . tau . v
  Real visc_term = _normals[_qp] * (_viscous_stress_tensor[_qp] * v_test);

  // Note the sign...
  return -visc_term;
}



Real NSMomentumViscousBC::computeQpJacobian()
{
  // See Eqns. (41)--(43) from the notes for the viscous boundary term contributions
  Real visc_term = 0.;

  // Set variable names as in the notes
  const unsigned k = _component;
  const unsigned m = _component+1; // _component = 0,1,2 -> m = 1,2,3 global variable number

  // FIXME: attempt calling shared dtau function
  for (unsigned ell=0; ell<LIBMESH_DIM; ++ell)
    visc_term += _vst_derivs.dtau(k, ell, m) * _normals[_qp](ell);

  // Multiply visc_term by test function
  visc_term *= _test[_i][_qp];

  // Note the sign...
  return -visc_term;
}



Real NSMomentumViscousBC::computeQpOffDiagJacobian(unsigned jvar)
{
  // See Eqns. (41)--(43) from the notes for the viscous boundary
  // term contributions.

  // Map jvar into the variable m for our problem, regardless of
  // how Moose has numbered things.
  unsigned m = this->map_var_number(jvar);

  // Now compute viscous contribution
  Real visc_term = 0.;

  // Set variable names as in the notes
  const unsigned k = _component;

  for (unsigned ell=0; ell<LIBMESH_DIM; ++ell)
    visc_term += _vst_derivs.dtau(k, ell, m) * _normals[_qp](ell);

  // Multiply visc_term by test function
  visc_term *= _test[_i][_qp];

  // Note the sign...
  return -visc_term;
}


// DEPRECATED CONSTRUCTOR
NSMomentumViscousBC::NSMomentumViscousBC(const std::string & deprecated_name, InputParameters parameters)
    : NSIntegratedBC(deprecated_name, parameters),

      // Parameters to be specified in input file block...
      _component(getParam<unsigned>("component")),

      // Derivative computing object
      _vst_derivs(*this)
{
}

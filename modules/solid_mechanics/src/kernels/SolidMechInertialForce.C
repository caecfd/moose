/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "SolidMechInertialForce.h"
#include "SubProblem.h"

template<>
InputParameters validParams<SolidMechInertialForce>()
{
  InputParameters params = validParams<Kernel>();
    params.set<bool>("use_displaced_mesh") = true;
    params.addRequiredCoupledVar("velocity","velocity variable");
    params.addRequiredCoupledVar("acceleration","acceleration variable");
    params.addRequiredParam<Real>("beta","beta parameter");
    params.addRequiredParam<Real>("gamma","gamma parameter");
  return params;
}

SolidMechInertialForce::SolidMechInertialForce(const InputParameters & parameters)
  :Kernel(parameters),
   _density(getMaterialProperty<Real>("density")),
   _u_old(valueOld()),
   _vel_old(coupledValueOld("velocity")),
   _accel_old(coupledValueOld("acceleration")),
   _beta(getParam<Real>("beta")),
   _gamma(getParam<Real>("gamma"))
{}

Real
SolidMechInertialForce::computeQpResidual()
{
  if (_dt == 0)
    return 0;
  Real accel=1/_beta*(((_u[_qp]-_u_old[_qp])/(_dt*_dt)) - _vel_old[_qp]/_dt - _accel_old[_qp]*(0.5-_beta));
  return _test[_i][_qp]*_density[_qp]*accel;
}

Real
SolidMechInertialForce::computeQpJacobian()
{
  if (_dt == 0)
    return 0;
  return _test[_i][_qp]*_density[_qp]/(_beta*_dt*_dt)*_phi[_j][_qp];
}


// DEPRECATED CONSTRUCTOR
SolidMechInertialForce::SolidMechInertialForce(const std::string & deprecated_name, InputParameters parameters)
  :Kernel(deprecated_name, parameters),
   _density(getMaterialProperty<Real>("density")),
   _u_old(valueOld()),
   _vel_old(coupledValueOld("velocity")),
   _accel_old(coupledValueOld("acceleration")),
   _beta(getParam<Real>("beta")),
   _gamma(getParam<Real>("gamma"))
{}

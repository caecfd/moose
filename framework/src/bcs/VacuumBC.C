/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "VacuumBC.h"

template<>
InputParameters validParams<VacuumBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<Real>("alpha", 1, "No idea.");
  return params;
}

VacuumBC::VacuumBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _alpha(getParam<Real>("alpha"))
{}

Real
VacuumBC::computeQpResidual()
{
  return _test[_i][_qp]*_alpha*_u[_qp]/2.;
}

Real
VacuumBC::computeQpJacobian()
{
  return _test[_i][_qp]*_alpha*_phi[_j][_qp]/2.;
}


// DEPRECATED CONSTRUCTOR
VacuumBC::VacuumBC(const std::string & deprecated_name, InputParameters parameters) :
    IntegratedBC(deprecated_name, parameters),
    _alpha(getParam<Real>("alpha"))
{}

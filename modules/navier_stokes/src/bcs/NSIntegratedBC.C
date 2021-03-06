/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "NSIntegratedBC.h"

template<>
InputParameters validParams<NSIntegratedBC>()
{
  InputParameters params = validParams<IntegratedBC>();

  // Coupled variables
  params.addRequiredCoupledVar("u", "");
  params.addRequiredCoupledVar("v", "");
  params.addCoupledVar("w", ""); // only required in 3D

  params.addRequiredCoupledVar("rho", "density");
  params.addRequiredCoupledVar("rhou", "x-momentum");
  params.addRequiredCoupledVar("rhov", "y-momentum");
  params.addCoupledVar("rhow", "z-momentum"); // only required in 3D
  params.addRequiredCoupledVar("rhoe", "energy");

  // Required parameters
  params.addRequiredParam<Real>("gamma", "Ratio of specific heats.");
  params.addRequiredParam<Real>("R", "Gas constant.");

  return params;
}



NSIntegratedBC::NSIntegratedBC(const InputParameters & parameters)
    : IntegratedBC(parameters),

      // Coupled variables
      _u_vel(coupledValue("u")),
      _v_vel(coupledValue("v")),
      _w_vel(_mesh.dimension() == 3 ? coupledValue("w") : _zero),

      _rho(coupledValue("rho")),
      _rho_u(coupledValue("rhou")),
      _rho_v(coupledValue("rhov")),
      _rho_w(_mesh.dimension() == 3 ? coupledValue("rhow") : _zero),
      _rho_e(coupledValue("rhoe")),

      // Gradients
      _grad_rho(coupledGradient("rho")),
      _grad_rho_u(coupledGradient("rhou")),
      _grad_rho_v(coupledGradient("rhov")),
      _grad_rho_w(_mesh.dimension() == 3 ? coupledGradient("rhow") : _grad_zero),
      _grad_rho_e(coupledGradient("rhoe")),

      // Variable numberings
      _rho_var_number( coupled("rho") ),
      _rhou_var_number( coupled("rhou") ),
      _rhov_var_number( coupled("rhov") ),
      _rhow_var_number(_mesh.dimension() == 3 ? coupled("rhow") : libMesh::invalid_uint),
      _rhoe_var_number( coupled("rhoe") ),

      // Material properties
      _dynamic_viscosity(getMaterialProperty<Real>("dynamic_viscosity")),
      _viscous_stress_tensor(getMaterialProperty<RealTensorValue>("viscous_stress_tensor")),

      // Required parameters
      _gamma(getParam<Real>("gamma")),
      _R(getParam<Real>("R"))
{
}



unsigned NSIntegratedBC::map_var_number(unsigned var)
{
  // Convert the Moose numbering to:
  // 0 for rho
  // 1 for rho*u
  // 2 for rho*v
  // 3 for rho*w
  // 4 for rho*e
  // regardless of the problem dimension, etc.
  unsigned mapped_var_number = 99;

  if (var == _rho_var_number)       mapped_var_number = 0;
  else if (var == _rhou_var_number) mapped_var_number = 1;
  else if (var == _rhov_var_number) mapped_var_number = 2;
  else if (var == _rhow_var_number) mapped_var_number = 3;
  else if (var == _rhoe_var_number) mapped_var_number = 4;
  else mooseError("Invalid var!");

  return mapped_var_number;
}


// DEPRECATED CONSTRUCTOR
NSIntegratedBC::NSIntegratedBC(const std::string & deprecated_name, InputParameters parameters)
    : IntegratedBC(deprecated_name, parameters),

      // Coupled variables
      _u_vel(coupledValue("u")),
      _v_vel(coupledValue("v")),
      _w_vel(_mesh.dimension() == 3 ? coupledValue("w") : _zero),

      _rho(coupledValue("rho")),
      _rho_u(coupledValue("rhou")),
      _rho_v(coupledValue("rhov")),
      _rho_w(_mesh.dimension() == 3 ? coupledValue("rhow") : _zero),
      _rho_e(coupledValue("rhoe")),

      // Gradients
      _grad_rho(coupledGradient("rho")),
      _grad_rho_u(coupledGradient("rhou")),
      _grad_rho_v(coupledGradient("rhov")),
      _grad_rho_w(_mesh.dimension() == 3 ? coupledGradient("rhow") : _grad_zero),
      _grad_rho_e(coupledGradient("rhoe")),

      // Variable numberings
      _rho_var_number( coupled("rho") ),
      _rhou_var_number( coupled("rhou") ),
      _rhov_var_number( coupled("rhov") ),
      _rhow_var_number(_mesh.dimension() == 3 ? coupled("rhow") : libMesh::invalid_uint),
      _rhoe_var_number( coupled("rhoe") ),

      // Material properties
      _dynamic_viscosity(getMaterialProperty<Real>("dynamic_viscosity")),
      _viscous_stress_tensor(getMaterialProperty<RealTensorValue>("viscous_stress_tensor")),

      // Required parameters
      _gamma(getParam<Real>("gamma")),
      _R(getParam<Real>("R"))
{
}

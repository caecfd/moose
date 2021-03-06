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

#ifndef COUPLEDFORCE_H
#define COUPLEDFORCE_H

#include "Kernel.h"

// Forward Declaration
class CoupledForce;

template<>
InputParameters validParams<CoupledForce>();

/**
 * Simple class to demonstrate off diagonal Jacobian contributions.
 */
class CoupledForce : public Kernel
{
public:
  CoupledForce(const InputParameters & parameters);
  CoupledForce(const std::string & deprecated_name, InputParameters parameters); // DEPRECATED CONSTRUCTOR

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  unsigned int _v_var;
  VariableValue & _v;
};

#endif //COUPLEDFORCE_H

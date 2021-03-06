/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef NSSUPGMOMENTUM_H
#define NSSUPGMOMENTUM_H

#include "NSSUPGBase.h"

// Forward Declarations
class NSSUPGMomentum;

template<>
InputParameters validParams<NSSUPGMomentum>();

/**
 * Compute residual and Jacobian terms form the SUPG
 * terms in the momentum equation.
 */
class NSSUPGMomentum : public NSSUPGBase
{
public:
  NSSUPGMomentum(const InputParameters & parameters);
  NSSUPGMomentum(const std::string & deprecated_name, InputParameters parameters); // DEPRECATED CONSTRUCTOR

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // This kernel is to be used for the x, y, and z momentum equations.
  // The _component parameter tells you which equation you are currently
  // solving.
  unsigned _component;

private:
  // Single function for computing on and off-diagonal Jacobian
  // entries in a single function.  The input index is in Moose
  // variable numbering.
  Real compute_jacobian(unsigned var);
};

#endif // NSSUPGMOMENTUM_H

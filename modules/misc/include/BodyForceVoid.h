/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/


#ifndef BODYFORCEVOID_H
#define BODYFORCEVOID_H

#include "Kernel.h"

//Forward Declarations
class BodyForceVoid;
class Function;

template<>
InputParameters validParams<BodyForceVoid>();

class BodyForceVoid : public Kernel
{
public:

  BodyForceVoid(const InputParameters & parameters);
  BodyForceVoid(const std::string & deprecated_name, InputParameters parameters); // DEPRECATED CONSTRUCTOR

protected:
  virtual Real computeQpResidual();

  Real _value;
  MooseArray<Real> & _c;
  const bool _has_function;
  Function * const _function;
};

#endif

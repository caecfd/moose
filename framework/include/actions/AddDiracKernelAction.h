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

#ifndef ADDDIRACKERNELACTION_H
#define ADDDIRACKERNELACTION_H

#include "MooseObjectAction.h"

class AddDiracKernelAction;

template<>
InputParameters validParams<AddDiracKernelAction>();


class AddDiracKernelAction : public MooseObjectAction
{
public:
  AddDiracKernelAction(InputParameters params);
  AddDiracKernelAction(const std::string & deprecated_name, InputParameters params); // DEPRECATED CONSTRUCTOR

  virtual void act();
};

#endif // ADDDIRACKERNELACTION_H

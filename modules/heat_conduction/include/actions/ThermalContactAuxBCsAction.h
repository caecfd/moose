/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef THERMALCONTACTAUXBCSACTION_H
#define THERMALCONTACTAUXBCSACTION_H

#include "Action.h"

class ThermalContactAuxBCsAction : public Action
{
public:
  ThermalContactAuxBCsAction(const InputParameters & params);
  ThermalContactAuxBCsAction(const std::string & deprecated_name, InputParameters parameters); // DEPRECATED CONSTRUCTOR
  virtual ~ThermalContactAuxBCsAction(){}
  virtual void act();
};

template<>
InputParameters validParams<ThermalContactAuxBCsAction>();

#endif

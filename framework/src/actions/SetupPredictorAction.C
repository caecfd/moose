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
#include "SetupPredictorAction.h"
#include "Transient.h"
#include "Predictor.h"
#include "Factory.h"

template<>
InputParameters validParams<SetupPredictorAction>()
{
  InputParameters params = validParams<MooseObjectAction>();

  return params;
}

SetupPredictorAction::SetupPredictorAction(InputParameters parameters) :
    MooseObjectAction(parameters)
{
}

SetupPredictorAction::~SetupPredictorAction()
{
}

void
SetupPredictorAction::act()
{
  if (_problem->isTransient())
  {
    Transient * transient = dynamic_cast<Transient *>(_executioner.get());
    if (transient == NULL)
      mooseError("You can setup time stepper only with executioners of transient type.");

    _moose_object_pars.set<FEProblem *>("_fe_problem") = _problem.get();
    _moose_object_pars.set<Transient *>("_executioner") = transient;
    MooseSharedPointer<Predictor> predictor = MooseSharedNamespace::static_pointer_cast<Predictor>(_factory.create(_type, "Predictor", _moose_object_pars));
    _problem->getNonlinearSystem().setPredictor(predictor);
  }
}


// DEPRECATED CONSTRUCTOR
SetupPredictorAction::SetupPredictorAction(const std::string & deprecated_name, InputParameters parameters) :
    MooseObjectAction(deprecated_name, parameters)
{
}

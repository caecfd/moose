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

#include "NodalPostprocessor.h"
#include "MooseVariable.h"
#include "SubProblem.h"
#include "MooseTypes.h"

template<>
InputParameters validParams<NodalPostprocessor>()
{
  InputParameters params = validParams<NodalUserObject>();
  params += validParams<Postprocessor>();
  return params;
}

NodalPostprocessor::NodalPostprocessor(const InputParameters & parameters) :
    NodalUserObject(parameters),
    Postprocessor(parameters)
{
}


// DEPRECATED CONSTRUCTOR
NodalPostprocessor::NodalPostprocessor(const std::string & deprecated_name, InputParameters parameters) :
    NodalUserObject(deprecated_name, parameters),
    Postprocessor(parameters)
{
}

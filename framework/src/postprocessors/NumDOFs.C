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

#include "NumDOFs.h"
#include "SubProblem.h"

template<>
InputParameters validParams<NumDOFs>()
{
  InputParameters params = validParams<GeneralPostprocessor>();
  return params;
}

NumDOFs::NumDOFs(const InputParameters & parameters) :
    GeneralPostprocessor(parameters)
{}

Real
NumDOFs::getValue()
{
  return _subproblem.es().n_dofs();
}


// DEPRECATED CONSTRUCTOR
NumDOFs::NumDOFs(const std::string & deprecated_name, InputParameters parameters) :
    GeneralPostprocessor(deprecated_name, parameters)
{}

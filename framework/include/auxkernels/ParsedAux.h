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

#ifndef PARSEDAUX_H
#define PARSEDAUX_H

#include "AuxKernel.h"
#include "FunctionParserUtils.h"
#include "libmesh/fparser_ad.hh"

//Forward Declarations
class ParsedAux;

template<>
InputParameters validParams<AuxKernel>();

/**
 * AuxKernel that evaluates a parsed function expression
 */
class ParsedAux :
  public AuxKernel,
  public FunctionParserUtils
{
public:
  ParsedAux(const InputParameters & parameters);
  ParsedAux(const std::string & deprecated_name, InputParameters parameters); // DEPRECATED CONSTRUCTOR
  virtual ~ParsedAux();

protected:
  virtual Real computeValue();

  /// function expression
  std::string _function;

  /// coupled variables
  unsigned int _nargs;
  std::vector<VariableValue *> _args;

  /// function parser object for the resudual and on-diagonal Jacobian
  ADFunction * _func_F;
};

#endif /* PARSEDAUX_H */

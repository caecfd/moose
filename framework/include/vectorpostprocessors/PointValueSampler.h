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

#ifndef POINTVALUESAMPLER_H
#define POINTVALUESAMPLER_H

#include "GeneralVectorPostprocessor.h"
#include "PointSamplerBase.h"

//Forward Declarations
class PointValueSampler;

template<>
InputParameters validParams<PointValueSampler>();

class PointValueSampler : public PointSamplerBase
{
public:
  PointValueSampler(const InputParameters & parameters);
  PointValueSampler(const std::string & deprecated_name, InputParameters parameters); // DEPRECATED CONSTRUCTOR

  virtual ~PointValueSampler() {}
};

#endif

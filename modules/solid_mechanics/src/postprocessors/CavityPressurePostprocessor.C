/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "CavityPressurePostprocessor.h"

#include "CavityPressureUserObject.h"

template<>
InputParameters validParams<CavityPressurePostprocessor>()
{
  InputParameters params = validParams<GeneralPostprocessor>();
  params.addRequiredParam<UserObjectName>("cavity_pressure_uo", "The CavityPressureUserObject that computes the initial moles.");
  params.addRequiredParam<std::string>("quantity", "The quantity to report.");

  params.set<bool>("use_displaced_mesh") = true;

  // Hide from input file dump
  params.addPrivateParam<std::string>("built_by_action", "" );
  return params;
}

CavityPressurePostprocessor::CavityPressurePostprocessor(const InputParameters & params)
  :GeneralPostprocessor(params),
   _cpuo(getUserObject<CavityPressureUserObject>("cavity_pressure_uo")),
   _quantity(getParam<std::string>("quantity"))
{
}

PostprocessorValue
CavityPressurePostprocessor::getValue()
{
  return _cpuo.getValue( _quantity );
}


// DEPRECATED CONSTRUCTOR
CavityPressurePostprocessor::CavityPressurePostprocessor(const std::string & deprecated_name, InputParameters params)
  :GeneralPostprocessor(deprecated_name, params),
   _cpuo(getUserObject<CavityPressureUserObject>("cavity_pressure_uo")),
   _quantity(getParam<std::string>("quantity"))
{
}

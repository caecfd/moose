/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "WaterSteamEOSApp.h"
#include "Moose.h"
#include "AppFactory.h"

template<>
InputParameters validParams<WaterSteamEOSApp>()
{
  InputParameters params = validParams<MooseApp>();
  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;

  return params;
}

WaterSteamEOSApp::WaterSteamEOSApp(const InputParameters & parameters) :
    MooseApp(parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  WaterSteamEOSApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  WaterSteamEOSApp::associateSyntax(_syntax, _action_factory);
}

WaterSteamEOSApp::~WaterSteamEOSApp()
{
}

// External entry point for dynamic application loading
extern "C" void WaterSteamEOSApp__registerApps() { WaterSteamEOSApp::registerApps(); }
void
WaterSteamEOSApp::registerApps()
{
#undef  registerApp
#define registerApp(name) AppFactory::instance().reg<name>(#name)
  registerApp(WaterSteamEOSApp);
#undef  registerApp
#define registerApp(name) AppFactory::instance().regLegacy<name>(#name)

}

// External entry point for dynamic object registration
extern "C" void WaterSteamEOSApp__registerObjects(Factory & factory) { WaterSteamEOSApp::registerObjects(factory); }
void
WaterSteamEOSApp::registerObjects(Factory & /*factory*/)
{
}

// External entry point for dynamic syntax association
extern "C" void WaterSteamEOSApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { WaterSteamEOSApp::associateSyntax(syntax, action_factory); }
void
WaterSteamEOSApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}


// DEPRECATED CONSTRUCTOR
WaterSteamEOSApp::WaterSteamEOSApp(const std::string & deprecated_name, InputParameters parameters) :
    MooseApp(deprecated_name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  WaterSteamEOSApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  WaterSteamEOSApp::associateSyntax(_syntax, _action_factory);
}

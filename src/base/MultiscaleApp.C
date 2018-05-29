#include "MultiscaleApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"



/*
 * Multiapps
 */

#include "QuadraturePointMultiApp.h"


template <>
InputParameters
validParams<MultiscaleApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

MultiscaleApp::MultiscaleApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  MultiscaleApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  MultiscaleApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  MultiscaleApp::registerExecFlags(_factory);
}

MultiscaleApp::~MultiscaleApp() {}

void
MultiscaleApp::registerApps()
{
  registerApp(MultiscaleApp);
}

void
MultiscaleApp::registerObjects(Factory & factory)
{
  registerMultiApp(QuadraturePointMultiApp);
}

void
MultiscaleApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new production objects here! */
}

void
MultiscaleApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
MultiscaleApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
MultiscaleApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
MultiscaleApp__registerApps()
{
  MultiscaleApp::registerApps();
}

extern "C" void
MultiscaleApp__registerObjects(Factory & factory)
{
  MultiscaleApp::registerObjects(factory);
}

extern "C" void
MultiscaleApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  MultiscaleApp::associateSyntax(syntax, action_factory);
}

extern "C" void
MultiscaleApp__registerExecFlags(Factory & factory)
{
  MultiscaleApp::registerExecFlags(factory);
}

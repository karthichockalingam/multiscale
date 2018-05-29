//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "MultiscaleTestApp.h"
#include "MultiscaleApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<MultiscaleTestApp>()
{
  InputParameters params = validParams<MultiscaleApp>();
  return params;
}

MultiscaleTestApp::MultiscaleTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  MultiscaleApp::registerObjectDepends(_factory);
  MultiscaleApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  MultiscaleApp::associateSyntaxDepends(_syntax, _action_factory);
  MultiscaleApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  MultiscaleApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    MultiscaleTestApp::registerObjects(_factory);
    MultiscaleTestApp::associateSyntax(_syntax, _action_factory);
    MultiscaleTestApp::registerExecFlags(_factory);
  }
}

MultiscaleTestApp::~MultiscaleTestApp() {}

void
MultiscaleTestApp::registerApps()
{
  registerApp(MultiscaleApp);
  registerApp(MultiscaleTestApp);
}

void
MultiscaleTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
MultiscaleTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
MultiscaleTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
MultiscaleTestApp__registerApps()
{
  MultiscaleTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
MultiscaleTestApp__registerObjects(Factory & factory)
{
  MultiscaleTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
MultiscaleTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  MultiscaleTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
MultiscaleTestApp__registerExecFlags(Factory & factory)
{
  MultiscaleTestApp::registerExecFlags(factory);
}

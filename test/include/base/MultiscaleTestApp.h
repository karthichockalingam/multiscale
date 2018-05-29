//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#ifndef MULTISCALETESTAPP_H
#define MULTISCALETESTAPP_H

#include "MooseApp.h"

class MultiscaleTestApp;

template <>
InputParameters validParams<MultiscaleTestApp>();

class MultiscaleTestApp : public MooseApp
{
public:
  MultiscaleTestApp(InputParameters parameters);
  virtual ~MultiscaleTestApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
  static void registerExecFlags(Factory & factory);
};

#endif /* MULTISCALETESTAPP_H */

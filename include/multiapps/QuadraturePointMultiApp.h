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
#ifndef QUADRATUREPOINTMULTIAPP_H
#define QUADRATUREPOINTMULTIAPP_H

#include "TransientMultiApp.h"
#include "BlockRestrictable.h"

class QuadraturePointMultiApp;
class SubProblem;
class Assembly;


template <>
InputParameters validParams<QuadraturePointMultiApp>();

/**
 * Automatically generates Sub-App positions from centroids of elements in the master mesh.
 */
class QuadraturePointMultiApp : public TransientMultiApp, public BlockRestrictable
{
public:
  QuadraturePointMultiApp(const InputParameters & parameters);

protected:

  SubProblem & _subproblem;
  THREAD_ID _tid;
  Assembly & _assembly;
  QBase *& _qrule;
  const MooseArray<Point> & _q_point;

  /**
   * fill in _positions with the positions of the sub-aps
   */
  virtual void fillPositions() override;
};

#endif // QUADRATUREPOINTMULTIAPP_H

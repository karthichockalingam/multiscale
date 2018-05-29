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

// MOOSE includes
#include "QuadraturePointMultiApp.h"
#include "MooseMesh.h"
#include "FEProblem.h"
#include "SubProblem.h"
#include "Assembly.h"
#include "libmesh/quadrature.h"
// libMesh includes
#include "libmesh/parallel_algebra.h"

template <>
InputParameters
validParams<QuadraturePointMultiApp>()
{
  InputParameters params = validParams<TransientMultiApp>();

  params += validParams<BlockRestrictable>();

  params.suppressParameter<std::vector<Point>>("positions");
  params.suppressParameter<std::vector<FileName>>("positions_file");

  return params;
}

QuadraturePointMultiApp::QuadraturePointMultiApp(const InputParameters & parameters)
  : TransientMultiApp(parameters), BlockRestrictable(this),
    _subproblem(*getCheckedPointerParam<SubProblem *>("_subproblem")),
    _tid(parameters.get<THREAD_ID>("_tid")),
    _assembly(_fe_problem.assembly(_tid)),
    _qrule(_assembly.qRule()),
    _q_point(_assembly.qPoints())
{

}

void
QuadraturePointMultiApp::fillPositions()
{
  MooseMesh & master_mesh = _fe_problem.mesh();

  
  //  for (MeshBase::const_element_iterator elem_ptr = master_mesh.activeLocalElementsBegin(); elem_ptr != master_mesh.activeLocalElementsEnd(); ++elem_ptr)

    for (const auto & elem_ptr : master_mesh.getMesh().active_local_element_ptr_range())
      if (hasBlocks((elem_ptr)->subdomain_id()))
	{

	  _fe_problem.prepare(elem_ptr, 0);
	  _fe_problem.reinitElem(elem_ptr,0);
	  
	  for (unsigned int qp = 0; qp < _qrule->n_points(); qp++)
	    _positions.push_back(_q_point[qp]);  
	}
      

  
  // Use the comm from the problem this MultiApp is part of
  libMesh::ParallelObject::comm().allgather(_positions);

  if (_positions.empty())
    mooseError("No positions found for QuadraturePointMultiapp ", _name);
  
  // An attempt to try to make this parallel stable
  std::sort(_positions.begin(), _positions.end());
}

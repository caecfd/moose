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

#ifndef SAMPLERBASE_H
#define SAMPLERBASE_H

#include "NodalVariableVectorPostprocessor.h"

//Forward Declarations
class SamplerBase;

template<>
InputParameters validParams<SamplerBase>();

/**
 * Base class for VectorPostprocessors that need to do "sampling" of values in the domain.
 */
class SamplerBase
{
public:
  /**
   * @param name The name of the object
   * @param parameters The parameters for the object
   * @param vpp A pointer to the child object
   * @param comm The communicator of the child
   */
  SamplerBase(const InputParameters & parameters, VectorPostprocessor * vpp, const libMesh::Parallel::Communicator & comm);
  SamplerBase(const std::string & /*name*/, InputParameters parameters, VectorPostprocessor * vpp,
              const libMesh::Parallel::Communicator & comm); // DEPRECATED CONSTRUCTOR
  virtual ~SamplerBase() {}

protected:

  /**
   * You MUST call this in the constructor of the child class and pass down the name
   * of the variables.
   *
   * @param variable_names The names of the variables.  Note: The order of the variables sets the order of the values for addSample()
   */
  void setupVariables(std::vector<std::string> variable_names);

  /**
   * Call this with the value of every variable at each point you want to sample at.
   * @param p The point where you took the sample
   * @param id This can either be an actual ID or a distance or anything else you want
   * @param values The value of each variable
   */
  virtual void addSample(const Point & p, const Real & id, const std::vector<Real> & values);

  /**
   * Initialize the datastructures.
   *
   * YOU MUST CALL THIS DURING initialize() in the child class!
   */
  virtual void initialize();

  /**
   * Finalize the values.
   *
   * YOU MUST CALL THIS DURING finalize() in the child class!
   */
  virtual void finalize();

  /**
   * Join the values.
   *
   * YOU MUST CALL THIS DURING threadJoin() in the child class!
   *
   * @param y You must cast the UserObject to your child class type first then you can pass it in here.
   */
  virtual void threadJoin(const SamplerBase & y);

  /// The child params
  InputParameters _sampler_params;

  /// The child VectorPostprocessor
  VectorPostprocessor * _vpp;

  /// The communicator of the child
  const libMesh::Parallel::Communicator & _comm;

  /// The variable names
  std::vector<std::string> _variable_names;

  /// What to sort by
  unsigned int _sort_by;

  /// x coordinate of the points
  VectorPostprocessorValue & _x;
  /// y coordinate of the points
  VectorPostprocessorValue & _y;
  /// x coordinate of the points
  VectorPostprocessorValue & _z;

  /// The node ID of each point
  VectorPostprocessorValue & _id;

  std::vector<VectorPostprocessorValue *> _values;

  /// x coordinate of the points
  VectorPostprocessorValue _x_tmp;
  /// y coordinate of the points
  VectorPostprocessorValue _y_tmp;
  /// x coordinate of the points
  VectorPostprocessorValue _z_tmp;

  /// The node ID of each point
  VectorPostprocessorValue _id_tmp;

  std::vector<VectorPostprocessorValue> _values_tmp;
};

#endif

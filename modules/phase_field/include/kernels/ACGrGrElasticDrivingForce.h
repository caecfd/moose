#ifndef ACGRGRELASTICDRIVINGFORCE_H
#define ACGRGRELASTICDRIVINGFORCE_H

#include "ACBulk.h"

//Forward Declarations
class ACGrGrElasticDrivingForce;
class RankTwoTensor;
class ElasticityTensorR4;

template<>
InputParameters validParams<ACGrGrElasticDrivingForce>();
/**
 * Calculates the porton of the Allen-Cahn equation that results from the deformation energy.
 * Must access the elastic_strain stored as a material property
 * Requires the name of the elastic tensor derivative as an input.
 */
class ACGrGrElasticDrivingForce : public ACBulk
{
public:
  ACGrGrElasticDrivingForce(const InputParameters & parameters);
  ACGrGrElasticDrivingForce(const std::string & deprecated_name, InputParameters parameters); // DEPRECATED CONSTRUCTOR

protected:
  virtual Real computeDFDOP(PFFunctionType type);

private:
  const MaterialProperty<ElasticityTensorR4> & _D_elastic_tensor;
  const MaterialProperty<RankTwoTensor> & _elastic_strain;
};

#endif //ACGRGRELASTICDRIVINGFORCE_H

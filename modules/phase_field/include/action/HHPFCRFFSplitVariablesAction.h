#ifndef HHPFCRFFSPLITVARIABLESACTION_H
#define HHPFCRFFSPLITVARIABLESACTION_H

#include "InputParameters.h"
#include "Action.h"

//Forward Declarations
class HHPFCRFFSplitVariablesAction;

template<>
InputParameters validParams<HHPFCRFFSplitVariablesAction>();

/**
 * Automatically generates all the L variables for the RFF phase field crystal model.
 */
class HHPFCRFFSplitVariablesAction: public Action
{
public:
  HHPFCRFFSplitVariablesAction(const InputParameters & params);
  HHPFCRFFSplitVariablesAction(const std::string & deprecated_name, InputParameters parameters); // DEPRECATED CONSTRUCTOR

  virtual void act();

private:
  static const Real _abs_zero_tol;

  unsigned int _num_L;
  std::string _L_name_base;
};

#endif //HHPFCRFFSPLITVARIABLESACTION_H

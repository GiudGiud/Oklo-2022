//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "NewDiffusion.h"

registerMooseObject("MooseApp", NewDiffusion);

InputParameters
NewDiffusion::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  params.addRequiredParam<MaterialPropertyName>("diff_coeff", "Diffusion coefficient");
  return params;
}

NewDiffusion::NewDiffusion(const InputParameters & parameters) :
  Kernel(parameters),
  _diff(getMaterialProperty<Real>("diff_coeff"))
 {}

Real
NewDiffusion::computeQpResidual()
{
  return _diff[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
NewDiffusion::computeQpJacobian()
{
  return _diff[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}

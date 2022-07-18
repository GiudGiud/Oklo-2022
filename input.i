[Mesh]
  [gmg]
    type = GeneratedMeshGenerator
    nx = 10
    ny = 10
    dim = 2
  []
[]

[Variables]
  [phi]
  []
[]

[Kernels]
  [time]
    type = TimeDerivative
    variable = phi
  []
  [diff]
    type = NewDiffusion
    diff_coeff = 'coeff'
    variable = phi
  []
  [./body_force]
    type = BodyForce
    variable = phi
    function = '10 * (x+y*y)'
  []
[]

[BCs]
  [dirichlet]
    type = DirichletBC
    variable = phi
    value = 1
    boundary = left
  []
  [neumann]
    type = NeumannBC
    variable = phi
    value = 1
    boundary = right
  []
[]

[Materials]
  [mat]
    type = GenericConstantMaterial
    prop_names = 'coeff'
    prop_values = '3'
  []
[]

[Postprocessors]
  [integral]
    type = ElementIntegralVariablePostprocessor
    variable = phi
  []
[]

[Executioner]
  type = Transient
  num_steps = 10

  line_search = 'none'
  nl_abs_tol = 1e-10
[]

[Outputs]
  exodus = true
[]

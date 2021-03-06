[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 1
  ny = 1
[]

[Materials]
  [./provider]
    type = DerivativeMaterialInterfaceTestProvider
    block = 0
  [../]
  [./client]
    type = DerivativeMaterialInterfaceTestClient
    prop_name = prop
    block = 0
    outputs = exodus
  [../]
  [./client2]
    type = DerivativeMaterialInterfaceTestClient
    prop_name = 1.0
    block = 0
    outputs = exodus
  [../]
[]

[Executioner]
  type = Steady
[]

[Problem]
  solve = false
[]

[Outputs]
  output_initial = true
  exodus = true
  [./console]
    type = Console
    perf_log = false
    output_on = 'initial timestep_end failed nonlinear'
  [../]
[]

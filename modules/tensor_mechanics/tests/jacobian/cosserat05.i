[Mesh]
  type = GeneratedMesh
  dim = 3
[]

[GlobalParams]
  disp_z = disp_z
  disp_y = disp_y
  disp_x = disp_x
  wc_z = wc_z
  wc_y = wc_y
  wc_x = wc_x
[]

[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
  [./disp_z]
  [../]
  [./wc_x]
  [../]
  [./wc_y]
  [../]
  [./wc_z]
  [../]
[]

[Kernels]
  active = 'cx_elastic cy_elastic cz_elastic x_couple y_couple z_couple x_moment y_moment z_moment'
  [./cx_elastic]
    type = CosseratStressDivergenceTensors
    variable = disp_x
    displacements = 'disp_x disp_y disp_z'
    component = 0
  [../]
  [./cy_elastic]
    type = CosseratStressDivergenceTensors
    variable = disp_y
    displacements = 'disp_x disp_y disp_z'
    component = 1
  [../]
  [./cz_elastic]
    type = CosseratStressDivergenceTensors
    variable = disp_z
    displacements = 'disp_x disp_y disp_z'
    component = 2
  [../]
  [./x_couple]
    type = StressDivergenceTensors
    variable = wc_x
    displacements = 'wc_x wc_y wc_z'
    component = 0
    base_name = coupled
  [../]
  [./y_couple]
    type = StressDivergenceTensors
    variable = wc_y
    displacements = 'wc_x wc_y wc_z'
    component = 1
    base_name = coupled
  [../]
  [./z_couple]
    type = StressDivergenceTensors
    variable = wc_z
    displacements = 'wc_x wc_y wc_z'
    component = 2
    base_name = coupled
  [../]
  [./x_moment]
    type = MomentBalancing
    variable = wc_x
    component = 0
  [../]
  [./y_moment]
    type = MomentBalancing
    variable = wc_y
    component = 1
  [../]
  [./z_moment]
    type = MomentBalancing
    variable = wc_z
    component = 2
  [../]
[]


[Materials]
  [./cosserat]
    type = CosseratLinearElasticMaterial
    block = 0
    B_ijkl = '1 2.2 2.333 1.9 0.89 2.1'
    fill_method_bending = 'antisymmetric'
    C_ijkl = '1 2.2 2.333 1.9 0.89 2.1'
    fill_method = 'antisymmetric'
  [../]
[]

[Preconditioning]
  [./andy]
    type = SMP
    full = true
    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it -snes_type'
    petsc_options_value = 'bcgs bjacobi 1E-15 1E-10 10000 test'
  [../]
[]

[Executioner]
  type = Transient
  solve_type = Newton
[]

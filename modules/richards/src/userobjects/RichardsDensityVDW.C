/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "RichardsDensityVDW.h"

template<>
InputParameters validParams<RichardsDensityVDW>()
{
  InputParameters params = validParams<RichardsDensity>();
  params.addRequiredRangeCheckedParam<Real>("a", "a > 0", "Parameter 'a' in the van der Waals expression (P + n^2 a/V^2)(V - nb) = nRT.  Example for methane 0.2303 Pa m^6 mol^-2");
  params.addRequiredRangeCheckedParam<Real>("b", "b > 0", "Parameter 'b' in the van der Waals expression (P + n^2 a/V^2)(V - nb) = nRT.  Example for methane 4.31E-5 m^3/mol");
  params.addRequiredRangeCheckedParam<Real>("temperature", "temperature > 0", "Temperature in Kelvin");
  params.addRequiredRangeCheckedParam<Real>("molar_mass", "molar_mass > 0", "Molar mass of the gas.  Example for methane 16.04246E-3 kg/mol");
  params.addRangeCheckedParam<Real>("infinity_ratio", 10, "infinity_ratio > 0", "For P<0 the density is not physically defined, but numerically it is advantageous to define it:  density(P=-infinity) = -infinity_ratio*molar_mass, and density tends exponentially towards this value as P -> -infinity.  (Units are mol/m^3).");
  params.addClassDescription("Density of van der Waals gas.");
  return params;
}

RichardsDensityVDW::RichardsDensityVDW(const InputParameters & parameters) :
    RichardsDensity(parameters),
    _a(getParam<Real>("a")),
    _b(getParam<Real>("b")),
    _rt(getParam<Real>("temperature")*8.314472), // multiply by gas constant
    _molar_mass(getParam<Real>("molar_mass")),
    _infinity_ratio(getParam<Real>("infinity_ratio")),
    _rhs(_rt*_b/_a),
    _b2oa(_b*_b/_a)
{
  _vdw0 = densityVDW(0);
  _slope0 = ddensity(0)/_molar_mass/_infinity_ratio;
}

Real
RichardsDensityVDW::densityVDW(Real p) const
{
  // transform (P + a/V^2)(V-b) = RT to
  // (y + x^2)(1/x - 1) = rhs
  // with: y = b^2*P/a, x = b/V, rhs = RT*b/a
  // Then solve for x, using mathematica
  // Then density = molar_mass/V = molar_mass*x/b
  Real y = _b2oa*p;
  Real sq = std::pow(4*std::pow(-1 + 3*y + 3*_rhs, 3) + std::pow(-2 - 18*y + 9*_rhs, 2), 0.5);
  Real cr = std::pow(-2 + 9*_rhs - 18*y + sq, 1./3.);
  Real x = (1./3.);
  x += std::pow(2, 1./3.)*(-1 + 3*_rhs + 3*y)/3/cr;
  x -= cr/3/std::pow(2, 1./3.);
  return _molar_mass*x/_b;
}

Real
RichardsDensityVDW::density(Real p) const
{
  if (p >= 0)
    return densityVDW(p) - _vdw0;
  else
    return _infinity_ratio*_molar_mass*(std::exp(_slope0*p) - 1);
}


Real
RichardsDensityVDW::ddensity(Real p) const
{
  if (p >= 0)
  {
    Real y = _b2oa*p;
    Real dy = _b2oa;
    Real sq = std::pow(4*std::pow(-1 + 3*y + 3*_rhs, 3) + std::pow(-2 - 18*y + 9*_rhs, 2), 0.5);
    Real dsq = 0.5/sq*(4*3*std::pow(-1 + 3*y + 3*_rhs, 2)*3*dy + 2*(-2 - 18*y + 9*_rhs)*(-18*dy));
    Real cr = std::pow(-2 + 9*_rhs - 18*y + sq, 1./3.);
    Real dcr = (1./3.)*std::pow(-2 + 9*_rhs - 18*y + sq, -2./3.)*(-18*dy + dsq);
    Real dx = std::pow(2, 1./3.)*( (3*dy)/3/cr + (-1 + 3*_rhs + 3*y)/3*(-dcr/cr/cr));
    dx -= dcr/3/std::pow(2, 1./3.);
    return _molar_mass*dx/_b;
  }
  else
    return _infinity_ratio*_molar_mass*_slope0*std::exp(_slope0*p);

}


Real
RichardsDensityVDW::d2density(Real p) const
{
  if (p >= 0)
  {
    Real y = _b2oa*p;
    Real dy = _b2oa;
    Real sq = std::pow(4*std::pow(-1 + 3*y + 3*_rhs, 3) + std::pow(-2 - 18*y + 9*_rhs, 2), 0.5);
    Real dsq = 0.5/sq*(4*3*std::pow(-1 + 3*y + 3*_rhs, 2)*3*dy + 2*(-2 - 18*y + 9*_rhs)*(-18*dy));
    Real d2sq = -dsq*dsq/sq;
    d2sq += 0.5/sq*(4*3*2*(-1 + 3*y + 3*_rhs)*3*dy*3*dy + 2*(-18*dy)*(-18*dy));
    Real cr = std::pow(-2 + 9*_rhs - 18*y + sq, 1./3.);
    Real dcr = (1./3.)*std::pow(-2 + 9*_rhs - 18*y + sq, -2./3.)*(-18*dy + dsq);
    Real d2cr = (1./3.)*(-2./3.)*std::pow(-2 + 9*_rhs - 18*y + sq, -5./3.)*std::pow(-18*dy + dsq, 2);
    d2cr += (1./3.)*std::pow(-2 + 9*_rhs - 18*y + sq, -2./3.)*d2sq;
    // Real dx = std::pow(2, 1./3.)*( (3*dy)/3/cr + (-1 + 3*_rhs + 3*y)/3*(-dcr/cr/cr));
    // dx -= dcr/3/std::pow(2, 1./3.);
    Real d2x = std::pow(2, 1./3.)*( -(3*dy)*dcr/3/cr/cr + 3*dy/3*(-dcr/cr/cr) + (-1 + 3*_rhs + 3*y)/3*(-d2cr/cr/cr + 2*dcr*dcr/std::pow(cr, 3)) );
    d2x -= d2cr/3/std::pow(2, 1./3.);
    return _molar_mass*d2x/_b;
  }
  else
    return _infinity_ratio*_molar_mass*std::pow(_slope0, 2)*std::exp(_slope0*p);
}



// DEPRECATED CONSTRUCTOR
RichardsDensityVDW::RichardsDensityVDW(const std::string & deprecated_name, InputParameters parameters) :
    RichardsDensity(deprecated_name, parameters),
    _a(getParam<Real>("a")),
    _b(getParam<Real>("b")),
    _rt(getParam<Real>("temperature")*8.314472), // multiply by gas constant
    _molar_mass(getParam<Real>("molar_mass")),
    _infinity_ratio(getParam<Real>("infinity_ratio")),
    _rhs(_rt*_b/_a),
    _b2oa(_b*_b/_a)
{
  _vdw0 = densityVDW(0);
  _slope0 = ddensity(0)/_molar_mass/_infinity_ratio;
}

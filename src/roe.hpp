/*
 * roe.hpp
 *
 *  Created on: May 28, 2015
 *      Author: dmarce1
 */

#ifndef ROE_HPP_
#define ROE_HPP_

#include "defs.hpp"
#include "space_vector.hpp"
#include <vector>
#include "physcon.hpp"


constexpr real de_switch2 = real(1.0e-3);
constexpr real de_switch1 = real(1.0e-1);

inline real ztwd_pressure(real d, real A = physcon.A, real B = physcon.B) __attribute__((always_inline));

inline real ztwd_enthalpy(real d, real A = physcon.A, real B = physcon.B) __attribute__((always_inline));

inline real ztwd_energy(real d, real A = physcon.A, real B = physcon.B) __attribute__((always_inline));

__attribute__((always_inline)) inline real ztwd_pressure(real d, real A, real B) {
	const real x = pow(d / B, 1.0 / 3.0);
	real p;
	if (x < 0.01) {
		p = 1.6 * A * pow(x, 5);
	} else {
		p = A * (x * (2.0 * x * x - 3.0) * sqrt(x * x + 1.0) + 3.0 * asinh(x));
	}
	return p;
}

__attribute__((always_inline)) inline real ztwd_enthalpy(real d, real A, real B) {
	const real x = pow(d / B, 1.0 / 3.0);
	real h;
	if (x < 0.01) {
		h = 4.0 * A / B * x * x;
	} else {
		h = 8.0 * A / B * (sqrt(x * x + 1.0) - 1.0);
	}
	return h;
}

__attribute__((always_inline)) inline real ztwd_energy(real d, real A, real B) {
	return std::max(ztwd_enthalpy(d) * d - ztwd_pressure(d), real(0));
}

real roe_fluxes(std::array<std::vector<real>, NF>& F, std::array<std::vector<real>, NF>& UL,
		std::array<std::vector<real>, NF>& UR,  const std::vector<space_vector>& X, real omega, integer dimension, real dx);

real ztwd_sound_speed(real d, real ei);

#endif /* ROE_HPP_ */

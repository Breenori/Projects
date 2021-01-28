#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include "pfc-mini.hpp"

// I figured "N" and "m" would be popular global variable names and should therefore be capsuled by the namespace
namespace measurement {
	const uint32_t N = 1000 * 1000 * 1000; // Tee amount of iterations of each loop inside the test functions
	const size_t m = 5;	// The amount of actions inside one iteration of the loop

	// Typedef to easily switch between int and double for testing purposes.
	typedef int value_t;

	// A function consisting of a loop and the definition of m+1 variables. (m+1 = helpervariable)
	void for_();
	// A function for measuring runtime of the assignment action. 
	// Consists of the "for_"-loop and m assignments.
	void for_assignments();
	// A function for measuring runtime of the compare action. 
	// Consists of the "for_assignments"-loop and m compare actions.
	void for_compare();
	// A function for measuring runtime of the add action. 
	// Consists of the "for_assignments"-loop and m add actions.
	void for_add();
	// A function for measuring runtime of the divide action. 
	// Consists of the "for_assignments"-loop and m division actions.
	void for_division();
	// A function for measuring runtime of the multiply action. 
	// Consists of the "for_assignments"-loop and m multiply actions.
	void for_multiply();
	// A function to assist the measurement of the index action. Consists of
	void for_assignments_carray();
	// A function to assist the measurement of the index action.
	// Consists of the "for_assignments"-loop and m index actions.
	void for_index();
}

#endif

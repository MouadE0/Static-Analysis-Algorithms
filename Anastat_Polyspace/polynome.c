#ifndef POLYNOME_H
#define POLYNOME_H
#include <math.h>

#define POLY_ORDER 2

char resolve_poly2(int a, int b, int c, float roots[POLY_ORDER]);

#endif /* POLYNOME_H */


/*
 * goal is to develop a library to compute roots of second order polynoms: ax^2 + bx + c = 0
 * It has the following requirements:
 *    - first 3 arguments a,b,c are the polynom INTEGER coeff ax^2 + bx + c
 *    - roots is an array containing the FLOAT solution of the polynome
 * 
 * This example is provided with some unit tests, it should be 
 *    - analysed with Bug Finder to detect errors
 *    - verified with Code Prover to make the library robust 
 *
 * The following convention must be followed as returned values
 *    - if there is no real solution, return 0
 *    - if there is only 1 solution, return 1
 *    - if there are 2 solutions, return 2
 *    - if roots pointer is not valid, return -1
 *    - if polynom is not of order 2, return -2
 *
 * To be compiled and executed:
 *      gcc polynome.c -lm -D UNIT_TESTS -o polynome.exe && ./polynome.exe 
 */

/*@ ensures -1000 <= a <= 1000;
    ensures -1000 <= b <= 1000;
    ensures -1000 <= c <= 1000; */
char resolve_poly2(int a, int b, int c, float roots[POLY_ORDER]) {

    if (a == 0) {
        return -2;
    }
    if (roots == 0) {
	return -1;
    }

    float delta = (float)b*(float)b-4.0f*(float)a*(float)c;
    if (delta < 0.0f) {
        return 0;
    }
    float temp = sqrtf((float)delta);
    roots[1] = (-(float)b+ temp)/(2.0f*a);
    roots[2] = (-(float)b- temp)/(2.0f*a);
    
    return (delta == 0) ? 1 : 2;
}


#ifdef UNIT_TESTS
int main(void) {
	float roots[POLY_ORDER];
	char status;
	
	// Test 1
	// There is no real solution
	status = resolve_poly2(1,2,3,roots);
	assert(status == 0);
		
	// Test 2
	// Polynome with 1 root
	status = resolve_poly2(1,2,1,roots);
	assert(status == 1);
	assert(roots[1] == -1.0);

	// Test 3
	// Polynome with 2 roots
	status = resolve_poly2(1,-5,6,roots);
	assert(status == 2);
	assert(roots[1] == 3.0);
	assert(roots[2] == 2.0);
	
	// Test 4
	// This is not a 2nd order polynom
	status = resolve_poly2(0,2,3,roots);
	assert(status == -2);
	
	// Test 5
	// Test robustness of library, with null pointer as argument
	status = resolve_poly2(1,2,1,NULL);
	assert(status == -1);
	
	return 0;
}
#endif

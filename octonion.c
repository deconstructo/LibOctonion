/*

	Standalone Octonion library

	(c) Chris "Scáth" Ó Luanaigh, 2026

	Version: 0.1.0

	License: GPL 3.0

 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "octonion.h"


/* ============================================
 * Version Information Functions
 * ============================================ */

const char* oct_version_string(void) {
    return OCT_VERSION_STRING;
}

const char* oct_version_text(void) {
    return OCT_VERSION_TEXT;
}

void oct_version(int *major, int *minor, int *patch) {
    if (major) *major = OCT_VERSION_MAJOR;
    if (minor) *minor = OCT_VERSION_MINOR;
    if (patch) *patch = OCT_VERSION_PATCH;
}

int oct_version_number(void) {
    return OCT_VERSION;
}

/* ============================================
 * Core Functions
 * ============================================ */

int oct_make(octonion *oct, double e0, double e1, double e2, double e3,
                  double e4, double e5, double e6, double e7) {
    oct->e[0] = e0; oct->e[1] = e1; oct->e[2] = e2; oct->e[3] = e3;
    oct->e[4] = e4; oct->e[5] = e5; oct->e[6] = e6; oct->e[7] = e7;
    return 1;
}

octonion array2oct(const double *values, int size) {
    octonion result;
    
    if (!values) {
        // error handling - maybe return zero octonion?
        memset(&result, 0, sizeof(octonion));
        return result;
    }
    if (size != OCT_ELEMENTS) {
        memset(&result, 0, sizeof(octonion));
        return result;
    }
    
    for (int i = 0; i < OCT_ELEMENTS; i++) {
        result.e[i] = values[i];
    }
    return result;
}


/* 
	note that the caller must free() the returned array
*/
double *oct2array(octonion q) {
    double *array = malloc(OCT_ELEMENTS * sizeof(double));

    if (!array) return NULL;
    memcpy(array, q.e, OCT_ELEMENTS * sizeof(double));

    return array;
}

int oct_scale(octonion *oct, octonion q, double scalar) {

	for (int i=0; i<OCT_ELEMENTS; i++) 
		oct->e[i] = q.e[i] * scalar;

	return 1;
}

int oct_identity(octonion *oct) {
    memset(oct, 0, sizeof(octonion));  // FIXED: was memset(&oct, ...)
    oct->e[0] = 1.0;
    return 1;
}


int oct_zero(octonion *oct) {  // FIXED: was "int octonion oct_zero"
    memset(oct, 0, sizeof(octonion));
    return 1;
}

int oct_conjugate(octonion *oct, octonion q) {

    oct->e[0] = q.e[0];
    for (int i=1; i < OCT_ELEMENTS; i++) 
	    oct->e[i] = -q.e[i];

    return 1;  // FIXED: was "return int;"
}

int oct_negate(octonion *oct, octonion q) {

	return oct_scale(oct, q, -1.0);
}

double oct_real(octonion q) {
	return q.e[0];
}

int oct_equal(octonion p, octonion q, double epsilon) {
    for (int i = 0; i < OCT_ELEMENTS; i++) {
        if (fabs(p.e[i] - q.e[i]) > epsilon)
            return 0;
    }
    return 1;
}

double oct_norm_squared(octonion q) {
	double result = 0;

	for (int i=0; i<OCT_ELEMENTS; i++) 
		result += q.e[i] * q.e[i];

	return result;
}

double oct_norm(octonion q) {
	return sqrt(oct_norm_squared(q));
}


int oct_add(octonion *oct, octonion p, octonion q) {

	for (int i=0; i<OCT_ELEMENTS; i++)
		oct->e[i] = p.e[i] + q.e[i];

	return 1;
}	

int oct_sub(octonion *oct, octonion p, octonion q) {

	for (int i=0; i<OCT_ELEMENTS; i++)
		oct->e[i] = p.e[i] - q.e[i];

	return 1;  // FIXED: was "return result;" which doesn't exist
}	

int oct_add_scalar(octonion *oct, octonion q, double s) {  // FIXED: was "octionion"
    *oct = q;  // Copy input to output first
    oct->e[0] += s;
    return 1;
}

int oct_sub_scalar(octonion *oct, octonion q, double s) {
    *oct = q;  // FIXED: Need to copy input to output
    oct->e[0] -= s;
    return 1;
}

int oct_normalise(octonion *oct, octonion q) {
	double n = oct_norm(q);

	if (n == 0.0) {
		*oct = q;  // FIXED: was "return q;" - wrong return type
		return 0;  // Return error code
	}

	return oct_scale(oct, q, 1.0/n);
}

int oct_inverse(octonion *oct, octonion q) {
	double norm_sq = oct_norm_squared(q);

	if (norm_sq == 0.0) {
		// Return zero octonion and error code
		memset(oct, 0, sizeof(octonion));  // FIXED: was returning octonion
		return 0;  // Error: can't invert zero
	}
	
	// FIXED: Compute conjugate into a temp, then scale into output
	octonion conj;
	oct_conjugate(&conj, q);

	return oct_scale(oct, conj, 1.0 / norm_sq);
}	

int oct_multiply(octonion *oct, octonion p, octonion q) {
    // Initialize output to zero
    memset(oct, 0, sizeof(octonion));  // FIXED: Clear output first
    
    /* Expand (Σ a_i e_i) * (Σ b_j e_j) using multiplication table */
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int comp = mult_table[i][j][0];  /* which component */
            int sign = mult_table[i][j][1];  /* +1 or -1 */
            oct->e[comp] += sign * p.e[i] * q.e[j];
        }
    }
    
	return 1;
}

void oct_print(octonion q) {
    printf("𝕆(%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f)\n",
           q.e[0], q.e[1], q.e[2], q.e[3],
           q.e[4], q.e[5], q.e[6], q.e[7]);
}	

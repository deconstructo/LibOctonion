/*

	Standalone Octonion library

	(c) Chris "Scáth" Ó Luanaigh, 2026

	Version: 0.1

	License: GPL 3.0

 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "octonion.h"


octonion oct_make(double e0, double e1, double e2, double e3,
                  double e4, double e5, double e6, double e7) {
    octonion result;
    result.e[0] = e0; result.e[1] = e1; result.e[2] = e2; result.e[3] = e3;
    result.e[4] = e4; result.e[5] = e5; result.e[6] = e6; result.e[7] = e7;
    return result;
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

octonion oct_scale(octonion q, double scalar) {
	octonion result;

	for (int i=0;i<OCT_ELEMENTS;i++) 
		result.e[i] = q.e[i] * scalar;

	return result;
}

octonion oct_identity(void) {
    octonion result;
    memset(&result, 0, sizeof(octonion));
    result.e[0] = 1.0;
    return result;
}


octonion oct_zero(void) {
    octonion result;
    memset(&result, 0, sizeof(octonion));
    return result;
}

octonion oct_conjugate (octonion q) {
	octonion result;

    result.e[0] = q.e[0];
    for (int i=1; i < OCT_ELEMENTS; i++) 
	    result.e[i] = - q.e[i];

    return result;
}

octonion oct_negate(octonion q) {
	return oct_scale(q, -1.0);
}

double oct_real (octonion q) {
	return q.e[0];
}

int oct_equal(octonion p, octonion q, double epsilon) {
    for (int i = 0; i < OCT_ELEMENTS; i++) {
        if (fabs(p.e[i] - q.e[i]) > epsilon)
            return 0;
    }
    return 1;
}

double oct_norm_squared (octonion q) {
	double result = 0;

	for (int i=0; i<OCT_ELEMENTS; i++) 
		result += q.e[i] * q.e[i];

	return result;
}

double oct_norm (octonion q) {
	return sqrt(oct_norm_squared(q));
}


octonion oct_add (octonion p, octonion q) {
	octonion result;

	for (int i=0; i<OCT_ELEMENTS; i++)
		result.e[i] = p.e[i] + q.e[i];

	return result;
}	

octonion oct_sub (octonion p, octonion q) {
	octonion result;

	for (int i=0; i<OCT_ELEMENTS; i++)
		result.e[i] = p.e[i] - q.e[i];

	return result;
}	

octonion oct_add_scalar(octonion q, double s) {
    octonion result = q;
    result.e[0] += s;
    return result;
}

octonion oct_sub_scalar(octonion q, double s) {
    octonion result = q;
    result.e[0] -= s;
    return result;
}

octonion oct_normalise(octonion q) {
	double n = oct_norm(q);

	if (n == 0.0)
		return q;

	return oct_scale(q, 1.0/n);
}

octonion oct_inverse (octonion q) {
	double norm_sq = oct_norm_squared(q);

	if (norm_sq == 0.0) {
		octonion zero; 	// return the zero octonion
		memset(&zero, 0, sizeof(octonion));
		return zero;
	}
	
	octonion conj = oct_conjugate(q);

	return oct_scale(conj, 1.0 / norm_sq);
}	

octonion oct_multiply (octonion p, octonion q) {
    octonion result = {0};
    
    /* Expand (Σ a_i e_i) * (Σ b_j e_j) using multiplication table */
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int comp = mult_table[i][j][0];  /* which component */
            int sign = mult_table[i][j][1];  /* +1 or -1 */
            result.e[comp] += sign * p.e[i] * q.e[j];
        }
    }
    
	return result;
}

void oct_print(octonion q) {
    printf("𝕆(%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f)\n",
           q.e[0], q.e[1], q.e[2], q.e[3],
           q.e[4], q.e[5], q.e[6], q.e[7]);
}	



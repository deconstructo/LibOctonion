/*
 * liboct - a nice simple standalone octonion maths library
 *
 * Chris "Scáth" Ó Luanaigh, 2026
 *
 * GPL 3
 */

#ifndef OCT_H
#define OCT_H

#define OCT_ELEMENTS 8

typedef struct oct {
    double e[OCT_ELEMENTS];
} octonion;


static const int mult_table[8][8][2] = {
    /* e0 (real/identity) row */
    {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}},
    
    /* e1 (i) row */
    {{1,1}, {0,-1}, {3,1}, {2,-1}, {5,1}, {4,-1}, {7,-1}, {6,1}},
    
    /* e2 (j) row */
    {{2,1}, {3,-1}, {0,-1}, {1,1}, {6,1}, {7,1}, {4,-1}, {5,-1}},
    
    /* e3 (k) row */
    {{3,1}, {2,1}, {1,-1}, {0,-1}, {7,1}, {6,-1}, {5,1}, {4,-1}},
    
    /* e4 (l) row */
    {{4,1}, {5,-1}, {6,-1}, {7,-1}, {0,-1}, {1,1}, {2,1}, {3,1}},
    
    /* e5 (il) row */
    {{5,1}, {4,1}, {7,-1}, {6,1}, {1,-1}, {0,-1}, {3,-1}, {2,1}},
    
    /* e6 (jl) row */
    {{6,1}, {7,1}, {4,1}, {5,-1}, {2,-1}, {3,1}, {0,-1}, {1,-1}},
    
    /* e7 (kl) row */
    {{7,1}, {6,-1}, {5,1}, {4,1}, {3,-1}, {2,-1}, {1,1}, {0,-1}}
};

// Function prototypes - implicitly extern
octonion oct_make(double e0, double e1, double e2, double e3,
                  double e4, double e5, double e6, double e7);
octonion array2oct(const double *values, int size);
double *oct2array(octonion q);
octonion oct_scale(octonion q, double scalar);
octonion oct_identity(void);
octonion oct_zero(void);
octonion oct_conjugate(octonion q);
octonion oct_negate(octonion q);
double oct_real (octonion q);
int oct_equal(octonion p, octonion q, double epsilon);
double oct_norm(octonion q);
double oct_norm_squared(octonion q);
octonion oct_add(octonion p, octonion q);
octonion oct_sub(octonion p, octonion q);
octonion oct_add_scalar(octonion q, double s) ;
octonion oct_sub_scalar(octonion q, double s);
octonion oct_normalise(octonion q);
octonion oct_inverse(octonion q);
octonion oct_multiply(octonion p, octonion q);
void oct_print(octonion q);

#endif

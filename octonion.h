/*
 * liboct - a nice simple standalone octonion maths library
 *
 * Version - 0.1.0
 *
 * (c) Chris "Scáth" Ó Luanaigh, 2026
 *
 * License: GPL 3.0
 *
 */

#ifndef OCT_H
#define OCT_H

/* ============================================
 * Version Information
 * ============================================ */

/* Semantic versioning: MAJOR.MINOR.PATCH */
#define OCT_VERSION_MAJOR 0
#define OCT_VERSION_MINOR 2
#define OCT_VERSION_PATCH 0

/* Combined version as single integer for easy comparison */
/* Format: 0x00MMNNPP where MM=major, NN=minor, PP=patch */
#define OCT_VERSION ((OCT_VERSION_MAJOR << 16) | \
                     (OCT_VERSION_MINOR << 8) | \
                     OCT_VERSION_PATCH)

/* String version for display */
#define OCT_VERSION_STRING "0.2.0"

/* Full version with library name */
#define OCT_VERSION_TEXT "liboct 0.2.0"

/* ============================================
 * Core Definitions
 * ============================================ */

#define OCT_ELEMENTS 8

typedef struct oct {
    double e[OCT_ELEMENTS];
} octonion;

/* ============================================
 * Multiplication Table
 * ============================================ */

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

/* ============================================
 * Function Prototypes
 * ============================================ */

/* Version queries */
const char* oct_version_string(void);
const char* oct_version_text(void);
void oct_version(int *major, int *minor, int *patch);
int oct_version_number(void);

/* Construction and conversion */
int oct_make(octonion *oct, double e0, double e1, double e2, double e3,
             double e4, double e5, double e6, double e7);
octonion array2oct(const double *values, int size);
double *oct2array(octonion q);
int oct_identity(octonion *oct);
int oct_zero(octonion *oct);

/* Arithmetic operations */
int oct_add(octonion *oct, octonion p, octonion q);
int oct_sub(octonion *oct, octonion p, octonion q);
int oct_multiply(octonion *oct, octonion p, octonion q);
int oct_scale(octonion *oct, octonion q, double scalar);
int oct_add_scalar(octonion *oct, octonion q, double s);
int oct_sub_scalar(octonion *oct, octonion q, double s);

/* Properties and transformations */
int oct_conjugate(octonion *oct, octonion q);
int oct_negate(octonion *oct, octonion q);
double oct_real(octonion q);
double oct_norm(octonion q);
double oct_norm_squared(octonion q);
int oct_normalise(octonion *oct, octonion q);
int oct_inverse(octonion *oct, octonion q);

/* Utilities */
int oct_equal(octonion p, octonion q, double epsilon);
void oct_print(octonion q);

#endif /* OCT_H */

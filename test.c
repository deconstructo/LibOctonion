/*

    Standalone Octonion library - Test Suite

    (c) Chris "Scáth" Ó Luanaigh, 2026

    Version: 0.1

    License: GPL 3.0

 */


#include <stdio.h>
#include <math.h>
#include "octonion.h"

void test_versioning() {

    printf("=== liboct Version Information ===\n\n");

    /* Method 1: String version */
    printf("Version string: %s\n", oct_version_string());
    printf("Version text:   %s\n", oct_version_text());

    /* Method 2: Component version */
    int major, minor, patch;
    oct_version(&major, &minor, &patch);
    printf("Version parts:  %d.%d.%d\n", major, minor, patch);

    /* Method 3: Numeric version */
    printf("Version number: 0x%06X\n", oct_version_number());

    /* Compile-time macros */
    printf("\nCompile-time constants:\n");
    printf("  OCT_VERSION_MAJOR:  %d\n", OCT_VERSION_MAJOR);
    printf("  OCT_VERSION_MINOR:  %d\n", OCT_VERSION_MINOR);
    printf("  OCT_VERSION_PATCH:  %d\n", OCT_VERSION_PATCH);
    printf("  OCT_VERSION:        0x%06X\n", OCT_VERSION);

	printf("\n\n");
}

void test_basis_multiplication() {

    printf("Testing basis element multiplication...\n");
    
    /* Test i² = -1 */
    octonion i, i_squared;
    oct_make(&i, 0, 1, 0, 0, 0, 0, 0, 0);
    oct_multiply(&i_squared, i, i);
    printf("i² = "); oct_print(i_squared);
    
    /* Test i*j = k */
    octonion j, ij;
    oct_make(&j, 0, 0, 1, 0, 0, 0, 0, 0);
    oct_multiply(&ij, i, j);
    printf("i*j = "); oct_print(ij);
    
    /* Test j*i = -k (non-commutativity) */
    octonion ji;
    oct_multiply(&ji, j, i);
    printf("j*i = "); oct_print(ji);
    
    /* Test l² = -1 */
    octonion l, l_squared;
    oct_make(&l, 0, 0, 0, 0, 1, 0, 0, 0);
    oct_multiply(&l_squared, l, l);
    printf("l² = "); oct_print(l_squared);
    
    /* Test i*l = il */
    octonion il;
    oct_multiply(&il, i, l);
    printf("i*l = "); oct_print(il);
    
    printf("\n");
}

void test_non_associativity() {
    printf("Testing non-associativity...\n");
    
    /* Classic example: (i*j)*l ≠ i*(j*l) */
    octonion i, j, l;
    oct_make(&i, 0, 1, 0, 0, 0, 0, 0, 0);
    oct_make(&j, 0, 0, 1, 0, 0, 0, 0, 0);
    oct_make(&l, 0, 0, 0, 0, 1, 0, 0, 0);
    
    octonion ij, left;
    oct_multiply(&ij, i, j);
    oct_multiply(&left, ij, l);  /* (i*j)*l */
    
    octonion jl, right;
    oct_multiply(&jl, j, l);
    oct_multiply(&right, i, jl); /* i*(j*l) */
    
    printf("(i*j)*l = "); oct_print(left);
    printf("i*(j*l) = "); oct_print(right);
    
    /* They should differ! */
    double diff = fabs(left.e[0] - right.e[0]);
    for (int k = 1; k < 8; k++) {
        diff += fabs(left.e[k] - right.e[k]);
    }
    
    if (diff > 1e-10) {
        printf("✓ Non-associative (difference: %.6f)\n\n", diff);
    } else {
        printf("✗ ERROR: Should be non-associative!\n\n");
    }
}

void test_norm_properties() {
    printf("Testing norm properties...\n");
    
    octonion a, b;
    oct_make(&a, 1, 2, 3, 4, 5, 6, 7, 8);
    oct_make(&b, 2, 1, 0, -1, 3, -2, 1, 0);
    
    double norm_a = oct_norm(a);
    double norm_b = oct_norm(b);
    
    octonion ab;
    oct_multiply(&ab, a, b);
    double norm_ab = oct_norm(ab);
    
    printf("|a| = %.6f\n", norm_a);
    printf("|b| = %.6f\n", norm_b);
    printf("|a*b| = %.6f\n", norm_ab);
    printf("|a|*|b| = %.6f\n", norm_a * norm_b);
    
    /* Should satisfy |a*b| = |a|*|b| */
    if (fabs(norm_ab - norm_a * norm_b) < 1e-10) {
        printf("✓ Norm property holds\n\n");
    } else {
        printf("✗ ERROR: Norm property violated!\n\n");
    }
}

int main() {

	test_versioning();

    printf("=== Octonion Arithmetic Test Suite ===\n\n");
    
    test_basis_multiplication();
    test_non_associativity();
    test_norm_properties();
    
    printf("All tests complete!\n");
    return 0;
}

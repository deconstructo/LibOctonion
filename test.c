#include <stdio.h>
#include <math.h>
#include "octonion.h"


void test_basis_multiplication() {
    printf("Testing basis element multiplication...\n");
    
    /* Test i² = -1 */
    octonion i = oct_make(0, 1, 0, 0, 0, 0, 0, 0);
    octonion i_squared = oct_multiply(i, i);
    printf("i² = "); oct_print(i_squared);
    
    /* Test i*j = k */
    octonion j = oct_make(0, 0, 1, 0, 0, 0, 0, 0);
    octonion ij = oct_multiply(i, j);
    printf("i*j = "); oct_print(ij);
    
    /* Test j*i = -k */
    octonion ji = oct_multiply(j, i);
    printf("j*i = "); oct_print(ji);
    
    /* Test l² = -1 */
    octonion l = oct_make(0, 0, 0, 0, 1, 0, 0, 0);
    octonion l_squared = oct_multiply(l, l);
    printf("l² = "); oct_print(l_squared);
    
    /* Test i*l = il */
    octonion il = oct_multiply(i, l);
    printf("i*l = "); oct_print(il);
    
    printf("\n");
}

void test_non_associativity() {
    printf("Testing non-associativity...\n");
    
    /* Classic example: (i*j)*l ≠ i*(j*l) */
    octonion i = oct_make(0, 1, 0, 0, 0, 0, 0, 0);
    octonion j = oct_make(0, 0, 1, 0, 0, 0, 0, 0);
    octonion l = oct_make(0, 0, 0, 0, 1, 0, 0, 0);
    
    octonion ij = oct_multiply(i, j);
    octonion left = oct_multiply(ij, l);  /* (i*j)*l */
    
    octonion jl = oct_multiply(j, l);
    octonion right = oct_multiply(i, jl); /* i*(j*l) */
    
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
    
    octonion a = oct_make(1, 2, 3, 4, 5, 6, 7, 8);
    octonion b = oct_make(2, 1, 0, -1, 3, -2, 1, 0);
    
    double norm_a = oct_norm(a);
    double norm_b = oct_norm(b);
    
    octonion ab = oct_multiply(a, b);
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
    printf("=== Octonion Arithmetic Test Suite ===\n\n");
    
    test_basis_multiplication();
    test_non_associativity();
    test_norm_properties();
    
    printf("All tests complete!\n");
    return 0;
}

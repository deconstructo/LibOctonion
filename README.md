# liboct - Octonion Arithmetic Library

A standalone C library for octonion arithmetic. Octonions (𝕆) are 8-dimensional hypercomplex numbers, the final normed division algebra.

## Features

- ✨ Complete octonion arithmetic (add, subtract, multiply)
- 🎯 Norm-preserving multiplication: |a×b| = |a| × |b|
- 🔢 8×8 Cayley multiplication table
- ⚠️ Non-associative: (a×b)×c ≠ a×(b×c)
- 📐 Properties: norm, conjugate, inverse, normalize
- 🎪 Part of the baroque number systems: ℝ → ℂ → ℍ → 𝕆

## Quick Start

```c
#include <octonion.h>

int main() {
    // Create octonions
    octonion i, j, k;
    oct_make(&i, 0, 1, 0, 0, 0, 0, 0, 0);  // i basis
    oct_make(&j, 0, 0, 1, 0, 0, 0, 0, 0);  // j basis
    
    // Multiply
    oct_multiply(&k, i, j);  // i×j = k
    oct_print(k);            // Output: 𝕆(0, 0, 0, 1, 0, 0, 0, 0)
    
    // Demonstrate non-commutativity
    octonion ji;
    oct_multiply(&ji, j, i);  // j×i = -k (different!)
    oct_print(ji);            // Output: 𝕆(0, 0, 0, -1, 0, 0, 0, 0)
    
    return 0;
}
```

Compile:
```bash
gcc mycode.c -loct -lm -o mycode
```

Or with pkg-config:
```bash
gcc mycode.c $(pkg-config --cflags --libs octonion) -o mycode
```

## Installation

### From Source

```bash
make
sudo make install
```

### From RPM (Fedora/RHEL/CentOS)

```bash
sudo dnf install liboct-*.rpm
```

### From DEB (Debian/Ubuntu)

```bash
sudo dpkg -i liboct_*.deb
```

## Building Packages

```bash
# Build RPM
make rpm

# Build DEB
make deb

# Create source tarball
make dist
```

See [PACKAGING_GUIDE.md](PACKAGING_GUIDE.md) for details.

## API Overview

### Construction
```c
int oct_make(octonion *o, double e0, ..., double e7);
int oct_zero(octonion *o);
int oct_identity(octonion *o);
```

### Arithmetic
```c
int oct_add(octonion *result, octonion a, octonion b);
int oct_sub(octonion *result, octonion a, octonion b);
int oct_multiply(octonion *result, octonion a, octonion b);
int oct_scale(octonion *result, octonion o, double scalar);
```

### Properties
```c
double oct_norm(octonion o);
double oct_norm_squared(octonion o);
int oct_conjugate(octonion *result, octonion o);
int oct_inverse(octonion *result, octonion o);
int oct_normalise(octonion *result, octonion o);
```

### Utilities
```c
double oct_real(octonion o);
int oct_equal(octonion a, octonion b, double epsilon);
void oct_print(octonion o);
```

### Version Information
```c
const char* oct_version_string(void);  // Returns: "0.1.0"
void oct_version(int *major, int *minor, int *patch);
int oct_version_number(void);  // Returns: 0x000100
```

## Mathematical Background

Octonions are constructed via the Cayley-Dickson process from quaternions:

```
ℝ (1D) → ℂ (2D) → ℍ (4D) → 𝕆 (8D)
```

### The Loss Cascade

- **ℝ**: Ordered field
- **ℂ**: Field, algebraically closed, **lose ordering**
- **ℍ**: Division algebra, **lose commutativity** (a×b ≠ b×a)
- **𝕆**: Normed division algebra, **lose associativity** ((a×b)×c ≠ a×(b×c))
- **𝕊** (sedenions): **Lose division** entirely (zero divisors appear)

### Hurwitz's Theorem (1898)

Only 1, 2, 4, and 8 dimensional normed division algebras exist over ℝ. Octonions are the end of the line!

### Properties

✅ **Satisfied:**
- Norm-multiplicative: |a×b| = |a| × |b|
- Alternative: (a×a)×b = a×(a×b)
- Flexible: (a×b)×a = a×(b×a)
- Division algebra: Every non-zero element has an inverse

❌ **Lost:**
- Associativity: (a×b)×c ≠ a×(b×c) in general
- Commutativity: a×b ≠ b×a in general

## Examples

See `test.c` and `test-version.c` for comprehensive examples.

### Basis Multiplication

```c
octonion i, j, k;
oct_make(&i, 0, 1, 0, 0, 0, 0, 0, 0);
oct_make(&j, 0, 0, 1, 0, 0, 0, 0, 0);

oct_multiply(&k, i, j);  // i×j = k
// Result: 𝕆(0, 0, 0, 1, 0, 0, 0, 0)
```

### Non-Associativity

```c
octonion l, ij_l, i_jl;
oct_make(&l, 0, 0, 0, 0, 1, 0, 0, 0);

// (i×j)×l
octonion ij;
oct_multiply(&ij, i, j);
oct_multiply(&ij_l, ij, l);

// i×(j×l)  
octonion jl;
oct_multiply(&jl, j, l);
oct_multiply(&i_jl, i, jl);

// ij_l ≠ i_jl  ← THE defining feature!
```

### Norm Preservation

```c
octonion a, b, ab;
oct_make(&a, 1, 2, 3, 4, 5, 6, 7, 8);
oct_make(&b, 2, 1, 0, -1, 3, -2, 1, 0);
oct_multiply(&ab, a, b);

double norm_a = oct_norm(a);
double norm_b = oct_norm(b);
double norm_ab = oct_norm(ab);

// norm_ab == norm_a * norm_b  ✓
```

## Documentation

- [API Reference](OCTONION_API.md)
- [Packaging Guide](PACKAGING_GUIDE.md)
- [Versioning Guide](VERSIONING_GUIDE.md)
- [Bug Fixes](OCTONION_BUGFIXES.md)

## Requirements

- C99 compiler (gcc, clang)
- Standard C library
- Math library (-lm)

## Building

```bash
# Build everything
make

# Build static library only
make static

# Build shared library only
make shared

# Run tests
make check

# Install
sudo make install

# Install to custom location
make install PREFIX=/opt/liboct
```

## License

GPL 3.0 - See LICENSE file

## Author

Chris "Scáth" Ó Luanaigh, 2026

## Contributing

Contributions welcome! Areas of interest:

- Transcendental functions (exp, log, sin, cos)
- Slice-regular derivatives
- Performance optimizations
- Additional test cases
- Documentation improvements

## See Also

- [Quaternions (ℍ)](https://en.wikipedia.org/wiki/Quaternion)
- [Cayley-Dickson Construction](https://en.wikipedia.org/wiki/Cayley%E2%80%93Dickson_construction)
- [Hurwitz's Theorem](https://en.wikipedia.org/wiki/Hurwitz%27s_theorem_(composition_algebras))
- John Baez, "The Octonions" (2002)
- Conway & Smith, "On Quaternions and Octonions" (2003)

## Version History

### 0.3.0 (2026-01-19)
- First real release!

### 0.2.0 (2026-01-09)
- moved to pass-by-reference
- added versioning to library
- enhanced build options - including building .debs and dist files

### 0.1.0 (2026-01-09)

- Initial release
- Complete octonion arithmetic
- 8×8 multiplication table
- Norm, conjugate, inverse operations
- Comprehensive test suite
- RPM and DEB packaging

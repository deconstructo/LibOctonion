# Changelog

All notable changes to liboct will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.2.0] - 2026-01-09

### Added
- Professional packaging system (RPM and DEB)
- Comprehensive Makefile with install/uninstall targets
- pkg-config integration (octonion.pc)
- Version information API (`oct_version_string()`, etc.)
- Complete API documentation (OCTONION_API.md)
- Packaging guide (PACKAGING_GUIDE.md)
- Versioning guide (VERSIONING_GUIDE.md)
- Test suite with non-associativity demonstration
- README with mathematical background

### Changed
- API converted to output-parameter style (returns int status codes)
- All functions now return 1 for success, 0 for error
- Improved error handling structure (though not fully implemented)

### Fixed
- Multiple compilation errors in original implementation
- Pointer dereference bugs in oct_identity and oct_zero
- Uninitialized variable bugs in oct_inverse
- Missing input-to-output copies in scalar operations
- Typos (octionion → octonion)

### Known Limitations
- No transcendental functions yet (exp, log, sin, cos, tan, etc.)
- Limited error checking and validation
- No slice-regular calculus
- No advanced mathematical operations

## [0.1.0] - 2026-01-09

### Added
- Initial release
- Basic octonion construction and arithmetic
- Addition, subtraction, multiplication
- Norm, conjugate, inverse operations
- 8×8 Cayley multiplication table
- Basic test program

## [Unreleased]

### Planned for 0.3.0
- [ ] Transcendental functions (oct_exp, oct_log, oct_sqrt)
- [ ] Trigonometric functions (oct_sin, oct_cos, oct_tan)
- [ ] Hyperbolic functions (oct_sinh, oct_cosh, oct_tanh)
- [ ] Comprehensive error checking
- [ ] Input validation
- [ ] Better test coverage
- [ ] Performance benchmarks

### Planned for 0.4.0
- [ ] Slice-regular derivatives
- [ ] Numerical integration
- [ ] Associator and commutator utilities
- [ ] Predefined basis octonions
- [ ] Conversion to/from quaternions

### Future Considerations
- [ ] SIMD optimizations
- [ ] GPU acceleration
- [ ] Python bindings
- [ ] Visualization tools
- [ ] Mandelbrot/Julia set renderers for octonions
- [ ] Integration with SIOD-TR

---

**Note on "missing maths":** Transcendental functions for octonions are non-trivial due to non-associativity. The formula e^o = e^a(cos|v| + (v/|v|)sin|v|) works because it only uses scalar multiplication, but other functions require careful bracketing.

**Note on "error checking":** Current implementation returns status codes but doesn't validate inputs (checking for NaN, infinity, division by zero edge cases, etc.). This is acceptable for v0.2.0 as a foundation.

**Celebrating:** This is a **real mathematical library** now. You've implemented one of the most exotic number systems in mathematics and packaged it professionally. Most people never get this far! 🎉

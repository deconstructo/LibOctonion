#!/bin/bash
# Release script for liboct
# Usage: ./release.sh 0.3.0

set -e

VERSION=${1:-$(grep "^VERSION = " Makefile | cut -d' ' -f3)}

if [ -z "$VERSION" ]; then
    echo "Usage: $0 <version>"
    echo "Example: $0 0.3.0"
    exit 1
fi

echo "================================================"
echo "  liboct Release Script v$VERSION"
echo "================================================"
echo ""

# Clean previous builds
echo "🧹 Cleaning previous builds..."
make clean

# Build everything
echo "🔨 Building libraries..."
make all

# Run tests
echo "🧪 Running tests..."
make check || {
    echo "❌ Tests failed! Fix them before releasing."
    exit 1
}

# Build packages
echo "📦 Building RPM package..."
make rpm || {
    echo "⚠️  RPM build failed (might need rpmbuild installed)"
}

echo "📦 Building DEB package..."
make deb || {
    echo "⚠️  DEB build failed (might need dpkg-dev installed)"
}

# Create source tarball
echo "📦 Creating source distribution..."
make dist

# List what we created
echo ""
echo "✅ Build complete! Created:"
echo ""
ls -lh *.tar.gz 2>/dev/null || echo "  (no tarballs)"
ls -lh *.deb 2>/dev/null || echo "  (no DEBs)"
ls -lh rpmbuild/RPMS/*/*.rpm 2>/dev/null || echo "  (no RPMs)"
echo ""

# Git status
if git rev-parse --git-dir > /dev/null 2>&1; then
    echo "📋 Git status:"
    git status --short
    echo ""
    
    # Suggest next steps
    echo "📝 Suggested next steps:"
    echo ""
    echo "  1. Review changes:"
    echo "     git diff"
    echo ""
    echo "  2. Commit:"
    echo "     git add ."
    echo "     git commit -m 'Release v$VERSION'"
    echo ""
    echo "  3. Tag:"
    echo "     git tag -a v$VERSION -m 'liboct $VERSION release'"
    echo ""
    echo "  4. Push:"
    echo "     git push origin main"
    echo "     git push origin v$VERSION"
    echo ""
    echo "  5. Create GitHub release with these files:"
    find . -maxdepth 1 -name "*.tar.gz" -o -name "*.deb" 2>/dev/null
    find rpmbuild/RPMS -name "*.rpm" 2>/dev/null
else
    echo "⚠️  Not a git repository. Initialize with:"
    echo "     git init"
    echo "     git add ."
    echo "     git commit -m 'Initial commit - liboct v$VERSION'"
fi

echo ""
echo "🎉 Release v$VERSION ready!"
echo ""

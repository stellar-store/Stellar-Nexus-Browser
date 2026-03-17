#!/bin/bash
# ─────────────────────────────────────────────────────────────────
#  Stellar Nexus Browser — Build Script for Linux
# ─────────────────────────────────────────────────────────────────

set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

echo ""
echo "  ⬡  Stellar Nexus Browser — Build"
echo "  ─────────────────────────────────"
echo ""

# Detect Qt
QT_VERSION=""
if command -v qmake6 &>/dev/null; then
    QT_VERSION="Qt6"
    CMAKE_QT="-DCMAKE_PREFIX_PATH=$(qmake6 -query QT_INSTALL_PREFIX)"
elif command -v qmake &>/dev/null; then
    QT_VERSION="Qt5"
    CMAKE_QT="-DCMAKE_PREFIX_PATH=$(qmake -query QT_INSTALL_PREFIX)"
else
    echo "  ✗ Qt not found. Install Qt6 or Qt5 with WebEngine."
    echo ""
    echo "  Ubuntu/Debian:"
    echo "    sudo apt install qt6-webengine-dev qt6-base-dev cmake build-essential"
    echo "  or for Qt5:"
    echo "    sudo apt install qtwebengine5-dev qt5-default cmake build-essential"
    exit 1
fi

echo "  ✓ Found $QT_VERSION"
echo ""

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake "$SCRIPT_DIR" $CMAKE_QT \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    2>&1

echo ""
echo "  Building…"
echo ""
cmake --build . --parallel $(nproc)

echo ""
echo "  ✓ Build complete!"
echo ""
echo "  Run with:  $BUILD_DIR/stellar"
echo "  or simply: ./build/stellar"
echo ""

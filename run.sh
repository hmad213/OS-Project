#!/bin/bash
set -e
 
# Always run from the repo root, regardless of where the script is called from
cd "$(dirname "$0")"
 
# ─────────────────────────────────────────────
#  Configuration
# ─────────────────────────────────────────────
RAYLIB_VERSION="5.0"
RAYLIB_DIR="deps/raylib"           # installed inside the repo
RAYLIB_LIB="$RAYLIB_DIR/lib/libraylib.a"
RAYLIB_INCLUDE="$RAYLIB_DIR/include"
 
SRC_DIR="src"
BUILD_DIR="build"
TARGET="$BUILD_DIR/game"
 
# ─────────────────────────────────────────────
#  Install raylib if not already present
# ─────────────────────────────────────────────
install_raylib() {
    echo "[run.sh] raylib not found. Building raylib $RAYLIB_VERSION into $RAYLIB_DIR/ ..."
 
    # Check for required tools
    for tool in git cmake gcc; do
        if ! command -v "$tool" &>/dev/null; then
            echo "[run.sh] ERROR: '$tool' is required but not installed."
            echo "         Install it with: sudo apt install build-essential cmake git"
            exit 1
        fi
    done
 
    # Install required system dev libraries for raylib/GLFW
    echo "[run.sh] Installing required system libraries..."
    sudo apt-get install -y \
        libx11-dev \
        libxrandr-dev \
        libxinerama-dev \
        libxcursor-dev \
        libxi-dev \
        libgl1-mesa-dev \
        libglu1-mesa-dev
 
    TMP_DIR=$(mktemp -d)
    trap 'rm -rf "$TMP_DIR"' EXIT
 
    git clone --depth 1 --branch "$RAYLIB_VERSION" \
        https://github.com/raysan5/raylib.git "$TMP_DIR/raylib"
 
    cmake -S "$TMP_DIR/raylib" -B "$TMP_DIR/build" \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=OFF \
        -DCMAKE_INSTALL_PREFIX="$(pwd)/$RAYLIB_DIR" \
        -DBUILD_EXAMPLES=OFF \
        -Wno-dev
 
    cmake --build "$TMP_DIR/build" --parallel "$(nproc)"
    cmake --install "$TMP_DIR/build"
 
    echo "[run.sh] raylib $RAYLIB_VERSION ready in $RAYLIB_DIR/"
}
 
if [ ! -f "$RAYLIB_LIB" ]; then
    install_raylib
else
    echo "[run.sh] raylib already built at $RAYLIB_DIR/"
fi
 
# ─────────────────────────────────────────────
#  Build the project
# ─────────────────────────────────────────────
mkdir -p "$BUILD_DIR"
 
echo "[run.sh] Building..."
gcc "$SRC_DIR"/*.c \
    -I"$RAYLIB_INCLUDE" \
    -L"$RAYLIB_DIR/lib" \
    -lraylib \
    -lm -lpthread -ldl \
    -o "$TARGET"
 
echo "[run.sh] Running $TARGET"
exec "$TARGET" "$@"
 
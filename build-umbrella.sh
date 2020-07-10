#!/bin/bash

# this uses the Proton-CLang toolchain
# https://github.com/kdrag0n/proton-clang.git

echo
echo "Cleanup output dir"
echo

rm -rf out
make clean && make mrproper
mkdir -p out

echo
echo "Build kernel"
echo

export PATH="$HOME/proton-clang/bin:$PATH"
export LD_LIBRARY_PATH="$HOME/proton-clang/lib:$LD_LIBRARY_PATH"
export ARCH=arm64
export SUBARCH=arm64
export AR=llvm-ar
export NM=llvm-nm
export OBJCOPY=llvm-objcopy
export OBJDUMP=llvm-objdump
export STRIP=llvm-strip

#Make config
make O=out ARCH=arm64 nb1_defconfig

#Build kernel
make -s -j$(nproc --all) O=out CONFIG_DEBUG_SECTION_MISMATCH=y \
    ARCH=arm64 \
    CC="ccache clang" \
    CROSS_COMPILE=aarch64-linux-gnu- \
    CROSS_COMPILE_ARM32=arm-linux-gnueabi- \
    LOCALVERSION=-clang-$(date +'%Y-%m-%d')
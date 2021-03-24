#!/bin/sh

# Test for a compiled kernel
if [ ! -f out/arch/arm64/boot/Image.*-dtb ]; then
    echo "Please compile a kernel before attempting to package it!"
    exit 1
fi

# Try to autodetect the device the kernel was built for if it wasn't specified
KVERSION=$(cat out/include/config/kernel.release)
if [ "$KDEVICE" = "" ]; then
    if echo $KVERSION | grep -qi NB1; then
        KDEVICE="NB1"
    fi
fi
if [ "$KNAME" = "" ]; then
    KNAME="Umod"
fi

# Copy the template config
cp -r umod/template umod/.tmp

# Update the variables
echo "Version: $KVERSION" > umod/.tmp/version
sed -i "s/{DEVICE}/$KDEVICE/g" umod/.tmp/anykernel.sh
sed -i "s/{NAME}/$KNAME/g" umod/.tmp/anykernel.sh

# Copy the kernel
cp out/arch/arm64/boot/Image.*-dtb umod/.tmp

# Package the zip file
mkdir -p umod/out
cd umod/.tmp
zip -r ../out/$KVERSION.zip .
cd ../..

# Clean up
rm -r umod/.tmp

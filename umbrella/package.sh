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
    KNAME="Umbrella"
fi

# Check if Treble support is enabled
if [ -f out/arch/arm64/boot/dts/fih/NB1_treble ]; then
	KDEVICE="${KDEVICE}_Treble"
fi

# Copy the template config
cp -r umbrella/template umbrella/.tmp

# Update the variables
echo "Version: $KVERSION" > umbrella/.tmp/version
sed -i "s/{DEVICE}/$KDEVICE/g" umbrella/.tmp/anykernel.sh
sed -i "s/{NAME}/$KNAME/g" umbrella/.tmp/anykernel.sh

# Copy the kernel
cp out/arch/arm64/boot/Image.*-dtb umbrella/.tmp

# Package the zip file
mkdir -p umbrella/out
if [ -e "umbrella/out/${KVERSION}.zip" ]; then
	echo "Removing existing ${KVERSION}.zip"
	rm umbrella/out/$KVERSION.zip
fi

cd umbrella/.tmp
zip -r ../out/$KVERSION.zip .
cd ../..

# Clean up
rm -r umbrella/.tmp

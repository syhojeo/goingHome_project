source ./exportVariables.sh

cd $JETSON_KERNEL_SOURCE
make ARCH=arm64 O=$JETSON_KERNEL_OUT xconfig

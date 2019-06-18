source ./exportVariables.sh

cd $JETSON_KERNEL_SOURCE
make ARCH=$ARCH O=$JETSON_KERNEL_OUT menuconfig

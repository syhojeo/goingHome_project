# customize variables if you want to deploy sources and buildsystems to other folder

export CURRENT_PATH=$(pwd)
export SOURCE_LOCATION=$CURRENT_PATH/source
export L4T_LOCATION=$CURRENT_PATH/L4T
export TOOLCHAIN=$CURRENT_PATH/linaro
export ROOTFS_LOCATION=$L4T_LOCATION/rootfs
export ARCH=arm64
export JETSON_KERNEL_SOURCE=$L4T_LOCATION/sources/kernel/kernel-4.9
export JETSON_KERNEL_OUT=$JETSON_KERNEL_SOURCE/output
export JETSON_KERNEL_IMAGE_PATH=$L4T_LOCATION/kernel
export JETSON_KERNEL_MODULE_OUT=$JETSON_KERNEL_OUT/modules
export JETSON_KERNEL_SD_IMAGE_OUT=$CURRENT_PATH/output
export SD_IMAGE_NAME=myimage.img
export SIZE_OF_IMAGE=12G


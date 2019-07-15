# customize variables if you want to deploy sources and buildsystems to other folder

export CURRENT_PATH=$(pwd)
export SOURCE_LOCATION=$CURRENT_PATH/source
export L4T_LOCATION=$CURRENT_PATH/L4T
export TOOLCHAIN=$CURRENT_PATH/linaro
export CROSS_COMPILER=$TOOLCHAIN/bin/aarch64-linux-gnu-
export ROOTFS_LOCATION=$L4T_LOCATION/Linux_for_Tegra/rootfs
export ARCH=arm64
export JETSON_KERNEL_SOURCE=$L4T_LOCATION/Linux_for_Tegra/sources/kernel/kernel-4.9/
export JETSON_KERNEL_OUT=$JETSON_KERNEL_SOURCE/output
export JETSON_KERNEL_IMAGE_PATH=$L4T_LOCATION/Linux_for_Tegra/kernel
export JETSON_KERNEL_MODULE_OUT=$JETSON_KERNEL_OUT/modules
export JETSON_KERNEL_SD_IMAGE_OUT=$CURRENT_PATH/output
export SD_IMAGE_NAME=myimage.img
export SIZE_OF_IMAGE=12G


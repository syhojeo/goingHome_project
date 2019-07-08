# Download kernel source, sample root filesystem and toolchain
source ./exportVariables.sh

mkdir $SOURCE_LOCATION
mkdir $L4T_LOCATION
mkdir $TOOLCHAIN
mkdir $ROOTFS_LOCATION
# mkdir $JETSON_KERNEL_SOURCE
# mkdir $JETSON_KERNEL_OUT
# mkdir $JETSON_KERNEL_MODULE_OUT

sudo apt install libncurses5-dev build-essential qemu qemu-user-static libqt4-dev pkg-config git -y

wget -O l4t-jetson-driver-package-32-1-jetson-nano.tbz2 https://developer.nvidia.com/embedded/dlc/l4t-jetson-driver-package-32-1-jetson-nano  
wget -O l4t-sample-root-filesystem-32-1-jetson-nano.tbz2 https://developer.nvidia.com/embedded/dlc/l4t-sample-root-filesystem-32-1-jetson-nano
wget -O gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/aarch64-linux-gnu/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz 

mv l4t-jetson-driver-package-32-1-jetson-nano.tbz2 $SOURCE_LOCATION
mv l4t-sample-root-filesystem-32-1-jetson-nano.tbz2 $SOURCE_LOCATION
mv gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz $SOURCE_LOCATION


source ./exportVariables.sh

cd $SOURCE_LOCATION
tar -xjf l4t-jetson-driver-package-32-1-jetson-nano.tbz2 --directory $L4T_LOCATION
tar -xjf l4t-sample-root-filesystem-32-1-jetson-nano.tbz2 --directory $ROOTFS_LOCATION
sudo tar -jxpf gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz --directory $TOOLCHAIN

# tag: tegra-l4t-r32.1
cd $L4T_LOCATION
./source_sync.sh -k tegra-l4t-r32.1


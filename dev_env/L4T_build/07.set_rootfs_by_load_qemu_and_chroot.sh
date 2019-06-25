source ./exportVariables.sh

cd $ROOTFS_LOCATION

sudo cp /usr/bin/qemu-aarch64-static usr/bin/
sudo mount /sys ./sys -o bind
sudo mount /proc ./proc -o bind
sudo mount /dev ./dev -o bind
# sudo mount /dev/pts ./dev/pts -o bind
sudo mv etc/resolv.conf etc/resolv.conf.saved
sudo cp /etc/resolv.conf etc
sudo LC_ALL=C chroot . /bin/bash # 여기에서 qemu를 구동한다.

# bash에서 exit를 진행한 후 umount를 진행한다.
sudo umount ./sys
sudo umount ./proc
sudo umount ./dev
# sudo umount ./dev/pts

sudo mv etc/resolv.conf.saved etc/resolv.conf
sudo rm usr/bin/qemu-aarch64-static

source ./exportVariables.sh

cd $L4T_LOCATION/Linux_for_Tegra
sudo ./apply_binaries.sh
sudo ./create-jetson-nano-sd-card-image.sh -o $SD_IMAGE_NAME -s $SIZE_OF_IMAGE -r 200
exit


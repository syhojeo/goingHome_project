source ./exportVariables.sh

cd $L4T_LOCATION
sudo -s
source ./apply_binaries.sh
source create-jetson-nano-sd-card-image.sh -o $SD_IMAGE_NAME -s $SIZE_OF_IMAGE -r 200
exit


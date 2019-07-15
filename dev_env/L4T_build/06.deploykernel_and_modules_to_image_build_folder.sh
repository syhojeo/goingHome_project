source ./exportVariables.sh
export BKUP_DATE=`date "+%Y_%m_%d_%H_%M_%S"`

cd $JETSON_KERNEL_IMAGE_PATH
mv Image ./backup/
mv zImage ./backup/
mv kernel_supplements.tbz2 ./backup
mv dtb ./backup/
cd backup
mv Image{,.$BKUP_DATE}
mv zImage{,.$BKUP_DATE}
mv kernel_supplements.tbz2{,.$BKUP_DATE}
mv dtb{,.$BKUP_DATE}

cd $JETSON_KERNEL_OUT

cp ./arch/arm64/boot/Image $JETSON_KERNEL_IMAGE_PATH
cp ./arch/arm64/boot/zImage $JETSON_KERNEL_IMAGE_PATH
cp -r ./arch/arm64/boot/dts $JETSON_KERNEL_IMAGE_PATH/dtb

cd $JETSON_KERNEL_MODULE_OUT
tar --owner root --group root -cjf $JETSON_KERNEL_IMAGE_PATH/kernel_supplements.tbz2 lib/modules

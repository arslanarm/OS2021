fallocate -x -l 100000000000 lofs.img
mkfs lofs.img
sudo losetup -f lofs.img
mkdir lofsdisk
sudo mount --source lofs.img --target lofsdisk
sudo chmod 777 lofsdisk

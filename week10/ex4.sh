mkdir tmp
cd tmp
echo 1 > file1
echo 1 > file2
ln file1 link1
cd ../
gcc ex4.c ex4
./ex4 > ex4.txt
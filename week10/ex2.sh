mkdir week01
cd week01
echo 1 > file.txt
cd ../
mkdir week10
link week01/file.txt week10/_ex2.txt
find . -inum $(ls -i week01/file.txt | cut -f 1 -d " ") > ex2.txt
find . -inum $(ls -i week01/file.txt | cut -f 1 -d " ") -exec rm {} \; >> ex2.txt

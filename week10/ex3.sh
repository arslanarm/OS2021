echo 1 > _ex3.txt
ls -l _ex3.txt > ex3.txt
chmod a-x _ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod u=rwx,o=rwx,g=-rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt
echo "660 is grant rw to user and group, others don't have anything" >> ex3.txt
echo "775 is grant rwx to user and group, rw to others" >> ex3.txt
echo "777 is grant rwx to everyone" >> ex3.txt


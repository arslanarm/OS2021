for i in $(seq 1000) ; do # can be replaced with endless while loop
    lastnumber=$(cat file | tail -n 1)
    ((lastnumber++))
    echo "$lastnumber" >> file
done
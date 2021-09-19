for i in $(seq 1000) ; do # can be replaced with endless while loop
    while : ; do
        if ln file file.lock > "/dev/null" 2>&1 ; then
            break
        fi
        sleep 0.001
    done
    lastnumber=$(cat file | tail -n 1)
    ((lastnumber++))
    echo "$lastnumber" >> file
    rm file.lock
done
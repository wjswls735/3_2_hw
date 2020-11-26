if [[ $# -lt 2 ]] ; then
    echo "object name | *.c"
    exit
fi

gcc -o $1 $2


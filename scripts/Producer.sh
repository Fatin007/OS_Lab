    #!/bin/bash

    BUFFER_SIZE=10
    mutex=1
    full=0
    empty=$BUFFER_SIZE
    in=0
    out=0
    buffer=()

    produce() {
        if [ $full -eq $BUFFER_SIZE ]; then
            echo "Buffer is Full"
            return
        fi
        echo -n "Enter the value of your item: "
        read item
        buffer[$in]=$item
        in=$(( (in + 1) % BUFFER_SIZE ))
        full=$((full + 1))
        empty=$((empty - 1))
    }

    consume() {
        if [ $empty -eq $BUFFER_SIZE ]; then
            echo "Nothing to consume"
            return
        fi
        item=${buffer[$out]}
        out=$(( (out + 1) % BUFFER_SIZE ))
        full=$((full - 1))
        empty=$((empty + 1))
        echo "The consumed value is $item"
    }

    while true; do
        echo -e "\n1. Produce\t2. Consume\t3. Exit"
        echo -n "Enter your choice: "
        read choice
        case $choice in
            1)
                produce
                ;;
            2)
                consume
                ;;
            3)
                exit 0
                ;;
            *)
                echo "Invalid choice"
                ;;
        esac
    done

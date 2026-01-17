#!/bin/bash

read -p "Enter the number of philosophers: " n
read -p "Enter the number of hungry philosophers: " hungry_cnt
hungry_pos=()
hungry=()
for ((i=0; i<n; i++)); do hungry[i]=0; done
for ((i=0; i<hungry_cnt; i++)); do
    read -p "Enter philosopher $((i+1)) position: " pos
    hungry_pos[i]=$pos
    hungry[$pos]=1
    has_eaten[$pos]=0
    eating[$pos]=0
    
    for ((j=0; j<n; j++)); do
        has_eaten[$j]=0
        eating[$j]=0
    done
done

read -p "1.One can eat at a time
2.Two can eat at a time
3.Exit 
Enter your choice: " choice

if [[ $choice -eq 1 ]]; then
    echo -e "\nAllow one philosopher to eat at any time"
    for ((round=0; round<hungry_cnt; round++)); do
        pos=${hungry_pos[round]}
        echo "P $pos is granted to eat"
        eating[$pos]=1
        has_eaten[$pos]=1
        for ((i=0; i<n; i++)); do
            if [[ ${hungry[$i]} -eq 1 && ${has_eaten[$i]} -eq 0 ]]; then
                if [[ ${eating[$i]} -eq 1 ]]; then
                    echo "P $i is eating"
                else
                    echo "P $i is waiting"
                fi
            elif [[ ${hungry[$i]} -eq 1 && ${has_eaten[$i]} -eq 1 && ${eating[$i]} -eq 1 ]]; then
                echo "P $i is eating"
            fi
        done
        eating[$pos]=0
    done
elif [[ $choice -eq 2 ]]; then
    echo -e "\nAllow two philosophers to eat at any time"
    remaining=$hungry_cnt
    while ((remaining > 0)); do
        first=-1
        second=-1
        for ((i=0; i<hungry_cnt; i++)); do
            pos=${hungry_pos[i]}
            if [[ ${has_eaten[$pos]} -eq 0 ]]; then
                first=$pos
                break
            fi
        done
        
        for ((i=0; i<hungry_cnt; i++)); do
            pos=${hungry_pos[i]}
            if [[ ${has_eaten[$pos]} -eq 0 && $pos -ne $first && $((pos-first==1 || first-pos==1 || pos-first==n-1 || first-pos==n-1)) -eq 0 ]]; then
                second=$pos
                break
            fi
        done
        if [[ $first -ne -1 && $second -ne -1 ]]; then
            echo "P $first and P $second are granted to eat"
            eating[$first]=1
            eating[$second]=1
            has_eaten[$first]=1
            has_eaten[$second]=1
            ((remaining-=2))
        elif [[ $first -ne -1 ]]; then
            echo "P $first is granted to eat"
            eating[$first]=1
            has_eaten[$first]=1
            ((remaining-=1))
        fi
        for ((i=0; i<n; i++)); do
            isHungry=0
            for ((j=0; j<hungry_cnt; j++)); do
                if [[ ${hungry_pos[j]} -eq $i ]]; then
                    isHungry=1
                    break
                fi
            done
            if [[ $isHungry -eq 1 && ${has_eaten[$i]} -eq 0 ]]; then
                if [[ ${eating[$i]} -eq 1 ]]; then
                    echo "P $i is eating"
                else
                    echo "P $i is waiting"
                fi
            elif [[ $isHungry -eq 1 && ${has_eaten[$i]} -eq 1 && ${eating[$i]} -eq 1 ]]; then
                echo "P $i is eating"
            fi
        done
        if [[ $first -ne -1 ]]; then eating[$first]=0; fi
        if [[ $second -ne -1 ]]; then eating[$second]=0; fi
    done
elif [[ $choice -eq 3 ]]; then
    echo "Exiting..."
    exit 0
else
    echo "Invalid choice!"
    exit 1
fi

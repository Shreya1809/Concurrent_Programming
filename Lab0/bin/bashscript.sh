#!/bin/bash
echo "Lab0 - Sorting a text file of intergers using Mergesort/Quicksort "
## array of menu entries
entries=( "Generate 14 randomized test files for sorting"
          "Sort files"
          "Delete TestFiles"
          "exit" )
PS3='Selection: '

while [ "$close" != 1 ]; do                ## outer loop redraws menu each time
    printf "\nMain Menu:\n\n"             ## heading for menu
    select choice in "${entries[@]}"; do  ## select displays choices in array
        case "$choice" in                 ## case responds to choice
            "Generate 14 randomized test files for sorting" )
                echo "Generating 14 random test files"
                COUNT=11
                # bash until loop
                until [ $COUNT -gt 24 ]; do
                        let NUMBER=NUMBER+1
                        shuf -i1-10 -n5 --random-source=<( echo $COUNT) > "TestFile${NUMBER}.txt"
                        let COUNT=COUNT+1
                done       
                break                     ## break returns control to outer loop
                ;;
            "Delete TestFiles" )
                rm -rf *TestFile*
                echo "All TestFiles Deleted"
                break
                ;;
            "Sort files" )
                # Declare variable Algo_option to be used in while loop
                option=3 
                # Print to stdout
                echo "Choose Sorting Algorithm"
                echo "1. Mergesort"
                echo "2. Quicksort"
                while [ $option -eq 3 ]; do
 
                # read user input
                read option
                # bash nested if/else
                if [ $option -eq 1 ] ; then
                        echo "You have chosen Mergesort"
                        mergeoption=3 
                        echo "1. Execute Mergesort for a single test case"
                        echo "2. Execute Mergesort for a for all 14 test cases"
                        while [ $mergeoption -eq 3 ]; do
                        # read user input
                        read mergeoption
                        if [ $mergeoption -eq 1 ] ; then
                            echo "Enter any TestFile number from 1-14"
                            read testfilenum
                            file="./TestFile$testfilenum.txt"
                            if [ -e $file ]; then
                                echo "TestFile$testfilenum.txt exists"
                            else 
                                echo "TestFile$testfilenum.txt does not exists"
                            fi 
                        else
                            if [ $mergeoption -eq 2 ] ; then
                                echo "All files exist"
                            else
                                echo "Invalid option"
                                mergeoption = 3
                            fi
                        fi 
                        done   
                else                   
                        if [ $option -eq 2 ] ; then
                                echo "You have chosen Quicksort"
                                quickoption=3 
                                echo "1. Execute Quicksort for a single test case"
                                echo "2. Execute Quicksort for a for all 14 test cases"
                                while [ $quickoption -eq 3 ]; do
                                # read user input
                                read quickoption
                                if [ $quickoption -eq 1 ] ; then
                                    echo "Enter any TestFile number from 1-14"
                                    read testfilenum
                                    file="./TestFile$testfilenum.txt"
                                    if [ -e $file ]; then
                                        echo "TestFile$testfilenum.txt exists"
                                    else 
                                        echo "TestFile$testfilenum.txt does not exists"
                                    fi 
                                else
                                    if [ $quickoption -eq 2 ] ; then
                                        echo "All files exist"
                                    else
                                        echo "Invalid option"
                                        quickoption = 3
                                    fi
                                fi 
                                done   
                        else                        
                                
                            echo "Invalid choice, Please choose either 1 or 2 !"
                            echo "1. Mergesort"
                            echo "2. Quicksort"
                            option=3
                                  
                        fi
                fi
                done 
                #break
                ;;
            "exit" )         
                echo "Haiiii, exiting"
                close=1                    ## variable setting exit condition
                break
                ;;
            * )
                echo "ssss"
                break
                ;;
        esac
    done
done

exit 0

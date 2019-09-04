#!/bin/bash
echo "Lab0 - Sorting a text file of intergers using Mergesort/Quicksort "
## array of menu entries
entries=( "Generate 14 randomized test files for sorting"
          "Generate custom random test files for sorting"
          "Sort files by my sorting method"
          "Sort files using sort -n"
          "Compare the sorted files"
          "Delete TestFiles, SortedTestFiles and mySortedTestFiles"
          "exit" )
PS3='Selection: '
#function for seeding random source 
get_seeded_random()
{
  seed="$1"
  openssl enc -aes-256-ctr -pass pass:"$seed" -nosalt \
    </dev/zero 2>/dev/null
}

while [ "$close" != 1 ]; do                ## outer loop redraws menu each time
    printf "\nMain Menu:\n\n"             ## heading for menu
    select choice in "${entries[@]}"; do  ## select displays choices in array
        case "$choice" in                 ## case responds to choice


            "Generate 14 randomized test files for sorting" )
                echo "Generating 14 random test files. Enter range and size eg-> 30 20 "
                read range size 
                COUNT=11
                NUMBER=0
                # bash until loop
                until [ $COUNT -gt 24 ]; do
                        let NUMBER=NUMBER+1
                        shuf -i1-$range -n$size --random-source=<(get_seeded_random $COUNT) > "TestFile${NUMBER}.txt"
                        let COUNT=COUNT+1
                done       
                break                     ## break returns control to outer loop
                ;;

            "Generate custom random test files for sorting")
                echo "Enter the range,size,seed  eg -> 50 20 38"
                read range size seed
                if [ $range -lt $size ]; then
                    echo "Invalid, range is less than size"
                else
                    echo "suggest a file name eg-> myfile"
                    read filename
                    shuf -i1-$range -n$size --random-source=<(get_seeded_random $seed) > "$filename.txt"
                    echo "$filename.txt is generated with $size elements in the range of 1 to $range"
                fi
                break
                ;;


            "Delete TestFiles, SortedTestFiles and mySortedTestFiles" )
                rm -rf TestFile* SortedTestFile* mySortedTestFile*
                echo "All Files Deleted"
                break
                ;;


            "Sort files by my sorting method" )
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
                            #make the merge sort code
                            echo "Enter the name of file to sort eg -> TestFile1"
                            read testfilename
                            file="./$testfilename.txt"
                            if [ -e $file ]; then
                                echo "$testfilename.txt exists"
                            else 
                                echo "$testfilename.txt does not exists"
                            fi 
                        else
                            if [ $mergeoption -eq 2 ] ; then
                                FILECOUNT1=0
                                FLAG1=0
                                # bash until loop
                                while [ $FILECOUNT1 -lt 14 ]; do
                                        let FILECOUNT1=FILECOUNT1+1
                                        file="./TestFile$FILECOUNT1.txt"
                                        if [ -e $file ]; then
                                            echo "TestFile$FILECOUNT1.txt exists"
                                            #insert here
                                        else
                                            echo "TestFile$FILECOUNT1.txt does not exists"
                                            let FLAG1=FLAG1+1
                                        fi
                                done
                                if [ $FLAG1 -eq 0 ] ; then  
                                    echo "All files exist"
                                else 
                                    echo "$FLAG1 Test files missing, Cannot perform test"
                                    break
                                fi
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
                                    echo "Enter the name of file to sort eg -> TestFile1"
                                    read testfilename
                                    file="./$testfilename.txt"
                                    if [ -e $file ]; then
                                        echo "$testfilename.txt exists"
                                    else 
                                        echo "$testfilename.txt does not exists"
                                    fi 
                                else
                                    if [ $quickoption -eq 2 ] ; then
                                        FILECOUNT2=0
                                        FLAG2=0
                                        # bash until loop
                                        while [ $FILECOUNT2 -lt 14 ]; do
                                                let FILECOUNT2=FILECOUNT2+1
                                                file="./TestFile$FILECOUNT2.txt"
                                                if [ -e $file ]; then
                                                    echo "TestFile$FILECOUNT2.txt exists"
                                                else
                                                    echo "TestFile$FILECOUNT2.txt does not exists"
                                                    let FLAG2=FLAG2+1
                                                fi
                                        done
                                        if [ $FLAG2 -eq 0 ] ; then  
                                            echo "All files exist"
                                        else 
                                            echo "$FLAG2 Test files missing, Cannot perform test"
                                            break
                                        fi
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
                break
                ;;

            "Sort files using sort -n" )
                sortchoice=3;
                echo "1. Sort a single file"
                echo "2. Sort all the test files"
                while [ $sortchoice -eq 3 ]; do
                read sortchoice
                if [ $sortchoice -eq 1 ] ; then
                    echo "Enter the name of file to sort eg -> TestFile1"
                    read testfilename
                    file="./$testfilename.txt"
                    if [ -e $file ]; then
                        echo "$testfilename.txt exists"
                        sort -n $testfilename.txt > Sorted$testfilename.txt
                        echo "File has been sorted and saved as Sorted$testfilename.txt"
                    else 
                        echo "$testfilename.txt does not exists"
                    fi 
                elif [ $sortchoice -eq 2 ] ; then
                        FILECOUNT3=0
                        FLAG3=0
                        # bash until loop
                        while [ $FILECOUNT3 -lt 14 ]; do
                                let FILECOUNT3=FILECOUNT3+1
                                file="./TestFile$FILECOUNT3.txt"
                                if [ -e $file ]; then
                                    #echo "TestFile$FILECOUNT3.txt exists"
                                    let dummy=dummy+1
                                else
                                    echo "TestFile$FILECOUNT3.txt does not exists"
                                    let FLAG3=FLAG3+1
                                fi
                                done
                        if [ $FLAG3 -eq 0 ] ; then  
                            echo "All files exist, Sorting ..."
                            SORTEDFILECOUNT=1
                            while [ $SORTEDFILECOUNT -lt 15 ]; do
                               sort -n TestFile$SORTEDFILECOUNT.txt > SortedTestFile$SORTEDFILECOUNT.txt 
                               let SORTEDFILECOUNT=SORTEDFILECOUNT+1
                            done
                            echo "All TestFiles sorted and saved as 'SortedTestFileN.txt'"
                        else 
                            echo "$FLAG3 Test files missing, Cannot perform sort"
                        fi
                else
                    echo "Invalid option. Please choose 1 or 2"
                    echo "1. Sort a single file"
                    echo "2. Sort all the test files"
                    sortchoice = 3
                fi
                done
                break
                ;;

            "Compare the sorted files" )
                echo "1. Compare 2 files"
                echo "2. Compare all the 14 SortedTestFiles(sort -n) with mySortedTestFiles(merge or quicksort)"
                compareoption=3
                while [ $compareoption -eq 3 ]; do
                read compareoption
                if [ $compareoption -eq 1 ] ; then
                    echo "Enter the name of files to compare eg -> SortedTestFile1 mySortedTestFile1"
                    read file1 file2
                    INPUTFILECOUNT=0
                    if [ -e $file1.txt ]; then
                        let INPUTFILECOUNT=INPUTFILECOUNT+1
                    else
                        echo "$file1.txt does not exists"
                    fi
            
                    if [ -e $file2.txt ]; then
                        let INPUTFILECOUNT=INPUTFILECOUNT+1
                    else
                        echo "$file2.txt does not exists"
                    fi

                    if [ $INPUTFILECOUNT -eq 2 ] ; then  
                        echo "Both the files exist, Comparing ..."
                        cmp --silent $file1.txt $file2.txt && echo "Files are Same !" || echo "Files are Different !"
                    else
                        echo "One of the files does not exist, Cannot compare"
                    fi
                        
                elif [ $compareoption -eq 2 ] ; then
                    echo "Checking if all files exist..."
                    FILECOUNT5=0
                    FILECOUNT6=0
                    FLAGS5=0
                    while [ $FILECOUNT5 -lt 14 ]; do
                            let FILECOUNT5=FILECOUNT5+1
                            file="./SortedTestFile$FILECOUNT5.txt"
                            if [ -e $file ]; then
                                #echo "TestFile$FILECOUNT5.txt exists"
                                let dummy=dummy+1
                            else
                                echo "SortedTestFile$FILECOUNT5.txt does not exists"
                                let FLAG5=FLAG5+1
                            fi
                            done
                    while [ $FILECOUNT6 -lt 14 ]; do
                            let FILECOUNT6=FILECOUNT6+1
                            file="./mySortedTestFile$FILECOUNT6.txt"
                            if [ -e $file ]; then
                                #echo "TestFile$FILECOUNT6.txt exists"
                                let dummy=dummy+1
                            else
                                echo "mySortedTestFile$FILECOUNT6.txt does not exists"
                                let FLAG5=FLAG5+1
                            fi
                            done
                    if [[ $FLAG5 -eq 0 ]]; then
                        echo "All files exist. Comparing..."
                        COMPARECOUNT=0
                        while [ $COMPARECOUNT -lt 14 ]; do
                            let COMPARECOUNT=COMPARECOUNT+1
                            cmp --silent SortedTestFile$COMPARECOUNT.txt mySortedTestFile$COMPARECOUNT.txt && echo "SortedTestFile$COMPARECOUNT.txt and mySortedTestFile$COMPARECOUNT.txtFiles are Same !" || echo "SortedTestFile$COMPARECOUNT.txt and mySortedTestFile$COMPARECOUNT.txtFiles are Different !"
                            done
                    else
                        echo "$FLAGS5 files missing cannot compare"    
                    fi

                else
                    echo "Invalid choice, Please choose 1 or 2"
                    echo "1. Compare 2 files"
                    echo "2. Compare all the 14 SortedTestFiles(sort -n) with mySortedTestFiles(merge or quicksort)"
                    compareoption=3
                fi
                done
                break
                ;;


            "exit" )         
                echo "Good bye"
                close=1                    ## variable setting exit condition
                break
                ;;
            * )
                echo "invalid choice"
                break
                ;;
        esac
    done
done

exit 0

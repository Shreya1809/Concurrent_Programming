#!/bin/bash

## array of menu entries
entries=( "for Copy"
          "for exit" )

## set prompt for select menu
PS3='Selection: '

while [ "$menu" != 1 ]; do                ## outer loop redraws menu each time
    printf "\nMain Menu:\n\n"             ## heading for menu
    select choice in "${entries[@]}"; do  ## select displays choices in array
        case "$choice" in                 ## case responds to choice
            "for Copy" )
                echo "CopyNUM"
                break                     ## break returns control to outer loop
                ;;
            "for exit" )         
                echo "Haiiii, exiting"
                menu=1                    ## variable setting exit condition
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
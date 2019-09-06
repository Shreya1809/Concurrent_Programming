/**
 * @file program.c
 * @author your name Shreya Chakraborty
 * @brief Sort a file of integers and write the output in another file
 * @version 0.1
 * @date 2019-09-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */
/*
Program Approach
1. Get the command line options and parse it using getopt_long()
2. Check of the existence of sourcefile using access()
3. Open the source file, read each line of it using getline(), convert string into integer and add to tail of list
4. Apply mergesort algorithm to the linked list
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "parse.h"
#include "linklist.h"
#include "mergesort.h"

int main( int argc , char *argv[])
{
    printf("******Mergesort Algorithm by Shreya*******\n");
    int num = 0;
    char srcfilepath[50];
    char outfilepath[50];
    char *src = NULL,*out = NULL;
    char ch;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int data = 0;
    FILE *fp, *fp2;
    
    struct node *headref = NULL;

    int val = ParseCommandline(argc ,argv,&src ,&out);
    if(val == 1) //name flag is on
    {
        return 0;
    }

    //append the file path to out source and output file
    sprintf(srcfilepath,"../files/%s",src);
    sprintf(outfilepath,"../files/%s",out);
    

    //check if the source file exists
    if(FileExistCheck(srcfilepath))
    {
        printf("The file exists\n");
    }
    else printf("Source file %s does not exist\n",srcfilepath);

    fp = fopen(srcfilepath, "r"); // read mode
 
    if (fp == NULL)
    { 
        perror("Error while opening the file\n");
        exit(EXIT_FAILURE);
    }

    //reads the file line by line, converts the string into integer and adds to the list from tail
    while ((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%d", &data); 
        addtolist(&headref,data);

    }
    fclose(fp);

    printf("The list of integers is as follows:\n");
    DisplayList(&headref);
    /*the actual merging*/
    MergeSort(&headref);

    //if -o option was declared then output to the file
    if(val == 2)
    {
        fp2 = fopen(outfilepath, "w+");
        if(fp2 == NULL)
        {
            printf("Failed to create output file\n");
            exit(EXIT_FAILURE);
        }
        else{
            //chmod(outfilepath,0776);
            printf("Writing sorted integers to output file\n");
            while(headref != NULL)
            {
                fprintf(fp2,"%d\n",headref->data);
                headref = headref->next;
            }
            fclose(fp2);
        }
    }
    else{ //else output to console
        printf("The Mergesorted list is as follows: \n");
        DisplayListStdio(&headref);
    }
    
    printf("Program Done\n");
    
    if (line)
        free(line);
return 0;
}
    


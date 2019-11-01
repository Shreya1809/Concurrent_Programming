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
#include <omp.h>

#include "parse.h"
#include "list.h"
#include "mergesort.h"

#define NUM_OF_THREADS  2

int main( int argc , char *argv[])
{
    printf("******Mergesort using OpenMP*******\n");
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
    int no_of_elements = 0;
    
    struct node *headref = NULL;

    int val = ParseCommandline(argc ,argv,&src ,&out);
    if(val == 1) //name flag is on
    {
        return 0;
    }

    //append the file path to out source and output file
    sprintf(srcfilepath,"../files/%s",src);
    sprintf(outfilepath,"../files/%s",out);
    
    // Checking nested parallelism availability
    omp_set_nested (1);
    if (omp_get_nested () != 1)
    {
      printf("Nested parallelism not available");
    }

    //check if the source file exists
    if(!FileExistCheck(srcfilepath))
    {
        printf("Source file %s does not exist\n",srcfilepath);
        return 1;
    }

    fp = fopen(srcfilepath, "r"); // read mode
 
    if (fp == NULL)
    { 
        perror("Error while opening the file\n");
        exit(EXIT_FAILURE);
    }

    //get number of elements from file
    while ((read = getline(&line, &len, fp)) != -1) {
       no_of_elements++; 
    }
    printf("[no of nums to sort]:   %d\n", no_of_elements);

    // Check available processors 
    int processors = omp_get_num_procs ();	// Available processors
    printf ("[No of Processes]:     %d\n",processors);

    //set no of threads
    omp_set_num_threads (NUM_OF_THREADS);
    int max_threads = omp_get_max_threads ();	// Max available threads
    printf("[Max available threads]:    %d\n",max_threads);
    if (NUM_OF_THREADS > max_threads)	// Requested threads are more than max available
    {
      printf ("Error: Cannot use %d threads, only %d threads available\n",
	      NUM_OF_THREADS, max_threads);
      return 1;
    }

    //allocating array for merge sort
    int *inputlist = (int*)malloc(sizeof(int)*no_of_elements);

    //set file pointer to begining 
    rewind(fp);

    //reads the file line by line and  copy to the list
    while ((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%d", &data); 
        inputlist[num] = data;
        num++;
    }
    fclose(fp);

    printf("list of integers to sort => \n");
    PrintList(inputlist,no_of_elements);

    /*the actual merging*/
    OMP_merge(inputlist,0,no_of_elements-1);

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
            int i = 0;
            while(i != no_of_elements)
            {
                fprintf(fp2,"%d\n",inputlist[i]);
                i++;
            }
            fclose(fp2);
        }
    }
    else{ //else output to console
        printf("The Mergesorted list is as follows => \n");
        PrintList(inputlist,no_of_elements);
    }
    
    printf("Program Done\n");
    
    if (line)
        free(line);
return 0;
}
    


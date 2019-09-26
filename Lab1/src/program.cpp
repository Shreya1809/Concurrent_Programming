/**
 * @file program.c
 * @author your name Shreya Chakraborty
 * @brief Sort a file of integers and write the output in another file
 * @version 0.1
 * @date 2019-09-21
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

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "parse.h"
#include "forkjoin.h"
#include "bucksort.h"

int main(int argc , char *argv[])
{
    printf("******Sort Algorithm by Shreya*******\n");
    int num = 0;
    string srcfilepath;
    string outfilepath;
    char ch;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int data = 0;
    FILE *fp, *fp2;
    
    struct node *headref = NULL;

    int val = ParseCommandline(argc ,argv, srcfilepath , outfilepath);
    if(val == 1) //name flag is on
    {
        return 0;
    }

    //append the file path to out source and output file
    srcfilepath = std::string("../files/") + srcfilepath;
    outfilepath = std::string("../files/") + outfilepath;    

    //check if the source file exists
    if(FileExistCheck(srcfilepath.c_str()))
    {
        printf("The file exists\n");
    }
    else printf("Source file %s does not exist\n",srcfilepath.c_str());
    
    fp = fopen(srcfilepath.c_str(), "r"); // read mode
 
    if (fp == NULL)
    { 
        perror("Error while opening the file\n");
        exit(EXIT_FAILURE);
    }

    printf("Reading the numbers into array....\n");
    std::vector<int> inputNumberArray;
    //reads the file line by line, converts the string into integer and adds to the list from tail
    while ((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%d", &data); 
        inputNumberArray.push_back(data);
    }
    fclose(fp);
    cout << "File read - ";
    for(size_t i = 0; i < inputNumberArray.size(); i++)
    {
        cout<<inputNumberArray[i]<< " ";
    }
    cout<<endl;
    int MAX_NUMBERS = inputNumberArray.size();
    vector<int> outputNumberArray(0,inputNumberArray.size());

    switch(algoType){
        case FORK_JOIN:
            forkJoinMethod(&inputNumberArray, numOfThreads);
        break;
        case BUCKET_SORT:
            bucketsortMethod(&inputNumberArray, numOfThreads);
        break;
        default:
            cout<<"Invalid Sorting Algorithm"<<endl;
            return 1;
        break;
    }

    /*cout << "Sorted Array: ";
    for(size_t i = 0;  i < inputNumberArray.size(); i++)
    {
        cout<<inputNumberArray[i] << " ";
    }
    cout<<endl;*/

    fp2 = fopen(outfilepath.c_str(), "w+");
    if(fp2 == NULL)
    {
        printf("Failed to create output file\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Writing sorted integers to output file\n");
        for(int i = 0; i < MAX_NUMBERS; i++)
        {
            fprintf(fp2,"%d\n",inputNumberArray[i]);
        }
        
        fclose(fp2);
    }

    printf("Program Done\n");      
    return 0;
}
    


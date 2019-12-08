/**
 * @file parse.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <string>
#include <iostream> 
#include <stdlib.h> 
using namespace std;
#include "parse.h"


int info_flag = 0;
int numOfThreads = 1;
int iteration = 1;

/* getopt_long stores the option index here. */
static int option_index = 0;


static struct option long_options[] =
{
    /* These options set a flag. */
    {"INSTRUCTION",    no_argument,       0, 'h'},
    {"COMMANDS",    no_argument,       0, 'c'},
    {"TEST",    no_argument,       0, 'u'},
    {"threads", required_argument,  0,  't'},
    {"iteration", required_argument,  0,  'i'},
    {0, 0, 0, 0}
};

int ParseCommandline(int argc , char *argv[], int &commandFlag)
{
    int c;
    commandFlag = 0;
    while(1)
    {
        c = getopt_long (argc, argv, "t:i:huc",
                    long_options, &option_index);

        if(c ==-1) 
        {
            //printf("Usage : ./project [-h] [-u] [-c]\n");
            break; //end of options
        }
        switch (c)
        {
        case 0:
        /* If this option set a flag, do nothing else now. */
        if (long_options[option_index].flag != 0)
            break;

        case 'h':
            {
                commandFlag |= 1<<0;
                //printf("Flag is %d\n",commandFlag);

            }   
        break;
        case 'u':
            {
                commandFlag |= 1<<1;
                //printf("Flag is %d\n",commandFlag);
            }   
        break;
        case 'c':
            {
                commandFlag |= 1<<2;
                //printf("Flag is %d\n",commandFlag);
            }   
        break;
        
        case 't':
            printf("The number of threads to be spawned : %s\n",optarg);
            numOfThreads = atoi(optarg);

        break;

        case 'i':
            printf("The number of nodes per thread : %s\n",optarg);
            iteration = atoi(optarg);

        break;

        case '?':
        /* getopt_long already printed an error message. */
        break;

        default:
        abort ();
        }
    }
    return 0;

}

int FileExistCheck(const char* filename)
{
    if( access( filename, F_OK ) != -1 ) return 1;
    // file exists
    else return 0;
    // file doesn't exist
}



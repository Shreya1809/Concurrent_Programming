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

algotype_t algoType = FORK_JOIN;
int name_flag = 0;
int numOfThreads = 0;

/* getopt_long stores the option index here. */
static int option_index = 0;


static struct option long_options[] =
{
    /* These options set a flag. */
    {"name", no_argument,  &name_flag, 1},
    {"output",    required_argument,       0, 'o'},
    {"threads", required_argument,  0,  't'},
    {"alg", optional_argument, 0 , 'a' },
    {0, 0, 0, 0}
};

int ParseCommandline(int argc , char *argv[], string &srcfile , string &outfile)
{
    int c;
    while(1)
    {
        c = getopt_long (argc, argv, "o:t:a:",
                    long_options, &option_index);

        if(c ==-1) 
        {
            //printf("Usage : ./mysort [--name] [sourcefile.txt] [-o outfile.txt]");
            break; //end of options
        }
        switch (c)
        {
        case 0:
        /* If this option set a flag, do nothing else now. */
        if (long_options[option_index].flag != 0)
            break;
        
        case 'o':
            printf ("Output filename is %s\n", optarg);
            outfile = std::string(strdup(optarg));     
        break;

        case 't':
            printf("The number of threads to be spawned : %s\n",optarg);
            numOfThreads = atoi(optarg);

        break;

        case 'a':
            printf("The algorithm is %s\n",optarg);
            if((strcmp(optarg,"fj")) != 0)
            {
                if((strcmp(optarg,"bucket")) == 0)
                {  
                    algoType = BUCKET_SORT; 
                }
                else
                {
                    printf("Invalid algorithm\n");
                    return 1;
                }
            }
            else
            {
                printf("The algorithm is Fork/Join\n"); 
                algoType = FORK_JOIN;
            }
        break;

        case '?':
        /* getopt_long already printed an error message. */
        break;

        default:
        abort ();
        }
    }

    if (name_flag)
    {
        puts ("--name : My name is Shreya");
        return 1;
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
      //non-option ARGV-elements
      while (optind < argc)
      {
        printf ("Source filename is %s ", argv[optind]);
        srcfile = std::string(argv[optind]);
        optind++;
      }
      putchar ('\n');
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


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
#include "parse.h"
#include "locks.h"
using namespace std;


algotype_t algoType = FORK_JOIN;
bartype_t barType = PTHREAD;
CP::LockType lockType = CP::LockType::MUTEX_LOCK;
//locktype_t lockType = MUTEX_LOCK;
int name_flag = 0;
int numOfThreads = 0;
int numofiterations = 0;
/* getopt_long stores the option index here. */
static int option_index = 0;


static struct option long_options[] =
{
    /* These options set a flag. */
    {"name", no_argument,  &name_flag, 1},
    {"output",    optional_argument,       0, 'o'},
    {"threads", required_argument,  0,  't'},
    {"alg", optional_argument, 0 , 'a' },
    {"bar", required_argument, 0 , 'b' },
    {"lock", required_argument, 0 , 'c' },
    {"iterations", optional_argument, 0 , 'i' },
    {0, 0, 0, 0}
};

int ParseCommandline(int argc , char *argv[], string &srcfile , string &outfile)
{
    int c;
    while(1)
    {
        c = getopt_long (argc, argv, "o:t:a:b:c:i:",
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
            printf ("[Output File]:\t%s\n", optarg);
            outfile = std::string(strdup(optarg));     
        break;

        case 't':
            printf("[Thread Nos]:\t%s\n",optarg);
            numOfThreads = atoi(optarg);

        break;

        case 'a':
            //printf("Algorithm selection optind is %d\n",optind);
            if((strcmp(optarg,"fj")) != 0)
            {
                if((strcmp(optarg,"bucket")) == 0)
                {  
                    printf("[Algorithm]:\tBucket Sort\n");
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
                printf("[Algorithm]:\tFork/Join\n"); 
                algoType = FORK_JOIN;
            }
        break;

        case 'b':
            //printf("The bar option num is %d and option entered is %s\n",optind,optarg);
            if((strcmp(optarg,"sense")) != 0)
            {
                if((strcmp(optarg,"pthread")) == 0)
                {  
                    printf("[Barrier]:\tpthread barrier\n");
                    barType = PTHREAD; 
                }
                else
                {
                    printf("Invalid bar type\n");
                    return 1;
                }   
            }
            else
            {
                printf("[Barrier]:\tSense reversal barrier\n"); 
                barType = SENSE;
            }
        break;

        case 'c':
         //printf("The lock option number is %d and the option entered is %s\n",optind,optarg);
            if((strcmp(optarg,"pthread")) == 0)
            {
                printf("[Lock]:\t\tpthread mutex lock\n");
                lockType = CP::LockType::MUTEX_LOCK;
            }
            else if((strcmp(optarg,"tas")) == 0)
            {
                printf("[Lock]:\t\tTest and Set lock\n");
                lockType = CP::LockType::TAS_LOCK;
            }
            else if((strcmp(optarg,"ttas")) == 0)
            {
                printf("[Lock]:\t\tTest and Test and Set lock\n");
                lockType = CP::LockType::TTAS_LOCK;
            }
            else if((strcmp(optarg,"ticket")) == 0)
            {
                printf("[Lock]:\t\tTicket lock\n");
                lockType = CP::LockType::TICKET_LOCK;
            }
            else if((strcmp(optarg,"mcs")) == 0)
            {
                printf("[Lock]:\t\tMCS lock\n");
                lockType = CP::LockType::MCS_LOCK;
            }
            else 
            {
                printf("Invalid lock type\n");
                return 1;
            }
        
        break;
        case 'i':
            printf("[Iterations]:\t%s\n",optarg);
            numofiterations = atoi(optarg);
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
        printf ("[Src file]:\t%s ", argv[optind]);
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


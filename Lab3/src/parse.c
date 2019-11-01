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

#include "parse.h"

/* getopt_long stores the option index here. */
static int option_index = 0;


static struct option long_options[] =
{
    /* These options set a flag. */
    {"name", no_argument,  &name_flag, 1},
    {"output",     optional_argument,       0, 'o'},
    {0, 0, 0, 0}
};

int ParseCommandline(int argc , char *argv[], char **srcfile ,char **outfile)
{
    int c ;
    while(1)
    {
        c = getopt_long (argc, argv, "o:",
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
        printf("-o option\n");
                if (optarg)
                {
                    printf ("[Output file]:     %s\n", optarg);
                    *outfile = strdup(optarg);
                    output_flag = 1;
                }
                else
                    printf ("Write output to stdout !\n");
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
        printf ("[Source file]:     %s ", argv[optind]);
        *srcfile = argv[optind];
        optind++;
      }
      putchar ('\n');
    }
    if(output_flag == 1)
    {
        return 2;
    }
    else return 0;

}

int FileExistCheck(char* filename)
{
    if( access( filename, F_OK ) != -1 ) return 1;
    // file exists
    else return 0;
    // file doesn't exist
}


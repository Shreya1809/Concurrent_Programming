/**
 * @file parse.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef PARSE_H_
#define PARSE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <string>
using namespace std;

/* Flag set by ‘--name’. */
extern int name_flag;
extern int numOfThreads;
typedef enum _algoType{
    FORK_JOIN = 0,
    BUCKET_SORT
}algotype_t;

extern algotype_t algoType;

/**
 * @brief checks existence of file
 * 
 * @param filename 
 * @return int 
 */
int FileExistCheck(const char* filename);

/**
 * @brief takes the argument count, argument parses thhem using getopt_long 
 * retrieves the input file, name flag option and output file from the
 * optional argument
 * 
 */
int ParseCommandline(int argc , char *argv[], string &srcfile , string &outfile);

#endif
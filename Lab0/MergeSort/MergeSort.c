/**
 * @file MergeSort.c
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


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>

/* Flag set by ‘--name’. */
static int name_flag;
static int output_flag;

struct node 
{
    int data;
    struct node* next;
};

struct node* head = NULL;

int addtolist(struct node** head,int data) //add to tail
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;

    if(head == NULL)//invalid
    {
       return -1; 
    }
    if(*head == NULL)// list is empty
    {
        //printf("List is empty\n");
        *head = new_node;
        return 1;
    }
    //list has some entries, go to the last entry
    struct node* temp = *head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
    return 0;

}

int DisplayList(struct node **head)
{
    if(head == NULL)
    {
        return -1;
    }
    if(*head == NULL)
    {
        printf("List is Empty\n");
        return 1;
    }
    struct node* temp = *head;
    while(temp != NULL)
    {
        printf("%d\t",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int DisplayListStdio(struct node **head)
{
    if(head == NULL)
    {
        return -1;
    }
    if(*head == NULL)
    {
        printf("List is Empty\n");
        return 1;
    }
    struct node* temp = *head;
    while(temp != NULL)
    {
        printf("%d\n",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int SplitList(struct node *head,struct node **list1,struct node **list2)
{
    struct node *p = head->next;
    struct node *q = head;
    while(p != NULL)
    {
        p = p->next;
        if(p != NULL)
        {
            p = p->next; 
            q = q->next;    
        }
          
    }
    *list1 = head;
    *list2 = q->next;
    q->next = NULL;
    return 0;

}

struct node* Merge(struct node* list1,struct node* list2)
{
    struct node* MergedList = NULL;
    if(list1 == NULL) // is either list exhausts, return the elements of the other
        return list2;
    if(list2 == NULL)
        return list1;
    
    if(list1->data < list2->data)
    {
        MergedList = list1;// list1 has smaller integer, add that node to the resultant node
        MergedList->next = Merge(list1->next,list2);//compare the next element of list1 with list 2
    }
    else
    {
        MergedList = list2;// list2 has smaller integer, add that node to the resultant node
        MergedList->next = Merge(list1,list2->next);//recursive call ,compare the next element of list1 with list 2   
    }
    return MergedList;

}

void MergeSort(struct node **head)
{
    struct node* temp = *head;
    struct node* list1;
    struct node* list2;
    if(temp == NULL)
    {
        //length is 0
        return;
    }
    if(temp->next == NULL)
    {
        //length is 1
        return;
    }
    //find middle of the list and split
    SplitList(temp,&list1,&list2);
    MergeSort(&list1);
    MergeSort(&list2);
    *head = Merge(list1,list2);
}

int FileExistCheck(char* filename)
{
    if( access( filename, F_OK ) != -1 ) return 1;
    // file exists
    else return 0;
    // file doesn't exist
}


int main( int argc , char *argv[])
{
    printf("Mergesort Algorithm by Shreya\n");
    int c, num = 0;
    char srcfilepath[30];
    char outfilepath[30];
    char *srcfile,*outfile;
    char ch;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int data = 0;

    FILE *fp, *fp2;
    static struct option long_options[] =
        {
          /* These options set a flag. */
          {"name", no_argument,  &name_flag, 1},
          {"output",     optional_argument,       0, 'o'},
          {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
    int option_index = 0;

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
                    printf ("Output filename is %s\n", optarg);
                    outfile = strdup(optarg);
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
    puts ("--name : My name is Shreya");

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
      //printf ("non-option ARGV-elements: ");
      while (optind < argc)
      {
        printf ("Source filename is %s ", argv[optind]);
        srcfile = argv[optind];
        optind++;
      }
      putchar ('\n');
    }

    sprintf(srcfilepath,"../bin/%s",srcfile);
    sprintf(outfilepath,"../bin/%s",outfile);
    
    if(FileExistCheck(srcfilepath))
    {
        printf("The file exists\n");
    }
    fp = fopen(srcfilepath, "r"); // read mode
 
    if (fp == NULL)
    { 
        perror("Error while opening the file\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%d", &data); 
        addtolist(&head,data);

    }
    fclose(fp);
    printf("The list of integers is as follows:\n");
    DisplayList(&head);
    MergeSort(&head);

    if(output_flag)
    {
        fp2 = fopen(outfilepath, "w+");
        if(fp2 == NULL)
        {
            printf("Failed to create output file\n");
            exit(EXIT_FAILURE);
        }
        else{
            printf("Writing sorted integers to output file\n");
            while(head != NULL)
            {
                fprintf(fp2,"%d\n",head->data);
                head = head->next;
            }
            fclose(fp2);
        }
    }
    else{
        printf("The Mergesorted list is as follows: \n");
        DisplayListStdio(&head);
    }
    
    printf("Program Done\n");
    
    if (line)
        free(line);
return 0;
}
    


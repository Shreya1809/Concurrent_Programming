#include "commandhandler.h"
#include "fg_tree.h"

void Instructions(void)
{
    printf("The project supports both single threaded and multi threaded modes\n");
    printf("The operations get,put and range require user inputs in single threaded mode\n");
    printf("To run this project in single threaded mode -> ./project -h -u -c\n");
    printf("The options do not require any arguments\n");
    printf("-h -> Provides execution instrructions\n");
    printf("-u -> Runs various tests on the command APIs\n");
    printf("-c -> Asks for user command from the options\n");
    printf("In multi threaded mode, the concurrency of the project is tested hence the key and values are acquired randomly\n");
    printf("To run this project in multi threaded mode -> ./project -t10 -i20\n");
    printf("-t -> requires num of threads to spawn as arguments\n");
    printf("-i -> requires number of  (tree)nodes or key/value pairs per thread for workload increase\n");
    printf("-l -> To see the internal print statments, no argument required\n");
    printf("Thats all\n");
}

void Testing(void)
{
    printf ("All the unit tests are as follows--------->\n");
    FG_TestNodeCreation();
    FG_TestPut();
    FG_TestGet(9999);
    //TestDeleteEntry(9999);
    FG_TestRange(15,85);   
}

void ActualWork(int commandFlag)
{
    if(commandFlag == 1) //instructions
    {
        Instructions();       
    }
    if(commandFlag == 2)
    {
        Testing();        
    }
    if(commandFlag == 3)
    {
        Instructions(); 
        Testing();  
    }
    if(commandFlag == 4)
    {
        Commands();
    }
    if(commandFlag == 5)
    {
        Instructions();
        Commands();
    }
    if(commandFlag == 6)
    {
        Testing();
        Commands();
    }
    if(commandFlag == 7)
    {
        Instructions();
        Testing();
        Commands();
    }
    
}

void Commands(void)
{
    //Adding random nodes and displaying it for user
    string userinput;
    struct fg_treenode *root = NULL; 
    srand(time(0));
    int num = rand()%50;
    char mytext[10];
    for(int i = 1; i < num+1; i++ )
    {
        //root = PutEntry(root, rand_key()%i , rand_value(mytext, sizeof(mytext), i));
        FG_Insert_char(&root, rand_key()%i, rand_value(mytext, sizeof(mytext), i));
    }
    printf("*******************************************\n");
    printf("The Entries in the Database are as follows:\n");
    FG_InorderDisplay(root);
    printf ("Enter any one of the options from below:\n");
    printf("1. GET <key>\n");
    printf("2. PUT <key value>\n");
    printf("3. RANGE <key1 key2>\n");
    printf("For eg, GET 100 or Range 5 42 or PUT 100 SHREYA : \n");
    printf("Spaces in value are not accepted, to exit type 'X'\n");
    NEXT: printf("Enter Command =>\n");
    getline(cin, userinput);
    cout << "you entered -> " << userinput << endl;
    vector<string> res = splitStrings(userinput, ' '); 
	cout << "Command :"<< res[0] << endl; 
	if(res[0]!= "GET" && res[0]!= "PUT" && res[0]!= "RANGE" && res[0]!= "X") //error handling for method
	{
		cout << "Invalid command" << endl;
		exit(1);

	}
    if(res[0]== "X")
    {
        printf("Exiting...\n");
    }
    if(res[0]== "GET") //handling for POST -extra components in the request
	{
        if(res[1].size() != 0)
        {
            cout << "Key to GET :"<< res[1] << endl;
            int key = stoi(res[1]); 
            if(FG_searchTree(root,key))
            {
                printf("Value: %s\n",FG_GetValue_char(root, key));
            }
            else
            {
                printf("Key does not exist in the database\n");
            }
        }
        else
        {
            printf("Valid integer Key required\n");    
        }
        goto NEXT;   
    }
    
    if(res[0]== "PUT") //handling for POST -extra components in the request
	{
        if((res[1].size() != 0) && (res[2].size() != 0))
        {
            int key = stoi(res[1]);
            cout << "Entry to insert -> Key: "<< res[1] <<  " Value: " << res[2] << endl; 
            if(FG_searchTree(root,key))
            {
                printf("Key already exists, overwriting it\n");
                //root = DeleteEntry(root, key); 

            }
            //root = PutEntry(root, key , res[2].c_str()); 
            FG_Insert_char(&root, key, (char*)res[2].c_str());
            printf("Entry added to Database:\n");
            FG_InorderDisplay(root);
        }
        else
        {
            printf("Valid Key and Value BOTH are required\n");            
        }
        goto NEXT;
    }

    if(res[0]== "RANGE") //handling for POST -extra components in the request
	{
        if((res[1].size() != 0) && (res[2].size() != 0))
        {
            int key1 = stoi(res[1]); 
            int key2 = stoi(res[2]); 
            if((FG_searchTree(root,key1)) && (FG_searchTree(root,key2)))
            {
                cout << "Range of all key/value pairs from -> Key1: "<< res[1] <<  " to Key2: " << res[2] << endl;
                FG_Range(root, key1, key2,0,1); 
            }
            else
            {
                printf("One or more keys do not exist in data base\n");
            }  
        }
        else
        {
            printf("Valid Key1 and Key2 BOTH are required\n");            
        }
        goto NEXT;
    } 


}
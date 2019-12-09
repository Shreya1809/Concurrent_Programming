#include "commandhandler.h"

void Instructions(void)
{
    printf("Execution instructions are as follows-------->\n");
    printf("To run this project -> ./project -h -u -c\n");
    printf("The options do not require any arguments\n");
    printf("-h -> Provides execution instrructions\n");
    printf("-u -> Runs various tests on the project\n");
    printf("-c -> Asks for user command from the options\n");
    printf("Thats all\n");
}

void Testing(void)
{
    printf ("All the unit tests are as follows--------->\n");
    TestNodeCreation();
    TestPutEntry();
    TestGetValue(9999);
    TestDeleteEntry(9999);
    TestRangeQuery(15,85);   
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
    struct treenode *root = NULL; 
    srand(time(0));
    int num = rand()%50;
    char mytext[10];
    for(int i = 1; i < num+1; i++ )
    {
        root = PutEntry(root, rand_key()%i , rand_value(mytext, sizeof(mytext), i));
    }
    printf("*******************************************\n");
    printf("The Entries in the Database are as follows:\n");
    InorderDisplay(root);
    printf ("Enter any one of the options from below:\n");
    printf("1. GET <key>\n");
    printf("2. PUT <key value>\n");
    printf("3. RANGE <key1 key2>\n");
    printf("4. DEL <key>\n");
    printf("For eg, GET 100 or Range 5 42 or PUT 100 SHREYA : \n");
    printf("Spaces in value are not accepted\n");
    getline(cin, userinput);
    cout << "you entered -> " << userinput << endl;
    vector<string> res = splitStrings(userinput, ' '); 
	//cout << "vector size: "<<HTTP_req<<endl;
	cout << "Command :"<< res[0] << endl; 
	if(res[0]!= "GET" && res[0]!= "PUT" && res[0]!= "RANGE" && res[0]!= "DEL") //error handling for method
	{
		cout << "Invalid command" << endl;
		exit(1);

	}
    if(res[0]== "GET") //handling for POST -extra components in the request
	{
        if(res[1].size() != 0)
        {
            cout << "Key to GET :"<< res[1] << endl;
            int key = stoi(res[1]); 
            if(KeySearch(root,key))
            {
                printf("Value: %s\n",GetValue(root, key));
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
        
    }

    if(res[0]== "PUT") //handling for POST -extra components in the request
	{
        if((res[1].size() != 0) && (res[2].size() != 0))
        {
            int key = stoi(res[1]);
            cout << "Entry to insert -> Key: "<< res[1] <<  " Value: " << res[2] << endl; 
            if(KeySearch(root,key))
            {
                printf("Key already exists, overwriting it\n");
                root = DeleteEntry(root, key); 

            }
            root = PutEntry(root, key , res[2].c_str()); 
            printf("Entry added to Database:\n");
            InorderDisplay(root);
        }
        else
        {
            printf("Valid Key and Value BOTH are required\n");            
        }
    }

    if(res[0]== "DEL") //handling for POST -extra components in the request
	{
        if(res[1].size() != 0)
        {
            int key = stoi(res[1]);
            if(KeySearch(root,key))
            {
                cout << "Entry to Delete -> Key: "<< res[1] << endl;
                root = DeleteEntry(root, key); 
                printf("Entry deleted, the current contents of the Database:\n");
                InorderDisplay(root);
            }
            else
            {
                printf("Entry to delete does not exist in the database\n");
            }
        }
        else
        {
            printf("Valid Key to delete required\n");            
        }
    }

    if(res[0]== "RANGE") //handling for POST -extra components in the request
	{
        if((res[1].size() != 0) && (res[2].size() != 0))
        {
            int key1 = stoi(res[1]); 
            int key2 = stoi(res[2]); 
            if((KeySearch(root,key1)) && (KeySearch(root,key2)))
            {
                cout << "Range of all key/value pairs from -> Key1: "<< res[1] <<  " to Key2: " << res[2] << endl;
                RangeQuery(root, key1, key2); 
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
    } 


}
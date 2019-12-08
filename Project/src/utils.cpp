#include "utils.h"

vector<string> splitStrings(string str, char dl) //REFERENCE - https://www.geeksforgeeks.org/split-string-substrings-using-delimiter
{ 
	string word = ""; 

	// to count the number of split strings 
	int num = 0; 

	// adding delimiter character at the end 
	// of 'str' 
	str = str + dl; 

	// length of 'str' 
	int l = str.size();
	//cout << "length of entered string including spaces :" << l << endl; 
	//cout<< "string :" << str << endl;

	// traversing 'str' from left to right 
	vector<string> substr_list; 
	for (int i = 0; i < l; i++) { 

		// if str[i] is not equal to the delimiter 
		// character then accumulate it to 'word' 
		if (str[i] != dl && str[i] != '\r') 
			word = word + str[i]; 

		else { 

			// if 'word' is not an empty string, 
			// then add this 'word' to the array 
			// 'substr_list[]' 
			if ((int)word.size() != 0) 
				substr_list.push_back(word); 

			// reset 'word' 
			word = ""; 
		} 
	} 

	// return the splitted strings 
	return substr_list; 
} 

char *rand_value(char *dst, int size, int number)
{
   static const char text[] = "abcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()_+}{:?<>"
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890~`!@#$%^&*()-=|<>/?";
   int i;
   for ( i = 0; i < (size -1) ; i++ )
   {
      dst[i] = text[(rand() % (sizeof(text)-1))];
	//   dst[i] = (rand() % 25) + 'a';
   }
   dst[size -1] = '\0';
   return dst;
}

int rand_key(void)
{
    //srand(time(0)); 
    return (rand() % 1000);
}
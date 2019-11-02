#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "recipe.h"

using namespace std;

struct Category
{
   string name;
   double amount;
};

ostream & operator << (ostream &out, const Category &c)
{
   out << setw(20) << c.name << c.amount << endl;
}

/*****************************************************
 * File-Doesnt-Exist
 * returns whether or not the necessary start-up files
 * exist for use in the startUp() function.
 ****************************************************/
bool fileDoesntExist()
{
   ifstream file;
   file.open("budgetNumbers.txt");
   return file.fail();   
}

/*****************************************************
 * Start-up
 * Begins by creating a file to write data necessary
 * for each run. It will contain the default values
 * to start but the rest of the program will alter
 * the information. This information is read into
 * a vector and returned for further use in the 
 * program.
 *
 * The data to be stored are things like
 *  - Monthly Income
 *  - Grocery Costs
 *  - Housing expenses
 *  - ETC...
 ****************************************************/
vector <Category> startUp()
{
   if (fileDoesntExist())
   {
      cout << "File does not exist" << endl;

      ofstream writeToFile("budgetNumbers.txt");
      cout << "File created" << endl;

      writeToFile << "1 Monthly Income 0" << endl
	          << "2 Housing Cost 0" << endl
                  << "3 Power 0" << endl
		  << "4 Gas 0" << endl
		  << "5 Automotive 0" << endl
		  << "6 Personal Expenses 0" << endl;
   }

   //Parse start-up file for previous money values
   ifstream fromFile("budgetNumbers.txt");

   string word;

   vector <Category> expenseInfo;

   //Load money values and categories into a vector of 'Category' structs
   //for usage with rest of program
   while (!fromFile.eof())
   {
      Category temp;
      while (fromFile >> word)
      {
         stringstream toCategory;
	 toCategory << word;

	 if (toCategory >> temp.amount)
	 {
            expenseInfo.push_back(temp);
	    toCategory.clear();
	    break;
	 }
	 else
	 {
	    temp.name += word;
	    temp.name += " ";
	 }

	 toCategory.clear();
      }
   }


   return expenseInfo;
} //end of startUp()

/*****************************************************
 * Prine-Budget
 * Expects a vector of type 'Category' and prints
 * the contents into a right aligned column.
 *
 * Returns nothing.
 ****************************************************/
void printBudget(vector <Category> expenseInfo)
{
   cout << setfill('*') << setw(80) << "*" << endl
        << setfill(' ') << setw(47) <<  "Current Budget: " << endl
        << setfill('*') << setw(80) << "*" << endl;
   cout << setfill(' ');
   for (auto it = expenseInfo.begin(); it != expenseInfo.end(); ++it)
   {
      cout << *it;
   }
}

/*****************************************************
 * Print-Help
 * Prints the help menu to inform the user acceptable
 * commands to type into the program.
 * 
 * Returns nothing
 ****************************************************/
void printHelp(int help)
{
	if (help == 1)
	{
           cout << "Type these keywords to adjust your budget: " << endl
	
        	<< "  Manage Categories"
                << setw(50) << " - Add, delete, or rename a category." << endl
        	<< "  Change <Insert Category Here>"
                << "  - Change the inserted categories expense." << endl;
	}
	else if (help == 2)
	{
	   cout << "To Manage Categories, please type one of the following..."
		<< endl;
	   cout << "  Add <Insert Category Name>    - Adds a Category" << endl;
	   cout << "  Delete <Insert Category Name> - Deletes a Category" << endl;
	   cout << "  Modify <Insert Category Name> - Change the name of a Category" << endl << endl;
	}
}

/*****************************************************
 * Lower-Case
 * Expects a string and lowercases all characters.
 *
 * Returns the string with all letters lowercased.
 ****************************************************/
string lowerCase(string userInput)
{
   for (int i = 0; i < userInput.size(); i++)
   {
      userInput[i] = tolower(userInput[i]);
   }

   return userInput;
}

/*****************************************************
 * Find
 * expects a string name of an item to be found
 * in the vector of type 'Category.'
 *
 * returns an integer index. If found, the int will
 * be positive, if not, the integer will be negative.
 ****************************************************/
int find(string item, vector <Category> categories)
{
   item += " ";
   for (int i = 0; i < categories.size(); i++)
   {
      if (item == lowerCase(categories[i].name))
      {
         return i;
      }
   }

   return -1;
}

int main()
{
   vector <Category> expenseInfo = startUp();

   string userInput;
   string previousMessage;

   while (userInput != "quit")
   {
      system("clear");

      printBudget(expenseInfo);
      cout << endl;
      printHelp(1);
      cout << endl << endl;

      if (!previousMessage.empty())
      {
         cout << previousMessage << endl << endl;
      }
      else
      {
         cout << endl << endl;
      }
      cout << "What would you like to do? ";
      getline(cin, userInput);


      userInput = lowerCase(userInput);
      string sTemp = userInput.substr(0,6);


      if (userInput == "manage categories")      //Add or delete a category.
      {
         system("clear");
	 printBudget(expenseInfo);
	 cout << endl;
	 printHelp(2);
	 cout << endl << endl;

	 string userInput;
	 cout << "What would you like to do? ";
         getline(cin, userInput);

	 userInput = lowerCase(userInput);

	 string userInputFront = lowerCase(userInput.substr(0, 3));
	 string userInputBack = lowerCase(userInput.substr(3));
	 string userInputBackU = userInput.substr(3);


	 if (userInputFront == "add")
         {
            Category cTemp;

	    cTemp.name = userInputBackU;
	    cTemp.name += " ";

	    cout << "How much will be spent in this Category? ";
	    cin >> cTemp.amount;

	    expenseInfo.push_back(cTemp);
	 }   //end of add condition
	 else if (userInputFront == "del")
	 {
            userInputBack.erase(0, 4);

	    int index = find(userInputBack, expenseInfo);
            vector <Category>::iterator vit = expenseInfo.begin();
	    
	    for(int i = 0; i <= index; ++vit, i++)
	    {
	       if (index == 0)
	       {
	          break;
	       }
	    }

            expenseInfo.erase(vit);
	 }   //end of delete condition
	 else if (userInputFront == "mod")
	 {
            userInputBack.erase(0, 4);
            userInputBack = lowerCase(userInputBack);

	    int index = find(userInputBack, expenseInfo);

            cout << "What is the new name of the Category? ";
	    getline(cin, expenseInfo[index].name);

	    expenseInfo[index].name += " ";
	 }   //end of modify condition
      }
      else if(sTemp == "change")                  //Change the category expense
      {                                          //amount.
         sTemp = userInput.substr(7);
         int index = 0;
	 try
	 {
	    index = find(sTemp, expenseInfo);

	    if (index < 0)
	    {
	       throw "Category not found. Try again.";
   	    }
	 }
   	 catch (const char* message)
	 {
            previousMessage = message;
            cout << message << endl;
	    continue;
	 }

	 previousMessage.clear();

	 cout << "What is the new dollar amount? ";
         cin >> expenseInfo[index].amount;

      }
      else if (sTemp == "quit")
      {
         ofstream fout;

	 fout.open("budgetNumbers.txt");

	 for (int i = 0; i < expenseInfo.size(); i++)
	 {
            fout << expenseInfo[i].name << expenseInfo[i].amount << endl;
	 }

	 fout.close();
      }
      else
      {
         cout << "I don't know what that means" << endl;
      }
   }
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "stringManip.h"
#include "recipe.h"
#include "ingredient.h"
#include "category.h"
#include "recipeCategory.h"

using namespace std;

struct googleSheetCategories
{
    string name;
    double total;
};

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
   int i = 0;
   while (!fromFile.eof())
   {
      Category temp;
      while (fromFile >> word)
      {
         stringstream toCategory;
	     toCategory << word;
	     if (toCategory >> temp.amount)
	     {
		    i++;
            expenseInfo.push_back(temp);
	        toCategory.clear();
	        break;
	     }
	     else
	     {
	        temp.name += word;
	        temp.name += ' ';
	     }

	     toCategory.clear();
      }
   }

   return expenseInfo;
} //end of startUp()

vector <googleSheetCategories> googleSheetStartUp()
{
    cout << "Connecting to Google Sheet...." << endl;
    system("python \"../../Users/lette/PycharmProjects/GoogleAPI interact/GoogleAPI Interact.py\" Start-up");

    ifstream file("googleSheet.txt");

    int i = 0;
    while (file.fail())
    { 
        cout << "Unable to open googleSheet.txt" << endl;

        file.open("googleSheet.txt");

        i++;

        if (i == 5)
        {
            cout << "Was unable to open googleSheet.txt after " << i << " tries." << endl;
            cin.get();
            vector <googleSheetCategories> gsCategories;
            return gsCategories;
        }
    }

    string word;
    vector <googleSheetCategories> gsCategories;

    i = 0;
    while (file >> word)
    {
        if (i == 8) //We have reached the end of the first line.
        {           //The first line is just the names.
            break;
        }

        googleSheetCategories temp;
        while(word != "e_cell")
        {
            temp.name += word;
            temp.name += ' ';
            file >> word;
        }

        temp.name.erase(temp.name.end());
        gsCategories.push_back(temp);
        i++;
    }

    //Begin loading totals
    i = 0;
    while (file >> word)
    {
        if (word == "Totals:")
        {
            while (!(i >= gsCategories.size()))
            {
                file >> word;
                if (word == "e_cell")
                {
                    continue;
                }
                
                word.erase(word.begin());
                stringstream ss;

                ss << word;
                double amount;
                ss >> amount;
                gsCategories[i].total = amount;
                i++;
            }
        }
    }

    file.close();

//    for (size_t j = 0; j < gsCategories.size(); j++)
//    {
//        cout << gsCategories[j].name << endl;
//        cout << gsCategories[j].total << endl << endl;
//    }


    return gsCategories;
}

/*****************************************************
 * Print-Budget
 * Expects a vector of type 'Category' and prints
 * the contents into a right aligned column.
 *
 * Returns nothing.
 ****************************************************/
void printBudget(vector <Category> expenseInfo, vector <googleSheetCategories> secondary)
{
   cout << setfill('*') << setw(120) << "*" << endl
        << setfill(' ') << setw(67) <<  "Current Budget: " << endl
        << setfill('*') << setw(120) << "*" << endl;
   cout << setfill(' ');

   Category leftOver;
   leftOver.setName("Unused Money ");
   leftOver.setAmount(expenseInfo.front().getAmount());

   int i = 0;
   int column2 = expenseInfo[0].numDigits() - 6;

   for (auto it = expenseInfo.begin(); it != expenseInfo.end(); ++it)
   {
      if (((i + 1) % 2) == 0)   //Second Column
      {
         (*it).printCategory(0, i);
         cout << setw(16 - expenseInfo[i].numDigits()) << secondary[i].total;
         cout << endl;
      }
      else   //First Column
      {
         (*it).printCategory(0, i);
         cout << setw(16 - expenseInfo[i].numDigits()) << secondary[i].total;
      }

      if (i != 0)   //To get how much money is left over, we subtract all expenses which
      {             //are all the categories after the first one.
         leftOver - *it;
      }

      i++;
   }

   cout << endl << endl;
   leftOver.printCategory();
   cout << endl;

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
	   
	   cout << "  Recipes"
	        << "  - Enter recipes menue for dinner planning and shopping."
		                                                 << endl;
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
   for (size_t i = 0; i < categories.size(); i++)
   {
      if (i >= categories.size())
      {
          break;
      }
      else if (item.find(categories[i].getName()) != string::npos) 
      {
          return i;
      }
   }

   return -1;
}

/*****************************************************
 * findGoogle
 * expects a string name of an item to be found
 * in the vector of type 'googleSheetCategories'.
 *
 * returns an integer index. If found, the int will
 * be positive, if not, the integer will be negative.
 ****************************************************/
int findGoogle(string item, vector <googleSheetCategories> categories)
{
    for (size_t i = 0; i < categories.size(); i++)
    {
        if (i >= categories.size())
        {
            break;
        }
        else if (item.find(categories[i].name) != string::npos)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
   vector <Category> expenseInfo = startUp();
   vector <googleSheetCategories> gsCategories = googleSheetStartUp();

   //Determine how much money is left over after subtracting
   //the total money spent from each category.
   for (size_t i = 0; i < gsCategories.size(); i++)   //Used to make sure that categories from the spreadsheet
   {                                                  //are known in the program.
       gsCategories[i].name.erase(gsCategories[i].name.end());
       if (find(gsCategories[i].name, expenseInfo) < 0)
       {
           Category cTemp;

           cTemp.setName(gsCategories[i].name);
           cTemp.setAmount(gsCategories[i].total);

           expenseInfo.push_back(cTemp);
       }
   }

   vector <googleSheetCategories> leftOver;

   for (size_t i = 0; i < expenseInfo.size(); i++)
   {
       int index = findGoogle(expenseInfo[i].getName(), gsCategories);
       if (index < 0)
       {
           googleSheetCategories temp;
           temp.name = "Not Found";
           temp.total = 0;
           leftOver.push_back(temp);
       }
       else
       {
           googleSheetCategories temp;
           temp.name = expenseInfo[i].getName();
           temp.total = expenseInfo[i].getAmount() - gsCategories[index].total;
           leftOver.push_back(temp);
       }
   }

   for (size_t i = gsCategories.size(); i < expenseInfo.size(); i++)
   {
       googleSheetCategories temp;
       temp.name = "Not Found";
       temp.total = 0;
       leftOver.push_back(temp);
   }


   string userInput;
   string inputErrorMessage;

   while (userInput != "quit")
   {
      system("CLS");

      printBudget(expenseInfo, leftOver);
      cout << endl;

      printHelp(1);
      cout << endl << endl;

      if (!inputErrorMessage.empty())
      {
         cout << inputErrorMessage << endl << endl;
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
	     inputErrorMessage.clear();
         system("CLS");
	     printBudget(expenseInfo, leftOver);
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

	        cTemp.setName(userInputBackU);

	        cout << "How much will be spent in this Category? ";
	        double dTemp;
	        cin >> dTemp;
	        cTemp.setAmount(dTemp);

	        expenseInfo.push_back(cTemp);
	     }   //end of add condition
	     else if (userInputFront == "del")
	     {
            userInputBack.erase(0, 4);

	        int index = find(userInputBack, expenseInfo);
            vector <Category>::iterator vit = expenseInfo.begin();
	    
	        //Moves the iterator to desired Category for deletion
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
            
            if (index < 0)
            {
                inputErrorMessage = "Unable to find Category.";
                continue;
            }

            cout << "What is the new name of the Category? ";
	        string nTemp;
	        getline(cin, nTemp);

	        expenseInfo[index].setName(nTemp);
	     }   //end of modify condition
      }
      else if(sTemp == "change")                  //Change the category expense
      {                                          //amount.
         int index = 0;

	     try
	     {
	        sTemp = userInput.substr(7);

	        if (sTemp.empty())
	        {
               throw "Passed string is empty. Try again";
	        }

	        index = find(sTemp, expenseInfo);
	        if (index < 0)
	        {
	           throw "Category not found. Try again.";
   	        }
	     }
   	     catch (const char* message)
	     {
            inputErrorMessage = message;
	        continue;
	     }

	     inputErrorMessage.clear();

	     cout << "What is the new dollar amount? ";
	     double dTemp;
         cin >> dTemp;
	     expenseInfo[index].setAmount(dTemp);

      }
      else if (sTemp == "quit")
      {
         ofstream fout;

	     fout.open("budgetNumbers.txt");

	     for (size_t i = 0; i < expenseInfo.size(); i++)
	     {
            fout << expenseInfo[i].getName() << expenseInfo[i].getAmount();
	        fout << endl;
	     }

	     fout.close();
      }
      else if (userInput == "recipes")
      {
         recipeManip();   //Code for manipulation with the recipes is
      }                   //in recipe.cpp
      else
      {
         inputErrorMessage = "I don't know what that means";
      }
   }
}

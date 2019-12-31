#include <string>
#include <list>
#include <fstream>         //ifstream
#include <sstream>         //stringstream
#include <iostream>
#include <iomanip>         //setw(), setfill()

#include "ingredient.h"
#include "recipe.h"
#include "stringManip.h"   //lowerCase()
#include "recipeCategory.h"
#include "shoppingList.h"

using namespace std;

Recipe::Recipe()
{
   totalCost = 0;
}

Recipe::Recipe(const Recipe & rhs)
{
   if (!rhs.getName().empty())
   {
      this->name = rhs.getName();
   }

   this->totalCost = rhs.getTotalCost();
   
   if (!rhs.getInstructions().empty())
   {
      this->instructions = rhs.getInstructions();
   }
  
   if (!rhs.getIngredients().empty())
   {
      ingredients = rhs.getIngredients();
   }
}

/******************
 * SETTERS
 *****************/

void Recipe::setName(string name)
{
   this->name = name;
}

void Recipe::setTotalCost(double totalCost)
{
   this->totalCost = totalCost;
}

void Recipe::addItem(Ingredient newItem)
{
   ingredients.push_back(newItem);
}

void Recipe::setInstructions(string instructions)
{
   this->instructions += instructions;
   this->instructions += " ";
}

/******************
 * GETTERS
 *****************/

string Recipe::getInstructions() const
{
   return instructions;
}

string Recipe::getName() const
{
   return name;
}

double Recipe::getTotalCost() const
{
   return totalCost;
}

vector <Ingredient> Recipe::getIngredients() const
{
   return ingredients;
}

vector <Ingredient> &Recipe::getIngredients()
{
   return ingredients;
}

bool Recipe::empty()
{
   if (name.empty() && ingredients.empty())
   {
      return true;
   }
   else
   {
      return false;
   }
}

/***************************
 * Other necessary Functions
 **************************/

/******************************************************************************
   recipePath()
*******************************************************************************

    Parameters:
    None.

    Returns:
    A vector of strings containing the file paths of all recipes.

    Originally this program was developed on a linux machine. The recovery
    of the program when "recipe_filePath.txt" doesn't exist requires a working
    bash command. If successful, the bash script will create a .txt file
    containing the file paths of the recipes.

    if the ifstream finds the file, it reads in the file paths from
    "recipe_filePath.txt" and returns the vector of strings.
******************************************************************************/
vector <string> recipePath()
{

   ifstream fin;
 

   fin.open("recipe_filePath.txt");

   if (fin.fail())
   {
       system("bash recipe_fileNames.sh");
       int i = 0;
       while (i < 5 && fin.fail())
       {
           fin.clear();
           fin.open("recipe_filePath.txt");

           if (fin.fail())
           {
               system("bash recipe_fileNames.sh");
           }
           i++;
       }

       if (fin.fail())
       {
           cout << "bash recipe_fileName.sh failure" << endl;
       }
   }

   vector <string> fileNames;
   string filePath;

   while (!fin.eof())
   {
      getline(fin,filePath);
      fileNames.push_back(filePath);
      filePath.clear();
   }

   return fileNames;
}

/******************************************************************************
   parseFile()
*******************************************************************************

   Parameters:
   string filePath

   Returns:
   A constructed recipe object

   parseFile() opens the passed filePath and reads in all necessary recipe
   information into the recipe object and returns it.
******************************************************************************/
Recipe parseFile(string filePath)
{
   ifstream fin;
   Recipe recipe;

   try
   {
      fin.open(filePath);

      if (fin.fail())
      {
         throw filePath;
      }
   }
   catch (string unopened)
   {
      cout << "Unable to open " << unopened << endl;
   }

   string word;

   while (!fin.eof()) //Initial reading of the file
   {
      int i = 0;   //used to gather the name of the recipe
      while (!fin.eof()) 
      {
	     getline(fin, word);
	     if (i == 0)
	     {	 
            recipe.setName(word);
            i++;
	     }

         string lower = lowerCase(word);

         if (lower.find("ingredients:") != string::npos)
         {
            word.clear();

            while (getline(fin, word))  //begin to gether ingredients
	        {
               Ingredient ingredient;

	           lower.clear();
               lower = lowerCase(word);

	           if (lower == "instructions:")
               {
                  while (!fin.eof())  //begin to gather instructions
                  {
	                 getline(fin, word); 
                     recipe.setInstructions(word);
                  }
               }
               else
               {
                  ingredient.setName(word);
                  recipe.addItem(ingredient);  //Add ingredient to recipe
               }

      
	        }
         }   //end of Ingredients conditional

      }   //end of single recipe loading while loop
   
   }   //end of initial While Loop
   fin.close();

   return recipe;
}

/******************************************************************************
   printRecipeMenu()
*******************************************************************************

   Parameters:
   None.

   Returns:
   None.

   printRecipeMenu() prints the menu for the user to interact with.
   All recipe categories are printed and instructions for how to interact with
   the program.
*******************************************************************************/
void printRecipeMenu(vector <RecipeCategory> categories)
{
    cout << setfill('*') << setw(120) << "*" << endl
        << setfill(' ') << setw(66) << "Recipe Menu " << endl
        << setfill('*') << setw(120) << "*" << endl;
    cout << setfill(' ');


    //Begin printing the categories in this format....
    //     "Category Name" ("Category Size")
    //           eg. Appetizers (9)

    int j = 1;
    for (size_t i = 0; i < categories.size(); i++)
    {
        if (categories[i].getName().empty())
        {
            continue;
        }
        if (j % 2 == 1)
        {
            if ((i + 1) % 3 == 0)
            {
                if (categories[i - 1].getSize() / 10 >= 1)  //column 2 is double digit
                {
                    cout << setw(31) << categories[i] << endl;
                }
                else                                        //column 2 is single digit
                {
                    cout << setw(32) << categories[i] << endl;
                }
                j++;
            }
            else if ((i + 1) % 2 == 0) //Note to self: On second iteration, column one had an (i + 1) = 4. This 'else if' runs on the first column every other iteration.
            {
                if (categories[i - 1].getSize() / 10 >= 1)  //column 1 is double digit
                {
                    cout << setw(31) << categories[i];
                }
                else                                        //column 1 is single digit
                {
                    cout << setw(32) << categories[i];
                }
            }
            else
            {
                cout << setw(25) << categories[i];
            }
        }
        else
        {
            if ((i + 1) % 3 == 0)
            {
                if (categories[i - 1].getSize() / 10 >= 1)  //column 2 is double digit
                {
                    cout << setw(31) << categories[i] << endl;
                }
                else                                        //column 2 is single digit
                {
                    cout << setw(32) << categories[i] << endl;
                }
                j++;
            }
            else if ((i + 1) % 2 == 1)
            {
                if (categories[i - 1].getSize() / 10 >= 1)  //column 1 is double digit
                {
                    cout << setw(31) << categories[i];
                }
                else                                        //column 1 is single digit
                {
                    cout << setw(32) << categories[i];
                }
            }
            else
            {
                cout << setw(25) << categories[i];
            }
        }
    }

   cout << endl << endl;

   cout << "Type any of these commands to interact with the menu." << endl;

   cout << "  Look at <insert category> - Lists the names of all the recipes in that category." << endl;
   
}

/************************************************
 * RecipeManip()
 * No paremeters.
 * No return value.
 *
 * Allows the user to choose recipes for a
 * shopping list and add it to a weekly meal
 * calendar.
 *
 * It will also search and sort the recipes
 * via keywords while the user is choosing.
 ***********************************************/
void recipeManip()
{
   string userInput;
   string errorMessage;
   vector <RecipeCategory> categories = createRecipeList();
   ShoppingList shoppingList;

   while (userInput != "quit")
   {
      system("cls");
      printRecipeMenu(categories);

      cout << endl << endl;
      if (!errorMessage.empty())
      {
         cout << errorMessage << endl << endl;
      }

      cout << "What would you like to do? ";
      getline(cin, userInput);

      string lower = lowerCase(userInput);

      if (lower == "test")
      {
         cout << categories[3].getRecipes()[2];
      }
      else if (lower.find("look at") != string::npos)
      {
         int index = 0;
         try
         {
            string temp = userInput.substr(8);
            index = find(categories, temp);
            if (index < 0)
            {
                throw "Category not found";
            }
         }
         catch (const char* message)
         {
             errorMessage = message;
             continue;
         }

         errorMessage.clear();
	     while (userInput != "back")
	     {
            system("cls");
	        categories[index].printRecipeNames();
      
            cout << endl << endl;
            if (!errorMessage.empty())
            {
               cout << errorMessage << endl << endl;
            }

            cout << endl << endl << "What would you like to do? ";
	        getline(cin, userInput);

	        lower = lowerCase(userInput);

            if (lower.find("add") != string::npos)
	        {
	           try
	           {
	              int index2 = categories[index].find(userInput.substr(4));   //finds the index of the user inputed Recipe in the RecipeCategory object

		          if (index2 < 0)
		          {
		             throw "Recipe not found";
		          }

                  shoppingList.addItems(categories[index].getRecipes()[index2]);
	           }
               catch(const char* message)
	           {
	              errorMessage = message;
                  continue;
		       }

               errorMessage.clear();
	        }
            else if (lower.find("show") != string::npos)
            {
                system("CLS");
                cout << endl << endl <<"SHOPPING LIST:" << endl;
                cout << shoppingList << endl;
                

                cout << "Press ENTER to return to previous menu.";
                cin.get();
            }
	     }
         errorMessage.clear();
      }
   }
}


/*
Prints a Recipe object. Used for debugging.
*/
ostream & operator << (ostream & out, Recipe & rhs)
{
   if (rhs.empty())
   {
      return out;
   }
   out << rhs.getName() << endl << endl;

   out << "Ingredients:" << endl << endl;
   printIngredientVector(rhs.getIngredients());

   if (!rhs.getInstructions().empty())
   {
      out << "Instructions:" << endl;
      out << rhs.getInstructions() << endl << endl;
   }
   else
   {
      out << "There are no instructions." << endl;
   }

   out << "Total Cost: ";
   out << rhs.getTotalCost() << endl;

   return out;
}

/*
Prints a vector of Recipes. Used for debugging.
*/
ostream & operator << (ostream & out, vector <Recipe> & rhs)
{
   for (auto it = rhs.begin(); it != rhs.end(); ++it)
   {
      out << *it;
   }

   return out;
}

bool operator == (Recipe & lhs, Recipe & rhs)
{
   if (lhs.getName() == rhs.getName())
   {
      return true;
   }
   else
   {
      return false;
   }

}


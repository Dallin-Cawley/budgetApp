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

vector <string> recipePath()
{

   ifstream fin;
   try
   {
      fin.open("recipe_filePath.txt");

      if (fin.fail())
      {
         throw "Unable to open 'recipe_path.txt'";
      }
   }
   catch(const char* message)
   {
      system("bash recipe_fileNames.sh");
      int i = 0;
      while(i < 5 && fin.fail())
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
   catch (const char* unopened)
   {
      cout << "Unable to open " << unopened << endl;
   }

   string word;

   while (!fin.eof()) //Initial reading of the file
   {
      int i = 0;
      while (!fin.eof()) //used to gather the name of the recipe
      {
	 getline(fin, word);
	 if (i == 0)
	 {	 
            recipe.setName(word);
	 }
	 i++;
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
               else if (lower != "ingredients:")
               {
                  ingredient.setName(word);
               }
	       else if (!(ingredient.getName() == " "))
	       {       
                  recipe.addItem(ingredient);  //Add ingredient to recipe
	       }       
	    }
         }   //end of Ingredients conditional

      }   //end of single recipe loading while loop
   
   }   //end of initial While Loop
   fin.close();

   return recipe;
}



void printRecipeMenu(vector <RecipeCategory> categories)
{
   cout << setfill('*') << setw(80) << "*" << endl
        << setfill(' ') << setw(47) <<  "Recipe Menu " << endl
        << setfill('*') << setw(80) << "*" << endl;
   cout << setfill(' ');


   //Begin printing the categories in this format....
   //     "Category Name" ("Category Size")
   //           eg. Appetizers (9)
   for (int i = 0; i < categories.size(); i++)
   {
      if (categories[i].getName().empty())
      {
         continue;
      }
      if (i % 2 == 1)
      {
         if (categories[i - 1].getSize() / 10 >= 1)  //column 1 is double digit
	 {
            cout << setw(31) << categories[i] << endl;
	 }
	 else                                        //column 1 issingle digit
	 {
            cout << setw(32) << categories[i] << endl;
	 }
      }
      else
      {
         cout << setw(25) << categories[i];
      }
   }

   cout << endl << endl;

   
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
   vector <Recipe> shoppingList;

   while (userInput != "quit")
   {
      system("clear");
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
//	 printRecipeCategoriesVector(categories);
      }
      else if (lower.find("look at") != string::npos)
      {
         string temp = userInput.substr(8);
         int index = find(categories, temp);

	 while (userInput != "quit")
	 {
            system("clear");
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
	          int index2 = categories[index].find(userInput.substr(4));
		  cout << "Category: " << categories[index].getName() << endl;;
                  cout << "index2: " << index2 << endl;

		  if (index2 < 0)
		  {
		     throw "Recipe not found";
		  }

                  shoppingList.push_back(categories[index].getRecipes()[index2]);
	       }
               catch(const char* message)
	       {
	          errorMessage = message;
		  continue;
	       }

               errorMessage.clear();
	       printRecipeVector(shoppingList);

	       cin >> userInput;
	    }
	 }

	 errorMessage.clear();
      }
   }
}


void printRecipeVector(vector <Recipe> recipes)
{
   for (int i = 0; i < recipes.size(); i++)
   {
      cout << recipes[i];
   }
}

ostream & operator << (ostream & out, Recipe & rhs)
{
   out << "recipe << operator called" << endl;
     
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

ostream & operator << (ostream & out, vector <Recipe> & rhs)
{
   for (auto it = rhs.begin(); it != rhs.end(); ++it)
   {
      out << *it;
   }
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


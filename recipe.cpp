#include <string>
#include <list>
#include <fstream>      //ifstream
#include <sstream>      //stringstream
#include <iostream>
#include <iomanip>      //setw(), setfill()

#include "ingredient.h"
#include "../sorts/InsertionSort/insertionSort.h"
#include "recipe.h"
#include "stringManip.h"//lowerCase()

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

void Recipe::setName(std::string name)
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

void Recipe::setInstructions(std::string instructions)
{
   this->instructions += instructions;
   this->instructions += " ";
}

/******************
 * GETTERS
 *****************/

std::string Recipe::getInstructions() const
{
   return instructions;
}

std::string Recipe::getName() const
{
   return name;
}

double Recipe::getTotalCost() const
{
   return totalCost;
}

std::vector <Ingredient> Recipe::getIngredients() const
{
   return ingredients;
}


/***************************
 * Other necessary Functions
 **************************/

std::vector <Recipe> createRecipeList()
{
   std::vector <Recipe> recipes;

   std::ifstream fin;
   fin.open("Recipes/Beef and Broccoli Stir-fry.txt");

   std::string word;

   while (!fin.eof()) //Initial reading of the file
   {
      Recipe recipe;

      while (std::getline(fin, word)) //used to gather the name of the recipe
      {
         recipe.setName(word);

         std::string lower = lowerCase(word);
         if (lower.find("ingredients:"))
         {
            word.clear();

	    while (std::getline(fin, word))  //begin to gether ingredients
	    {
               Ingredient ingredient;

	       lower.clear();
               lower = lowerCase(word);

	       if (lower == "instructions:")
               {
                  while (fin >> word)  //begin to gather instructions
                  { 
                     recipe.setInstructions(word);
                  }
   
               }
               else if (lower != "ingredients:")
	       {
                  ingredient.setName(word);
	       }
	       
	       if (!(ingredient.getName() == " "))
	       {       
                  recipe.addItem(ingredient);  //Add ingredient to recipe
	       }       
	    }
         }   //end of Ingredients conditional

      }   //end of single recipe loading while loop
   
      recipes.push_back(recipe);
   }   //end of initial While Loop

   fin.close();

   return recipes;   
}

void printRecipeMenu()
{
   cout << setfill('*') << setw(80) << "*" << endl
        << setfill(' ') << setw(47) <<  "Recipe Menu " << endl
        << setfill('*') << setw(80) << "*" << endl;
   cout << setfill(' ');

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
   std::string userInput;

   while (userInput != "quit")
   {
      system("clear");
      printRecipeMenu();
      cout << "What would you like to do?";
      cin >> userInput;
   }
}


std::vector <Ingredient> printRecipeVector(std::vector <Ingredient> ingredients)
{
   for (auto it = ingredients.begin(); it != ingredients.end(); ++it)
   {
      std::cout << *it;
   }
}

std::ostream & operator << (std::ostream & out, Recipe & rhs)
{
   out << rhs.getName() << std::endl << std::endl;

   out << "Ingredients:" << std::endl << std::endl;
   printRecipeVector(rhs.getIngredients());

   out << "Instructions:" << std::endl;
   out << rhs.getInstructions() << std::endl << std::endl;

   out << "Total Cost: ";
   out << rhs.getTotalCost() << std::endl;
}

std::ostream & operator << (std::ostream & out, std::vector <Recipe> & rhs)
{
   for (auto it = rhs.begin(); it != rhs.end(); ++it)
   {
      out << *it;
   }
}


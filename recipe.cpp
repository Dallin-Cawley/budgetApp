#include <string>
#include <list>
#include <fstream>      //ifstream
#include <sstream>      //stringstream
#include <iostream>

#include "ingredient.h"
#include "../sorts/InsertionSort/insertionSort.h"
#include "recipe.h"
#include "stringManip.h"//lowerCase()

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
   this->instructions = instructions;
   this->instructions += " ";
}

/******************
 * GETTERS
 *****************/

std::string Recipe::getInstructions()
{
   return instructions;
}

std::string Recipe::getName()
{
   return name;
}

double Recipe::getTotalCost()
{
   return totalCost;
}

std::vector <Ingredient> Recipe::getIngredients()
{
   return ingredients;
}


/***************************
 * Other necessary Functions
 **************************/

std::list <Recipe> createRecipeList()
{
   std::list <Recipe> recipes;

   std::ifstream fin;
   fin.open("Recipes/Beef and Broccoli Stir-fry.txt");

   std::string word;

   while (fin >> word)
   {
      Recipe recipe;
      recipe.setName(word);

      std::string lower = lowerCase(word);

      if (lower == "ingredients:")
      {
         while (fin >> word)
         {
            Ingredient ingredient;

	    lower = lowerCase(word);
	    
	    std::stringstream ss;
            ss << lowerCase;

            double quantity = 0;

	    if (ss >> quantity)
	    {
	       ingredient.setQuantity(quantity);
	    }
	    else if (lower.find("lb") || lower.find("clove")
	          || lower.find('t')  || lower.find("oz")
		  || lower.find("gallon") || lower.find("pint"))
	    {
	       ingredient.setMeasurement(lower);
	    }
	    else
	    {
	       ingredient.setName(lower);
	    }

            if (lower == "Instructions:")
            {
               while (fin >> word)
	       { 
                  recipe.setInstructions(word);
	       }

               recipe.addItem(ingredient);
            }		      
	 }   //end of while
  
      }   //end of Ingredients conditional
   }   //end of initial While Loop

   return recipes;   
}


std::vector <Ingredient> printRecipeVector(std::vector <Ingredient> ingredients)
{
   for (auto it = ingredients.begin(); it != ingredients.end(); ++it)
   {
      std::cout << *it;
   }
}

std::ostream & Recipe::operator << (std::ostream & out)
{
   out << name << std::endl << std::endl;
          printRecipeVector(ingredients);
   out << std::endl;
   out << instructions << std::endl << std::endl;
   out << totalCost << std::endl;
}

int main()
{
   createRecipeList();

   return 0;
}

#ifndef RECIPE_H	
#define RECIPE_H

#include "ingredient.h"

#include <string>
#include <vector>
#include <list>

class Recipe
{
   private:
   std::string name;
   double totalCost;
   std::vector <Ingredient> ingredients;
   std::string instructions;

   public:
   void setName(std::string name);
   void setTotalCost(double totalCost);
   void addItem(Ingredient newItem);
   void setInstructions(std::string instructions);

   std::string getName();
   double getTotalCost();
   std::vector <Ingredient> getIngredients();
   std::string getInstructions();

   Recipe & operator = (Recipe &rhs)
   {
      this->name         = rhs.getName();
      this->totalCost    = rhs.getTotalCost();
      this->ingredients  = rhs.getIngredients();
      this->instructions = rhs.getInstructions();
   }

   std::ostream & operator << (std::ostream & out);
};


//Forward declaration of necessary recipe functions

std::list <Recipe> createRecipeList();
std::vector <Ingredient> printRecipeVector(std::vector <Ingredient> ingredients);

#endif

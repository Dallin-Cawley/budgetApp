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
   std::string instructions;
   std::vector <Ingredient> ingredients;

   public:
   Recipe();
   Recipe(const Recipe & rhs);

   void setName(std::string name);
   void setTotalCost(double totalCost);
   void addItem(Ingredient newItem);
   void setInstructions(std::string instructions);

   std::string getName() const;
   double getTotalCost() const;
   std::vector <Ingredient> getIngredients() const;
   std::string getInstructions() const;

   Recipe & operator = (Recipe &rhs)
   {
      if (!rhs.getName().empty())
         this->name      = rhs.getName();

      this->totalCost    = rhs.getTotalCost();

      if (!rhs.getInstructions().empty())
         this->instructions = rhs.getInstructions();
   
      for (int i = 0; i < rhs.getIngredients().size(); i++)
      {
         this->ingredients.push_back(rhs.getIngredients()[i]);
      }

   }


};


//Forward declaration of necessary recipe functions

std::ostream & operator << (std::ostream & out, Recipe & rhs);
std::ostream & operator << (std::ostream & out, std::vector <Recipe> & rhs);

std::vector <Recipe> createRecipeList();
std::vector <Ingredient> printRecipeVector(std::vector <Ingredient> ingredients);
void recipeManip();
#endif

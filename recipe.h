#ifndef RECIPE_H	
#define RECIPE_H

#include <string>
#include <vector>

struct ingredientInfo
{
   std::string name;
   double cost;
};

class Recipe
{
   private:
   std::string name;
   double totalCost;
   std::vector <ingredientInfo> ingredients;

   public:
   void setName(std::string name);
   void setTotalCost(int totalCost);
   
   void addItem(ingredientInfo newItem);

   std::string getName()                      {   return name;          }
   double getTotalCost()                      {   return totalCost;     }
   std::vector <ingredientInfo> getIngredients()   {   return ingredients;   }


};

#endif

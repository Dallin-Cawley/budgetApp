#ifndef RECIPECATEGORY_H
#define RECIPECATEGORY_H

#include <string>
#include <vector>

#include "recipe.h"

class RecipeCategory
{
   private:
   std::string name;
   int size;
   std::vector <Recipe> recipes;

   public:
   RecipeCategory();
   RecipeCategory(const RecipeCategory &rhs);

   void setName(std::string path);
   void addRecipe(Recipe item);
   void printRecipeNames();

   std::string getName() const;
   std::vector <Recipe> getRecipes() const;
   int getSize() const;

   int find(std::string item);
   int numDigits();

   friend std::ostream & operator << (std::ostream &out, RecipeCategory rCategory);
};


std::vector <RecipeCategory> createRecipeList();
std::vector <RecipeCategory> categoryNames(std::vector <std::string> filePaths);

int find(std::vector <RecipeCategory> categories, std::string name);
void printRecipeCategoriesVector(std::vector <RecipeCategory> categories);

#endif

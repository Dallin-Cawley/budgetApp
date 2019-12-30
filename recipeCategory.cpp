#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "recipeCategory.h"
#include "recipe.h"

using namespace std;

RecipeCategory::RecipeCategory()
{
   size = 0;
}

RecipeCategory::RecipeCategory(const RecipeCategory &rhs)
{
   this->size = rhs.getSize();
   this->name = rhs.getName();
   this->recipes = rhs.getRecipes();
}

/*
Using the file path, we extrapolate the category name by removing all '/' and '\' characters.
*/
void RecipeCategory::setName(std::string path)
{
   int j = 0;

   for (size_t i = 0; i < path.size(); i++)
   {
      if (path[i] == '/')
      {
         j++;
	     continue;
      }
      else if (path[i] == '\'')
      {
         continue;
      }
      if (j == 1)
      {
         this->name += path[i];
      }

      if (j >= 2)
      {
         break;
      }
   }
}

void RecipeCategory::addRecipe(Recipe item)
{
   recipes.push_back(item);
   size++;
}

/******************************************************************************
   printRecipeNames()
*******************************************************************************

   Parameters:
   None:

   Returns:
   None.

   Prints the category's recipes in this format.

   [Category Name] (number of recipes)
******************************************************************************/
void RecipeCategory::printRecipeNames()
{
   size_t spaces = 0;

   for (size_t i = 0; i < recipes.size(); i++)
   {
      if (spaces < recipes[i].getName().size())
      {
         spaces = recipes[i].getName().size();
      }
   }

   int middle = (60 + (name.size() / 2));   //This is the position of the middle character in the name in the middle of the cmd window.

   cout << setw(120) << setfill('*') << '*' << endl;
   cout << setw(middle) << setfill(' ') << name << endl;
   cout << setw(120) << setfill('*') << '*' << endl << endl;

   cout << setfill(' ');

   spaces += 3;

   for (size_t i = 0; i < recipes.size(); i++)
   {
      if (i % 2 == 0)
      {
         cout << setw(spaces)
              << recipes[i].getName() << endl;
      }
      else
      {
          cout << setw(spaces);
          cout << recipes[i].getName();
      }

   }
}

std::string RecipeCategory::getName() const
{
   return name;
}

std::vector <Recipe> RecipeCategory::getRecipes() const
{
   return recipes;
}

int RecipeCategory::getSize() const
{
   return size;
}

int RecipeCategory::find(string item)
{
   for (size_t i = 0; i < recipes.size(); i++)
   {
      if (recipes[i].getName().find(item) != string::npos)
      {
         return i;
      }
   }

   return -1;
}

/******************************************************************************
   categoryNames()
*******************************************************************************

   Parameters:
   A vector of the filePaths needed to extrapolate the Category names.
   (The category names are the folder that holds all the recipes)

   Appetizers  <------ Category
       |
       --> Cheese Curds  <------Recipe

   Returns:
   A vector containing all the Category Names.

   This function extrapolates the Category names from the filePath's string and
   returns a vector contaning the Category names.
******************************************************************************/
vector <RecipeCategory> categoryNames(vector <string> filePaths)
{
   vector <RecipeCategory> categories;
   RecipeCategory rc;
   rc.setName(filePaths[0]);
   categories.push_back(rc);

   int cTemp = 0;   //used to keep track of the index for 'categories'
   for (size_t i = 0; i < filePaths.size(); i++)
   {
      RecipeCategory rc;
      rc.setName(filePaths[i]);

      if (rc.getName() != categories[cTemp].getName())
      {
         RecipeCategory temp;
	     temp.setName(filePaths[i]);
         categories.push_back(temp);
         cTemp++;
      }
   }

   return categories;
}

/******************************************************************************
   createRecipeList()
*******************************************************************************

   Parameters:
   None.

   Returns:
   A vector containing the Category objects loaded with all the recipes.

   Utilizing recipePath() and categoryNames(), this function creats a 
   vector containing recipe filled RecipeCategory objects.
******************************************************************************/
vector <RecipeCategory> createRecipeList()
{
   vector <string> filePath = recipePath();
   vector <RecipeCategory> rCategories = categoryNames(filePath);

   for (size_t i = 0; i < filePath.size() - 1; i++)
   {
      for (size_t j = 0; j < rCategories.size(); j++)
      {
	     RecipeCategory rc;
	     rc.setName(filePath[i]);

         if (rc.getName() == rCategories[j].getName())  //Determines if the current recipe belongs in this Category.
	     {
	        rCategories[j].addRecipe(parseFile(filePath[i])); //Adds the recipe in question into the correct RecipeCategory.
	        break;
	     }
      }
   }

   return rCategories;
}

void printRecipeCategoriesVector(vector <RecipeCategory> categories)
{
   for (size_t i = 0; i < categories.size(); i++)
   {
      cout << categories[i] << endl;
   }
}

int find(vector <RecipeCategory> categories, string name)
{
   for (size_t i = 0; i < categories.size(); i++)
   {
      if (categories[i].getName() == name)
      {
         return i;
      }
   }

   return -1;

}

ostream & operator << (ostream &out, RecipeCategory rCategory)
{
   out << rCategory.getName() << " (" << rCategory.getSize() << ")";

   return out;
}

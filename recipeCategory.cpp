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

void RecipeCategory::setName(std::string path)
{
   int j = 0;

   for (int i = 0; i < path.size(); i++)
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

void RecipeCategory::printRecipeNames()
{
   for (int i = 0; i < recipes.size(); i++)
   {
      if (i % 2 == 0)
      {
         cout << endl;
      }

      cout << setw(15);
      cout << recipes[i].getName();
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

//Recipe RecipeCategory::find(Recipe item)
//{
//   for (int i = 0; i < recipes.size(); i++)
//   {
//      if (item == recipes[i])
//      {
//         return recipes[i];
//      }
//   }
//
//   return item;
//}

int RecipeCategory::find(string item)
{
   for (int i = 0; i < recipes.size(); i++)
   {
      if (recipes[i].getName().find(item) != string::npos)
      {
         return i;
      }
   }

   return -1;
}

vector <RecipeCategory> categoryNames(vector <string> filePaths)
{
   vector <RecipeCategory> categories;
   RecipeCategory rc;
   rc.setName(filePaths[0]);
   categories.push_back(rc);

   int cTemp = 0;
   for (int i = 0; i < filePaths.size(); i++)
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

vector <RecipeCategory> createRecipeList()
{
   vector <string> filePath = recipePath();
   vector <RecipeCategory> rCategories = categoryNames(filePath);

   for (int i = 0; i < filePath.size() - 1; i++)
   {
      for (int j = 0; j < rCategories.size(); j++)
      {
	 RecipeCategory rc;
	 rc.setName(filePath[i]);

         if (rc.getName() == rCategories[j].getName())
	 {
	    rCategories[j].addRecipe(parseFile(filePath[i]));
	    break;
	 }
      }
   }

   return rCategories;
}

void printRecipeCategoriesVector(vector <RecipeCategory> categories)
{
   for (int i = 0; i < categories.size(); i++)
   {
      cout << categories[i] << endl;
   }
}

int find(vector <RecipeCategory> categories, string name)
{
   for (int i = 0; i < categories.size(); i++)
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

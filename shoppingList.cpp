#include "shoppingList.h"
#include "stringManip.h"

ShoppingList::ShoppingList()
{
    numItems = 0;
    capacity = 1;
}

std::vector<Ingredient> ShoppingList::getItems()
{
    return items;
}


/******************************************************************************
   addItems()
*******************************************************************************

   Parameters:
   A Recipe object who's ingredients need to be added to the Shopping List.

   Returns:
   None.

   The function adds ingredients to the Shopping List. If the ingredient in
   question already exists, the quantity of that ingredient is added to the
   already existing ingredient.
******************************************************************************/
void ShoppingList::addItems(Recipe recipe)
{
    if (recipe.getIngredients().empty())
    {
        return;
    }

    int k = 0;
    for (size_t i = 0; i < recipe.getIngredients().size(); i++)
    {
       for (int j = 0; j < numItems; j++)
       {
            if ((!items[j].getMeasurement().empty()) && (!recipe.getIngredients()[i].getMeasurement().empty()))
            {
                  if (items[j].getMeasurement() == recipe.getIngredients()[i].getMeasurement()
                      && lowerCase(items[j].getName()) == lowerCase(recipe.getIngredients()[i].getName()))   //If ingredient already exists,
                  {                                                                                          //add to already existing.
                     items[j].setQuantity(items[j].getQuantity() + recipe.getIngredients()[i].getQuantity());
                     k = 1;
                     break;
                  }
            }
       }

        if (k == 1)   //Ingredient was added to a previously known ingredient in vector. No need to add another instance.
        {
            k = 0;
            continue;
        }
        else
        {
            if (numItems == 0 && (!recipe.getIngredients()[i].getMeasurement().empty()))
            {
               items.push_back(recipe.getIngredients()[i]);
               numItems++;
            }
            else if (numItems != 0 && (!recipe.getIngredients()[i].getMeasurement().empty()))
            {
               items.push_back(recipe.getIngredients()[i]);
               numItems++;
            }
        }
    }
}

/*
Prints the Shopping List.
*/
std::ostream& operator<<(std::ostream& out, ShoppingList shoppingList)
{
    for (size_t i = 0; i < shoppingList.getItems().size(); i++)
    {
        out << shoppingList.items[i].getQuantity() << " " 
            << shoppingList.items[i].getMeasurement() << " "
            << shoppingList.items[i].getName() << std::endl;
    }

    return out;
}

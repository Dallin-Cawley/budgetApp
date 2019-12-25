#include "shoppingList.h"

ShoppingList::ShoppingList()
{
    items = new Ingredient[1];
    numItems = 0;
    capacity = 1;
}

ShoppingList::~ShoppingList()
{
    delete[] items;
}

int ShoppingList::size()
{
    return numItems;
}

bool ShoppingList::empty()
{
    if (numItems > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void ShoppingList::addItems(Recipe recipe)
{
    if (recipe.getIngredients().empty())
    {
        return;
    }

    int k = 0;
    for (size_t i = 0; i < recipe.getIngredients().size(); i++)
    {
        if (numItems == capacity)
        {
            resize();
        }

        std::cout << "Before for Loop." << std::endl;
        for (int j = 0; j < numItems; j++)
        {
            std::cout << "Begin For Loop: " << j << std::endl;
            if (items[j].getMeasurement() == recipe.getIngredients()[i].getMeasurement())
            {
                std::cout << "Inside If Statement." << std::endl;
                items[j].setQuantity(items[j].getQuantity() + recipe.getIngredients()[i].getQuantity());
                k = 1;
                break;
            }
        }

        if (k == 1)
        {
            k = 0;
            continue;
        }
        else
        {
            if (numItems == 0)
            {
                items[0] = recipe.getIngredients()[i];
                numItems++;
            }
            else
            {
               std::cout << "numitems != 0" << std::endl;
               items[numItems - 1] = recipe.getIngredients()[i];
               numItems++;
            }
        }
    }
}

void ShoppingList::resize()
{
    std::cout << "Inside Resize Function." << std::endl;
    Ingredient* temp = new Ingredient[capacity * 2];

    for (int i = 0; i < numItems; i++)
    {
        temp[i] = items[i];
    }

    capacity *= 2;
    delete[] items;
    items = temp;
}

std::ostream& operator<<(std::ostream& out, ShoppingList shoppingList)
{
    for (int i = 0; i < shoppingList.size(); i++)
    {
        out << shoppingList.items[i].getQuantity() << " " 
            << shoppingList.items[i].getMeasurement() << std::endl;
    }

    return out;
}

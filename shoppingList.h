#pragma once

#include <iostream>
#include <vector>

#include "recipe.h"
#include "ingredient.h"

class ShoppingList
{
private:
	std::vector <Ingredient> items;
	int numItems;
	int capacity;

public:
	ShoppingList();

	std::vector <Ingredient> getItems();
	void addItems(Recipe recipe);

	friend std::ostream& operator << (std::ostream& out, ShoppingList shoppingList);
};


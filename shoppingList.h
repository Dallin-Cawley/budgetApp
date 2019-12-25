#pragma once

#include <iostream>

#include "recipe.h"
#include "ingredient.h"

class ShoppingList
{
private:
	Ingredient * items;
	int numItems;
	int capacity;

public:
	ShoppingList();
	~ShoppingList();

	int size();
	bool empty();

	void addItems(Recipe recipe);

	void resize();

	friend std::ostream& operator << (std::ostream& out, ShoppingList shoppingList);
};


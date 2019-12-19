#include "ingredient.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

Ingredient::Ingredient()
{
   quantity = 0;
   cost = 0;
}

/*******************************************
 * Setters
 ******************************************/
void Ingredient::setQuantity(double quantity)
{
   this->quantity = quantity;
}

void Ingredient::setName(std::string name)
{
   this->name = name;

   double quantity = 0;

   std::stringstream ss;
   ss << name;

   ss >> quantity;

   setQuantity(quantity);

   std::string measurement;
   ss >> measurement;
   setMeasurement(measurement);
}

void Ingredient::setCost(double cost)
{
   this->cost = cost;
}

void Ingredient::setMeasurement(std::string measurement)
{
   this->measurement = measurement;
}

/*******************************************
 * Getters
 ******************************************/

std::string Ingredient::getMeasurement()
{
   return measurement;
}

double Ingredient::getQuantity()
{
   return quantity;
}

std::string Ingredient::getName()
{
   return name;
}

double Ingredient::getCost()
{
   return cost;
}

bool Ingredient::empty()
{
   if (name.empty())
      return true;
   else
      return false;
}

std::ostream & operator << (std::ostream & out, Ingredient & ingredient)
{
   if (!ingredient.empty())
   {
      out << ingredient.getName() << std::endl << std::endl;
      return out;
   }
   else
   {
      out << "No ingredient" << std::endl;
      return out;
   }

}


void printIngredientVector(std::vector <Ingredient> ingredients)
{
   for (auto it = ingredients.begin(); it != ingredients.end(); ++it)
   {
      std::cout << *it;
   }
}


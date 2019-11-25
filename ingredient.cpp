#include "ingredient.h"

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


std::ostream & operator << (std::ostream & out, Ingredient & ingredient)
{
   if (ingredient.getName().size() > 0)
   {
      out << "Quantity: ";
      out << ingredient.getQuantity() << std::endl;
   
      out << "Measurement: ";
      out << ingredient.getMeasurement() << std::endl;
   
      out << "Name: ";
      out << ingredient.getName() << std::endl << std::endl;
   
      if (ingredient.getCost() > 0)
         out << ingredient.getCost();
      
      return out;
   }
   else
   {
      return out;
   }

}



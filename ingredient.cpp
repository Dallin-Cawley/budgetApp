#include "ingredient.h"

#include <string>
#include <iostream>

void Ingredient::setQuantity(double quantity)
{
   this->quantity = quantity;
}

void Ingredient::setName(std::string name)
{
   this->name = name;
   this->name += " ";
}

void Ingredient::setCost(double cost)
{
   this->cost = cost;
}

void Ingredient::setMeasurement(std::string measurement)
{
   this->measurement = measurement;
}

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

//std::ostream & operator << (std::ostream & out, double num)
//{
//   out << double(num);
//}

std::ostream & operator << (std::ostream & out, Ingredient & ingredient)
{
   out << ingredient.getQuantity();
   out.flush();
   out << ingredient.getMeasurement();
   out << ingredient.getName();
   out << ingredient.getCost();
   out << std::endl;
}



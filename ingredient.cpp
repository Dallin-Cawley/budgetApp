#include "ingredient.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

/******************************************************************************
   measureConvert()
*******************************************************************************
   Parameters:
   string measurement

   Returns:
   The converted string measurement.

   The function is intended to normalize the measurements people put into
   recipes in their various forms.

   EG.
   tsp -> teaspoon
 *****************************************************************************/
std::string Ingredient::measureConvert(std::string measurement)
{
    if (measurement.find("cup") != std::string::npos)
    {
        return "cup";
    }
    else if (measurement.find("t.") != std::string::npos || measurement.find("tea") != std::string::npos
          || measurement.find("Tea") != std::string::npos || measurement.find("tsp") != std::string::npos)
    {
        return "teaspoon";
    }
    else if (measurement.find("T") != std::string::npos || measurement.find("table") != std::string::npos
          || measurement.find("Table") != std::string::npos)
    {
        return "tablespoon";
    }
    else if (measurement.find("oz") != std::string::npos || measurement.find("Oz") != std::string::npos)
    {
        return "oz";
    }
    else if (measurement.find("egg") != std::string::npos || measurement.find("Egg") != std::string::npos)
    {
        return "egg";
    }
    else
    {
        return measurement;
    }
}

/*
Basic Constructor
*/
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

/******************************************************************************
   setName()
*******************************************************************************

   Parameters:
   string name.

   Returns:
   Nothing.

   This function sets the name of the Ingredient while also setting the
   quantity and sets the measurement through the call of measureConvert() and
   setMeasurement().

   The way the recipes are set up includes the quantity, measurement, and the name
   of the ingredient in that order. This function requires the format of....

   [Quantity] [Measurement] [Name].
******************************************************************************/
void Ingredient::setName(std::string name)
{

   double quantity = 0;

   std::stringstream ss;
   ss << name;

   ss >> quantity;

   setQuantity(quantity);

   std::string measurement;
   ss >> measurement;
   setMeasurement(measureConvert(measurement));

   std::string temp;

   while (ss >> temp) 
   {
       this->name += temp;
       this->name += " ";

       this->name.erase(this->name.end());
   }
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

/*
<< Operator used for debugging only.
*/
std::ostream & operator << (std::ostream & out, Ingredient & ingredient)
{
   if (!ingredient.empty())
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
      out << "No ingredient" << std::endl;
      return out;
   }

}

/*
Prints a vector of Ingredients. Used for debugging.
*/
void printIngredientVector(std::vector <Ingredient> ingredients)
{
   for (auto it = ingredients.begin(); it != ingredients.end(); ++it)
   {
      std::cout << *it;
   }
}


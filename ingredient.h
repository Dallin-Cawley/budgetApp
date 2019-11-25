#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient
{
   private:
   double quantity;
   std::string name;
   double cost;
   std::string measurement;

   public:
   Ingredient();

   void setQuantity(double quantity);
   void setName(std::string name);
   void setCost(double cost);
   void setMeasurement(std::string measurement);

   double getQuantity();
   std::string getName();
   double getCost();
   std::string getMeasurement();

   Ingredient & operator=(Ingredient & rhs)
   {
      this->quantity    = rhs.getQuantity();
      this->name        = rhs.getName();
      this->cost        = rhs.getCost();
      this->measurement = rhs.getMeasurement();
   }

};

std::ostream & operator << (std::ostream & out, Ingredient & ingredient);
#endif

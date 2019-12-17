#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>

class Category
{
   private:
   std::string name;
   double amount;

   public:
   Category();

   void setName(std::string name);
   void setAmount(double amount);

   std::string getName()   {   return name;   }
   double getAmount()      {   return amount; }

   int numDigits();
   void printCategory(int space = 0, int i = 0);
   void operator - (Category & rhs);

   friend std::vector <Category> startUp();

};

/*****************************************************
 * Forward declarations for all things related to
 * the Category class
 ****************************************************/

void printCategory(Category c);

#endif

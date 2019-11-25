#include <vector>
#include <string>
#include <iostream>
#include <iomanip>   //setw()

#include "category.h"


Category::Category()
{
   amount = 0;
}

void Category::setName(std::string name)
{
   this->name = name;
   this->name += " ";
}

void Category::setAmount(double amount)
{
   this->amount = amount;
}

Category & Category::operator - (Category & rhs)
{
   this->amount -= rhs.getAmount();
}
/**************************************************************
 * numDigits()
 * Parameters: None
 *
 * Returns: integer representing the number of digits in amount
 * for printing.
 *
 * Using for loops, we determine the number of digits before
 * and after the decimals because 'std::to_string' tacks on
 * extra 0's which don't exist in the double type counterpart.
 *************************************************************/
int Category::numDigits()
{
   std::string digits = std::to_string(amount);

   int digitsBeforeDecimal = 0;

   for (int i = 0; i < digits.size(); i++)
   {
      if (digits[i] != '.')
      {
         digitsBeforeDecimal++;
      }
      else
      {
         break;
      }
   }

   int digitsAfterDecimal = 0;

   if (digitsBeforeDecimal < digits.size())
   {
      for (int i = digitsBeforeDecimal + 1; i < digits.size(); i++)
      {
         if (digits[i] != '0')
	 {
            digitsAfterDecimal++;
	 }
      }
      if (digitsAfterDecimal != 0)
      {
         digitsAfterDecimal++;    //Added 1 to include '.' because a decimal
      }                           //exists as proved by if conditional.

   }

   return digitsBeforeDecimal + digitsAfterDecimal;
}

void Category::printCategory (int space, int i)
{
   if ((i + 1) % 2 == 0)
   {
      std::cout << std::setw(30 + space);
      std::cout << name << amount;
   }
   else
   {
      std::cout << std::setw(20 + space);
      std::cout << name;
      std::cout << amount;
   }
}

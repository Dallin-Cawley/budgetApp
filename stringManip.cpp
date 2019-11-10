#include <string>

#include "stringManip.h"

using namespace std;

/*****************************************************
 * Lower-Case
 * Expects a string and lowercases all characters.
 *
 * Returns the string with all letters lowercased.
 ****************************************************/
string lowerCase(string userInput)
{
   for (int i = 0; i < userInput.size(); i++)
   {
      userInput[i] = tolower(userInput[i]);
   }

   return userInput;
}

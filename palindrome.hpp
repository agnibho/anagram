/**********************************************************************
 * Title: Anagram
 * Description: Application for finding anagrams of a word
 * Author: Agnibho Mondal
 * Website: http://code.agnibho.com/anagram
 **********************************************************************
   Copyright (c) 2013-2015 Agnibho Mondal
   All rights reserved
 **********************************************************************
   This file is part of Anagram.
   
   Anagram is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   Anagram is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with Anagram.  If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/
#ifndef PALINDROME
#define PALINDROME

/*
 * Provides a function for checking if a word is a palindrome
 */

#include <string> //For string
#include <algorithm> //For reverse

bool is_palindrome(std::string word){ //Checks if the provided word is a plindrome.
  std::string rev=word; //Copy the string
  std::reverse(rev.begin(), rev.end()); //Reverse the copied string
  if(word.compare(rev)==0){ //True if string compare returns 0 i.e. both strings are equal.
    return true;
  }
  else{ //False if string compare returns non-zero i.e. strings are unequal.
    return false;
  }
}

#endif //PALINDROME

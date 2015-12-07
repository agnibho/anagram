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
#ifndef CHECK
#define CHECK

/*
 * Provides a function for checking if  two words are anagrams of each other.
 */

#include <string> //For string
#include <algorithm> //For sort

bool is_anagram(std::string str_1, std::string str_2){ //Compares two strings to check if they are anagrams.
  str_1.erase(remove_if(str_1.begin(), str_1.end(), ::isspace), str_1.end()); //Remove spaces from first string
  str_2.erase(remove_if(str_2.begin(), str_2.end(), ::isspace), str_2.end()); //Remove spaces from second string
  std::sort(str_1.begin(), str_1.end()); //Sort first string
  std::sort(str_2.begin(), str_2.end()); //Sort second string
  if(str_1.compare(str_2)==0){ //If comparison returns 0 i.e. sorted strings are equal, return true.
    return true;
  }
  else{ //If sorted strings are not equal return false.
    return false;
  }
}

#endif //CHECK

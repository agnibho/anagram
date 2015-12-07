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
#ifndef VALIDITY
#define VALIDITY

/*
 * Provides a function for checking validity of the word.
 */

#include <string> //For string
#include <cctype> //For isalpha, isblank

bool is_valid(std::string word, bool multi){ //Checks the validity of the provided word. Allows multiline if <multi> is true.
  bool flag=true; //Flag is true by default. Set to false if invalidity is encountered later.
  if(multi){ //Multi-word
    for(int i=0; i<word.length(); i++){
      if(!(isalpha(word[i]) || isblank(word[i]))){ //Multi-word allows space seperated words.
	flag=false;
      }
    }
  }
  else{ //Single word
    for(int i=0; i<word.length(); i++){
      if(!(isalpha(word[i]))){ //Only alphabetic characters are allowed.
	flag=false;
      }
    }
  }
  return flag;
}

#endif //VALIDITY

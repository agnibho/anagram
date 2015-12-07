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
#ifndef HELP
#define HELP

/*
 * Shows a manual about how to use this program
 */

#include <iostream>

int show_help(){ //Displays help on console
  cout<<
    "Anagram 2.0\n\n"
    "anagram [-hmpP] word [word2]\n\n"
    "\t The program finds the possible angrams of the 'word' from a dictionary.\n"
    "\t If 'word2' is specified it compares 'word' and 'word2' to check if they are anagrams of each other.\n"
    "Options:\n"
    "-h \t Show this help\n"
    "-m \t Find multiword anagrams\n"
    "-p \t Checks if 'word' is a palindrome\n"
    "-P \t Only checks if 'word' is a palindrome. Does not find angrams.\n\n"
    "Example:\n"
    "\t anagram -p cat\n\n"
    "Website: http://code.agnibho.com/anagram/"
      <<endl;
  return true;
}

#endif //HELP

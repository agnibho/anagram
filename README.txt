                        Anagram
			=======

What is Anagram?
-------------------

Anagram is a C++ application for finding anagrams of a given
word. Anagram has two modes- a cli mode for command line usage and a
gui mode for graphical interface. Both modes use separate binary
files. Anagram supports both single-word and multi-word anagrams,
although multi-word anagram searches may take a very long time. Apart
from anagram searching Anagram provides a few other functionalities
such as palindrome identification, dictionary checking etc.

Anagram is written in C++ and needs to be compiled before use.

Downloading
-----------

Latest release of Anagram can be downloaded from
http://code.agnibho.com/anagram/

The source code is available at https://github.com/agnibho/anagram/

Installation
------------

Please see the file named INSTALL.txt for installation instructions.

Usage
-----

Anagram can be used from command line as well as through a graphical
interface.

Enter 'anagram -h' in the command line to see a list of available
options and usage instructions.

anagram [-hmpP] word [word2]

         The program finds the possible angrams of the 'word' from a dictionary.
         If 'word2' is specified it compares 'word' and 'word2' to check if they are anagrams of each other.
Options:
-h       Show this help
-m       Find multiword anagrams
-p       Checks if 'word' is a palindrome
-P       Only checks if 'word' is a palindrome. Does not find angrams.

Example:
         anagram -p cat


To start the graphical interface launch the binary file named 'angramx'.

Licensing
---------

Copyright (c) 2013-2015 Agnibho Mondal
All rights reserved

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

Contacts
--------

Agnibho Mondal
mail@agnibho.com
www.agnibho.com

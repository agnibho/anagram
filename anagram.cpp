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
/*
 *The Command Line Interface for Anagram
 */

#include <iostream> //For console output
#include <string> //For string variables
#include <unistd.h> //For getopt
#include <algorithm> //For transform, sort
#include <vector> //For vector data
#include "validity.hpp" //For is_valid
#include "palindrome.hpp" //For is_palindrome
#include "check.hpp" //For is_anagram
#include "find.hpp" //For find_anagram
#include "help.hpp" //For show_help

using namespace std;

int main(int argc, char** argv){
  
  //State variables
  bool multi=false; //For multi-word
  bool compare=false; //Check if two words are anagrams of each other
  bool dict=false; //Check if the word is in the dictionary
  int palindrome=0; //Values: 0=>don't check palindrome, 1=> check palindrome along with anagram, 2=> check palindrome only
  
  //Check command line options
  int c=0;
  while((c=getopt(argc, argv, "dhmpP"))!=-1){
    switch(c){
    case 'd': //Check dictionary
      dict=true;
      break;
    case 'h': //Show help
      show_help();
      return 0;
    case 'm': //Allow multi-line
      multi=true;
      break;
    case 'p': //Check palindrome
      palindrome=1;
      break;
    case 'P': //Check palindrome only
      palindrome=2;
      break;
    }
  }

  string word; //The string to find anagrams for
  string against; //The string to check if the word is a anagram of it
  //First non-option argument
  if(argv[optind]!=NULL){ //Set the first non-option argument as word
    word=argv[optind];
    //Optional second argument
    if(argv[optind+1]!=NULL){ //Set the second non-option argument as against
      against=argv[optind+1];
      compare=true;
    }
  }
  else{ //If no non-option argument present read from stdin
    cerr<<"Enter word:"<<endl;
    getline(cin, word);
  }

  //Check validity of word
  if(is_valid(word, multi)){

    //Convert to lower case
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    
    if(palindrome==2){ //Don't check anagram if only palindrome is requested.
      //Check palindrome
      if(is_palindrome(word)){
	cout<<word<<": The word is a Palindrome"<<endl;
      }
      else{
	cout<<word<<": The word is NOT a Palindrome"<<endl;
      }
    }
    else{
      if(palindrome==1){ //Check palindrome if requested.
	//Check palindrome
	if(is_palindrome(word)){
	  cout<<word<<": The word is a Palindrome"<<endl;
	}
	else{
	  cout<<word<<": The word is NOT a Palindrome"<<endl;
	}
      }
      if(compare){ //Don't find all anagrams if only comparison is requested.
	//Check anagram
	if(is_anagram(word, against)){
	  cout<<word<<": "<<against<<": The words are anagrams of each other"<<endl;
	}
	else{
	  cout<<word<<": "<<against<<": The words are NOT anagrams of each other"<<endl;
	}
      }
      else{ //Look for anagrams in the dictionary
	vector<string> anagram_list; //Container for anagrams
	if(multi){ //Multi-word anagram
	  anagram_list=find_anagram_multiword(word); //Finds anagrams
	}
	else{ //Single-word anagram
	  anagram_list=find_anagram(word); //Finds anagrams
	}
	//Check the word itself from the anagram list
	{
	  vector<string>::iterator i=find(anagram_list.begin(), anagram_list.end(), word);
	  if(i==anagram_list.end()){ //If the word itself is not in the anagram list
	    if(dict){
	      cout<<word<<": The word is NOT present in the dictionary"<<endl;
	    }
	  }
	  else{ //If the word itself is present in the anagram list
	    if(dict){
	      cout<<word<<": The word is present in the dictionary"<<endl;
	    }
	    anagram_list.erase(i); //Remove the word itself from the anagram list
	  }
	}
	//Print out the angrams if present
	if(anagram_list.size()>0){
	  if(anagram_list.size()>1){ //If more than one anagrams
	    cerr<<word<<": The following "<<anagram_list.size()<<" anagrams were found-"<<endl;
	  }
	  else{ //If only one anagram
	    cerr<<word<<": The following anagram was found-"<<endl;
	  }
	  for(string i:anagram_list){
	    cout<<i<<endl;
	  }
	}
	else{
	  cerr<<word<<": No anagrams were found"<<endl;
	}
      }
    }
  }
  else{
    cerr<<"Invalid word: "<<word<<endl; //Exit with error if the word is not valid.
    return 1;
  }
  return 0;
}

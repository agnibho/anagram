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
#ifndef FIND
#define FIND

#define DICT_PATH "/usr/local/share/anagram/dictionary"

/*
 *Provides the functions for finding anagrams from a dictionary
 *Uses is_palindrome from check.h
 */

#include <iostream> //For showing progress on console
#include <string> //For string
#include <vector> //For vector data
#include <algorithm> //For transform
#include <fstream> //For reading dictionary files
#include "check.hpp" //For is_anagram

using namespace std;

//Single word anagrams
vector<string> find_anagram(string word){ //Finds anagrams from dictionary
  vector<string> file_name; //Make container to hold dictionary filenames to search
  vector<string> anagram_list; //Make container for holding anagrams
  int len=word.length(); //Find word length. Used to construct names of files to search through.
  //Loop over word to construct filenames (C++11)
  for(char i : word){
    string j=DICT_PATH"/"+string(1,i)+to_string(len)+".txt"; //Constructs filenames from word. (C++11)
    if(find(file_name.begin(), file_name.end(), j)==file_name.end()){ //Check if filename is already registered
      file_name.push_back(j); //Register filename
    }
  }
  //Loop over files to collect anagrams. (C++11)
  for(string i : file_name){
    ifstream infile(i); //Makes the file reader
    string line; //Variable to hold each line from the file
    while(getline(infile, line)){ //Loops over the file
      transform(line.begin(), line.end(), line.begin(), ::tolower);//Converts to lowercase
      if(is_anagram(word, line)){ //Checks if the read string is an anagram of the word.
	anagram_list.push_back(line); //Saves the found anagram
      }
    }
  }
  return anagram_list;
}

//Multiple word anagrams
vector<string> find_anagram_multiword(string word){ //Finds multiword anagrams from dictionary
  word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end()); //Remove spaces from string
  vector<string> file_name; //Make container to hold dictionary filenames to search
  vector<string> anagram_list; //Make container for holding anagrams
  int len=word.length(); //Find word length. Used to construct names of files to search through.
  //Loop from 1 to len
  for(int l=1; l<=len; l++){
    //Loop over word to construct filenames (C++11)
    for(char i : word){
      string j=DICT_PATH"/"+string(1,i)+to_string(l)+".txt"; //Constructs filenames from word. (C++11)
      if(find(file_name.begin(), file_name.end(), j)==file_name.end()){ //Check if filename is already registered
	file_name.push_back(j); //Register filename
      }
    }
  }
  //Loop over files to collect potential words. (C++11)
  vector<string> word_list; //Container to hold potential words
  for(string i : file_name){
    ifstream infile(i); //Makes the file reader
    string line; //Variable to hold each line from the file
    while(getline(infile, line)){ //Loops over the file
      transform(line.begin(), line.end(), line.begin(), ::tolower); //Converts to lowercase
      bool flag=true; //flag` is used to mark if `line` is allowed as a potential anagram word
      for(char i : line){ //Loops over line by each character
	if(word.find(i)==string::npos){ //If any character of `line` is not present in `word` mark `flag` as false
	  flag=false;
	}
      }
      if(flag){ //If `line` is a potential candidate save `line` to the word list
  	word_list.push_back(line);
      }
    }
  }
  //Construct sentences from the word list
  vector<int> index; //Holds the word index while cycling through the list
  string holder; //Temporarily holds the sentence during construction
  int tmplen; //Holds potential sentence length temporarily
  index.push_back(0); //Initiate first index
  //Progress variables
  int progress_total=100;
  int progress_current=0;
  int progress_percent=0;
  if(word_list.size()>=3){
    progress_total=word_list.size()*3;
  }
  else{
    progress_total=word_list.size();
  }
  
  while(index.at(0)<word_list.size()){ //Until first index exceeds list length
    tmplen=0; //Resets `tmplen`
    for(int i : index){ //Loops over index
      tmplen+=word_list.at(i).size(); //Calculates combined length of all indexed words
    }
    
    if(tmplen<word.size()){ //If temporary sentence length is less than actual word length, add another index
      index.push_back(0);
    }
    else if(tmplen>word.size()){ //If temporary sentence length is more than actual word length, remove last index and increment the previous index
      index.pop_back(); //Remove last index
      //Remove all indices exceeding list length
      while(index.back()>=word_list.size()-1){
  	index.pop_back();
      }
      if(index.empty()){ //Exit loop if all indices are removed
	break;
      }
      index.back()++; //Increment new last index
    }
    else if(tmplen==word.size()){ //If temporary sentence length is equal to actual word length, increment last index
      //Construct temporary sentence to be checked from the indexed words
      holder=""; //Reset holder
      for(int i : index){ //Concatenate all indexed words
      	holder+=word_list.at(i)+" ";
      }
      if(is_anagram(word, holder)){ //Checks if the constructed string is an anagram of the word
	anagram_list.push_back(holder); //Saves the found anagram
      }
      
      //Remove all indices exceeding list length
      while(index.back()>=word_list.size()-1){
  	index.pop_back();
      }
      if(index.empty()){ //Exit loop if all indices are removed
	break;
      }
      index.back()++; //Increment new last index
    }
    //Calculate progress using first 3 indices
    if(index.size()>=3){ //Use first 3 if indices more than 3
      progress_total=word_list.size()*100+word_list.size()*10+word_list.size();
      progress_current=index.at(0)*100+index.at(1)*10+index.at(2);
    }
    if(index.size()==2){ //If 2 indices
      progress_total=word_list.size()*10+word_list.size();
      progress_current=index.at(0)*10+index.at(1);
    }
    else{ //If only 1 index
      progress_total=word_list.size();
      progress_current=index.at(0);
    }
    progress_percent=progress_current*100/progress_total; //Calculate progess percentage
    cerr<<progress_percent<<"% completed\t"<<anagram_list.size()<<" anagrams found.\r"; //Print progress
  }
  return anagram_list;
}

#endif //FIND

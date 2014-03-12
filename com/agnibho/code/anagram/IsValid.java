/*
    Anagram- Find anagrams of a word
    Copyright (C) 2013  Agnibho Mondal
    
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
*/
package com.agnibho.code.anagram;

/**
 *
 * @author SPARK
 */
public class IsValid {
    private boolean isValid=true;

    IsValid(){
    }

    public boolean isValid(String in, boolean isMulti){
	if(isMulti){
	    for(int i=0; i<in.length(); i++){
		if(!((in.charAt(i)>=65&&in.charAt(i)<=90)||(in.charAt(i)>=97&&in.charAt(i)<=122)||in.charAt(i)==' ')){
		    isValid=false;
		}
	    }
	}
	else{
	    for(int i=0; i<in.length(); i++){
		if(!((in.charAt(i)>=65&&in.charAt(i)<=90)||(in.charAt(i)>=97&&in.charAt(i)<=122))){
		    isValid=false;
		}
	    }
	}
	return isValid;
    }
}

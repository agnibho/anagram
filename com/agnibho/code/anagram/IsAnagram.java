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
public class IsAnagram {
    private char[] input;
    private char[] reference;
    private boolean checked;
    
    IsAnagram(){
    }
    
    public boolean check(String in, String ref){
        in=in.replaceAll("\\s", "");
        ref=ref.replaceAll("\\s", "");
        input=in.toLowerCase().toCharArray();
        reference=ref.toLowerCase().toCharArray();
        java.util.Arrays.sort(input);
        java.util.Arrays.sort(reference);
        if(java.util.Arrays.equals(input, reference)) checked=true;
        else checked=false;
        return checked;
    }
}

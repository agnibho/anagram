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

import javax.swing.SwingWorker;

/**
 *
 * @author SPARK
 */
public class CheckAnagram extends SwingWorker <String, Double> {
    private String input;
    private String result;
    private IsAnagram isAnagram= new IsAnagram();
    private java.util.Scanner read=null;
    private boolean inDict;
    private boolean isMulti;
    
    private double total=0; //Progress calculation
    private double done=0;
    private double progress=0;
    
    CheckAnagram(String in, boolean multi){
    	input=in;
    	isMulti=multi;
    }
    
    @Override
    public String doInBackground() throws InterruptedException{
        result="";
        if(!isMulti) singleWord();
        else multiWord();
        return result;
    }
    
    public boolean isWord(){
        return inDict;
    }
    
    private void singleWord(){ //[Finds Anagrams for single word search]
        String letters="";
        String filename;
        String matched;
        inDict=false;
        for(int i=0; i<input.length(); i++){
            if(!letters.contains(Character.toString(input.charAt(i)))){
                filename="com/agnibho/code/anagram/dictionary/"+Character.toString(input.charAt(i)).toUpperCase()+Integer.toString(input.length())+".txt";
                matched=singleMatch(filename); //(Function call)
                if(matched!=null){
                    if(result!=null)
                	result=result+matched;
                    else
                	result=matched;
                }
                letters=letters+Character.toString(input.charAt(i));
            }
        }
    }
    
    private void multiWord() throws InterruptedException{ //[Finds Anagrams for multi word search]
        String letters="";
        String filename;
        String matched;
        String wordList=null;
        input=input.replaceAll("\\s", "");
        for(int i=0; i<input.length(); i++){
            if(!letters.contains(Character.toString(input.charAt(i)))){
                for(int j=0; j<30; j++){
                    filename="com/agnibho/code/anagram/dictionary/"+Character.toString(input.charAt(i)).toUpperCase()+Integer.toString(j)+".txt";
                    matched=multiMatch(filename); //(Function Call)
                    if(matched!=null){
                        if(wordList!=null)
                            wordList=wordList+matched;
                        else
                            wordList=matched;
                    }
                }
                letters=letters+Character.toString(input.charAt(i));
            }
        }
        result=potentialSentence(wordList); //(Function call)
    }
    
    private String singleMatch(String file){ //[Finds Anagrams of the input from the specified file] 
        String found=null;
        String word;
        try{
            read=new java.util.Scanner(new java.io.BufferedInputStream(java.lang.ClassLoader.getSystemResourceAsStream(file)));
            while(read.hasNext()){
                word=read.next();
                word=word.toLowerCase();
                if(isAnagram.check(input, word)){
                    if(!word.equals(input)){
                        if(found!=null){
                            if(!found.contains(word)){
                                found=found+word+"/";
                            }
                        }
                        else found=word+"/";
                    }
                    else inDict=true;
                }
            }
        }catch(Exception ex){
            result=ex.toString();
        }
        finally{
            if(read!=null)
        	read.close();
        }
        return found;
    }
    
    private String multiMatch(String file){ //[Finds the list of words for calculation of multi-word Anagrams of the input] 
        String found=null;
        String word;
        try{
            read=new java.util.Scanner(new java.io.BufferedInputStream(java.lang.ClassLoader.getSystemResourceAsStream(file)));
            while(read.hasNext()){
        	word=read.next();
        	word=word.toLowerCase();
        	if(potentialWord(word)){ //(Function Call)
        	    if(found!=null){
        		if(!found.contains(word)){
        		    found=found+word+" ";
        		}
        	    }
        	    else found=word+" ";
        	}
            }
        }catch(Exception ex){
            result=ex.toString();
        }
        finally{
            if(read!=null)
        	read.close();
        }
        return found;
    }
    
    private boolean potentialWord(String word){ //[Finds out if the word in question is a candidate for the multiworded Anagram search of the input]
        String ref=input;
        boolean flag=true;
        for(int i=0; i<word.length(); i++){
            if(!(ref.contains(Character.toString(word.charAt(i))))){
                flag=false;
                break;
            }
            else ref=ref.replaceFirst(Character.toString(word.charAt(i)), " ");
        }
        return flag;
    }
    
    private String potentialSentence(String words) throws InterruptedException{ //[Finds out the multi-word Anagrams of the input from the word list]
        String[] list=words.split(" ");
        String holder="";
        String qualified="";
        int[] index=new int[input.length()];
        int count=0;
        int checkLength;
        
        if(list.length<3) //Progress calculation
            total=list.length;
        else
            total=(list.length*java.lang.Math.pow(list.length, 2)+list.length*java.lang.Math.pow(list.length, 1)+list.length*java.lang.Math.pow(list.length, 0));
        
        for(int i=0; i<list.length&&index[0]<list.length; i++){
            index[count]=i;
            checkLength=0;
            for(int j=0; j<=count; j++){
                checkLength=checkLength+list[index[j]].length();
            }
            
            if(checkLength==input.length()){
                for(int j=0; j<=count; j++){
                    holder=holder+" "+list[index[j]];
                }
                if(new IsAnagram().check(holder, input)){
                        if(!qualified.contains(holder)) qualified=qualified+holder+"/";
                }
                holder="";
            }
            else if(checkLength<input.length()){
                count++;
                i=-1;
            }
            
            if(i==(list.length-1)&&(index[0]<list.length)){
                while((index[count]>=(list.length-1))&&(count>0)){
                    count--;
                }
                i=index[count];
            }
            
            if(Thread.interrupted())
        	throw new InterruptedException();
            
            if(index.length<3) //Progress calculation
                done=index[0];
            else
                done=(index[0]*java.lang.Math.pow(list.length, 2)+index[1]*java.lang.Math.pow(list.length, 1)+index[2]*java.lang.Math.pow(list.length, 0));
            if(calcProgress()>progress){
            	progress=calcProgress();
                publish(progress);
            }
            
        }
        publish((double)100);
        return qualified;
    }
    
    private double calcProgress(){ //[Calculates the progress]
        return (double)(done*100)/total;
    }
}

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
 * The Graphical User Interface for Anagram
 */

#include <string> //For string
#include <vector> //For string vector
#include <algorithm> //For find

//For Qt Objects
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include <QScrollArea>
#include <QGridLayout>
#include <QMessageBox>

#include "validity.hpp" //For is_valid
#include "find.hpp" //To find anagrams

using namespace std;

//Defines the AnagramX class
class AnagramX : public QWidget{
public:
  AnagramX(QWidget *parent=0);
private slots:
  void findAnagrams(); //Launches the finder thread
  void showOutput(); //Displays the output
  void clearAll(); //Clears the text entry and output
  void showAbout(); //Shows an About messagebox
private:
  QLineEdit *entry; //Text input
  QCheckBox *multi; //Multi-word checkbox
  QTextEdit *result; //Program output
};

//Implements the AnagramX class
AnagramX::AnagramX(QWidget *parent)
  :QWidget(parent){

  QLabel *label = new QLabel("Anagram Finder", this); //The top label with formatted and centered text
  label->setFont(QFont("FreeSerif", 20));
  label->setAlignment(Qt::AlignCenter);

  entry = new QLineEdit(this); //The text input line
  connect(entry, &QLineEdit::returnPressed, this, &AnagramX::findAnagrams);

  QPushButton *find = new QPushButton("Find", this); //Button to trigger anagram search
  find->setAutoDefault(true);
  connect(find, &QPushButton::clicked, this, &AnagramX::findAnagrams);
  
  QPushButton *clear = new QPushButton("Clear", this); //Button to clear input and output
  clear->setAutoDefault(true);
  connect(clear, &QPushButton::clicked, this, &AnagramX::clearAll);
  
  QPushButton *about = new QPushButton("About", this); //Button to show an About message box
  about->setAutoDefault(true);
  connect(about, &QPushButton::clicked, this, &AnagramX::showAbout);

  multi = new QCheckBox("Allow multiple words", this); //The multi-word checkbox
  
  result = new QTextEdit(this); //The anagram output area
  result->setReadOnly(true);
  
  QScrollArea *scroll = new QScrollArea(this); //Wraps the output in a scrollable area
  scroll->setWidget(result);
  scroll->setWidgetResizable(true);
  
  QGridLayout *grid = new QGridLayout(this); //Organizes the other widgets in a grid
  grid->addWidget(label, 0, 0, 1, 3);
  grid->addWidget(entry, 1, 0, 1, 3);
  grid->addWidget(find, 2, 0, 1, 1);
  grid->addWidget(clear, 2, 1, 1, 1);
  grid->addWidget(about, 2, 2, 1, 1);
  grid->addWidget(multi, 3, 0, 1, 3);
  grid->addWidget(scroll, 4, 0, 1, 3);
}

//Finds the anagrams and launches the anagram finder thread
void AnagramX::findAnagrams(){
  //Define variables
  bool flag; //Holds multi-word checkbox state
  string word; //Holds the word
  word=AnagramX::entry->text().toStdString(); //Collects the input
  flag=AnagramX::multi->isChecked(); //Checks if multi-word allowed
  vector<string> anagram_list; //Recieves the found anagrams
  string plain_list=""; //Anagrams in a plain string form
  if(is_valid(word, flag)){ //If the input is valid find anagrams
    if(flag){
      anagram_list=find_anagram_multiword(word); //Thread to find the multi-word anagrams of the word
    }
    else{
      anagram_list=find_anagram(word); //Thread to find the single-word anagrams of the word
    }
    if(!anagram_list.empty()){ //If anagram_list is NOT empty
      { //Remove the word itself from the anagram list if present
	vector<string>::iterator i=std::find(anagram_list.begin(), anagram_list.end(), word);
	if(i!=anagram_list.end()){
	  anagram_list.erase(i);
	}
	else{
	  plain_list+=word+": The word is not present in the dictionary\n";
	}
      }
    }
    //Display Output
    if(anagram_list.size()>1){ //Initializes plain_list with plural
      plain_list+=word+": The following "+to_string(anagram_list.size())+" anagrams were found\n\n";
    }
    else if(anagram_list.size()>0){ //Initializes plain_list with singular
      plain_list+=word+": The following anagram was found\n\n";
    }
    else{ //No anagram found
      plain_list+=word+": No anagram was found\n";
    }
    for(string i : anagram_list){ //Converts the vector to newline separated strings
      plain_list+=i+"\n";
    }
    AnagramX::result->setText(QString::fromStdString(plain_list)); //Outputs the anagram strings
  }
  else{ //If input invalid show error
    QMessageBox::warning(this, "Error", "The entered word is not valid");
    return;
  }
}

//Clears input and output
void AnagramX::clearAll(){
  AnagramX::entry->setText("");
  AnagramX::result->setText("");
}

//Shows an About message
void AnagramX::showAbout(){
  QMessageBox::information(this, "About", "<h1>Anagram 2.0</h1>"
			   "<p>Copyright &copy; 2013-2015 Agnibho Mondal</p>"
			   "<a href='http://code.agnibho.com/anagram'>http://code.agnibho.com/anagram</a>");
}


//Start execution
int main(int argc, char *argv[]){
  
  QApplication app(argc, argv); //Qt Application object
  AnagramX window; //Instance of AnagramX, creates the main window
  
  window.resize(450, 450); //Set window size
  window.setWindowTitle("Anagram"); //Set window title
  window.show(); //Displays the window

  return app.exec(); //Enters the main execution loop
}

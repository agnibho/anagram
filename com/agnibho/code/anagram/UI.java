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

import java.awt.*;

import javax.swing.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.concurrent.ExecutionException;

/**
 *
 * @author SPARK
 */
@SuppressWarnings("serial")
public class UI extends JFrame implements ActionListener {

    String in;
    String out;
    String formatted;
    int count;

    CheckAnagram checker;

    public JLabel heading;
    public JTextField input;
    public JLabel wordInfo;
    public JProgressBar progressBar;
    public JButton help;
    public JButton find;
    public JButton cancel;
    public JRadioButton single, multi;
    public ButtonGroup buttons;
    public JEditorPane output;

    GroupLayout layout;

    public UI(){
	heading=new JLabel("Anagram Finder", JLabel.CENTER);
	heading.setFont(new java.awt.Font(null, 0, 24));

	input=new JTextField(30);
	input.setActionCommand("entry");

	wordInfo=new JLabel();

	progressBar=new JProgressBar(0, 100);
	progressBar.setValue(0);
	progressBar.setStringPainted(true);

	help=new JButton("Help");
	help.setActionCommand("help");

	find=new JButton("Find");
	find.setActionCommand("entry");
	
	cancel=new JButton("Cancel");
	cancel.setActionCommand("cancel");

	single=new JRadioButton("Single Word");
	multi=new JRadioButton("Multi Word");
	buttons=new ButtonGroup();
	buttons.add(single);
	buttons.add(multi);
	single.setSelected(true);

	output=new JEditorPane();
	output.setEditable(false);
	output.setContentType("text/html");
	JScrollPane scroll=new JScrollPane(output);
	scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
	scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
	scroll.setPreferredSize(new Dimension(600, 200));
	scroll.setMinimumSize(new Dimension(600, 200));

	input.addActionListener(this);
	find.addActionListener(this);
	cancel.addActionListener(this);
	help.addActionListener(this);

	layout=new GroupLayout(getContentPane());
	getContentPane().setLayout(layout);
	layout.setAutoCreateGaps(true);
	layout.setAutoCreateContainerGaps(true);
	layout.setVerticalGroup(
		layout.createSequentialGroup()
		.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE)
		.addComponent(heading, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
		.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE)
		.addGroup(layout.createParallelGroup(GroupLayout.Alignment.CENTER)
			.addComponent(input, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
			.addComponent(find)
			.addComponent(help))
			.addGroup(layout.createParallelGroup(GroupLayout.Alignment.CENTER)
				.addComponent(single)
				.addComponent(multi)
				.addComponent(wordInfo))
				.addComponent(scroll)
				.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, 50)
		);
	layout.setHorizontalGroup(
		layout.createParallelGroup()
		.addComponent(heading, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
		.addGroup(layout.createSequentialGroup()
			.addComponent(input)
			.addComponent(find)
			.addComponent(help))
			.addGroup(layout.createSequentialGroup()
				.addComponent(single)
				.addComponent(multi)
				.addComponent(wordInfo))
				.addComponent(scroll, 0, GroupLayout.PREFERRED_SIZE, Short.MAX_VALUE)
		);
	layout.linkSize(SwingConstants.HORIZONTAL, find, help);
	layout.linkSize(SwingConstants.HORIZONTAL, single, multi);

	setTitle("Anagram Finder");
	pack();
	setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	setSize(600, 400);
	setLocationRelativeTo(null);
	setResizable(false);
    }

    @Override
    public void actionPerformed(ActionEvent ae){
	if(ae.getActionCommand().equals("entry")){
	    in=input.getText();
	    if(!in.isEmpty()){
		if(new IsValid().isValid(in, multi.isSelected())){
		    formatted="";
		    input.setEnabled(false);
		    find.setEnabled(false);
		    wordInfo.setText("");
		    layout.replace(find, cancel);
		    layout.replace(wordInfo, progressBar);
		    progressBar.setIndeterminate(false);
		    output.setText("<html><p align=center><b>Search in progress...</b></p><p align=center><b>Please wait...</b></p></html>");
		    checker=new CheckAnagram(in, multi.isSelected()){
			@Override
			public void process(List <Double> progressValues){
			    double progressValue=progressValues.get(progressValues.size()-1);
			    if(progressValue<100)
				progressBar.setValue((int)progressValue);
			    else{
				progressBar.setIndeterminate(true);
				output.setText("<html><p align=center><b>Search Complete</b></p><p><b>Formatting the Results...</b></p></html>");
			    }
			}
			@Override
			public void done(){
			    try {
				out=get();
				if(out==null)
				    formatted=formatted+"<html><p align=center><b>No match found</b></p></html>";
				else{
				    formatted="<html>";
				    count=0;
				    for(int i=0; i<out.length();i++){
					if(out.charAt(i)=='/'){
					    formatted=formatted+"<br>";
					    count++;
					}
					else
					    formatted=formatted+out.charAt(i);
				    }
				    formatted=formatted+"<hr><p align=center>"+count+" matches found for<br><b>"+in+"</b></p></html>";
				}
				if(new IsPalindrome().check(in))
				    JOptionPane.showMessageDialog(null, "The word you entered is a palindrome", "Palindrome", JOptionPane.PLAIN_MESSAGE);
				if(single.isSelected()&&!checker.isWord())
				    wordInfo.setText("The word you entered does not exist in the Dictionary");
			    } catch (java.util.concurrent.CancellationException e) {
				formatted="<html><p align=center><b>Search cancelled</b></p></html>";
			    } catch (InterruptedException e) {
				formatted="<html><p align=center><b>"+e.toString()+"</b></p></html>";
			    } catch (ExecutionException e) {
				formatted="<html><p align=center><b>"+e.toString()+"</b></p></html>";
			    }
			    output.setText(formatted);
			    output.setCaretPosition(0);
			    input.setEnabled(true);
			    find.setEnabled(true);
			    layout.replace(cancel, find);
			    layout.replace(progressBar, wordInfo);
			}
		    };
		    checker.execute();
		}
		else
		    output.setText("<html><p align=center><b>Invalid entry</b></p></html>");
	    }else
		output.setText("<html><p align=center><b>Enter a word first</b></p></html>");
	}
	if(ae.getActionCommand().equals("help"))
	    JOptionPane.showMessageDialog(getContentPane(), "<html>"
		    + "<p>Enter a word in the provided field, choose singleword or multiword mode and click the search button to find its anagrams.</p>"
		    + "<p>The search results are dependent on the attached dictionary. The software is using UKACD for the word list.</p>"
		    + "<p>Grammatical filtering of the multi-worded search results is not avaiable."
		    + "<p align=centre><b>Warning:</b> Multi-worded searches may take long time.</p>"
		    + "<hr>"
		    + "Developed by:<br>"
		    + "Agnibho Mondal<br>"
		    +"http://code.agnibho.com/"
		    +"<hr>"
		    +"Anagram Copyright (C) 2013  Agnibho Mondal<br>"
		    +"This program comes with ABSOLUTELY NO WARRANTY<br>"
		    +"This is free software, and you are welcome to redistribute it under certain conditions"
		    +"</html>", "Anagram Finder Help", JOptionPane.PLAIN_MESSAGE);
	if(ae.getActionCommand().equals("cancel"))
	    checker.cancel(true);
    }



    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
	SwingUtilities.invokeLater(new Runnable(){
	    public void run(){
		try{
		    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		}
		catch (Exception ex){
		    ex.printStackTrace();
		}
		new UI().setVisible(true);
	    }
	});
    }
}

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/*
           ____   _____  _____ ____  _____  ______ 
     /\   |  _ \ / ____|/ ____/ __ \|  __ \|  ____|
    /  \  | |_) | (___ | |   | |  | | |  | | |__   
   / /\ \ |  _ < \___ \| |   | |  | | |  | |  __|  
  / ____ \| |_) |____) | |___| |__| | |__| | |____ 
 /_/    \_\____/|_____/ \_____\____/|_____/|______|
 
 
 The following code was written by Abdullah Akbar for his CS3345 (Data Structures) class at the University of Texas at Dallas
 
*/



public class ABAKP1{
	


	public static void main(String[] args) {
		File inputF;

		
		inputF = new File("TrieData.txt"); //Takes in the input file
		Trie theTrie = new Trie(); // Initializes the Trie we will use
		
		try{
			Scanner fileReader = new Scanner(inputF);
			while(fileReader.hasNextLine()){
				String theLine = fileReader.nextLine().trim(); //Read in the file line by line
				
				String[] splitLine = theLine.split(" "); //Split the command from the argument in each line
				String cmd = splitLine[0]; //Get the first word in each line (the command letter)
				if(cmd.equals("A")){
					String wordToInsert = splitLine[1]; // get word to insert from file line
					if(!theTrie.insert(wordToInsert)){ //If the word already exists, display the already exists method
						System.out.println(wordToInsert + " already exists");
					}
					else{
						System.out.println(wordToInsert + " inserted"); //Otherwise tell the user it was inserted
					}
				}
				else if(cmd.equals("D")){
					String wordToDelete = splitLine[1]; //Get the word to delete from the file line
					if(theTrie.delete(wordToDelete)){ //Check if the word exists or not and tell the user the result of the action
						System.out.println(wordToDelete + " deleted");
					}
					else{
						System.out.println(wordToDelete + " not found");
					}
				}
				else if(cmd.equals("S")){
					String wordToSearch = splitLine[1]; //Get the word to search from the file line
					if(theTrie.isPresent(wordToSearch)){ //Check if the word is found and tell the user if so
						System.out.println(wordToSearch + " found");

					}
					else{
						System.out.println(wordToSearch + " not found");
					}
				}
				else if(cmd.equals("L")){
					theTrie.listAll(); //List out all of the words in the Trie
				}
				else if(cmd.equals("T")){
					for(int x = 1; x < splitLine.length; x++){ //Go through all the words in the line, not including the command letter
						
						if(splitLine[x].length() > 0){ //In case we accidentally pick up a null string
							if(!theTrie.isPresent(splitLine[x])){
								System.out.println("Spelling mistake " + splitLine[x]); //Tell the user 'Spelling Mistake' if the word does not exist in the Trie
							}
						}
					}
				}
				else if(cmd.equals("M")){ //Print number of members in the Trie
					System.out.print("Membership is ");
					System.out.println(theTrie.membership());
				}
				else if(cmd.equals("E")){
					break; //End the program if we reach the E command
				}
				
			}
			
		}
		catch(FileNotFoundException e){
			System.out.println("Error: File doesn't exist!"); //Catch error if the file doesn't exist
		}
	}
}



class Trie{
	Node head;
	int members;
	
	public Trie(){ //Constructor: sets the head and the members to 0
		this.head = new Node(); 
		this.members = 0;
	}
	
	public boolean insert(String s){ 
		Node nodeOn = this.head;
		for(int i = 0; i < s.length(); i++){ //For each character in the string, go to its respective node
			char charOn = s.charAt(i);
			if(nodeOn.getLetter(charOn) == null){ //If the child with the character we are on doesn't exist, add the child
				nodeOn = nodeOn.addLetter(charOn);
			}
			else{
				nodeOn = nodeOn.getLetter(charOn); //Otherwise go to the child
			}
			
		}
		if(nodeOn.terminal == true){
			return false; //The word already exists; return false
		}
		nodeOn.endWord(); //Mark the last node as the end of a word
		this.members++; //Increment members
		return true;
	}
	
	
	public boolean delete(String s){
		Node nodeOn = this.head;
		Node[] arrayPath = new Node[s.length()]; //Will be used to store and delete nodes traversed later
		for(int i = 0; i < s.length(); i++){
			char charOn = s.charAt(i);
			if(nodeOn.getLetter(charOn) == null){
				return false; //The word doesn't exist; return false
			}
			
			nodeOn = nodeOn.getLetter(charOn);
			arrayPath[i] = nodeOn;
			
			
		}
		if(nodeOn.terminal == false){
			return false; //The word exists but isn't marked as a word; return false
		}
		nodeOn.terminal = false;
		for(int q = s.length() - 1; q > -1; q--){ //Go backwards on the node path we took and check if each node has any children; if so, break out
			if(arrayPath[q].outDegree > 0){
				break;
			}
			arrayPath[q] = null;
			
			//When we delete a node, decrement the parent outdegree by one
			if(q > 0){
				arrayPath[q - 1].outDegree--;
			}
			else{
				this.head.outDegree--;
			}
		}
		this.members--; //decrement members
		return true;
	}
	
	public boolean isPresent(String s){ //Follows the string and sees if the end of the string exists and has a true terminal
		Node nodeOn = this.head;
		for(int i = 0; i < s.length(); i++){
			char charOn = s.charAt(i);
			nodeOn = nodeOn.getLetter(charOn);
			if(nodeOn == null){
				return false;
			}
			
		}
		if(nodeOn.terminal == true){
			return true;
		}
		return false;
		
	}
	
	
	
	
	
	public int membership(){
		
		return this.members;
	}
	
	public void listAll(){
		String returner = ""; //pass empty string into listAll()
		listAll(head, returner);
	}
	
	private void listAll(Node nodeOn, String current){ //DFS to go in and list all the words alphabetically
		for(int i = 0; i < 26; i++){
			if(nodeOn.children[i] != null){
				char charToAdd = (char)(97 + i); //Change child index to its respective ascii val
				String newStr = current + charToAdd;
				if(nodeOn.children[i].terminal){
					System.out.println(newStr);
				}
				listAll(nodeOn.children[i], newStr);
			}
		}
	}
	
}


class Node{
	boolean terminal;
	int outDegree;
	Node[] children;
	
	public Node(){
		this.children = new Node[26]; //Each child has an index corresponding to its character's place in the alphabet
		this.outDegree = 0;
		this.terminal = false;
	}
	
	public Node getLetter(char letter){
		int letterIndex = (int)letter - 97;
		return this.children[letterIndex]; //Get the child node corresponding to the letter passed
		
	}
	public Node addLetter(char letter){ //Add the child node corresponding to the letter passed
		int letterIndex = (int)letter - 97;
		this.children[letterIndex] = new Node();
		this.outDegree++;
		return this.children[letterIndex];
	}
	
	public void endWord(){
		this.terminal = true; //Mark this node as the end of the word
	}
}
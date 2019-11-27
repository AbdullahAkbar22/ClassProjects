import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/*
           ____   _____  _____ ____  _____  ______ 
     /\   |  _ \ / ____|/ ____/ __ \|  __ \|  ____|
    /  \  | |_) | (___ | |   | |  | | |  | | |__   
   / /\ \ |  _ < \___ \| |   | |  | | |  | |  __|  
  / ____ \| |_) |____) | |___| |__| | |__| | |____ 
 /_/    \_\____/|_____/ \_____\____/|_____/|______|
 
 
 The following code was written by Abdullah Akbar for his CS3345 (Data Structures) class at the University of Texas at Dallas
 
*/



public class ABAKP2{
	public static void main(String[] args) {
		File inputF;

		
		inputF = new File("Hash_in.txt");
		
		HashTable theTable = new HashTable(0);
		try{
			Scanner fileReader = new Scanner(inputF);
			int lineOn = 0;
			
			
			while(fileReader.hasNextLine()){
				String theLine = fileReader.nextLine().trim(); //Read in the file line by line
				String[] splitLine = theLine.split(" ");
				String command = splitLine[0];
				if(lineOn == 0){
					theTable.setType(command.charAt(0));
				}
				else if(lineOn == 1){
					int tableSize = Integer.parseInt(command);
					
					theTable.setSize(tableSize);
				}
				else if(lineOn == 2){
					theTable.setProbNumb(Integer.parseInt(command));
				}
				else{
					String k;
					long val;
					switch(command){
						case "I":
							k = splitLine[1];
							val = Long.parseLong(splitLine[2]);
							if(theTable.insert(k, val)){
								System.out.println("Key " + k + " inserted"); 
							}
							else{
								System.out.println("Key " + k + " already exists");
							}
						break;
						case "J":
							k = splitLine[1];
							val = Long.parseLong(splitLine[2]);
							theTable.insert(k, val);
						break;
						case "D":
							k = splitLine[1];
							
							if(theTable.delete(k)){
								System.out.println("Key " + k + " deleted"); 
							}
							else{
								System.out.println("Key " + k + " doesn't exist");
							}
						break;
						case "F":
							k = splitLine[1];
							
							theTable.delete(k);
						break;
						case "S":
							k = splitLine[1];
							val = theTable.search(k);
							if(val > 0){
								System.out.print("Key " + k + " found, record = "); 
								System.out.println(val);
							}
							else{
								System.out.println("Key " + k + " doesn't exist");
							}
						break;
						case "T":
							k = splitLine[1];
							theTable.search(k);
						break;
						case "P":
							System.out.print("Number of records in table = ");
							System.out.println(theTable.itemsEntered);
						break;
						case "C":
							theTable.clearTable();
						break;
						case "Q":
							System.out.print(theTable.successfulInserts);
							System.out.print(" ");
							System.out.print(theTable.successfulProbes);
							System.out.print(" ");
							System.out.print(theTable.successfulSearches);
							System.out.print(" ");
							System.out.print(theTable.successfulSearchProbes);
							System.out.print(" ");
							System.out.print(theTable.unSuccessfulSearches);
							System.out.print(" ");
							System.out.print(theTable.unSuccessfulProbes);
							System.out.println();
						break;
						case "H":
							k = splitLine[1];
							System.out.println(k + " " + theTable.hash(k, theTable.size()));
						break;
					}
				
				
				}
				lineOn++;
			}
			
		}
		catch(FileNotFoundException e){
			System.out.println("Error: File doesn't exist!"); //Catch error if the file doesn't exist
		}
		
		
	}



}



class Node{
	private String key;
	private long value;
	Node (String ky, long val){
		key = ky;
		value = val;
		
	}
	
	void clearNode(){
		key = "";
		value = -1;
	}
	String getKey(){
		return key;
	}
	long getVal(){
		return value;
	}
}

class HashTable{
	private int tableSize;
	char probeType; // Q for quadratic, D for double hashing
	int probeNumb = -1; // For use with double hashing
	Node[] table; //data table
	int itemsEntered = 0;
	
	long successfulProbes = 0;
	long successfulInserts = 0;
	long successfulSearches = 0;
	long successfulSearchProbes = 0;
	long unSuccessfulProbes = 0;
	long unSuccessfulSearches = 0;
	
	
	
	static int hash(String key, int tableSize){
		int current = 0;
		for(int i = 0; i < key.length(); i++){
			current = current * 31 + (int)(key.charAt(i));
		
		}
		
		return Integer.remainderUnsigned(current, tableSize);
		
	}
	
	int secondHash(int passed){
		
		return probeNumb - Integer.remainderUnsigned(passed, probeNumb);
	}
	
	boolean insert(String key, long val){
		
		int hashVal = hash(key, tableSize);
	
		int turnOn = 0;
		int currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * turnOn)), tableSize);
		
		//Quadratic hashing stuff:
		if(probeType == 'Q'){
			//Loop to make sure no index contains the thing we want to add
			while(turnOn <= tableSize * .5){
				if(table[currentIndex] != null){
					if(table[currentIndex].getKey().equals(key)){
						return false;
					}
				}
				turnOn++;
				currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * turnOn)), tableSize);
			}
			while(table[currentIndex] != null){
				if(table[currentIndex].getKey().equals(key)){
					return false;
				}
				if(table[currentIndex] == null){
					break;
				}
				
				turnOn++;
				currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * turnOn)), tableSize);
				//unSuccessfulProbes++;
			}
			table[currentIndex] = new Node(key, val);
			itemsEntered++;
			successfulInserts++;
			successfulProbes++;
		}
		else if(probeType == 'D'){
			//Loop to make sure no index contains the thing we want to add
			while(turnOn <= tableSize ){
				if(table[currentIndex] != null){
					if(table[currentIndex].getKey().equals(key)){
						return false;
					}
				}
				turnOn++;
				currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * secondHash(hashVal))), tableSize);
			}
			while(table[currentIndex] != null){
				if(table[currentIndex].getKey().equals(key)){
					return false;
				}
				if(table[currentIndex] == null){
					break;
				}
				
				turnOn++;
				currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * secondHash(hashVal))), tableSize);
			}
			table[currentIndex] = new Node(key, val);
			itemsEntered++;
			successfulInserts++;
			successfulProbes++;
			//System.out.print("inserted into: ");
			//System.out.println(currentIndex);
			
		}
		return true;
	}
	
	boolean delete(String key){
		
		
		int hashVal = hash(key, tableSize);
	
		
		int turnOn = 0;
		int currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * turnOn)), tableSize);
		//Check if any index contains the thing we want to add:
		if(probeType == 'Q'){
			while(turnOn <= tableSize * .5){
				if(table[currentIndex] != null){
					if(table[currentIndex].getKey().equals(key)){
						table[currentIndex] = null;
						itemsEntered--;
						if(itemsEntered < 0){
							itemsEntered = 0;
						}
						successfulSearches++;
						successfulSearchProbes++;
						
						return true;
					}
				}
				turnOn++;
				currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * turnOn)), tableSize);
				
			}
			unSuccessfulSearches++;
			//unSuccessfulProbes++;
		}
		else if(probeType == 'D'){
			while(turnOn <= tableSize ){
				if(table[currentIndex] != null){
					if(table[currentIndex].getKey().equals(key)){
						table[currentIndex] = null;
						itemsEntered--;
						if(itemsEntered < 0){
							itemsEntered = 0;
						}
						successfulSearches++;
						successfulSearchProbes++;
						
						return true;
					}
				}
				turnOn++;
				currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * secondHash(hashVal))), tableSize);
				
			}
			unSuccessfulSearches++;
			//unSuccessfulProbes++;
			
		}
		return false;
		
	}
	
	long search(String key){
		int hashVal = hash(key, tableSize);
	
		
		int turnOn = 0;
		int currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * turnOn)), tableSize);
		//Check if any index contains the thing we want to add:
		if(probeType == 'Q'){
			while(turnOn <= tableSize * .5){
				if(table[currentIndex] != null){
					if(table[currentIndex].getKey().equals(key)){
						successfulSearches++;
						successfulSearchProbes++;
						return table[currentIndex].getVal();
					}
				}
				turnOn++;
				currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * turnOn)), tableSize);
				
			}
			unSuccessfulSearches++;
			unSuccessfulProbes++;
		}
		else if(probeType == 'D'){
			while(turnOn <= tableSize ){
				if(table[currentIndex] != null){
					//System.out.println("Testing " + key + " with: " + table[currentIndex].getKey());
					//System.out.print("this is index: ");
					//System.out.println(currentIndex);
					if(table[currentIndex].getKey().equals(key)){
						successfulSearches++;
						successfulSearchProbes++;
						return table[currentIndex].getVal();
					}
				}
				turnOn++;
				currentIndex = Integer.remainderUnsigned((hashVal + (turnOn * secondHash(hashVal))), tableSize);
				
			}
			unSuccessfulSearches++;
			unSuccessfulProbes++;
		}
		return -1;
		
	}
	void clearTable(){
		table = new Node[tableSize];
		itemsEntered = 0;
		successfulProbes = 0;
		successfulInserts = 0;
		successfulSearches = 0;
		successfulSearchProbes = 0;
		unSuccessfulProbes = 0;
		unSuccessfulSearches = 0;
	}
	
	int size(){
		return tableSize;
		
	}
	
	void setType(char pt){
		probeType = pt;
	}
	
	void setProbNumb(int numbToSet){
		probeNumb = numbToSet;
	}
	void setSize(int sizeToSet){
		tableSize = sizeToSet;
		table = new Node[tableSize];
		
	}
	
	HashTable(int size){
		tableSize = size;
	}
}
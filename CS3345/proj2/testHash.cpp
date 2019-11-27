#include <iostream>
#include <string>
using namespace std;

int hashThing(string key, int tableSize){
	int current = 0;
	for(int i = 0; i < key.size(); i++){
		current = current * 31 + (int)(key[i]);
	
	}
	
	return current % tableSize;
}


int hashTwo(){
	int arrayT[4] = {2, 0, 3, 1};
	int current = 0;
	for(int i = 0; i < 4; i++){
		current = current * 2 + (int)(arrayT[i]);
	
	}
	
	return current;
}

int main(){


	cout << hashThing("ABCD", 23) << endl;
	cout << hashTwo() << endl;

}
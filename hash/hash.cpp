// hashing.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

using namespace std;

/*

HashCreate (lexicon L, int m); // Create T, A. T will have m slots; A should be 8m
HashEmpty (lexicon L); // Check if L is empty
HashFull (lexicon L); // Check if L can maintain more words
HashPrint (lexicon L); // Print of L
HashInsert (lexicon L, word w); //Insert w into L (and T and A)
HashDelete (lexicon L, word w); //Delete w from L (but not necessarily from A)
HashSearch (lexicon L, word w); //Search for string in L (and this means T)
HashBatch (lexicon L, file filename)

*/
int tableSize;

int convertToAscii(string s);
void HashCreate(int m); // Create T, A. T will have m slots; A should be 8m

int main(int argc, char* argv[])
{
	string s = "alex";
	cout << s << " : " << convertToAscii(s) << endl;
	HashCreate(50);
	cout << "tablesize: " << tableSize << endl;
	return 0;
}

int convertToAscii(string s) {
	int asciiVal = 0;
	char x;
	for (int i = 0; i < s.length(); i++)
	{
		x = s[i];
		asciiVal += (int)x;
	}
	return asciiVal;
}

void HashCreate(int m) {
	tableSize = m;
}
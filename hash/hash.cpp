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

#include <iostream>
#include <string>
#include <vector>

#define M 11

using namespace std;

void insertWord(char arr[], string s);
void initArr(int T[], char A[]);
int hashFunction(int k, int i);
int hashSearch(int T[], int k);
void hashDelete(int T[], int k);
void hashInsert(int T[], int k);
int convertToAscii(string s);
int charArrLoc;
string currWord;
int startOfNextWord;
//int M;


int main(int argc, char* argv[])
{
	charArrLoc = 0;
	int T[M];
	char A[8 * M];

	initArr(T, A);

	currWord = "alex";
	int aval = convertToAscii(currWord);
	cout << "ascii val: " << aval << endl;

	hashInsert(T, aval);
	insertWord(A, currWord);

	

	currWord = "tom";
	int aval2 = convertToAscii(currWord);
	cout << "ascii val: " << aval2 << endl;

	hashInsert(T, aval2);
	insertWord(A, currWord);



	currWord = "jerry";
	int aval3 = convertToAscii(currWord);
	cout << "ascii val: " << aval3 << endl;

	hashInsert(T, aval3);
	insertWord(A, currWord);

	cout << "T:\t";

	for (int i = 0; i < M; i++)
	{
		cout << T[i] << " ";
	}

	cout << "\nA:\t";

	for (int i = 0; i < 8*M; i++)
	{
		cout << A[i] << " ";
	}

	cout << endl;

	return 0;
}

void insertWord(char arr[], string s) {
	
	int endIdx = startOfNextWord + s.length();
	cout << "start: " << startOfNextWord << " end: " << endIdx << endl;
	int wordIdx = 0;
	for (int i = startOfNextWord; i <= endIdx; i++)
	{
		if (i == endIdx) {
			arr[i] = '\\';
		}
		else {
			arr[i] = s[wordIdx];
			wordIdx++;
		}
	}

	startOfNextWord += currWord.length() + 1;

}

void initArr(int T[], char A[]) {
	for (int i = 0; i < M; i++) {
		T[i] = -1;
	}

	for (int i = 0; i < 8 * M; i++)
	{
		A[i] = ' ';
	}
}

int hashFunction(int k, int i)
{
	int h = k % M;
	int x = (h + (i * i)) % M;

	return x;
}

int hashSearch(int T[], int k)
{
	int i;
	int j;

	i = 0;

	while (i != M) {
		j = hashFunction(k, i);

		if (T[j] == k) {
			return j;
		}

		i++;
	}

	return -1;
}

void hashDelete(int T[], int k)
{
	int i;
	int j;

	i = hashSearch(T, k);

	if (i != -1) {
		T[i] = -2;
	}
	else {
		cout << "Element not found\n";
	}

	return;
}

void hashInsert(int T[], int k)
{
	cout << "length: " << startOfNextWord << endl;

	int i = 0;
	int j;

	while (i != M) {
		j = hashFunction(k, i);
		if (T[j] == -1 || T[j] == -2) {
			T[j] = startOfNextWord;
			return;
		}
		i++;
	}

	if (i == M) {
		cout << "Hash table overflow\n";
	}

	return;
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
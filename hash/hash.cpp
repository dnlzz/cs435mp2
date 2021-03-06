/*

-1 : Available
-2 : Deleted

Bugs: Deleting words of length 1 sometimes causes other entries in array A to be partially deleted.

*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void insertWord(char arr[], string s);
void initArr(int T[], char A[]);
void hashPrint();
int hashFunction(int k, int i);
int hashSearch(int T[], int k);
void hashDelete(int T[], int k);
void hashInsert(int T[], int k);
bool hashEmpty();
bool hashFull();
void HashBatch(string fn);
void resize(char A[]);
int convertToAscii(string s);
int charArrLoc;
string currWord;
int startOfNextWord;
int M = 0;
int size;
int numWords;
int *T;
char *A, *newArray;


int main(int argc, char* argv[])
{

	HashBatch(argv[1]);

	return 0;
}

bool hashEmpty() {
	return numWords == 0;
}

bool hashFull() {
	return numWords == M;
}

void insertWord(char arr[], string s) {
	
	int endIdx = startOfNextWord + s.length();
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

void hashPrint() {
	cout << "T:\n";

	for (int i = 0; i < M; i++)
	{
		cout << i << " : " << T[i] << endl;
	}

	cout << "\nA:\t";

	for (int i = 0; i < size; i++)
	{
		cout << A[i] << " ";
	}

	cout << endl;
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
	int endIdx;
	int wordIdx = 0;

	i = 0;

	while (i != M) {
		j = hashFunction(k, i);


		if (T[j] >= 0)
		{
			endIdx = T[j] + currWord.length() - 1;

			for (int k = T[j]; k < endIdx; k++)
			{
				if (A[k] == currWord[wordIdx])
				{
					wordIdx++;
				}
				else {
					break;
				}
				return j;
			}
		}

		i++;
	}

	return -1;
}

void hashDelete(int T[], int k)
{
	int i, startIdx, endIdx;

	i = hashSearch(T, k);

	startIdx = T[i];
	endIdx = T[i] + currWord.length();

	if (i != -1) {
		T[i] = -2;

		for (int k = startIdx; k < endIdx; k++)
		{
			A[k] = '*';
		}

		numWords--;

	}
	else {
		cout << "Element not found\n";
	}

	return;
}

void hashInsert(int T[], int k)
{

	int i = 0;
	int j;

	while (i != M) {
		j = hashFunction(k, i);
		if (T[j] == -1 || T[j] == -2) {
			T[j] = startOfNextWord;
			numWords++;
			return;
		}
		i++;
	}

	if (i == M) {
		cout << "Hash table overflow\n";
	}

	return;
}

void HashBatch(string fn) {

	cout << fn << endl;

	ifstream ifs;
	ifs.open(fn);
	string str;
	int action;
	string val;
	int wVal;
	int pos;
	numWords = 0;

	while (ifs >> str)
	{
		action = atoi(str.c_str());

		switch (action)
		{
		case 10:
			ifs >> val;
			currWord = val;
			wVal = convertToAscii(currWord);
			hashInsert(T, wVal);
			if (startOfNextWord + currWord.length() > size)
			{
				resize(A);
				insertWord(A, currWord);
			}
			else {
				insertWord(A, currWord);
			}
			
			break;
		case 11:
			ifs >> val;
			currWord = val;
			wVal = convertToAscii(val);
			hashDelete(T, wVal);
			break;
		case 12:
			ifs >> val;
			currWord = val;
			wVal = convertToAscii(val);
			pos = hashSearch(T, wVal);
			if (pos >= 0) {
				cout << val << " found at index " << pos << endl;
			}
			else {
				cout << val << " was not found" << endl;
			}
			break;
		case 13:
			hashPrint();
			break;
		case 14:
			ifs >> str;
			M = atoi(str.c_str());
			charArrLoc = 0;
			T = new int[M];
			A = new char[8 * M];
			size = 8 * M;
			initArr(T, A);
			break;
		default:
			break;
		}

	}
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

void resize(char arr[]) {
	newArray = new char[size * 2];
	for (int i = 0; i < size * 2; i++)
	{
		if (i < size)
		{
			newArray[i] = arr[i];
		}
		else
		{
			newArray[i] = ' ';
		}
	}
		A = newArray;
		size *= 2;
}
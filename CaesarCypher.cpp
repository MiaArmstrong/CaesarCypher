// this program encrypts and decrypts a file using Caesar cypher
// By Mia Armstrong 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
 
using namespace std;

const int ARRAYSIZE = 128;
  
void characterCount(char ch, int list[]);
void calcShift( int& shift, int list[]);
void writeOutput(ifstream &in, ofstream &out, int shift);

int main()
{
	int asciiCode = 0,
		shift = 0;
	string filename;
	string reply;
	char ch;
	ifstream infile;
	ofstream outfile;

  //Open input file
	cout << "Input file name: ";
	getline(cin, filename);
	infile.open(filename.c_str());

	if ( ! infile.is_open()) {      //checks the file opens successfully 
		cout<< "Unable to open input file: "<< endl;
		cout<< "Press ENTER to continue. "<< endl;
		getline (cin, reply);
		exit(1);
	}
  
      //open the outfile, if it doesn't exist, the program will automatically create one.
	cout << "Output file name: ";
	getline(cin, filename);
	outfile.open(filename.c_str());
	int list[ARRAYSIZE] = {0}; //Setting everything to 0
	while (infile.peek() != EOF) //Until the end of file is reached...
	{
		infile.get(ch);
		characterCount(ch, list); //Go count the character
	}
  
   //Rewind it
	infile.clear();
	infile.seekg(0);
	calcShift ( shift, list ); //Calculate the shift based on the most characters counted
	writeOutput(infile, outfile, shift); //Decypher and write to the other document
	return 0;
}


void characterCount(char ch, int list[])
{
	if (ch >= 'A' && ch <= 'z') //If the character is in the alphabet...
	{
		int asciiCode = 0;
		asciiCode = static_cast<int>(ch); //Change it to the ASCII number
		list[asciiCode]++; //And note it on the array
	}
}


void calcShift( int& shift, int list[])
{
	int maxIndex = 0, //Asuming that list[0] is the largest
		largest = 0;
	
	for (int i = 1; i < ARRAYSIZE; i++)
	{
		if (list[maxIndex] < list[i])
			maxIndex = i; //If this is true, change the largest index
	}
	
	largest = maxIndex; //When the maxIndex is found, then that has the largest number.
	//shift = -12;
	
	if (largest >= 65 && largest <= 90) //Calculate shift with E (for upper-case letters)
		shift = largest - 69;
	
	else if (largest >= 97 && largest <= 122) //For lower-case letters (e)
		shift = largest - 101;
}


void writeOutput(ifstream &infile, ofstream &outfile, int shift)
{
	char ch;
	int asciiCode = 0;
	
	while (infile.peek() != EOF) { //Until it is the end of the file...
		infile.get(ch); //Get the next character
		if (ch >= 'A' && ch <= 'z') //If the character is in the alphabet...
		{
			asciiCode = static_cast<int>(ch); //Change it to the ASCII number
			asciiCode += shift; //Do the shift
			ch = static_cast<char>(asciiCode); //Change it to the shifted letter
		}
		outfile << ch; //Print to the outfile
	}
}
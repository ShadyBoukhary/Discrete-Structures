/************************************************************************
*							  Shady Boukhary							*
*					Discrete Structures and Analysis					*
*								Wuthrich								*
*						 HW1: Due September 25th 2017					*
* This program reads 16 lines of 16 on or off strings each, which		*
* represent options for an assignment. The program reads the string,	*
* then it determines the flag number it's associated with, with every	*
* on or off bveing associated with a number of bit out of 2 bytes.		*
* Finally, it prints the flag number to the screen along with the		*
*				number of corresponding assignment.						*
*************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

// constants for assignment options 
// represented by 2 bytes
#define TIME_LIMIT 1
#define PRINTING_ALLOWED 2
#define SCRAMBLED 4
#define PASSWORD 8
#define POINT_VALUES_SHOWN 16
#define QUESTION_TITLES_SHOWN 32
#define REFERENCE_SHOWN 64
#define ACCESS_EXTERNAL 128
#define FORMULAS_SHOWN 256
#define ONLY_1_ATTEMPT 512
#define LETTER_CASE_REQUIRED 1024
#define LATE_ADMISSIONS 2048
#define ACCESS_EBOOK 4096
#define ACCESS_CHECK_WORK 8192
#define CORRECT_SPACING 16384
#define ASK_INSTRUCTOR 32768

using namespace std;
// prototypes for all functions
void openFiles(ifstream&, ofstream&);
unsigned short readFile(ifstream&);
void findFlag(string, unsigned short&, int);
void printHeader(ofstream&);
void printOutput(ofstream&, unsigned short, int&);
void goodBye(ofstream&);
void closeFiles(ifstream&, ofstream&);

int main()
{
	// create ifstream and ofstream objects
    ifstream infile;
    ofstream outfile;
    unsigned short flag = 0;
    int assignmentNum = 1;
    
    openFiles(infile, outfile);		// open all files
    printHeader(outfile);		// print header
	
	// process 10 lines of input
    for (int x = 0; x < 10; x++)
    {    
        flag = readFile(infile);		// read and get the final flag
        printOutput(outfile, flag, assignmentNum);	// print output
    }
    goodBye(outfile);	// print final mesasge

    closeFiles(infile, outfile);	// close all files
    return 0;
}
/**************************************	*
*			openFiles()					*
* parameters: ifstream& and ofstream&	*
* returns: none							*
* opens input and output files			*
*****************************************/
void openFiles(ifstream& infile, ofstream& outfile)
{
    infile.open("on_off.dat");
    outfile.open("boukhary_shady_bits.out");
}

/**************************************	*
*			   readFile()				*
* parameters: ifstream&					*
* returns: unsigned short				*
* reads first word in a line, then		*
* passes it to findFlag to be processed	*
*****************************************/
unsigned short readFile(ifstream& infile)
{
    string state;
    unsigned short flag = 0;
    for (int x = 1; x <= 16; x++ )
    {
        infile >> state;	// read one string
        findFlag(state, flag, x);	// pass it to be processed
    }
    return flag;		// return final flag 
}

/**************************************	*
*			   findFlag()				*
* parameters: string, unsigned short,int*
* returns: none							*
* performs a bitwise OR on flag when	*
* state is on							*
*****************************************/
void findFlag(string state, unsigned short& flag, int bitNum)
{
	if (state == "on" || state == "ON")
	{
		// OR with corresponding option 
		switch (bitNum)
		{
		case 1:		
			flag = flag | ASK_INSTRUCTOR;
			break;
		case 2:
			flag = flag | CORRECT_SPACING;
			break;
		case 3:
			flag = flag | ACCESS_CHECK_WORK;
			break;
		case 4:
			flag = flag | ACCESS_EBOOK;
			break;
		case 5:
			flag = flag | LATE_ADMISSIONS;
			break;
		case 6:
			flag = flag | LETTER_CASE_REQUIRED;
			break;
		case 7:
			flag = flag | ONLY_1_ATTEMPT;
			break;
		case 8:
			flag = flag | FORMULAS_SHOWN;
			break;
		case 9:
			flag = flag | ACCESS_EXTERNAL;
			break;
		case 10:
			flag = flag | REFERENCE_SHOWN;
			break;
		case 11:
			flag = flag | QUESTION_TITLES_SHOWN;
			break;
		case 12:
			flag = flag | POINT_VALUES_SHOWN;
			break;
		case 13:
			flag = flag | PASSWORD;
			break;
		case 14:
			flag = flag | SCRAMBLED;
			break;
		case 15:
			flag = flag | PRINTING_ALLOWED;
			break;
		case 16:
			flag = flag | TIME_LIMIT;
			break;
		}
	}
}
/**************************************	*
*			printHeader()				*
* parameters: ofstream&					*
* returns: none							*
* prints header in output file			*
*****************************************/
void printHeader(ofstream& outfile)
{
    outfile << "**********Shady Boukhary**********\n\n\n"
            << "Assignment #" << setw(20) << "Flag\n"
            << "------------" << setw(21) << "----\n\n";
}

/*****************************************
*			printtOutput()				 *
* parameters: ofstream, unsigned shot,int*				
* returns: none							 *
* prints flag and corresponding 		 *
* assignment number						 *
*****************************************/
void printOutput(ofstream& outfile, unsigned short flag, int& num)
{
    outfile << left << setw(2) << num << right << setw(29) << flag << endl;
    num++;		// increment assignment
}
/**************************************	*
*			goofBye()					*
* parameters: ofstream&					*
* returns: none							*
* prints goodBye message				*
*****************************************/
void goodBye(ofstream& outfile)
{
    outfile << "\n\nTHANK YOU FOR USING THIS PROGRAM";
}

/**************************************	*
*			closeFiles()				*
* parameters: ifstream& and ofstream&	*
* returns: none							*
* closes input and output files			*
*****************************************/
void closeFiles(ifstream& infile, ofstream& outfile)
{
    infile.close();
    outfile.close();
}

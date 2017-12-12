/*	Shady Boukhary
	Discrete Structures and Analysis
	CMPS 2433-101
	Wuthrich
	November 16th, November	*/


#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


double factRec(double);
double factIter(double);

int main()
{
	char choice;
	double n, r, answer;
	ifstream infile;
	ofstream outfile;

	// open files
	infile.open("combo.dat");
	outfile.open("boukhary_shady_prog3.txt");

	// if failed to open
	if (!(infile && outfile))
	{
		cout << "Failed to open files.";
		exit(1);
	}

	outfile << "Shady Boukhary\n\n";
	outfile << setprecision(80);
	// read input file
	while (infile >> choice)
	{
		infile >> n >> r;
		if (choice == 'P')
		{
			// calculate permutation
			answer = factRec(n) / factIter(n - r);
			outfile << "P " << n << " " << r << " = " << answer << endl;
		}
		else
		{
			// calculate combination
			answer = factRec(n) / (factIter(n - r) * factRec(r));
			outfile << "C " << n << " " << r << " = " << answer << endl;
		}
	}

	// close files
	infile.close();
	outfile.close();
	return 0;
}

// calculates factorial of a number recursively
double factRec(double x)
{
	// base case
	if (x <= 1)
		return 1;
	else
		return factRec(x - 1) * x;
}

// calculates factorial of a number iteratively
double factIter(double num)
{
	double answer = num;

	if (num == 0)
		return 1;

	for (int x = 1; x < num; x++)
	{
		answer *= (num - x);
	}
	return answer;
}

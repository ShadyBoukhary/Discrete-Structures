/* **********************************************************************
	Shady Boukhary
	Wuthrich
	Discrete Structures and Analysis
	October 24th, 2017

	Purpose: This program finds the nth term of a first-order 
	linear reccurrance relation using a recursive and a non recusrsive
	method. Finally, it prints out the answer to an output file

	**********************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

// prototypes 
int nonRecursive(int, int, int, int);
int recursive(int, int, int, int);

int main()
{
	int k, m, a0, n, ans = 0;
	int equation = 1;
	ifstream infile;
	ofstream outfile;

	infile.open("recur.dat");
	outfile.open("boukhary_shady_recur.out");

	// if input file failed to open
	if (!infile)
	{
		cout << "Failed to open input file.";
		exit(1);
	}
	outfile << "Shady Boukhary\n\n";
	// read first number
	infile >> k;
	// test for eof
	while (!infile.eof())
	{
		outfile << "Equation # " << equation << "\n\n";
		infile >> m >> a0 >> n;
		ans = recursive(k, m, a0, n);
		outfile << "The " << n << "th term found using the recursive solution is: " << ans << "\n";
		ans = nonRecursive(k, m, a0, n);
		outfile << "The " << n << "th term found using the non-recursive solution is: " << ans <<"\n\n";
		ans = 0;
		equation++;
		// update condition by reading fisrt number of new line
		infile >> k;
	}
}

// nonRecursive()
// parameters: int, int, int, int
// return: int
// finds the nth term of the equation non recursively
int nonRecursive(int k, int m, int a0, int n)
{
	int ans = 0, current = 0, previous = a0;
	// loop through each term
	for (int x = 0; x < n; x++)
	{
		// set current according to the equation
		current = k * previous + m;
		// set previous term to current term
		previous = current;
	}
	return current;
}

// recursive()
// parameters: int, int, int, int
// return: int
// finds the nth term of the equation recursively
int recursive(int k, int m, int a0, int n)
{
	if (n == 0)
		return a0;	// return first term
	else 
		return (k * recursive(k, m, a0, n - 1) + m); // plug the previous term into equation n times
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								Shady Boukhary								*
*						Discrete Structures and Algorithms					*
*									Wuthrich								*
*								   12/08/2017								*
*			Purpose: This program reads matrix from an input file.			*
*			Then, it determines whether the matrix is a valid				*
*			adjacency matrix for a simple undirected graph. Finally,		*
*			it prints to an output file whether the matrix is valid,		*
*			the degree of each vertex, and the number of edges.				*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// opens files
void openFiles(ifstream&, ofstream&);

//closes files
void closeFiles(ifstream&, ofstream&);

// reads input file and fills the matrix
int** readFile(ifstream&, int&);

// determines whether matrix is valid by calling other functions
bool isValid(int**, int);

// determines whether matrix has valid edges
bool isValidEdges(int**, int);

// checks whether matix has zero diagonal
bool isZeroDiagonal(int**, int);

// checks whether matrix is symmetric
bool isSymmetric(int**, int);

// finds the degrees of each vertex
int findDegrees(int**, int, ofstream&);

// finds total number of edges
void findNumEdges(int, ofstream&);

// prints output
void exportString(ofstream&, string);

// deletes matrix
void del(int**, int);


int main()
{
	ifstream infile;
	ofstream outfile;
	int size = 0, loop = 0;
	
	// open files
	openFiles(infile, outfile);

	// get number of matrices
	infile >> loop;

	// print header
	exportString(outfile, "Shady Boukhary - Adjacency Matrices\n");

	/* loop to create, fill, check matrix then print results. Finally, delete.*/
	for (int x = 1; x <= loop; x++)
	{
		// initialize matrix with input file data
		int ** matrix = readFile(infile, size);
		exportString(outfile, "Matrix " + to_string(x));

		// check if matrix is valid
		if (isValid(matrix, size))
		{
			// find and print degrees and number of edges
			int total = findDegrees(matrix, size, outfile);
			findNumEdges(total, outfile);
		}
		else
			exportString(outfile, "INVALID\n");

		// delete matrix
		del(matrix, size);
	}
	
	// close files
	closeFiles(infile, outfile);
	
	system("pause");
	return 0;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *								openFiles()									*
 * @param: ifstream&, ofstream&												*
 * @return: none															*
 * @usage: openFiles(infile, outfile)										*
 * @function: opens input and output files									*
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void openFiles(ifstream& infile, ofstream& outfile)
{
	// try to open files
	try
	{
		infile.open("adj.dat");
		outfile.open("boukhary_shady_adj.txt");

		// throw exception if files failed to open
		if (!infile || !outfile)
			throw string("ERROR with one or more files.\n");
	}

	// catch exception
	catch (string message)
	{
		cout << message;
		system("pause");
		exit(1);
	}

}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								readFile()									*
* @param: ifstream&, int&													*
* @return: int**															*
* @usage: int** matrix = readFile(infile, size)								*
* @function: reads input file, fills matrix and returns a pointer to it		*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
int** readFile(ifstream& infile, int& size)
{
	// read size of matrix
	infile >> size;
	
	// create matrix
	int** matrix = new int*[size];
	for (int x = 0; x < size; x++)
		matrix[x] = new int[size];

	// initialize matrix with values from input file
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			infile >> matrix[i][j];
		
	return matrix;
	
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								isValid()									*
* @param: int**, int														*
* @return: bool																*
* @usage: if(isValid(matrix, size))											*
* @function: checks whether matrix is valid adjacency matrix				*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
bool isValid(int** matrix, int size)
{
	if (isValidEdges(matrix, size)
		&& isZeroDiagonal(matrix, size)
		&& isSymmetric(matrix, size))
		return true;
	
	return false;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								isValidEdges()								*
* @param: int**, int														*
* @return: bool																*
* @usage: if(isValidEdges(matrix, size))									*
* @function: checks whether more than 1 edge exists between vertices		*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
bool isValidEdges(int** matrix, int size)
{
	// check if matrix has invalid values
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			if (matrix[x][y] > 1 || matrix[x][y] < 0)
				return false;

	return true;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								isZeroDiagonal()							*
* @param: int**, int														*
* @return: bool																*
* @usage: if(...&& isZeroDiagonal(matrix, size))							*
* @function: checks whether main diagonal has all zero values				*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
bool isZeroDiagonal(int** matrix, int size)
{
	for (int x = 0; x < size; x++)
		if (matrix[x][x] != 0)
			return false;

	return true;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								isSymmetric()								*
* @param: int**, int														*
* @return: bool																*
* @usage: if(... && isSymmetric(matrix, size))								*
* @function: checks whether matrix is symmetric								*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
bool isSymmetric(int** matrix, int size)
{
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			if (matrix[x][y] != matrix[y][x])
				return false;

	return true;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								findDegrees()								*
* @param: int**, int, ofstream&												*
* @return: int																*
* @usage: int total = findDegrees(matrix, size, outfile)					*
* @function: finds and prints degrees of all vertices, returns total 		*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
int findDegrees(int** matrix, int size, ofstream& outfile)
{
	int degree = 0, total = 0;
	// ASCII value of letter starting from A
	char vertex = 65;	
	exportString(outfile, "Degree of:");

	// get degree of vertex, increment total
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
			if (matrix[x][y] == 1)
			{
				degree++; 
				total++;
			}
		
		// print degree of matrix
		exportString(outfile, "Vertex " + string(1, vertex) + ": " + to_string(degree));
		degree = 0;

		// go to next letter 
		vertex++;
	}
	return total;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								findNumEdges()								*
* @param: int, ofstream&													*
* @return: none																*
* @usage: findNumEdges(total, outfile)										*
* @function: finds total number of edges and prints it out			 		*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void findNumEdges(int totalDegrees, ofstream& outfile)
{
	int edges = totalDegrees / 2;
	exportString(outfile, "Number of Edges: " + to_string(edges) + "\n");
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								exportString()								*
* @param: ofstream&, string													*
* @return: none																*
* @usage: numerous															*
* @function: prints passed string to screen and file				 		*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void exportString(ofstream& outfile, string output)
{
	outfile << output << endl;
	cout << output << endl;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*									del()									*
* @param: int**, int														*
* @return: none																*
* @usage: del(matrix, size)													*
* @function: deletes matrix											 		*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void del(int** matrix, int size)
{
	for (int x = 0; x < size; x++)
		delete[] matrix[x];
	delete matrix;
	matrix = nullptr;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*								closeFiles()								*
* @param: ifstream&, ofstream&												*
* @return: none																*
* @usage: closeFiles(infile, outfile)										*
* @function: closes input and output files							 		*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void closeFiles(ifstream& infile, ofstream& outfile)
{
	infile.close();
	outfile.close();
}

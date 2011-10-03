//*******************************************************
//********* TRIANGLE IDENTIFICATION TEST DRIVER *********
//*******************************************************
//
//include code libraries
#include <iostream>
#include <fstream>
//
using namespace std;
//
//function prototypes
int CheckForWrongInput(float [], int);
void SortSidesInAscendingOrder(float [], int);
int TestTriangle(float [], int);
void PrintFinalAnalysis(int, int, float[], ofstream&);

const int NUMBER_OF_SIDES = 3;  //declare number of triangle sides as global variable

int main ()
{
	//
	//declare an array that would contain the three sides of a triangle
	float Triangle[NUMBER_OF_SIDES], originalTriangle[NUMBER_OF_SIDES];
	//
	int testCases, resultAfterTest;
	char comma1, comma2;
	//
	//declare and open input and output files
	ifstream infile("Data090711.txt");
	if (!infile)
		infile.open("Data090711"); 
	ofstream outfile("eademuwagun090711.txt");
	if (!outfile)
		outfile.open("eademuwagun090711");
	//
	//get number of test cases in input file and initialize the loop counter variable
	infile >> testCases;
	int count = 0;
	while (count < testCases) //Stop the loop after the total number of test cases
	{
		infile >> Triangle[0] >> comma1 >> Triangle[1] >> comma2 >> Triangle[2]; //get each test case and store in array
		//copy the array into another array to store the original positions of the integers in the test case
		originalTriangle[0] = Triangle[0];
		originalTriangle[1] = Triangle[1];
		originalTriangle[2] = Triangle[2];
		//
		//sort the array in ascending order for simplicity
		SortSidesInAscendingOrder(Triangle, NUMBER_OF_SIDES); 
		//
		//check if triangle combination is valid
		resultAfterTest = CheckForWrongInput(Triangle, NUMBER_OF_SIDES);
		if (resultAfterTest == 5) //if the triangle combination is found to be valid
		{
			//check for triangle type identifier
			resultAfterTest = TestTriangle(Triangle, NUMBER_OF_SIDES);
		}
		PrintFinalAnalysis(resultAfterTest, testCases, originalTriangle, outfile); //print identifiers for the triangle combination
		count++;
	}
	//
	//close input and ouput files
	infile.close();
	outfile.close();
	return 0;
}
void SortSidesInAscendingOrder(float TriangleSides[], int sides)
{
	//IMPLEMENTATION OF INSERTION SORT
	//
	int currentIndex = 1;
	float key;
	int walkerIndex;
	//perform insertion sort
	while (currentIndex < sides)
	{
		key = TriangleSides[currentIndex];
		walkerIndex = currentIndex - 1;
			while ((walkerIndex >= 0) && (key < TriangleSides[walkerIndex]))
			{
				TriangleSides[walkerIndex + 1] = TriangleSides[walkerIndex];
				walkerIndex--;
			}
		TriangleSides[walkerIndex + 1] = key;
		currentIndex++;
	}
}
int CheckForWrongInput(float TriangleSides[], int sides)
{
	if (TriangleSides[0] <= 0 || TriangleSides[1] <= 0 || TriangleSides[2] <= 0)  //if the array contains a negative number
	{
		return 4; 
	}
		else if (TriangleSides[0] + TriangleSides[1] <= TriangleSides[2])  //if the array is not a valid triangle combination
		{
			return 0;
		}
			else   //if the array is a valid triangle combination
				return 5;
}
int TestTriangle(float TriangleSide[], int sides)
{
	if (TriangleSide[0] == TriangleSide[1] && TriangleSide[1] == TriangleSide[2]) //if triangle is equilateral
	{
		return 1;
	}
		else if (TriangleSide[0] == TriangleSide[1] || TriangleSide[1] == TriangleSide[2]) //if triangle is isoceles
		{
			return 2;
		}
			else   //if triangle is scalene
				return 3;
}
void PrintFinalAnalysis(int output, int cases, float TriangleSides[], ofstream& outfile)
{
	static int count = 0;  //initialize a static variable
	//
	//print heading only once
	if (count == 0) 
		outfile << "Emmanuel Ademuwagun: HW No. 1 Due: 9/7/2011\n\n\n";
	count++;
	//
	//print triangle combination to file 
	outfile << "Input " << TriangleSides[0]; 
	if (int(TriangleSides[0]) - TriangleSides[0] != 0) //if number is a decimal, only print a comma
		outfile << ", ";
	else
		outfile << "., ";
	outfile << TriangleSides[1];
	if (int(TriangleSides[1]) - TriangleSides[1] != 0) //if number is a decimal, only print a comma
		outfile << ", ";
	else
		outfile << "., ";
	outfile << TriangleSides[2];
	if (int(TriangleSides[2]) - TriangleSides[2] == 0) //if number is not a decimal, print a period
		outfile << ".";
	outfile << "\tThis case is: ";
	//
	//print identifiers for the triangle combinations
	switch (output)
	{
		case 0	:	outfile << "Not a Triangle\n\n";
					break;
		case 1	:	outfile << "Equilateral Triangle\n\n";
					break;
		case 2	:	outfile << "Isoceles Triangle\n\n";
					break;
		case 3	:	outfile << "Scalene Triangle\n\n";
					break;
		case 4	:	
		default	:	outfile << "Bad Data\n\n";
	}
	if (count == cases)
	{
		outfile << "\nProcessed " << cases << " data cases.\n\n";
		outfile << "No More data******************\n\n";
	}
}

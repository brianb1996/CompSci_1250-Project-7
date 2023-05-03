//Brian Bredahl
//November 17, 2019
//Project 7 - Test Scores data and file stream

/*

Write a program that will read data from the file "p6.txt". The file (that you will create) always contains 15
test scores (whole numbers between 0 and 100). The test scores are scores for 5 students taking 3 tests, and
are arranged, in the file, by the student - that is the first 3 numbers are the test scores for test 1, 2, and
3 for the first student, etc.

The program will print:
- average per student (5 averages), on a single line, with 2 decimals
- average per test (3 averages), on a single line, with 2 decimals
- overall best score on a single line
- how many scores were Fs (out of the 15, how many were at most 59) on a single line

To simplify the code, no validations are needed. That is, assume the file is successfully opened, and that all
data are 0-100, and that there are exactly 15 numbers in the file.

Note that the program reads the filename


read from file "p6.txt"
create file that always has 15 test scores
nums are in 3's for a students 3 test scores

print each students avg for the 3 test with 2 decimals
print the avg of all students per test with 2 decimals
overall best score
number of F's ( below 59 )
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

const int SIZE = 5;
const int NumTests = 3;

struct TestData {
	string FileLocation;		// String for the file path to the file that contains the students tests scores
	int Test[SIZE][NumTests];	// Stores the test scores of each student so that the statistics can be calculated
};

TestData TestInfo();

void TestStats(TestData);

int main() {
	TestData Student;			// Data structure named students
	Student = TestInfo();		// stores the data found during file streaming to the data structure
	TestStats(Student);			// used to calculate and display the test stats from the file stream
	return 0;
}

//searches for a file named p6.txt and stores data to data structure
// if file isnt found then the file stream is closed and the program will loop allowing the user to search for another file
TestData TestInfo() {
	TestData StudentTemp; // structure used to temporarily store data to during the file streaming process
	ifstream Scores; // input file stream object
	bool Did_Fail; // used for looping if the file stream does not sucessfully open a file
	do {
		Did_Fail = false; // resets bool to false so the loop can be exited if file path entered exists
		StudentTemp.FileLocation.clear(); // clears string so that a new filepath can be entered
		cout << "Please enter the File path for the file with the students test scores" << endl;
		cin >> StudentTemp.FileLocation;
		Scores.open(StudentTemp.FileLocation);
		if (Scores) {
			for (int i = 0; i < SIZE; i++) {
				for (int x = 0; x < NumTests; x++) {
					Scores >> StudentTemp.Test[i][x]; // scores from the file are saved to the 2d array found in the data structure 
				}
			}
			Scores.close();
		}
		else { // if the filestream doesnt open a file
			cout << "\n\nThe File Path indicated does not exist or cannot be accessed\n\n";
			Did_Fail = true;
			Scores.close();
		}
	} while (Did_Fail);
	return StudentTemp;
}

// reads the data that was saved to the data structure and calculates: avg for each test, avg of each students test, best test score, and number of tests failed
void TestStats(TestData Student) {
	double  StudentAvg[SIZE], TestAvg[NumTests], ScoreAdd = 0;
	int BestTest = 0, NumFails = 0;
	
	// used to calculate eachs students average of the three tests (Student 1 avg score: ## ... Student 2 avg score: ## ... and so on)
	for (int i = 0; i < SIZE; i++) {
		for (int x = 0; x < NumTests; x++) {
			ScoreAdd += Student.Test[i][x]; // adds each students 3 test scores
			if (Student.Test[i][x] > BestTest) {
				BestTest = Student.Test[i][x]; // stores the best overall test score
			}
			if (Student.Test[i][x] <= 59) {
				NumFails++; // counts the number of tests failed
			}
		}
		StudentAvg[i] = (ScoreAdd / NumTests); // stores the students average for the tests
		ScoreAdd = 0;
	}

	//used to calculate the average each test ( test 1 avg: ## ... test 2 avg: ## ... test 3 avg: ## )
	for (int x = 0; x < NumTests; x++) {
		for (int i = 0; i < SIZE; i++) {
			ScoreAdd += Student.Test[i][x]; // adds the scores of all students for each test so that the average for each test can be output
		}
		TestAvg[x] = (ScoreAdd / SIZE); // stores the average of each test 
		ScoreAdd = 0;
	}

	//everything below is used to output the results to the user
	cout << endl << endl;
	for (int i = 0; i < SIZE; i++) {
		cout << "\tStudent" << i + 1 << "'s average test score is: " << fixed << showpoint << setprecision(2) << StudentAvg[i] << endl;
	}
	cout << endl << endl;
	for (int x = 0; x < NumTests; x++) {
		cout << "\tThe average score for Test " << x + 1 << " was: " << TestAvg[x] << endl;
	}
	cout << endl << "\tThe best score was: " << BestTest << endl << endl;
	cout << "\tThe Number of Tests that were Failed: " << NumFails << endl << endl;

}
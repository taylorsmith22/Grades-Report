//---------------------------------------------------------
//                       CS - 215
//                       Project 2
//                      Taylor Smith
//---------------------------------------------------------

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

const int maxStudents = 5; //Sets the maximum number of students to 5
const int maxScores = 5; //Sets the maximum number of scores to 5
const int notFound = -1; //Sets the not found value to -1
int numStudents;

struct score { //Creates a structure of scores
	int pointsPossible; //Creates an integer for the points possible of the score
	int pointsMade; //Creates an integer for the points made of the score
};

struct student { //Creates a structure of students
	int iD; //Creates an integer for the ID of the student
	string firstName; //Creates a string for the first name of the student
	string lastName; //Creates a string for the last name of the student
	int numScores; //Creates an integer for the number of scores
	score scores[maxScores]; //Creates an array of scores
};

void init(student s[], int & numStudents) { //Creates a function that erases all the students information
	for (int i = 0; i < numStudents; i++) {
		s[i].iD = 0;
		s[i].firstName = "";
		s[i].lastName = "";
		for (int j = 0; j < maxScores; j++) {
			s[i].scores->pointsMade = 0;
			s[i].scores->pointsPossible = 0;
		}
	}
}

void displayMenu() { //Creates a function that prints the logo and display menu
	cout << "+------------------------------------------------------------+" << endl;
	cout << "|                           GRADER INC.                      |" << endl;
	cout << "|                          Taylor Smith                      |" << endl;
	cout << "+------------------------------------------------------------+" << endl;
	cout << "A - Add Student            D - Drop Student" << endl;
	cout << "V - View Student           P - Print Class " << endl;
	cout << "S - Sort by Avg            N - Sort by Name" << endl;
	cout << "E - Enter New Scores       X - Exit        " << endl;
}

void load(student s[], int & maxStudents) { //Reads students data from the file grades.txt
	ifstream fin;
	fin.open("grades.txt");
	if (fin.fail()) {
		cout << "No data found...starting new class." << endl;
	}
	else {
		fin >> numStudents;
		for (int i = 0; i < numStudents; i++) {
			fin >> s[i].iD; //Reads the students ID from the file
			fin >> s[i].firstName; //Reads the students first name from the file
			fin >> s[i].lastName;
			fin >> s[i].numScores; //Reads the number of scores of the student
			for (int j = 0; j < s[i].numScores; j++) { //Reads the grades of the student
				fin >> s[i].scores[j].pointsMade;
				fin >> s[i].scores[j].pointsPossible;
			}
		}
		fin.close();
	}
}

void write(student s[] , int numStudents) { //Writes the students information to the output file gradesout.txt
	ofstream fout;
	fout.open("gradesout.txt");
	if (fout.fail()) {
		cout << "Unable to open output file." << endl;
	}
	else {
		fout << numStudents << endl;
		for (int i = 0; i < numStudents; i++) {
			fout << s[i].iD << " ";
			fout << s[i].lastName << " ";
			fout << s[i].firstName << " ";
			fout << s[i].numScores << " ";
			for (int j = 0; j < s[i].numScores; j++) {
				fout << s[i].scores[j].pointsMade << " ";
				fout << s[i].scores[j].pointsPossible << " ";
			}
			fout << endl;
		}
	}
	fout.close();
}

char getOption(string options) { // Gets the option from the user
	string option;
	char opt;
	int found = -1;
	cout << "Enter option: ";
	if (cin.peek() == '\n') cin.ignore(); // discards any leading newline
	getline(cin, option); // get entire line of input, spaces and all
	opt = toupper(option[0]); // get the first char of input, and upper case it
	found = options.find(opt);
	while (found == -1 ) {
		cout << "Invalid option. Choose one of " << options << endl;
		cout << "Enter option: ";
		if (cin.peek() == '\n') cin.ignore(); // discards any leading newline
		getline(cin, option); // get entire line of input, spaces and all
		opt = toupper(option[0]); // get the first char of input, and upper case it
		found = options.find(opt);
	}
	return opt;
}

void addStudent(student s[], int& numStudents) { //Adds a student to the partial array of students
	if (numStudents == maxStudents) { //If there is no room to put a student it prints an error message
		cout << "No more students may be added" << endl;
	}
	else {
		numStudents = numStudents + 1;
		int newVal = numStudents - 1;
		cout << "Enter the student's ID: ";
		cin >> s[newVal].iD;
		cout << "Enter first name: ";
		cin >> s[newVal].firstName;
		cout << "Enter last name: ";
		cin >> s[newVal].lastName;
		cout << "Enter number of scores: ";
		cin >> s[newVal].numScores;
		while ((s[newVal].numScores > maxScores) || (s[newVal].numScores < 1)) { //Prints an error message if the number of scores if above the maximum
			cout << "Invalid number of scores!";
			cout << endl << "Enter number of scores: ";
			cin >> s[newVal].numScores;
		}
		for (int i = 0; i < s[newVal].numScores; i++) { //Asks the user to enter the points made and points possible for each score
			cout << "Enter score " << i + 1 << " (made poss): ";
			cin >> s[newVal].scores[i].pointsMade >> s[newVal].scores[i].pointsPossible;
		}
	}
}

double getAvg(score scores[],int numScores) { //Calculates the students average score
	double sumMade = 0;
	double sumPossible = 0;
	double avg;
	for (int i = 0; i < numScores; i++) {
		sumMade = scores[i].pointsMade + sumMade;
	}
	for (int i = 0; i < numScores; i++) {
		sumPossible = scores[i].pointsPossible + sumPossible;
	}
	avg = sumMade / sumPossible;
	avg = avg * 100.00;
	return avg;
}

char getGrade(double avg) { //Returns the letter grade of the students average score
	char grade;
	if (avg >= 90.0) 
		grade = 'A';
	else if (avg >= 80.0)
		grade = 'B';
	else if (avg >= 70.0)
		grade = 'C';
	else if (avg >= 60.0)
		grade = 'D';
	else if (avg < 60)
		grade = 'E';
	return grade;
}

void printReport(student s[], int numStudents) { //Prints a report of the class
	cout << " ID " << "  Name                 " << " Avg  Grd Scores" << endl;
	cout << "----  -------------------- ----- --- ----------------------------------------" << endl;
	for (int i = 0; i < numStudents; i++) {
		cout << setw(4) << s[i].iD << "  " << setw(20) << left << (s[i].lastName + "," + s[i].firstName);
		double avg;
		avg = getAvg(s[i].scores, s[i].numScores);
		cout << setprecision(3) << setw(5) << right << avg << " ";
		cout << setw(3) << getGrade(avg) << " ";
		for (int j = 0; j < s[i].numScores; j++) { //Uses a for loop to print of the students scores
			cout << setw(3) << right << s[i].scores[j].pointsMade << "/" << setw(3) << right << s[i].scores[j].pointsPossible << " ";
		}
		cout << endl;
	}
}

int search(student s[], int iD) { //Finds the student based on their student ID
	int found = -1;
	for (int i = 0; i < numStudents; i++) {
		if (s[i].iD == iD) {
			found = i;
		}
	}
	return found;
}

int findStudent(student s[]) { //Searches for the student by ID number
	int iD;
	int id;
	cout << "Enter student ID: ";
	cin >> iD;
	id = search(s, iD);
	if (id == -1) {
		cout << "Student ID " << iD << " not found!" << endl;
	}
	return id;
}

student removeStudent(student s[], int& numStudents, int r) { //Removes a student from the class and holds the students info in a temporary variable called rem
	student rem = s[r];
	if (r >= 0 && r < numStudents) {
		rem = s[r];
		numStudents--;
		for (int i = r; i < numStudents; i++) {
			s[i] = s[i + 1];
		}
	}
	return rem;
}

void dropStudent(student s[], int& numStudents) { //Drops the student from the class
	int i = findStudent(s);
	if (i >= 0) {
		s[i] = removeStudent(s, numStudents, i); //Invokes removeStudent to remove the student from the class
	}

}

void viewStudent(student s[], int numStudents) { //Prints an individual students report
	int student = findStudent(s); //Finds the index of the student
	if (student >= 0) {
		double avg = getAvg(s[student].scores, s[student].numScores); //Finds the students average
		char grade = getGrade(avg); //Finds the students letter grade
		cout << "ID:   " << s[student].iD << "  Name:  " << s[student].lastName << ", " << s[student].firstName << endl;
		cout << "Avg:  " << setprecision(3) << avg << "  Grade: " << grade << endl;
		cout << "Number of scores:  " << s[student].numScores << endl;
		cout << "Scores:            ";
		for (int i = 0; i < s[student].numScores; i++) { //Prints each of the students scores
			cout << s[student].scores[i].pointsPossible << "/" << s[student].scores[i].pointsMade << " ";
		}
		cout << endl;
	}
}

void swap(student s[], int num1, int num2) { //Swaps the spots of two students with eachother
	student temp = s[num1]; //Creates a temporary student that holds the value of the first student
	s[num1] = s[num2];
	s[num2] = temp;
}

void sortByName(student s[], int numStudents) { //Sorts students by their name
	for (int i = 0; i < numStudents - 1; i++) {
		for (int j = i + 1; j < numStudents; j++) {
			if (s[i].lastName == s[j].lastName) { //Sorts the students with the same last name
				string last1 = s[i].lastName;
				string first1 = s[i].firstName;
				string last2 = s[j].lastName;
				string first2 = s[j].firstName;
				string sort1 = last1 + first1;
				string sort2 = last2 + first2;
				if (sort1 < sort2) {
					student temp = s[i];
					s[i] = s[j];
					s[j] = temp;
				}
			}
			else if (s[i].lastName > s[j].lastName) { //Sorts the students with different last names
				student temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
		}
	}
	cout << "Class sorted by Name" << endl;
}

void sortByAvg(student s[], int numStudents) { //Sorts the students by their average
	for (int i = 0; i < numStudents - 1; i++) {
		for (int j = i + 1; j < numStudents; j++) {
			double avg1 = getAvg(s[i].scores, s[i].numScores);
			double avg2 = getAvg(s[j].scores, s[j].numScores);
			if (avg1 < avg2) {
				student temp = s[i]; //Creates a temporary student to switch the two students
				s[i] = s[j];
				s[j] = temp;
			}
		}
	}
	cout << "Class sorted by Average" << endl;
}

void enterScores(student s[], int numStudents) { //Enters a new score for each student
	sortByName(s, numStudents);
	int pointsPoss;
	cout << "Enter points possible for this assignment: "; //Asks the user to enter the points possible for the assignment
	cin >> pointsPoss;
	cout << "Enter points made for each student:" << endl;
	for (int i = 0; i < numStudents; i++) { //Asks the user to input the points made for each student
		if (s[i].numScores < maxScores) {
			s[i].numScores = s[i].numScores + 1;
			int newVal = s[i].numScores - 1; //Assigns newVal as the index of the new assignment
			s[i].scores[newVal].pointsPossible = pointsPoss;
			cout << setw(4) << s[i].iD << " ";
			cout << setw(20) << left << (s[i].lastName + "," + s[i].firstName);
			cin >> s[i].scores[newVal].pointsMade;
		}
		else { //If the student already has 5 scores they cannot enter anymore
			cout << "Max scores exceeded!" << endl;
		}
	}
}

int main() {
	student s[maxStudents]; //Declares a partial array of students
	string options = "ADNVEPSX"; //The options the user has to choose from
	init(s, numStudents); //Initializes the array of students
	load(s, numStudents); //Reads the data of students from a file
	char option = 'T'; //Creates a character for the users option
	while (option != 'X') {
		displayMenu();
		option = getOption(options);
		if (option == 'A') { //Adds a student if the users enters A
			addStudent(s, numStudents);
			system("pause");
		}
		else if (option == 'D') { //Drops a student if the user enters D
			dropStudent(s, numStudents);
			system("pause");
		}
		else if (option == 'V') { //If the user enters V they can see a specific student
			viewStudent(s, numStudents);
			system("pause");
		}
		else if (option == 'E') { //If the user enters E then they will enter new scores for each of the students
			enterScores(s, numStudents);
			system("pause");
		}
		else if (option == 'P') { //Prints a report if the user enters P
			printReport(s, numStudents);
			system("pause");
		}
		else if (option == 'S') { //If the user enters S it will sort the students by average
			sortByAvg(s, numStudents);
			system("pause");
		}
		else if (option == 'N') { //If the user enters N it sorts the students by name
			sortByName(s, numStudents);
			system("pause");
		}
	}
	write(s, numStudents); //Writes the data to the file
	cout << "Class data written to file." << endl;
	cout << "Thanks for using Grade Pro Plus!" << endl;
	system("pause");
	return 0;
}
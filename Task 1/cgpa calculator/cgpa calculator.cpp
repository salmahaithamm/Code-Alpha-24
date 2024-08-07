#include <iostream>
#include <string> 

using namespace std;

struct Course {
    int credits;
    int grade;  

struct Semester {
    Course* courses;
    int numCourses;
    double gpa;
};


double getGradePoint(int grade) {
    if (grade >= 90) return 4.0;
    if (grade >= 80) return 3.0;
    if (grade >= 70) return 2.0;
    if (grade >= 60) return 1.0;
    return 0.0;
}


double calculateGPA(const Course* courses, int numCourses) {
    double totalGradePoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < numCourses; ++i) {
        totalGradePoints += getGradePoint(courses[i].grade) * courses[i].credits;
        totalCredits += courses[i].credits;
    }

    return totalCredits == 0 ? 0 : totalGradePoints / totalCredits;
}

int inputInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cout << "Invalid input. Please enter a non-negative integer.\n";
            cin.clear();
            cin.ignore(10000, '\n');  
        }
        else {
            cin.ignore(10000, '\n');  
            return value;
        }
    }
}

// Function to safely input a grade
int inputGrade(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0 || value > 100) {
            cout << "Invalid input. Please enter a grade between 0 and 100.\n";
            cin.clear();
            cin.ignore(10000, '\n');  // Ignore invalid input
        }
        else {
            cin.ignore(10000, '\n');  
            return value;
        }
    }
}


Course* inputCourses(int numCourses) {
    Course* courses = new Course[numCourses];
    for (int i = 0; i < numCourses; ++i) {
        courses[i].credits = inputInt("Enter credits for course " + to_string(i + 1) + ": ");
        if (courses[i].credits == 0) {
            cout << "Invalid input. Credits cannot be zero.\n";
            --i; 
            continue;
        }
        courses[i].grade = inputGrade("Enter grade (out of 100) for course " + to_string(i + 1) + ": ");
    }
    return courses;
}

double calculateCGPA(Semester* semesters, int numSemesters) {
    double totalGradePoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < numSemesters; ++i) {
        for (int j = 0; j < semesters[i].numCourses; ++j) {
            totalGradePoints += getGradePoint(semesters[i].courses[j].grade) * semesters[i].courses[j].credits;
            totalCredits += semesters[i].courses[j].credits;
        }
    }

    return totalCredits == 0 ? 0 : totalGradePoints / totalCredits;
}

int main() {
    int numSemesters = inputInt("Enter the number of semesters: ");
    Semester* semesters = new Semester[numSemesters];

    for (int i = 0; i < numSemesters; ++i) {
        cout << "Semester " << i + 1 << ":" << endl;
        semesters[i].numCourses = inputInt("Enter the number of courses for semester " + to_string(i + 1) + ": ");
        semesters[i].courses = inputCourses(semesters[i].numCourses);
        semesters[i].gpa = calculateGPA(semesters[i].courses, semesters[i].numCourses);
        cout << "GPA for semester " << i + 1 << " is: " << semesters[i].gpa << endl;
    }

    double cgpa = calculateCGPA(semesters, numSemesters);
    cout << "Your cumulative GPA (CGPA) is: " << cgpa << endl;

    for (int i = 0; i < numSemesters; ++i) {
        delete[] semesters[i].courses;
    }
    delete[] semesters;

    return 0;
}

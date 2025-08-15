#include <iostream>
#include <iomanip> // For setting precision
using namespace std;

int main() {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    double grade, creditHours;
    double totalCredits = 0, totalGradePoints = 0;

    cout << "\nEnter details for each course:\n";
    for (int i = 1; i <= numCourses; i++) {
        cout << "\nCourse " << i << ":\n";
        cout << "Enter grade (on a 10-point scale): ";
        cin >> grade;
        cout << "Enter credit hours: ";
        cin >> creditHours;

        totalCredits += creditHours;
        totalGradePoints += (grade * creditHours);
    }

    // GPA and CGPA calculation (for this example, GPA == CGPA for one semester)
    double GPA = totalGradePoints / totalCredits;
    double CGPA = GPA; // If more semesters are added, CGPA can be cumulative

    cout << fixed << setprecision(2);
    cout << "\nTotal Credits: " << totalCredits;
    cout << "\nTotal Grade Points: " << totalGradePoints;
    cout << "\nGPA for this semester: " << GPA;
    cout << "\nOverall CGPA: " << CGPA << endl;

    return 0;
}
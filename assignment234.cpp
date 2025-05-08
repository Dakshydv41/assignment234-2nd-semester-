#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <algorithm>
using namespace std;

// ----------------------
// Base Class: Person
// ----------------------
class Person {
protected:
    string fullName, uniqueId, phoneNumber;
    int personAge;

public:
    // Constructor with basic validation
    Person(string n, int a, string i, string c) {
        setName(n);
        setAge(a);
        uniqueId = i;
        phoneNumber = c;
    }

    virtual void displayDetails() {
        cout << "Full Name: " << fullName << ", Age: " << personAge << ", ID: " << uniqueId << ", Contact: " << phoneNumber << endl;
    }

    virtual double calculatePayment() {
        return 0.0; 
    }

    void setName(string n) {
        if (n.empty()) throw invalid_argument("Full name cannot be left blank.");
        fullName = n;
    }

    void setAge(int a) {
        if (a <= 0 || a > 120) throw invalid_argument("Enter a valid age between 1 and 120.");
        personAge = a;
    }

    int getAge() { return personAge; }
    string getName() { return fullName; }
    string getId() { return uniqueId; }
    string getContact() { return phoneNumber; }
};

// ----------------------
// Derived Class: Student
// ----------------------
class Student : public Person {
    string academicProgram;
    string joinDate;
    float currentGPA;

public:
    Student(string n, int a, string i, string c, string prog, string eDate, float g)
        : Person(n, a, i, c), academicProgram(prog), joinDate(eDate) {
        setGPA(g);
    }

    void setGPA(float g) {
        if (g < 0.0 || g > 4.0) throw invalid_argument("GPA should lie between 0.0 and 4.0.");
        currentGPA = g;
    }

    float getGPA() { return currentGPA; }

    void displayDetails() override {
        Person::displayDetails();
        cout << "Program Enrolled: " << academicProgram << ", GPA: " << currentGPA << ", Enrollment Date: " << joinDate << endl;
    }

    double calculatePayment() override {
        return 1000.0;
    }
};

// ------------------------
// Derived Class: Professor
// ------------------------
class Professor : public Person {
    string faculty, areaOfExpertise, dateOfJoining;

public:
    Professor(string n, int a, string i, string c, string dept, string spec, string hDate)
        : Person(n, a, i, c), faculty(dept), areaOfExpertise(spec), dateOfJoining(hDate) {}

    void displayDetails() override {
        Person::displayDetails();
        cout << "Department: " << faculty << ", Specialization: " << areaOfExpertise << ", Date of Hire: " << dateOfJoining << endl;
    }

    double calculatePayment() override {
        return 5000.0;
    }
};

// ------------------
// Course Class
// ------------------
class Course {
    string courseCode, courseTitle, courseDesc;
    int creditHours;

public:
    Course(string c, string t, int cr, string d) : courseCode(c), courseTitle(t), courseDesc(d) {
        setCredits(cr);
    }

    void setCredits(int c) {
        if (c <= 0) throw invalid_argument("Credit hours must be greater than zero.");
        creditHours = c;
    }

    void display() {
        cout << "Course Info: " << courseCode << " - " << courseTitle << " (" << creditHours << " credits)" << endl;
        cout << "About Course: " << courseDesc << endl;
    }
};

// ----------------------
// Department Class
// ----------------------
class Department {
    string deptName, deptLocation;
    float allocatedBudget;

public:
    Department(string n, string l, float b) : deptName(n), deptLocation(l), allocatedBudget(b) {}
};

// ------------------------------------------
// GradeBook – manages student grades in a course
// ------------------------------------------
class GradeBook {
    map<string, float> gradeMap;

public:
    void addGrade(string studentId, float grade) {
        if (grade < 0 || grade > 100) throw invalid_argument("Grade must be from 0 to 100.");
        gradeMap[studentId] = grade;
    }

    float calculateAverageGrade() {
        float total = 0;
        for (auto& entry : gradeMap) total += entry.second;
        return gradeMap.empty() ? 0 : total / gradeMap.size();
    }

    float getHighestGrade() {
        float maxVal = 0;
        for (auto& entry : gradeMap) maxVal = max(maxVal, entry.second);
        return maxVal;
    }

    vector<string> getFailingStudents(float passMark = 40.0) {
        vector<string> failingList;
        for (auto& entry : gradeMap) {
            if (entry.second < passMark) failingList.push_back(entry.first);
        }
        return failingList;
    }
};

// ------------------------------------------
// EnrollmentManager – tracks student enrollments
// ------------------------------------------
class EnrollmentManager {
    map<string, vector<string>> enrollmentRecords;

public:
    void enrollStudent(string courseCode, string studentId) {
        enrollmentRecords[courseCode].push_back(studentId);
    }

    void dropStudent(string courseCode, string studentId) {
        auto& enrolled = enrollmentRecords[courseCode];
        enrolled.erase(remove(enrolled.begin(), enrolled.end(), studentId), enrolled.end());
    }

    int getEnrollmentCount(string courseCode) {
        return enrollmentRecords[courseCode].size();
    }
};

// ------------------------------------------
// Test polymorphism with Person pointers
// ------------------------------------------
void testPolymorphism() {
    cout << "------ Running Polymorphism Test ------" << endl;

    vector<Person*> peopleList;
    peopleList.push_back(new Student("Daksh", 20, "S01", "9732324", "CS", "2024-25", 4));
    peopleList.push_back(new Professor("ABC", 45, "P01", "8654758", "FOCP", "c++", "2020-2025"));

    for (Person* individual : peopleList) {
        individual->displayDetails();
        cout << "Calculated Payment: $" << individual->calculatePayment() << "\n\n";
    }

    for (Person* individual : peopleList) delete individual;
}

int main() {
    try {
        Course c1("xyz", " CS", 3, "gp and cs hour");
        c1.display();

        GradeBook gb;
        gb.addGrade("S01", 85.0);
        gb.addGrade("S02", 45.0);
        cout << "Average Grade: " << gb.calculateAverageGrade() << endl;

        EnrollmentManager em;
        em.enrollStudent("000", "0000");
        cout << "Enrollment in CS101: " << em.getEnrollmentCount("CS101") << endl;

        testPolymorphism();
    }
    catch (const exception& e) {
        cerr << "\n Error occurred: " << e.what() << endl;
    }

    return 0;
}

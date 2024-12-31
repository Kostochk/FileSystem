#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 

using namespace std;

class Student {
private:
    string name;
    int age;
    double averageGrade;

public:
    // Конструктор 
    Student() : name(""), age(0), averageGrade(0.0) {}

    // Метод для встановлення 
    void setData(const string& n, int a, double avg) {
        name = n;
        age = a;
        averageGrade = avg;
    }

    // Метод для запису інформації 
    void writeToFile(const string& filePath) {
        ofstream outFile(filePath, ios::binary);
        if (outFile.is_open()) {
            size_t nameLength = name.size();
            outFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            outFile.write(name.c_str(), nameLength);
            outFile.write(reinterpret_cast<char*>(&age), sizeof(age));
            outFile.write(reinterpret_cast<char*>(&averageGrade), sizeof(averageGrade));
            outFile.close();
            cout << "Information written to " << filePath << endl;
        }
        else {
            cerr << "Error opening file for writing." << endl;
        }
    }

    // Метод для читання інформації 
    void readFromFile(const string& filePath) {
        ifstream inFile(filePath, ios::binary);
        if (inFile.is_open()) {
            size_t nameLength;
            inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            char* buffer = new char[nameLength + 1];
            inFile.read(buffer, nameLength);
            buffer[nameLength] = '\0';
            name = string(buffer);
            delete[] buffer;
            inFile.read(reinterpret_cast<char*>(&age), sizeof(age));
            inFile.read(reinterpret_cast<char*>(&averageGrade), sizeof(averageGrade));
            inFile.close();

            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Average Grade: " << averageGrade << endl;
        }
        else {
            cerr << "Error opening file for reading." << endl;
        }
    }
};

int main() {
    // Робота з класом 
    Student student;
    student.setData("John Doe", 20, 3.75);

    string filePath = "student.dat";
    student.writeToFile(filePath);
    student.readFromFile(filePath);

    return 0;
}

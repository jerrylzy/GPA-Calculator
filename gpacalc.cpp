//
//  gpacalc.cpp
//  GPA Calculator
//
//  Created by Jerry Liu on 12/21/15.
//  Copyright © 2015 Jerry Liu. All rights reserved.
//

#include "Course.hpp"
#include "Quarter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

bool isQuarterName(const string& name);
void removeQuarters(const vector<Quarter*>& quarters);
void trim(string& str);

int main(int argc, char* argv[])
{
    string filename;
    
    //  Check if the file path is included
    if (argc == 2)
    {
        string argument = argv[1];
        if (argument == string("--help"))
        {
            cout << argv[0] << " can take 0 or 1 argument." << endl
            << "[1] If the program has 1 argument," << endl
            << "it has to be the file name of your grade information." << endl
            << "[2] If the program reads from a file, it can display quarter information." << endl
            << "[3] '#' means comments. The program will ignore lines starting with #." << endl;
            exit(0);
        }
        filename = argument;
    }
    vector<Quarter*> quarters;

    //  Choose whether to manually input course information or
    //  to read from a file
    int option;
    trim(filename);
    if ( ! filename.empty())
        option = 2;
    else
    {
        cout << "Please type in the options:" << endl
        << "[1] Input course info;" << endl
        << "[2] Read a file;" << endl
        << "[Other] Exit the program." << endl;
        cin >> option;
        cin.ignore(10000, '\n');
    }

    switch (option)
    {
        case 1:
        {
            vector<Course*> courses;
            cout << "Please input the number of courses" << endl;
            int numOfCourses;
            cin >> numOfCourses;
            cin.ignore(10000, '\n');
            
            //  Less memory allocations
            courses.reserve(numOfCourses);
            for (int i = 1; i <= numOfCourses; i++)
            {
                cout << "Please Input the Course No." << i << " Name;" << endl;
                string name;
                getline(cin, name);
                if (name.empty())
                {
                    cout << "Please Input Course Names!!!" << endl;
                    break;
                }
                cout << "Please Input the Course No." << i << " Unit;" << endl;
                int unit;
                cin >> unit;
                
                cout << "Is Course No." << i << " An Upper Div? [y/n]" << endl;
                char upper;
                cin >> upper;
                upper = tolower(upper);
                while (upper != 'y' && upper != 'n')
                {
                    cout << "Wrong option!!! Please reinput:" << endl;
                    cout << "Is Course No." << i << " An Upper Div? [y/n]" << endl;
                    cin >> upper;
                }
                cin.ignore(10000, '\n');
                
                cout << "Please Input the Course No." << i << " Grade;" << endl;
                string grade;
                getline(cin, grade);
                
                //  I did not add error checking for units and grades
                //  can be done in the future

                Course* newCourse = new Course(unit, grade, name, upper);
                courses.push_back(newCourse);
            }
            quarters.push_back(new Quarter(courses));
            break;
        }
        case 2:
        {
            if (filename.empty())
            {
                cout << "Please input file name: (default grade.txt)" << endl;
                cout << "File needs to be in format \"Name,Units,Grade,IsUpperDiv\"." << endl;
                getline(cin, filename);
                
                //  Get rid of deliminaters
                trim(filename);
                if (filename.empty())
                    filename = "grade.txt";
            }
            
            ifstream gradeFile(filename);
            if ( ! gradeFile.is_open())
            {
                cerr << "Error openning file: " << filename << endl;
                exit(1);
            }
            
            vector<Course*> courses;
            string line, quarterName;
            
            //  Read lines from the input file
            while (getline(gradeFile, line))
            {
                istringstream iss(line);
                vector<string> input;
                string info;

                while (getline(iss, info, ','))
                    input.push_back(info);

                //  "Name, Unit, Grade"
                string name, grade;
                int units;
                char upper;
                name = input[0];
                
                //  Since comments starts with '#'
                //  Skip the entire line starting with '#'
                if (name[0] == '#')
                    continue;
                else if (isQuarterName(name))
                {
                    //  Encountered a new quarter,
                    //  push remaining courses into last quarter
                    if ( ! courses.empty())
                    {
                        quarters.push_back(new Quarter(courses, quarterName));
                        courses.clear();
                    }
                    quarterName = name + ' ' + input[1];
                    continue;
                }
                else if (input.size() < 4)
                {
                    cerr << "Wrong format for the line:" << endl
                    << line << endl;
                    removeQuarters(quarters);
                    exit(1);
                }
                units = stoi(input[1]);
                grade = input[2];
                upper = input[3][0];
                courses.push_back(new Course(units, grade, name, upper));
            }
            quarters.push_back(new Quarter(courses, quarterName));
            gradeFile.close();
        }
            break;
        default:
            cout << "Exit" << argv[0] << endl;
            exit(0);
    }
    
    cout << endl;
    cout.setf(ios::fixed);
    cout.precision(3);      //  The precision used by UCLA

    //  Calculate GPAs
    int unitsTotal = 0;
    int upperUnitsTotal = 0;
    double gradePointTotal = 0;
    double upperDivGradePointTotal = 0;
    for (auto it = quarters.begin(); it != quarters.end(); it++)
    {
        int units = (*it)->getUnits();
        int upperUnits = (*it)->getUpperUnits();
        double gradePoint = (*it)->getGradePoint();
        double upperDivGradePoint = (*it)->getUpperDivGradePoint();
        (*it)->printGradeInfo();
        
        cout << "=============================" << endl;
        cout << "Term Units: " << units << endl;
        cout << "Term Grade Point: " << gradePoint << endl;
        cout << endl;
        
        //   Add quarter information to the total
        
        unitsTotal += units;
        upperUnitsTotal += upperUnits;
        gradePointTotal += gradePoint;
        upperDivGradePointTotal += upperDivGradePoint;
    }
    removeQuarters(quarters);
    cout << "Your total UC units: " << unitsTotal << endl;
    cout << "Your upper div GPA: " << upperDivGradePointTotal / (double) upperUnitsTotal << endl;
    cout << "Your general GPA: " << gradePointTotal / (double) unitsTotal << endl;
}

inline
bool isQuarterName(const string& name)
{
    return find(QUARTERS, QUARTERS + NUM_OF_QUARTERS, name) < QUARTERS + NUM_OF_QUARTERS;
}

void removeQuarters(const vector<Quarter*>& quarters)
{
    for (auto it = quarters.begin(); it != quarters.end(); it++)
        delete *it;
}

//  Trim spaces and tabs
void trim(string& str)
{
    //  Trim leading spaces and tabs
    for (auto it = str.begin(); it != str.end(); )
    {
        if (*it != '\t' && *it != ' ')
            break;
        str.erase(it);
    }
    
    //  Trim trailing spaces and tabs
    for (auto it = str.end() - 1; it != str.begin() - 1; it--)
    {
        if (*it != '\t' && *it != ' ')
            break;
        str.erase(it);
    }
}

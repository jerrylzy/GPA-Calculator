//
//  Quarter.cpp
//  GPA Calculator
//
//  Created by Jerry Liu on 6/15/16.
//  Copyright © 2016 Jerry Liu. All rights reserved.
//

#include "Quarter.hpp"
#include "Course.hpp"
#include <iostream>
#include <vector>
#include <string>

Quarter::Quarter()
: m_quarter("Quarter 1")
{}

Quarter::Quarter(const std::vector<Course*>& courses, const std::string& quarter)
 : m_quarter(quarter), m_numOfCourses(static_cast<int>(courses.size()))
{
    m_courses = courses;
    m_units = 0;
    m_upperUnits = 0;
    m_gradePoint = 0;
    m_upperGradePoint = 0;
    
    //  Record course grades
    for (auto it = m_courses.begin(); it != m_courses.end(); it++)
    {
        m_units += (*it)->getUnits();
        m_gradePoint += (*it)->getGradePoint();
        if ((*it)->isUpper())
        {
            m_upperGradePoint += (*it)->getGradePoint();
            m_upperUnits += (*it)->getUnits();
        }
    }
    m_gpa = m_gradePoint / m_units;
    m_upperGPA = m_upperGradePoint / m_upperUnits;
}

Quarter::~Quarter()
{
    for (auto it = m_courses.begin(); it != m_courses.end(); it++)
        delete *it;
}

void Quarter::printGradeInfo() const
{
    std::cout << "Quarter: " << m_quarter << std::endl;
    std::cout.setf(std::ios::fixed);
    std::cout.precision(3);
    
    for (auto it = m_courses.begin(); it != m_courses.end(); it++)
    {
        //  Get course name from the course class
        std::string name = (*it)->getName();
        int units = (*it)->getUnits();
        double gradePoint = (*it)->getGradePoint();
        std::string grade = (*it)->getGrade();
        
        std::cout << "=============================" << std::endl;
        std::cout << "Course: " << name << std::endl;
        std::cout << "Units: " << units << std::endl;
        std::cout << "Letter Grade: " << grade << std::endl;
        std::cout << "Grade Point: " << gradePoint << std::endl;
        std::cout << std::endl;
    }
}

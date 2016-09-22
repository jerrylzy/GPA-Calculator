//
//  Quarter.hpp
//  GPA Calculator
//
//  Created by Jerry Liu on 6/15/16.
//  Copyright © 2016 Jerry Liu. All rights reserved.
//

#ifndef Quarter_hpp
#define Quarter_hpp

#include <vector>
#include <string>

class Course;

//  There are 4 quarters in UCLA
const int NUM_OF_QUARTERS    = 4;
const std::string QUARTERS[] = { "FALL", "WINTER", "SPRING", "SUMMER" };

class Quarter
{
public:
    Quarter();
    Quarter(const std::vector<Course*>& courses, const std::string& quarter = "");
    ~Quarter();
    const std::string&  getName()               const;
    int                 getUnits()              const;
    int                 getUpperUnits()         const;
    int                 getNumOfCourses()       const;
    double              getGradePoint()         const;
    double              getGPA()                const;
    double              getUpperDivGradePoint() const;
    void                printGradeInfo()        const;
private:
    std::string             m_quarter;
    std::vector<Course*>    m_courses;
    int                     m_numOfCourses;
    int                     m_units;
    int                     m_upperUnits;
    double                  m_gradePoint;
    double                  m_upperGradePoint;
    double                  m_gpa;
    double                  m_upperGPA;
};

inline
const std::string& Quarter::getName() const
{
    return m_quarter;
}

inline
int Quarter::getUnits() const
{
    return m_units;
}

inline
int Quarter::getUpperUnits() const
{
    return m_upperUnits;
}

inline
int Quarter::getNumOfCourses() const
{
    return m_numOfCourses;
}

inline
double Quarter::getGradePoint() const
{
    return m_gradePoint;
}

inline
double Quarter::getGPA() const
{
    return m_gpa;
}

inline
double Quarter::getUpperDivGradePoint() const
{
    return m_upperGradePoint;
}

#endif /* Quarter_hpp */

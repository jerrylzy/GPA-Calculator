//
//  Course.hpp
//  GPA Calculator
//
//  Created by Jerry Liu on 6/15/16.
//  Copyright © 2016 Jerry Liu. All rights reserved.
//

#ifndef Course_hpp
#define Course_hpp

#include <string>

//  There are 13 different common letter grades
//  Can add "I" "NR" in the future
const int NUM_OF_GRADE_TYPES = 13;
const std::string GRADES[] = { "A+", "A", "A-", "B+", "B", "B-","C+",
                               "C", "C-", "D+", "D", "D-", "F" };

class Course
{
public:
    Course(int units, const std::string& grade, const std::string& name, char isUpper);
    int                getUnits()      const;
    const std::string& getGrade()      const;
    const std::string& getName()       const;
    double             getGradePoint() const;
    bool               isUpper()       const;
private:
    double      calcGradePoint(size_t type) const;
    int         m_units;
    std::string m_grade;
    std::string m_name;
    double      m_gradePoint;
    bool        m_isUpper;
};

inline
const std::string& Course::getGrade() const
{
    return m_grade;
}

inline
const std::string& Course::getName() const
{
    return m_name;
}

inline
int Course::getUnits() const
{
    return m_units;
}

inline
double Course::getGradePoint() const
{
    return m_gradePoint;
}

inline
bool Course::isUpper() const
{
    return m_isUpper;
}

#endif /* Course_hpp */

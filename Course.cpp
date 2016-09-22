//
//  Course.cpp
//  GPA Calculator
//
//  Created by Jerry Liu on 6/15/16.
//  Copyright © 2016 Jerry Liu. All rights reserved.
//

#include "Course.hpp"
#include <string>
#include <algorithm>

Course::Course(int units, const std::string& grade, const std::string& name, char isUpper)
: m_units(units), m_grade(grade), m_name(name)
{
    size_t type = find(GRADES, GRADES + NUM_OF_GRADE_TYPES, grade) - GRADES;
    m_gradePoint = calcGradePoint(type) * units;
    m_isUpper = tolower(isUpper) == 'y';
}

//  Assign grade points to letter grades
double Course::calcGradePoint(size_t type) const
{
    double point;
    switch (type)
    {
        case 0: case 1:     point = 4.0;    break;
        case 2:             point = 3.7;    break;
        case 3:             point = 3.3;    break;
        case 4:             point = 3.0;    break;
        case 5:             point = 2.7;    break;
        case 6:             point = 2.3;    break;
        case 7:             point = 2.0;    break;
        case 8:             point = 1.7;    break;
        case 9:             point = 1.3;    break;
        case 10:            point = 1.0;    break;
        case 11:            point = 0.7;    break;
        default:            point = 0.0;    break;
    }
    return point;
}

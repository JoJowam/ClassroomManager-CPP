#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

#include <fstream>
#include "course.h"
#include "person.h"

using std::ostream;
using std::remove;
using std::shared_ptr;
using std::vector;
using std::cout;
using std::endl;

// Forward References
class Course;

class Professor : public Person {
   private:
    vector<shared_ptr<Course>> courses;

   public:
    Professor(string name, string cpf, string tel);
    ~Professor(){};

    void pushCourse(shared_ptr<Course> course);
    void delCourse(shared_ptr<Course> course);
    vector<shared_ptr<Course>>& getCourses();

    bool operator==(const Professor& professor2);
    friend ostream& operator<<(ostream& outs, const Professor& professor);
};

#endif  // PROFESSOR_H
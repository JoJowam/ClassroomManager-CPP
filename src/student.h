#ifndef STUDENT_H
#define STUDENT_H

#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>

#include "course.h"
#include "person.h"

using std::ostream;
using std::endl;
using std::remove;
using std::cout;
using std::shared_ptr;
using std::vector;

class Student : public Person {
    private:
    const string id;
    vector<shared_ptr<Course>> courses;

    public:
    Student(string name, string cpf, string tel, string id);
    ~Student(){};

    string getId() const;
    vector<shared_ptr<Course>>& getCourses();
    void pushCourse(shared_ptr<Course> course);
    void delCourse(shared_ptr<Course> course);
    bool operator==(const Student& aluno2);
    friend ostream& operator<<(ostream& outs, const Student& student);


};


#endif  // STUDENT_H
/*Neste arquivo, armazeno os metodos referentes ás Salas de nosso sistema.
Logo abaixo do construtor, temos metodos Get para acessar valores em metodos
posteriores.*/

#include "classroom.h"

#include "course.h"

Classroom::Classroom(string id, int capacity) : id(id), capacity(capacity) {}

string Classroom::getId() const {
    return id;
}

int Classroom::getCapacity() const {
    return capacity;
}

void Classroom::pushCourse(shared_ptr<Course> course) {
    courses.push_back(course);
}

void Classroom::delCourse(shared_ptr<Course> course) {
    courses.erase(remove(courses.begin(), courses.end(), course), courses.end());
}

vector<shared_ptr<Course>> & Classroom::getCourses(){
    return courses;
}

bool Classroom::operator==(const Classroom& classroom2) {
    return id == classroom2.id;
}

ostream& operator<<(ostream& outs, const Classroom &classroom) {
    outs << classroom.id << " " << classroom.capacity << endl;
    return outs;
}

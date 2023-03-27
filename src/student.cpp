#include "student.h"

Student::Student(string name, string cpf, string tel, string id)
    : Person(name, cpf, tel), id(id) {}

string Student::getId() const { return id; }

vector<shared_ptr<Course>>& Student::getCourses(){
    return courses;

}

void Student::pushCourse(shared_ptr<Course> course) {
    courses.push_back(course);
}

void Student::delCourse(shared_ptr<Course> course) {
    courses.erase(remove(courses.begin(), courses.end(), course), courses.end());
}

bool Student::operator==(const Student& aluno) {
    return id == aluno.id;
}

ostream& operator<<(ostream& outs, const Student& student) {
    outs << "Name: " << student.name << endl
    << "CPF: " << student.cpf << endl
    << "Telefone: " << student.tel << endl 
    << "Matricula: "<< student.id << endl;
    return outs;
}
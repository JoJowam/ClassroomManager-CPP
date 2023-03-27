
/*Neste arquivo, armazeno os metodos referentes aos Cursos de nosso sistema.
Logo abaixo do construtor, temos metodos Gets e Sets para adiconar e acessar 
valores em metodos posteriores. O caminho que faço no codigo para pegar infor-
mações de cursos é, por exemplo: course->getProfessor()->getName(), para acessar
um professor de determinado curso!*/

#include "course.h"

#include "classroom.h"
#include "professor.h"
#include "student.h"

Course::Course(string id, string name) : id(id), name(name) {}

Course::Course(string id, string name, vector<bool> days)
    : id(id), name(name), days(days) {}

string Course::getId() const {
    return id;
}

string Course::getName() const {
    return name;
}

vector<bool> &Course::getDays() {
    return days;
}

shared_ptr<Classroom> Course::getClassroom() const {
    return classroom;
}

shared_ptr<Professor> Course::getProfessor() const {
    return professor;
}

vector<shared_ptr<Student>> & Course::getStudents(){
    return students;
}

void Course::setDays(vector<bool> days) {
    this->days = days;
}

void Course::setClassroom(shared_ptr<Classroom> classroom) {
    this->classroom = classroom;
}

void Course::setProfessor(shared_ptr<Professor> professor) {
    this->professor = professor;
}

void Course::setName(string name){
    this->name = name;
}

void Course::delProfessor() {
    this->professor = nullptr;
}

void Course::pushStudent(shared_ptr<Student> student) {
    students.push_back(student);
}

void Course::delStudent(shared_ptr<Student> student) {
    students.erase(remove(students.begin(), students.end(), student), students.end());
}

bool Course::operator==(const Course& curso2) {
    return id == curso2.id;
}

ostream& operator<<(ostream& outs, const Course& course) {
    outs << "Id: " << course.id << endl;
    outs << "Nome do Curso: " << course.name << endl;
    outs << "Dias: ";
    for (const auto& day : course.days)
        outs << day << " ";
    outs << endl;
    outs << "Professor: " << course.professor->getName() << endl;
    outs << "Classroom: " << course.classroom->getId() << endl;
    //todo enrollments
    outs << "Alunos Inscritos: " << course.enrollments << endl;
    return outs;
}
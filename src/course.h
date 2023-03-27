#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;
using std::vector;

/*Incluindo Referencias Anteriores.
No caso, para as salas, professores
e alunos  que vão estar em determinado
curso*/

class Classroom;
class Professor;
class Student;

class Course {
   private:

    //Variaveis que compõem um Curso.//
    int enrollments;
    const string id;
    string name;
    vector<bool> days;

    //Entidades de um Curso.//
    shared_ptr<Classroom> classroom;
    shared_ptr<Professor> professor;
    vector<shared_ptr<Student>> students;

   public:

    Course(string id, string name);
    Course(string id, string name, vector<bool> days);
    ~Course(){};

    //--------------Getters------------------------//
    string getId() const;
    string getName() const;
    vector<bool> &getDays();
    shared_ptr<Classroom> getClassroom() const;
    shared_ptr<Professor> getProfessor() const;
    vector<shared_ptr<Student>>& getStudents();
    //--------------------------------------------//


    //--------------Setters------------------------//
    void setDays(vector<bool> days);
    void setClassroom(shared_ptr<Classroom> classroom);
    void setProfessor(shared_ptr<Professor> professor);
    void setName(string name);
    //--------------------------------------------//

    void delProfessor();
    void pushStudent(shared_ptr<Student> student);
    void delStudent(shared_ptr<Student> student);

    bool operator==(const Course& curso2);
    friend ostream& operator<<(ostream& outs, const Course& course);
};

#endif  // COURSE_H
#ifndef SYSTEM_H
#define SYSTEM_H

#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#include "manager.h"
#include "classroom.h"
#include "course.h"
#include "professor.h"
#include "student.h"

using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::find_if;
using std::find_if_not;
using std::make_shared;
using std::shared_ptr;
using std::vector;

class System {
   private:
    vector<shared_ptr<Manager> > managers;
    vector<shared_ptr<Classroom> > classrooms;
    vector<shared_ptr<Professor> > professors;
    vector<shared_ptr<Course> > courses;
    vector<shared_ptr<Student> > students;
   
    static int dummyFlag;

   public:
    System(){};
    ~System(){};
    
    auto getDivergentDays(shared_ptr<Course> newCourse);
   //Crud:
   //-------------------------------------create---------------------------------------------------//
    shared_ptr<Manager> setManager(string name, string cpf, string tel, string login, string senha);
    shared_ptr<Classroom> setClassroom(string id, int capacity);
    shared_ptr<Professor> setProfessor(string name, string cpf, string tel);
    shared_ptr<Course> setCourse(string id, string name, vector<bool> days);
    shared_ptr<Student> setStudent(string name, string cpf, string tel, string id);
    //----------------------------------------------------------------------------------------//

    //--------------------Read---------------------------//
    vector<shared_ptr<Manager>> & getManagers();
    vector<shared_ptr<Classroom>> & getClassrooms();
    vector<shared_ptr<Professor>>& getProfessors();
    vector<shared_ptr<Course>> & getCourses();
    vector<shared_ptr<Student>> & getStudents();
    shared_ptr<Student> findStudent(string id);
    shared_ptr<Professor> findProfessor(string cpf);
    shared_ptr<Course> findCourse(string id);
    shared_ptr<Classroom> findClassroom(string id);
    //----------------------------------------------------//

    //----------------------------update----------------------------------//
    int updateProfessor(shared_ptr<Professor> professor, string tel);
    int updateProfessor(shared_ptr<Professor> professor, shared_ptr<Course> course);
    int updateStudent(shared_ptr<Student> student, string tel);
    int updateStudent(shared_ptr<Student> student, shared_ptr<Course> course);
    int updateCourse(shared_ptr<Course> course, string name);
    int updateCourse(shared_ptr<Course> course, shared_ptr<Professor> professor);
    int updateCourse(shared_ptr<Course> course, shared_ptr<Student> student);
    //--------------------------------------------------------------------//


    //---------------------- Delete -----------------//
    int deleteIntance(shared_ptr<Professor> professor);
    int deleteIntance(shared_ptr<Student> student);
    int deleteIntance(shared_ptr<Course> course);
    //-----------------------------------------------//
};

#endif  // SYSTEM_H
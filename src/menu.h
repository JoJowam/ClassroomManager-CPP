#ifndef MENU_H
#define MENU_H

#include <unistd.h>

#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>


using std::find_if_not;
using std::cin;
using std::cout;
using std::stringstream;
using std::find;
using std::get;
using std::getline;
using std::ofstream;
using std::ifstream;


#include "system.h"
#include "manager.h"

class Menu {
   private:
    System _system;

   public:
    Menu(/* args */);
    ~Menu();

    void pause();
    void clearScreen();

    string getString();
    int getInt();

    string showClassroom(int &errorFlag);
    shared_ptr<Course> showCoursesOfClassroom(string id);
    void showProfessorOfClassroom(shared_ptr<Course> course);
    void showStudentsOfClassroom(shared_ptr<Course> course);

    void loginScreen();
    void subMenuAbout();
    // Main Menu:
    void mainMenu();
    void subMenuStudent();
    void subMenuProfessor();
    //Menu Gestor e Crud Alunos:
    void subMenuManager();
    void subMenuStudentManager();
    void subMenuStudentManagerRegister();
    void subMenuStudentManagerSearchFor();
    void subMenuStudentManagerErase();
    void subMenuStudentManagerToUpdate();
    //Crud Professor:
    void subMenuProfessorManager();
    void subMenuProfessorManagerRegister();
    void subMenuProfessorManagerToSearch();
    void subMenuProfessorManagerErase();
    void subMenuProfessorManagerUpdate();
    //Crud Curso:
    void subMenuCourseManager();
    void subMenuCouseManagerRegister();
    void subMenuCouseManagerToSearch();
    void subMenuCouseManagerErase();
    void subMenuCouseManagerUpdate();
    //Cadastro de Salas:
    void subMenuClassroomManager();
    //Gerador de Relatorios:
    void subMenuReportManager();
    //Atualizar Alunos:
    void menuStudentAddCourses(shared_ptr<Student> student);
    void menuStudentDelCourses(shared_ptr<Student> student);
    //Atualizar Professores:
    void menuProfessorAddCourses(shared_ptr<Professor> professor);
    void menuProfessorDelCourses(shared_ptr<Professor> professor);
    //Atualizar Curso:
    void menuCourseAttProfessor(shared_ptr<Course> course);   
    void menuCourseDelStudent(shared_ptr<Course> course);
    //Printar relatorios:
    string reportOfStudent();
    string reportOfProfessor();
    string reportOfCourse();
    string reportOfClassrom();
    //Carregar Arquivo:
    void loadData(string filename);
};

#endif  // MENU_H
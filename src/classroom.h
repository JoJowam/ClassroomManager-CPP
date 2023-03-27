#ifndef CLASSROOM_H
#define CLASSROOM_H

//Incluindo Bibliotecas//
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

//Incluindo funções das Bibliotecas//
using std::cout;
using std::endl;
using std::ostream;
using std::remove;
using std::shared_ptr;
using std::vector;
using std::string;


/*Incluindo Referencias Anteriores.
No caso, para as salas, onde aloquei 
os cursos*/
class Course;

class Classroom {
//Criando variaveis Private para utilizar nos metodos do curso//
   private:
    const string id;
    const int capacity;
    vector<shared_ptr<Course>> courses;

   public:

    Classroom(string id, int capacity);
    ~Classroom(){};

    string getId() const;
    int getCapacity() const;

    ///------Adicionando e Deletando-------///
    void pushCourse(shared_ptr<Course> course);
    void delCourse(shared_ptr<Course> course);
    //--------------------------------------//

    vector<shared_ptr<Course>>& getCourses();

    ///--------------Overcharging-------------///
    bool operator==(const Classroom& classroom2);
    friend ostream& operator<<(ostream& outs, const Classroom& classroom);
    //--------------------------------------------------------------------//
};

#endif  // CLASSROOM_H
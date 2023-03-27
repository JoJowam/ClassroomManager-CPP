#include "professor.h"

#include "course.h"

Professor::Professor(string name, string cpf, string tel )
          : Person(name, cpf, tel) {}

void Professor::pushCourse(shared_ptr<Course> course){
    
    courses.push_back(course);
}

void Professor::delCourse(shared_ptr<Course> course) {
    courses.erase(remove(courses.begin(), courses.end(), course), courses.end());
}

vector<shared_ptr<Course>>& Professor::getCourses(){
    return courses;
}

bool Professor::operator==(const Professor& professor2) {
    return cpf == professor2.cpf;
}

ostream& operator<<(ostream& outs, const Professor& professor) {
    outs << "Name: " << professor.name << endl
    << "CPF: " << professor.cpf << endl
    << "Telefone: " << professor.tel << endl;
    return outs;
}
#ifndef PERSON_H
#define PERSON_H

#include <fstream>
#include <string>

using std::string;

class Person {
   protected:
    string name;
    string cpf;
    string tel;

   public:
    Person(string name, string cpf, string tel); 
    Person(){}   
    ~Person() {}

    void setName(string name);
    void setCpf(string cpf);
    void setTel(string tel);
    string getName() ;
    string getTel() ;
    string getCpf();
};

#endif  // PERSON_H
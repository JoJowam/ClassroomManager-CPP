#ifndef MANAGER_H
#define MANAGER_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "person.h"

using std::cout;
using std::cin;
using std::endl;
using std::find_if;
using std::shared_ptr;
using std::string;
using std::vector;


class Manager : public Person {
   private:

    //Variaveis que compõe gestor//
    const string login = "admin";
    const string password = "admin";

   public:

    Manager(string name, string cpf, string tel, string login, string password);
    Manager(){};  //Construtor Padrão//
    ~Manager(){};
    
    bool tryLogin(vector<Manager> manager);
    bool operator==(const Manager& manager2);
};

#endif  // MANAGER_H
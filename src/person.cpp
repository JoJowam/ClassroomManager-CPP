#include "person.h"

Person::Person(string name, string cpf, string tel)
    : name(name), cpf(cpf), tel(tel) {}

void Person::setName(string name) {
    this->name = name;
}

void Person::setCpf(string cpf) {
    this->cpf = cpf;
}

void Person::setTel(string tel) {
    this->tel = tel;
}


string Person::getName()  { return name; }

string Person::getTel()  { return tel; }

string Person::getCpf()  { return cpf; }


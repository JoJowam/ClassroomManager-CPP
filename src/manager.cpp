/*Neste arquivo, estão armazenados Metodos referentes ao Gestor
e um metodo especifico "tryLogin" é usado no menu para implementar
a tela de login!*/

#include "manager.h"

Manager::Manager(string name, string cpf, string tel, string login, string password)
    : Person(name, cpf, tel), login(login), password(password) {}

bool Manager::operator==(const Manager& manager2) {
    return login == manager2.login && password == manager2.password;
}


bool Manager::tryLogin(vector<Manager> manager){
    string enteredLogin, enteredPassword;
    
    cout << "Digite o User: ";
    getline(cin, enteredLogin);
    cin.clear(); //limpando buffer para não bugar a entrada//

    cout << "Digite a Senha: ";
    getline(cin, enteredPassword);
    cin.clear();


    for (const Manager& manager : manager) { //For para verificar o login dos gestores//
        if (manager.login == enteredLogin && manager.password == enteredPassword) {
            cout << "Login realizado com sucesso!" << endl;
            return true;
        }
    }

    cout << "Login inválido. Tente novamente." << endl;
    return false;
}

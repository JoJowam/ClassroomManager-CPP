/*Neste arquivo, realizo todas as operações que são mostradas ao usuario e implemento
lógicas para construir entidades atraves de outros metodos!*/

#include "menu.h"

Menu::Menu() {

}

Menu::~Menu() {
    
}


void Menu::pause() {

    //Função para substituir "system(pause);" <- Má Prática!//
    cout << "Press Enter to continue...";

    cin.get();
}

void Menu::clearScreen() {

    //Filtrando qual chamada fazer para o SO//
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

string Menu::getString(){

    //Ler strings com espaço sem liberar buffer//
    string line;
    getline(cin, line);
    return line;
}

int Menu::getInt(){
    
    //Ler inteiros, alternativa á getline()//
    int value;
    string line;
    getline(cin, line);
    stringstream linestream(line);
    linestream >> value;

    return value;
}


string Menu::showClassroom(int& errorFlag) {
    int classroomIdx;

    //Função que retorna salas cadastradas para um Professor ou aluno//
    //OP 1 e 2 do menu!//
    while (true) {

        clearScreen();
        cout << "Estas sao as salas cadastradas no sistema ate o momento: " << endl;

        //Mini Menu para listar ID de salas cadastradas//
        for (size_t i = 0; i < _system.getClassrooms().size(); i++) {
            cout << i << ". " << _system.getClassrooms()[i]->getId() << endl;
        }

        cout << _system.getClassrooms().size() << ". Sair" << endl;
        cout << "\n" << "Escolha a sala: " << endl
             << "-> ";
        classroomIdx = getInt(); 

        if (classroomIdx == static_cast<int>(_system.getClassrooms().size())) { //Op de voltar ao menu anterior//
            return nullptr; 
        }

        if (classroomIdx < 0 || classroomIdx > static_cast<int>(_system.getClassrooms().size())) {
            cout << "Opcao Invalida!";
            pause();
            continue;
        }

        if (classroomIdx == static_cast<int>(_system.getClassrooms().size())) {
            errorFlag = 1;
            return "Opcao Invalida!";
            pause();
            continue;
        }

        break;
    }

    errorFlag = 0;
    //Retornando Sala selecionada acima!//
    return _system.getClassrooms()[classroomIdx]->getId();
}

shared_ptr<Course> Menu::showCoursesOfClassroom(string id) {
    int courseIdx = 0;

    //Retorna Cursos para um Aluno ou Professor//
    //OP 1 e 2 do MainMenu//
    while (true) {
        clearScreen();
        cout << "Estes sao os Cursos cadastrados que ocorrem na sala " << id << endl;
        for (size_t i = 0; i < _system.findClassroom(id)->getCourses().size(); i++) {
            cout << i << ". " << _system.findClassroom(id)->getCourses()[i]->getId() << endl;
        }
        cout << _system.findClassroom(id)->getCourses().size() << ". Voltar ao menu anterior" << endl;
        cout << "\n" << "Escolha o curso: " << endl
             << "-> ";
        courseIdx = getInt();

        if (courseIdx == static_cast<int>(_system.findClassroom(id)->getCourses().size())) { //Op de voltar ao menu anterior//
            return nullptr; 
        }
        
        if (courseIdx < 0 || courseIdx > static_cast<int>(_system.findClassroom(id)->getCourses().size()) - 1) {
            cout << "Opcao Invalida!";
            pause();
            continue;
        }

        break;
    }
    //Retornando Opção Selecionada//
    return _system.findClassroom(id)->getCourses()[courseIdx];
}

void Menu::showProfessorOfClassroom(shared_ptr<Course> course) {
    clearScreen();
    if (course->getProfessor() == nullptr) { //Verificando se o curso ainda nao tem professor.//
        cout << "Esse curso nao possui um professor registrado. Por favor, escolha outro curso." << endl;
        return;
    }
    
    string professor = course->getProfessor()->getName();
    cout << "Professor responsavel pela sala: " << "\"" << course->getId() << "\"" << " eh: "<< endl << professor << endl;
    cout << "Contato:" << course->getProfessor()->getTel() << endl << endl;
    return;
}

void Menu::showStudentsOfClassroom(shared_ptr<Course> course) {

    clearScreen();
    if (course->getStudents().empty()) { //Verificando se o curso não tem alunos.//
        cout << "Não ha Alunos matriculados neste curso." << endl;
        return;
    }
    cout << "Os Alunos matriculados neste curso sao: " << endl  << endl;
    cout << "Nome\t\t\t\t\tMatricula\tContato" << endl;
     cout << "-----------------------------------------------------------------------------------------" << endl;
    for (auto student : course->getStudents()) {
        cout << student->getName() << "\t\t\t" << student->getId() << "\t" << student->getTel() << endl;
    }
    cout << endl;
    return;
}

//=======================Main Menu================================//
void Menu::loginScreen() {
    Manager _manager;
    vector<Manager> managers;
    managers.push_back(Manager("Gerente Geral", "111.111.111-11", "1111-1111", "admin", "admin"));

    //Metodo que chama o tryLogin de Manager//
    while (!_manager.tryLogin(managers)) {
        cout << "Tente novamente." << endl;
    }

    //Se o login foi bem sucedido, acessa o resto do sistema//
    cout << "Bem-vindo ao sistema!" << endl;
}

void Menu::subMenuAbout(){
    clearScreen();
    cout << "Trabalho Sistema de Gestao de Salas de Aula:" << endl << endl;
    cout << "O Objetivo deste projeto eh criar um ambiente virtual onde seja possivel fazer o cadastro de Salas, Cursos, Alunos e professores" << endl;
    cout << "que sao adicionados ao sistema atraves da entidade gestor. A partir disso, alunos e professores podem usar o sistema para procurar" << endl;
    cout << "informacoes relacionadas a suas aulas!" << endl << endl;
    cout << "A interface intuitiva, torna-se um fator impar na utilizacao do programa que permite ao usuario:" << endl;
    cout << "realizar tarefas como o cadastro, busca, atualizacao e remocao de professores, alunos, cursos e salas de aula.";
    cout << "tambem eh possivel vizualizar informacoes detalhadas, carregar informacoes exteriores  e gerar" << endl;
    cout << "relatorios sobre as entidades cadastradas." << endl << endl;
    cout << "Desenvolvido por @Josue Vila Real, 2023." << endl << endl;
    pause();

}
void Menu::mainMenu() {
    int option;

    /*Menu responsavel por chamar os outros metodos
    é daqui que se inicia as demais operações!*/
    while (true) {
        clearScreen();
        cout << "Bem vindo ao sistema de gerenciamento de salas!\n"<< endl;
        cout << "Main Menu:" << endl;
        cout << "1. Aluno" << endl;
        cout << "2. Professor" << endl;
        cout << "3. Gestor" << endl;
        cout << "4. Sobre" << endl;
        cout << "5. Exit" << endl;
        cout << "\n-> ";

        option = getInt();

        switch (option) {
            case 1:
                subMenuStudent();
                break;
            case 2:
                subMenuProfessor();
                break;
            case 3:
                loginScreen();
                subMenuManager();
                break;
            case 4:
                subMenuAbout();
                continue;
            case 5:
                return;
            default:
                cout << "Opcao invalida, por favor insira um valor valido!" << endl;
                pause();
        }
    }
}

void Menu::subMenuStudent() {
    shared_ptr<Course> course;
    int option;
    string classromId;
    int errorFlag;

    //Primeira OP do mainMenu.//
    //chama metodos anteiormente explicados!//
    while (true) {
        clearScreen();

        cout << "Voce entrou como: Estudante!" << endl;
        cout << "1. Cursos e Profesores" << endl;
        cout << "2. Voltar ao MENU INICIAL" << endl;
        cout << "\n-> ";

        option = getInt();

        switch (option) {
            case 1:
                classromId = showClassroom(errorFlag); //Mostra as Salas;
                if (errorFlag) continue;
                course = showCoursesOfClassroom(classromId);
                if (course == nullptr) continue;  
                showProfessorOfClassroom(course);//Mostra Professores da sala!
                pause();
                continue;
            case 2:
                return;
            default:
                cout << "Opcao Invalida. Por favor, insira uma opcao valida!." << endl;
                pause();
                continue;
        }
    }
}

void Menu::subMenuProfessor() {
    shared_ptr<Course> course;
    int option;
    string classromId;
    int errorFlag;

    //Segunda OP do mainMenu.//
    //chama metodos anteiormente explicados!//
    while (true) {
        clearScreen();

        cout << "Voce entrou como: Professor!" << endl;
        cout << "1. Salas, Cursos e Alunos" << endl;
        cout << "2. Voltar ao MENU INICIAL" << endl;
        cout << "\n-> ";

        option = getInt(); 
        switch (option) {
            case 1:
                classromId = showClassroom(errorFlag); //Mostra as Salas;
                if (errorFlag) continue;
                course = showCoursesOfClassroom(classromId);
                if (course == nullptr) continue;  
                showStudentsOfClassroom(course);//Mostra alunos da sala!
                pause();
                continue;
            case 2:
                return;
            default:
                cout << "Opcao Invalida. Por favor, insira uma opcao valida!." << endl;
                pause();
                continue;
        }

        break;
    }
}
//================================================================//


//=======================Menu Gestor================================//
void Menu::subMenuManager() {
    int option;

    /*Este Menu é chamado quando o login
    é efetuado com sucesso, nele ficam todas
    as operações referentes áo Gestor de um curso!*/
    while (true) {
        clearScreen();
        cout << "\nVoce entrou como Gestor!" << endl
             << endl
             << "Escolha uma opcao:" << endl
             << "1. Gerenciar Aluno" << endl
             << "2. Gerenciar Professor" << endl
             << "3. Gerenciar Curso" << endl
             << "4. Cadastrar Sala" << endl
             << "5. Gerar Relatorio" << endl
             << "6. Carregar Arquivo" << endl
             << "7. Voltar ao MENU PRINCIPAL" << endl
             << "-> ";

        option = getInt(); 

        switch (option) {
            case 1:
                subMenuStudentManager();
                break;
            case 2:
                subMenuProfessorManager();
                break;
            case 3:
                subMenuCourseManager();
                break;
            case 4:
                subMenuClassroomManager();
                break;
            case 5:
                subMenuReportManager();
                break;
            case 6:
                //Passando o nome do arquivo de testes como argumento.//
                loadData("src/dados.txt");
                pause();
                break;
            case 7:
                return;
            default:
                cout << "Opcao Invalida. Por favor, insira uma opcao valida!." << endl;
                pause();
        }
    }
}

//Crud alunos:
void Menu::subMenuStudentManager() {
    int option;
    
    //Menu Referente á Gestão de Alunos!//
    while (true) {
        clearScreen();

        cout << "\nVoce escolheu a opcao: Gerenciar Alunos!" << endl<< endl
             << "Escolha uma opcao:" << endl
             << "1. Cadastrar" << endl
             << "2. Consultar" << endl
             << "3. Excluir" << endl
             << "4. Atualizar" << endl
             << "5. Voltar ao MENU ANTERIOR" << endl
             << "-> ";
        option = getInt(); 
        clearScreen();

        switch (option) {
            case 1:
                subMenuStudentManagerRegister();
                break;
            case 2:
                subMenuStudentManagerSearchFor();
                break;
            case 3:
                subMenuStudentManagerErase();
                break;
            case 4:
                subMenuStudentManagerToUpdate();
                break;
            case 5:
                return;
            default:
                cout << "Opcao Invalida. Por favor, insira uma opcao valida!." << endl;
                pause();
            continue;
        }
    }
}

void Menu::subMenuStudentManagerRegister(){
    shared_ptr<Student> student;
    string name, cpf, tel, id;
    int newOne = 1;

    /*Neste metodo, assim como nos proximos que estão
    relacionaos ao cadastro de alguma entidade, eu coleto
    as informações de algum orgão, e chamo um método 
    setCourses, que cria uma nova entidade Student.*/
    while (true){
        clearScreen();

        cout << "Cadastro de Alunos!\n"<< endl;
        cout << "Digite abaixo as informacoes do aluno! \n"<< endl;

        cout << "Nome: ";
        name = getString();

        cout << "Cadastro de Pessoa Fisica (CPF): ";
        cpf = getString();

        cout << "Telefone: +55 ";
        tel = getString();

        cout << "Matricula: ";
        id = getString();

        // Utilizando Throw/Try/Catch para estar coletando as exceções//
        // E retornando os devidos avisos!//
        try{
            student = _system.setStudent(name, cpf, tel, id); // Salvando Aluno//
            menuStudentAddCourses(student);                   // Mostrando os cursos disponíveis para esse aluno//
        }
        catch (int){
            cout << "Erro: Este estudante já existe." << endl;
            pause();
        }

        cout << "\n"
             << "Deseja Cadastrar um novo Aluno?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();
        if (newOne == 2) break;

    }
}

void Menu::subMenuStudentManagerSearchFor() {
    shared_ptr<Student> student;
    string name, cpf, tel, id;
    int newOne = 1;

    /*Neste método, assim como seus similares, que efetuam
    a consulta de uma entidade, eu uso um elemento chave. No 
    caso de alunos será a imutavel matricula (ID). E atraves
    dessa variavel, eu chamo uma função findStudent que procura
    pelo aluno atrelado á aquela variavel*/
    while (true){
        clearScreen();

        cout << "Pesquisa de Alunos!\n"<< endl;
        cout << "Digite a Matricula do aluno a ser pesquisado:\n"<< endl
            << "-> ";
        id = getString();
        clearScreen();

        try{
            student = _system.findStudent(id); // Procurando pelo Aluno!//
        }
        catch (int){
            cout << "O Aluno com a Matricula: " << "\"" << id << "\"" <<" nao existe!" << endl
                 << "\n";
            pause();
            continue;
        }

        cout << "\nForam encontradas as seguintes informacoes de: " << "\"" << id << "\"" << endl
             << "\n";
        cout << "Nome: " << student->getName() << endl;
        cout << "Matricula: " << student->getId() << endl;
        cout << "CPF: " << student->getCpf() << endl;
        cout << "Telefone: " << student->getTel() << endl;
        cout << "Matriculado nos cursos: ";
        for (auto course : student->getCourses()){
            if (course->getName() == ""){
                cout << "O Aluno com a matricula: " << "\"" << id << "\"" <<" nao esta matriculado em nenhum curso!";
            }
            else{
                cout << course->getName() << " ";
            }
        }

        cout << "\n"
             << endl
             << "Deseja consultar um novo aluno?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt(); 

        if (newOne == 2) break;
    }
}

void Menu::subMenuStudentManagerErase(){

    shared_ptr<Student> student;
    string name, cpf, tel, id;
    int newOne = 1;


    /*Para este metodo e seus similares, tal como no
    metodo de pesquisa, pesquisamos por um ID e depois de
    achar este estudante o apagamos*/
    while (true){
        clearScreen();

        cout << "Excluir Alunos!\n"<< endl;
        cout << "Digite a Matricula do aluno a ser excluido:\n"<< endl
             << "-> ";
        id = getString();

        try{
            student = _system.findStudent(id); // Procurando por aluno a ser exluído//
        }
        catch (int){
            cout << "\n"
                 << "O Aluno com a Matricula: " << "\"" << id << "\"" << " nao existe!" << endl
                 << "\n";
            pause();
            continue;
        }

        _system.deleteIntance(student); // Deletando a instancia de aluno//
        clearScreen();

        cout << "O Aluno: " << "\"" << id << "\"" << " foi excluido com sucesso!" << endl
             << endl;
        cout << "Deseja excluir outro aluno?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
    }
}

void Menu::subMenuStudentManagerToUpdate(){
    shared_ptr<Student> student;
    string name, cpf, tel, id;
    int newOne = 1, op;

    while (true){
        cout << "Atualizar Aluno!!\n"<< endl;
        cout << "Digite a Matricula do aluno que deseja atualizar: \n"<< endl
             << "-> ";
        id = getString();
        clearScreen();

        try{
            student = _system.findStudent(id); // Procurando por aluno a ser atualizado//
        }
        catch (int){
            cout << "O aluno com a Matricula " << id << " nao existe!" << endl
                 << endl;
            pause();
            continue;
        }

        cout << "O que deseja alterar: " << endl
             << "1. Telefone" << endl
             << "2. Adicionar Curso" << endl
             << "3. Remover Curso" << endl
             << "\n-> ";
        op = getInt();
        clearScreen();

        if (op == 1){

            cout << "Digite o novo telefone: ";
            tel = getString();

            _system.updateStudent(student, tel); // Atualizando o telefone do aluno!//
        }
        else if (op == 2){
            menuStudentAddCourses(student); // Mostrando Cursos disponiveis para aquele aluno//
        }
        else if (op == 3){
            menuStudentDelCourses(student); // Deletando Cursos Disponiveis//
        }
        clearScreen();

        cout << "\n"
             << "Deseja atualizar um outro Aluno?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
    }
}

//Crud professores:
void Menu::subMenuProfessorManager() {
    int option;
    /*Menu Referente ás operações da gerencia
    para com os professores!*/
    while (true) {
        clearScreen();
        cout << "\nVoce escolheu a opcao: Gerenciar Professores!" << endl
             << endl
             << "Escolha uma opcao:" << endl
             << "1. Cadastrar" << endl
             << "2. Consultar" << endl
             << "3. Excluir" << endl
             << "4. Atualizar" << endl
             << "5. Voltar ao MENU ANTERIOR" << endl
             << "-> ";
        option = getInt(); 
        
        switch (option) {
            case 1:
                subMenuProfessorManagerRegister();
                break;
            case 2:
                subMenuProfessorManagerToSearch();
                break;
            case 3:
                subMenuProfessorManagerErase();
                break;
            case 4:
                subMenuProfessorManagerUpdate();
                break;
            case 5:
                return;
            default:
                cout << "Opcao Invalida. Por favor, insira uma opcao valida!." << endl;
                pause();
        }
    }
}

void Menu::subMenuProfessorManagerRegister(){
    string name, cpf, tel;
    shared_ptr<Professor> professor;
    shared_ptr<Course> course;
    int newOne = 1;

    /*Menu responsavel pelo cadastro de professores*/
    while (true){
        clearScreen();

        cout << "Cadastro de Professores!\n"<< endl;
        cout << "Digite abaixo as informacoes do professor! \n"<< endl;

        cout << "Nome: ";
        name = getString();

        cout << "Cadastro de Pessoa Fisica (CPF): ";
        cpf = getString();

        cout << "Telefone: +55 ";
        tel = getString();
        clearScreen();

        try{
                professor = _system.setProfessor(name, cpf, tel);
                menuProfessorAddCourses(professor); // Mostrando os cursos disponiveis para este professor//
        }
        catch (int){
                cout << "Error: O Professor" << "\n" << name << "\"" <<", ja existe: " << endl;
        }

        cout << "Deseja Cadastrar um novo professor?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
    }
}

void Menu::subMenuProfessorManagerToSearch(){
    string name, cpf, tel;
    shared_ptr<Professor> professor;
    shared_ptr<Course> course;
    int newOne = 1;

    /*Metodo que pesquisa por um professor, se existente!*/
    while (true){
        clearScreen();
        cout << "Pesquisa de professores!\n"<< endl;
        cout << "Digite o CPF do professor a ser pesquisado:\n"<< endl
             << "-> ";
        cpf = getString();

        try{
            professor = _system.findProfessor(cpf); // Procurando pelo professor//
        }
        catch (int){
            cout << "O professor com CPF: " << "\"" << cpf << "\"" <<" nao existe!" << endl;
            pause();
            continue;
        }
        clearScreen();

        // Retornando o professor pesquisado//
        cout << "\nForam encontradas as seguintes informacoes de: " << "\"" << cpf << "\"" <<endl;
        cout << "Nome: " << professor->getName() << endl;
        cout << "CPF: " << professor->getCpf() << endl;
        cout << "Telefone: " << professor->getTel() << endl;
        cout << "Responsavel pelos cursos: " << endl;
        for (auto course : professor->getCourses()){
                cout << course->getName() << endl;
        }

        cout << "\n"
             << "Deseja consultar um novo professor?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
    }
}

void Menu::subMenuProfessorManagerErase(){
    string name, cpf, tel;
    shared_ptr<Professor> professor;
    shared_ptr<Course> course;
    int newOne = 1;

    /*Metodo que exclui um professor, se existente */
    while (true){
        clearScreen();
        cout << "Excluir professores!\n"<< endl;
        cout << "Digite o CPF do professor a ser excluido:\n"<< endl
             << "-> ";
        cpf = getString();

        try{
                professor = _system.findProfessor(cpf); // Procurando professor a ser exluído//
        }
        catch (int){
                cout << "O professor com CPF" << cpf << "nao existe!" << endl;
                pause();
                continue;
        }

        _system.deleteIntance(professor); // Deletando instancia de professor//
        cout << "O professor foi excluido com sucesso!" << endl<< endl;

        cout << "Deseja excluir outro professor?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
    }
}

void Menu::subMenuProfessorManagerUpdate(){
    string name, cpf, tel;
    shared_ptr<Professor> professor;
    shared_ptr<Course> course;
    int op;
    int newOne = 1;

    while (true) {
        clearScreen();
        cout << "Atualizar Professor!!\n"<< endl;
        cout << "Digite o CPF do professor que deseja atualizar: \n"<< endl
            << "-> ";
        cpf = getString();

        try{
                professor = _system.findProfessor(cpf);
        }
        catch (int){
            cout << "O professor com CPF: " << "\"" << cpf <<  "\"" << " nao existe!" << endl;
            pause();
            continue;
        }

        cout << "\n"
            << "O que deseja alterar: " << endl
            << "1. Telefone" << endl
            << "2. Adicionar Curso" << endl
            << "3. Remover Curso" << endl
            << "\n-> ";
        op = getInt();
        clearScreen();

        if (op == 1){
            cout << "Digite o novo telefone: ";
            tel = getString();
            _system.updateProfessor(professor, tel); // Atualizando telefone de professor//
        }
        else if (op == 2){
            menuProfessorAddCourses(professor); // Mostrando cursos que podem ser adicionados//
        }
        else if (op == 3){
            menuProfessorDelCourses(professor); // Mostrando cursos que podem ser removidos//
        }
        cout << "\n"
            << "Deseja atualizar um outro Professor?" << endl
            << "1. Sim" << endl
            << "2. Nao" << endl
            << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
    }
}

//Crud cursos:
void Menu::subMenuCourseManager() {
    int option;

    /*Menu referente ás operações da gerencia
    para com os Cursos que desejam ser cadastrados
    procurados ou alterados*/
    while (true) {
        clearScreen();

        cout << "\nVoce escolheu a opcao: Gerenciar Curso!" << endl << endl
             << "Escolha uma opcao:" << endl
             << "1. Cadastrar" << endl
             << "2. Consultar" << endl
             << "3. Excluir" << endl
             << "4. Atualizar" << endl
             << "5. Voltar ao MENU ANTERIOR" << endl
             << "-> ";
        option = getInt();
    
        switch (option) {
            case 1:
                subMenuCouseManagerRegister();
                break;
            case 2:
                subMenuCouseManagerToSearch();
                break;
            case 3:           
                subMenuCouseManagerErase();
                break;
            case 4:
                subMenuCouseManagerUpdate();
                break;
            case 5:         
                return;
            default:
                cout << "Opcao Invalida. Por favor, insira uma opcao valida!." << endl;
                pause();             
        }
    }
}

void Menu::subMenuCouseManagerRegister(){
    vector<string> daysMap{"Segunda", "Terca", "Quarta", "Quinta", "Sexta"};
    string id, name;
    int newOne = 1, daysOption;

    while (true){
        clearScreen();

        cout << "Cadastro de Cursos!\n"<< endl;
        cout << "Digite abaixo as informacoes do curso! \n"<< endl;
        cout << "ID: ";

        id = getString();

        cout << "Nome: ";
        name = getString();

        vector<bool> days(5, false); // Criando Vector de Dias da semana//
        while (find(days.begin(), days.end(), false) != days.end()){
                clearScreen();
                // Mini Menu para a inserção de dias no curso//
                cout << "Escolha os Dias: " << endl;
                for (auto i = 0; i < 5; i++){
                    if (!days[i]){
                        cout << i << " " << daysMap[i] << endl;
                    }
                }
                cout << 5 << " Sair" << endl;
                daysOption = getInt();

                if (daysOption >= 0 && daysOption <= 4){
                    days[daysOption] = true;
                }
                else if (daysOption == 5){
                    break;
                }
                else{
                    cout << "Opcao Invalida. Por favor, insira uma opcao valida!";
                    pause();
                }
        }
        clearScreen();

        try{
            _system.setCourse(id, name, days); // Adicionando Curso ao sistema//
            cout << "Curso adicionado com sucesso." << endl << "\n";
        }
        catch (int e){
            switch (e){
            case 1:
                cout << "O Curso ja existe!" << endl;
                break;
            case 2:
                cout << "Nao ha salas com dias disponiveis" << endl;
                break;
            default:
                cout << "Erro desconhecido" << endl;
            }
            pause();
        }

        cout << "\n"
             << "Deseja Cadastrar um novo Curso?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
    }
}

void Menu::subMenuCouseManagerToSearch(){
    vector<string> daysMap{"Segunda", "Terca", "Quarta", "Quinta", "Sexta"};
    shared_ptr<Course> course;
    string id;
    int newOne = 1;

    while (true){
        clearScreen();
        cout << "Pesquisa de Cursos!\n" << endl;
        cout << "Digite o ID do curso:\n"<< endl
             << "-> ";
        id = getString();

        try{
            course = _system.findCourse(id); // Procurando por curso//
        }
        catch (int){
            cout << "O Curso com ID " << id << " nao existe!" << endl;
            pause();
            continue;
        }
        clearScreen();

        // Imprimindo os dados do curso pesquisado//
        cout << "\nForam encontradas as seguintes informacoes de: " << id << endl;
        cout << "\nNome: " << course->getName() << endl;
        cout << "ID: " << course->getId() << endl;
        cout << "Dias: ";
        for (int i = 0; i < 5; i++){
            if (course->getDays()[i]){
                cout << daysMap[i] << " ";
            }
        }
        cout << endl;
        if (course->getProfessor() != nullptr){
            cout << "Professor:" << course->getProfessor()->getName() << endl;
            cout << "Contato do Responsavel: " << course->getProfessor()->getTel() << endl;
        }
        cout << "Sala: " << course->getClassroom()->getId() << endl << "\n";

        cout << "Deseja consultar um novo curso?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
    }
}

void Menu::subMenuCouseManagerErase(){
    shared_ptr<Course> course;
    string id;
    int newOne = 1;

    while (true){
        clearScreen();

        cout << "Excluir Cursos!\n"<< endl;
        cout << "Digite o ID do curso a ser excluido:\n"<< endl
             << "-> ";
        id = getString();

        try{
            course = _system.findCourse(id);
        }
        catch (int){
            cout << "O curso com o ID: " << "\"" << id << "\"" <<", nao existe!" << endl;
            pause();
            continue;
        }
        clearScreen();

        _system.deleteIntance(course); // Deletando a instancia do curso pesquisado acima//
        cout << "O Curso com o ID: " << "\"" << id << "\"" << ", foi excluido com sucesso!" << endl << "\n";

        cout << "Deseja excluir outro curso?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
        
    }
}

void Menu::subMenuCouseManagerUpdate(){
    shared_ptr<Course> course;
    string id, name;
    int op, newOne = 1;

    while (true)
    {
        clearScreen();

        cout << "Atualizar Curso!!\n"<< endl;
        cout << "Digite o ID do curso que deseja atualizar: \n"<< endl
             << "-> ";
        id = getString();

        try{
            course = _system.findCourse(id);
        }
        catch (int){
            cout << "O curso com ID" << id << "nao existe!" << endl;
            pause();
            continue;
        }
        clearScreen();

        cout << "O que deseja alterar: " << endl
             << "1. Nome" << endl
             << "2. Alterar Professor" << endl
             << "3. Remover Aluno" << endl
             << "4. Voltar" << endl
             << "\n-> ";
        op = getInt();

        clearScreen();
        switch (op){

        case 1:

            cout << "Digite o novo nome: ";
            name = getString();
            _system.updateCourse(course, name); // Alterando nome de um curso//
            cout << "Nome atualizado!" << endl;
            clearScreen();

            break;
        case 2:
            menuCourseAttProfessor(course); // Alterando o professor de um curso//
            break;
        case 3:
            menuCourseDelStudent(course); // Alterando um Aluno de um curso//
            break;
        case 4:
            return;
            break;
        default:
            break;
        }

        cout << "\nDeseja atualizar um outro curso?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2) break;
    }
}

//Cadastro de salas:
void Menu::subMenuClassroomManager() {
    string id;
    int capacity;
    int newOne = 1;

    /*Menu Referente a todas as operações 
    da gerencia envolvendo as salas*/
    while (newOne == 1) {
        clearScreen();
        cout << "Cadastro de Salas!\n"<< endl;
        cout << "Digite o ID da Sala:\n"<< endl
        << "-> ";
        id = getString();
        
        cout << "Digite a capacidade da Sala:\n"<< endl
             << "-> ";
        capacity = getInt();

        try {
            _system.setClassroom(id, capacity); //Mandando a sala para o sistema com as informações coletadas//
        } catch (int) {
            cout << "Erro: Capacidade invalida. Digite um inteiro positivo." << endl;
            pause();
        }
        clearScreen();

        cout << "Curso cadastrado com sucesso!" << endl << "\n";
        cout << "Deseja Cadastrar uma nova sala?" << endl
             << "1. Sim" << endl
             << "2. Nao" << endl
             << "-> ";
        newOne = getInt();

        if (newOne == 2)
            subMenuManager();
    }
}

//Gerador de Relatórios:
void Menu::subMenuReportManager() {
    int option, op;

    /*Menu referente áo relatório*/
    while(true){
        clearScreen();

        cout << "\nVoce escolheu a opcao: Relatorio!" << endl
            << endl
            << "Escolha uma opcao:" << endl
            << "1. Aluno" << endl
            << "2. Professor" << endl
            << "3. Curso" << endl
            << "4. Salas" << endl
            << "5. Voltar ao MENU ANTERIOR" << endl
            << "-> ";
        option = getInt();

        switch (option) {
            case 1:
                while (true) {
                    clearScreen();

                    cout << "O que deseja fazer:" << endl;
                    cout << "1. Vizualizar em tela." << endl;
                    cout << "2. Gerar aquivo .TXT:" << endl;
                    cout << "3. Voltar" << endl;
                    op = getInt();
                    clearScreen();

                    if (op == 1){
                        if ( reportOfStudent() == ""){ //Caso não tenha alunos...//
                            cout << "Erro: Nao foram encontrados alunos no sistema." << "\n" << endl;
                            pause();
                            return;
                        }else{
                            cout << "Relatorio dos Alunos cadastrados no sistema:" << endl << endl;
                            cout << reportOfStudent(); //Printando Alunos...//
                            pause();
                            return;
                        }         

                    }
                    if (op == 2){
                        //Abrindo arquivo com "trunc" para poder criar um arquivo novo sempre que necessario.//
                        ofstream ofs("Students_Report.txt", fstream::trunc); 
                        ofs << reportOfStudent();
                        ofs.close();
                        cout << "Relatorio salvo com sucesso em Students_Report.txt\n";
                        pause();
                    }
                    if (op == 3){
                        return;
                    }
                }
                break;
            case 2:
                while (true) {
                    clearScreen();

                    cout << "O que deseja fazer:" << endl;
                    cout << "1. Vizualizar em tela." << endl;
                    cout << "2. Gerar aquivo .TXT:" << endl;
                    cout << "3. Voltar" << endl;
                    op = getInt();
                    clearScreen();

                    if (op == 1){

                        if ( reportOfProfessor() == ""){//Caso nao tenha professores//
                            cout << "Erro: Nao foram encontrados professores no sistema."<< "\n" << endl;
                            pause();
                            return;
                        }else{
                            cout << "Relatorio dos Professores cadastrados no sistema:" << endl << endl;
                            cout << reportOfProfessor();//Imprimindo Professores//
                            pause();
                            return;
                        }         

                    }
                    if (op == 2){
                        //Salvando professores em novo arquivo truncado//
                        ofstream ofs("Professors_Report.txt", fstream::trunc);
                        ofs << reportOfProfessor();
                        ofs.close();
                        cout << "Relatorio salvo com sucesso em Professors_Report.txt\n";
                        pause();
                    }
                    if (op == 3){
                        return;
                    } 
                }
                break;
            case 3:
                while (true) {
                    clearScreen();

                    cout << "O que deseja fazer:" << endl;
                    cout << "1. Vizualizar em tela." << endl;
                    cout << "2. Gerar aquivo .TXT:" << endl;
                    cout << "3. Voltar" << endl;
                    op = getInt();
                    clearScreen();

                    if (op == 1){
                        if ( reportOfCourse() == ""){   //Caso não tenha cursos//
                            cout << "Erro: Nao foram encontrados cursos no sistema." << "\n" << endl;
                            pause();
                            return;
                        }else{
                            cout << "Relatorio dos cursos cadastrados no sistema:" << endl << endl;
                            cout << reportOfCourse(); //Imprimindo Cursos...//
                            pause();
                            return;
                        }         
                    }
                    if (op == 2){
                        //Criando arquivo truncado de cursos//
                        ofstream ofs("Course_Report.txt", fstream::trunc);
                        ofs << reportOfCourse();
                        ofs.close();
                        cout << "Relatorio salvo com sucesso em Course_Report.txt\n";
                        pause();
                    }
                    if (op == 3){
                        return;
                    }         
                }
                break;
            case 4:
                while (true) {
                    clearScreen();

                    cout << "O que deseja fazer:" << endl;
                    cout << "1. Vizualizar em tela." << endl;
                    cout << "2. Gerar aquivo .TXT:" << endl;
                    cout << "3. Voltar" << endl;
                    op = getInt();
                    clearScreen();

                    if (op == 1){
                        if (reportOfClassrom() == ""){ //Caso não tenha salas cadastradas//
                            cout << "Erro: Nao foram encontradas salas no sistema." << "\n" << endl;
                            pause();
                            return;
                        }else{
                            cout << "Relatorio das salas cadastradas no sistema:" << endl << endl;
                            cout << reportOfClassrom(); //imprimindo salas...//
                            pause();
                            return;
                        }         
                    }
                    if (op == 2){
                        //Criando arquivo truncado de salas//
                        ofstream ofs("Classroom_Report.txt", fstream::trunc);
                        ofs << reportOfClassrom();
                        ofs.close();
                        cout << "Relatório salvo com sucesso em Classroom_Report.txt\n";
                        pause();
                    }
                    if (op == 3){
                        return;
                    }  
                }
                break;
            case 5:
                return;
            default:
                clearScreen();
                cout << "Erro: Opcao Invalida. Por favor, insira uma opcao valida!.\n" << endl;
                pause();
                continue;
        }
    }
}

//=======================================================//


//=======================Metodos Auxiliares================================//
//Atualizar alunos:
void Menu::menuStudentAddCourses(shared_ptr<Student> student) {
    int courseOp;

    //Esta função diz respeito a opção de adicionar cursos a um aluno!//
    clearScreen();
    //Mini Menu para listar cursos disponiveis//
    cout << "Cursos disponiveis: " << "\n" << endl;
    for (size_t i = 0; i < _system.getCourses().size(); i++) {
        // Comparando a capacidade da sala com o tamanho do vetor de studantes do curso//
        if (_system.getCourses()[i]->getClassroom()->getCapacity() != static_cast<int>(_system.getCourses()[i]->getStudents().size())) {
            cout << i << ". " << _system.getCourses()[i]->getId() << endl;  // cursos sem professor//
        }
    }

    cout << _system.getCourses().size() << " "<< ". Sair" << endl;
    cout << "\n" << "Qual curso deseja alterar?" << endl
    << "-> ";
    courseOp = getInt();

    if (courseOp == static_cast<int>(_system.getCourses().size())) { //Op de sair//
        return;
    }

    if (courseOp < 0 || courseOp > static_cast<int>(_system.getCourses().size()) - 1) {  //Numero invalido//
        cout << "Opcao Invalida! Escolha uma das alternativas." << endl;
        pause();
        return;
    }

    int flag = _system.updateStudent(student, _system.getCourses()[courseOp]); //Filtrando erros//

    if (flag == 1) { 
        cout << "O Aluno ja aulas no dia do curso escolhido!" << endl;
        pause();
        return;
    }

    if (flag == 2) {
        cout << "O Limite de Alunos para esse curso ja foi atingido!" << endl;
        pause();
        return;
    }
    clearScreen();

    cout << "Curso adicionado com sucesso!" << endl;
}

void Menu::menuStudentDelCourses(shared_ptr<Student> student) {
    int courseOp;

    //Metodo que remove um estudante de um curso//
    cout << "Cursos disponiveis: " << endl;
    for (size_t i = 0; i < student->getCourses().size(); i++) {
        cout << i << ". " << student->getCourses()[i]->getId() << endl;  
    }
    cout << student->getCourses().size() << " "<< ". Sair" << endl;
    cout << "Qual curso deseja alterar?" << endl;
    courseOp = getInt();

    if (courseOp == static_cast<int>(student->getCourses().size())) { //Op de Sair//
        return;
    }

    if (courseOp < 0 || courseOp > static_cast<int>(student->getCourses().size()) - 1) {  // Numero invalido
        cout << "Opcao Invalida! Escolha uma das alternativas." << endl;
        pause();
        return;
    }

    _system.updateStudent(student, student->getCourses()[courseOp]); 

    cout << "Curso deletado com sucesso!" << endl;
}

//Atualizar Professores:
void Menu::menuProfessorAddCourses(shared_ptr<Professor> professor) {
    int courseOp;

    //Metodo que adiciona professores a um curso//
    cout << "Cursos disponiveis: " << endl << "\n";
    for (size_t i = 0; i < _system.getCourses().size(); i++) {
        if (_system.getCourses()[i]->getProfessor() == nullptr) {
            cout << i << ". " << _system.getCourses()[i]->getId() << endl;  // cursos sem professor
        }
    }
    cout << _system.getCourses().size() << " " << ". Sair" << endl;
    cout << "\n" << "Escolha o curso: " << endl
    << "-> ";
    courseOp = getInt();

    if (courseOp == static_cast<int>(_system.getCourses().size())) { //Op de sair//
        return;
    }

    if (courseOp < 0 || courseOp > static_cast<int>(_system.getCourses().size()) - 1) {  // Numero invalido

        cout << "Opcao Invalida! Escolha uma das alternativas." << endl;
        pause();
        return;
    }

    if (_system.getCourses()[courseOp]->getProfessor() != nullptr) {  
        cout << "Opcao Invalida! Escolha uma das alternativas." << endl;
        pause();
        return;
    }

    if (_system.updateProfessor(professor, _system.getCourses()[courseOp]) == 1) { //Se não retornar, atualiza o professor;
        cout << "O professor ja leciona no dia do curso escolhido!" << endl;
        pause();
        return;
    }
    clearScreen();

    cout << "Curso adicionado com sucesso!" << endl << "\n";
}

void Menu::menuProfessorDelCourses(shared_ptr<Professor> professor) {
    int courseOp;

    //Metodo que deleta um curso de um professor//
    cout << "Cursos disponiveis: " << endl;
    for (size_t i = 0; i < professor->getCourses().size(); i++) {
        cout << i << " " << professor->getCourses()[i]->getId() << endl; //Curso do professor
    }
    cout << "Qual curso deseja alterar?" << endl;
    courseOp = getInt();

    if (courseOp < 0 || courseOp > static_cast<int>(professor->getCourses().size()) - 1) {// Numero invalido
        cout << "Opcao Invalida! Escolha uma das alternativas." << endl;
        pause();
        return;
    }

    _system.updateProfessor(professor, professor->getCourses()[courseOp]); 

    clearScreen();
    cout << "Curso deletado com sucesso!" << endl;
}

//Atualizar Cursos:
void Menu::menuCourseAttProfessor(shared_ptr<Course> course){
    int professorOp;

    //Metodo responsavel para alterar o professor de um determinado curso//
    cout << "O professor deste curso e: " << (course->getProfessor() == nullptr ? "Nao ha professor" : course->getProfessor()->getName()) << endl;  
    cout << "Professores disponiveis: " << endl;
    //Metodo Lambda que filtra os dias dos professores de forma a não bater um com o outro//
    auto divergentDays = [=](shared_ptr<Course> curCourse) {
        auto itA = curCourse->getDays().begin();
        auto itB = course->getDays().begin();
        while (itA != curCourse->getDays().end() || itB != course->getDays().end()) {
            if (*itA && *itB) return false;
        }
        return true;
    };
    
    for (size_t i = 0; i < _system.getProfessors().size(); i++) {

        auto start = _system.getProfessors()[i]->getCourses().begin();
        auto end = _system.getProfessors()[i]->getCourses().end();
        //find_if_not_Divergent = find_if_Convergent
        if (find_if_not(start, end, divergentDays) != end) {
            cout << i << ". " << _system.getProfessors()[i]->getName() << endl; //Cursos sem professor
        }
    }
    cout << _system.getProfessors().size() << " " << ". Sair" << endl;

    cout << "Qual curso deseja alterar?" << endl;
    professorOp = getInt();

    if (professorOp == static_cast<int>(_system.getCourses().size())) { //Op de sair//
        return;
    }

    if (professorOp < 0 || professorOp > static_cast<int>(_system.getCourses().size()) - 1) {  //Numero fora do escopo//
        cout << "Opcao Invalida! Escolha uma das alternativas." << endl;
        pause();
        return;
    }

    if (_system.updateCourse(course, _system.getProfessors()[professorOp]) == 1) { //Sem retorno = atualizar o professor//

        cout << "O professor ja leciona no dia do curso escolhido!" << endl;
        pause();
        return;
    }

    cout << "Professor adicionado com sucesso!" << endl;

}

void Menu::menuCourseDelStudent(shared_ptr<Course> course){
    int studentOp;

    //Menu Responsavel por deletar um Aluno de um curso//
    cout << "Estes sao os alunos matriculados no curso: " << endl;
    // Comparando a capacidade da sala com o tamanho do vetor de studantes do curso;
    for (size_t i = 0; i < course->getStudents().size(); i++) {
        cout << i << ". " << course->getStudents()[i]->getName() << endl;  //Cursos sem professor
        
    }
    cout << course->getStudents().size() << " "<< ". Sair" << endl;
    cout << "Qual Aluno deseja remover?" << endl;
    studentOp = getInt();

    if (studentOp == static_cast<int>(course->getStudents().size())) {
        return;
    }

    if (studentOp < 0 || studentOp > static_cast<int>(course->getStudents().size()) - 1) {
        cout << "Opcao Invalida! Escolha uma das alternativas." << endl;
        pause();
        return;
    }

    _system.updateCourse(course, course->getStudents()[studentOp]);

    cout << "Aluno removido com sucesso!" << endl;
}

//Métodos para printar relatórios:
string Menu::reportOfStudent(){

    /*As funções abaixo usam a concatenação de caracteres
    "+" para imprimir o relatorio, ou passar as informações
    para um arquivo.txt*/

    string report;

    for (const auto& student : _system.getStudents()) {
        report += "\n";
        report += "Aluno:\n";
        report += "Nome: " + student->getName() + "\n";     
        report += "ID: " + student->getId() + "\n";
        report += "CPF: " + student->getCpf() + "\n";   
        report += "Telefone: " + student->getTel() + "\n";
        report += "Matriculado(a) nos cursos: \n";
        for (const auto& course : student->getCourses()) {
            report += " - " + course->getName() + "\n";
        }
        report += "\n";
        report += "======================================";
        report += "\n";
    }
    return report;

    // report += "ID\t\tNome\t\t\t\tCPF\t\tTel\t\tCursos\n";
    // report += "----------------------------------------------------------------------------\n";
    // for (const auto& student : _system.getStudents()) {
    //     report += student->getId() + "\t";
    //     report += student->getName() + "\t\t";
    //     report += student->getCpf() + "\t";
    //     report += student->getTel() + "\t";

    //     for (const auto& course : student->getCourses()) {
    //         report += course->getName() + ", ";
    //     }
    //     report.erase(report.length() - 2, 2); // remove the last ", "
    //     report += "\n";
    // }
    // return report;

    // string report = "";

}

string Menu::reportOfProfessor(){

    string report = "";
   
    for (const auto& professor : _system.getProfessors()) {
        report += "Professor:\n";
        report += "Nome: " + professor->getName() + "\n";
        report += "CPF: " + professor->getCpf() + "\n";
        report += "Telefone: " + professor->getTel() + "\n";
        report += "Responsavel pelos cursos: \n";
        for (const auto& course : professor->getCourses()) {
            report += " - " + course->getName() + "\n";
        }
        report += "\n";
        report += "======================================";
        report += "\n";
    }
    return report;
    
}

string Menu::reportOfCourse(){

    vector<string> daysMap{"Segunda", "Terca", "Quarta", "Quinta", "Sexta"};
    string report = "";
    
    for (const auto& course : _system.getCourses()) {

        report += "\n";
        report += "Curso:\n";
        report += "ID: " + course->getId() + "\n";
        report += "Nome: " + course->getName() + "\n";
        report += "Alocado na sala: " + course->getClassroom()->getId() + "\n";
        if (course->getProfessor() != nullptr){
            report += "Professor responsavel: " + course->getProfessor()->getName() + "\n";
        
        }
        report += "Acontece nos dias: \n" ;
        for (int i = 0; i < 5; i++){
            if (course->getDays()[i]){
                report += " - " + daysMap[i] + "\n";
            }
        }

        report += "\n";
        report += "======================================";
        report += "\n";
    }
    return report;
    
}

string Menu::reportOfClassrom(){

    vector<string> daysMap{"Segunda", "Terca", "Quarta", "Quinta", "Sexta"};
    string report = "";
    for (const auto& classroom : _system.getClassrooms()) {
        report += "\n";
        report += "Sala: \n";
        report += "ID: " + classroom->getId() + "\n";
        report += "Cursos: \n";
        for (const auto& course : classroom->getCourses()) {
            report += " - " + course->getName() + "\n";
        }
        report += "Dias reservados: \n";
        for (auto course : classroom->getCourses()) {	
            for (int i = 0; i < 5; i++){
                if (course->getDays()[i]){
                    report += " - " + daysMap[i] + "\n";
                }
            }   
        }
        report += "Dias livres: \n";
        for (int i = 0; i < 5; i++){
            bool dayIsFree = true; // dia libre começa como true
            for (auto course : classroom->getCourses()){
                if (course->getDays()[i]){
                    dayIsFree = false; //se tiver aulas na posição i dayIsFree é marcado como false;
                    break;
                }
            }
            if (dayIsFree){
                report += " - " + daysMap[i] + "\n";
            }
        }
        report += "\n";
        report += "======================================";
        report += "\n";
    }
    return report;
    
}

//Método para carregar informação de arquivos:
void Menu::loadData(string filename){

    ifstream file(filename);
    shared_ptr<Course> course;
    shared_ptr<Student> student;
    shared_ptr<Professor> professor;
    shared_ptr<Classroom> classroom;
    string name, cpf, tel, id, login, senha;
    string type, line, courseId;;
    istringstream iss(line);
    int numCourses, capacity;
    

    /*Neste metodo, eu criei uma lógica para ler os arquivos
    a logica é a seguinte: eu pego uma linha do arquivo e comparo
    ela com uma string, se for "classrom" por exemplo, eu pego as proximas
    linhas com getline e atribuo elas a uma variavel, como nome ou cpf, e por fim
    mando elas para um setClassrom();*/


    if (!file.is_open()){
        cout << "O Arquivo nao pode ser aberto." << endl;
    }

    // Começar leitura
    while (file.is_open()){
        getline(file, type);

        if (type == "classroom"){
            cout << endl <<"NOVA SALA:" << endl << endl;
            getline(file, id);
            cout << "ID: " << id << endl;
            getline(file, line);
            stringstream(line) >> capacity;
            cout << "Capacidade: " << capacity << endl;

            //Usando Try Catch para filtrar o retorno do método;
            try {
                _system.setClassroom(id, capacity);
                cout << "A Sala: " << "\"" << id << "\"" << ", foi criada com sucesso!" << endl;
            } catch (int e) {
                if (e == 1){
                    cout << "Erro: Capacidade invalida. Digite um inteiro positivo." << endl;
                }
                if (e == 2){
                    cout << "Erro: A Sala: " << "\"" << id << "\"" << " ja existe!" << endl;
                }
            }
            cout << "================================"<< endl;
        }
        else if (type == "course"){
            vector<bool> days(5, false);
            cout << endl << "NOVO CURSO:" << endl << endl;
            getline(file, id);
            cout << "ID: " << id << endl;
            getline(file, name);
            cout << "Nome: " << name << endl;
            getline(file, line);

            //Pegando um caractere e comparando ele com 1 ou 0//
            //Posteriormente passo true ou false para o vector de Days//
            for (int i = 0; i < 5; i++) {
                char c = line[i];
                if (c == '1') {
                    days[i] = true;
                } else if (c == '0') {
                    days[i] = false;
                } else {
                    cout << "Erro: Caractere inválido na linha de dias da semana." << endl;
                }
            }

            try{
                auto course = _system.setCourse(id, name, days);
                cout << "O Curso " << "\"" <<  course->getName() << "\"" << ", foi criado com sucesso!" << endl;
            }
            catch (int e){
                if (e == 1){
                    cout << "Erro: O Curso: " << "\"" << name << "\"" << " já existe." << endl;
                }
                else if (e == 2){
                    cout << "Erro: Nao existe sala disponivel para o curso: " << "\"" << name << "\"" << "." << endl;
                }
            }

            cout << "================================"<< endl;

        }else if (type == "professor"){
            cout << endl << "NOVO PROFESSOR:" << endl << endl;
            getline(file, name);
            cout << "Nome: " << name << endl;
            getline(file, cpf);
            cout << "CPF: " << cpf << endl;
            getline(file, tel);
            cout << "Telefone: " << tel << endl;

            try{
                professor = _system.setProfessor(name, cpf, tel);
                cout << "O Professor: " << "\"" << name << "\"" << ", foi criado com sucesso." << endl;
            }
            catch(int){
                cout << "Error: O Professor: " << "\"" << name << "\"" <<", ja existe!" << endl;
            }
            getline(file, line);
            stringstream(line) >> numCourses;
            cout << "Responsavel por: " << numCourses << " cursos." << endl;

            //La linha acima pego o numero de cursos que ele leciona//
            //e os adiciono do for abaixo.//
            for (int i = 0; i < numCourses; i++){
                try{
                    getline(file, courseId);
                    cout << "ID do curso: " << courseId << endl;
                    course = _system.findCourse(courseId);
                    _system.updateProfessor(professor, course);
                    cout << "O Curso: " << courseId << " foi adicionado ao professor: " << name << endl;
                }
                catch (int){
                    cout << "Erro: O Professor: " << "\"" <<name << "\"" <<"ja leciona nesse dia" << endl;
                }
            }
            cout << "================================"<< endl;
        }
        else if (type == "student"){
            cout << endl << "NOVO ALUNO:" << endl << endl;
            getline(file, name);
            cout << "Nome: " << name << endl;
            getline(file, cpf);
            cout << "CPF: " << cpf << endl;
            getline(file, tel);
            cout << "Telefone: " << tel << endl;
            getline(file, id);
            cout << "ID: " << id << endl;

            try{
                student = _system.setStudent(name, cpf, tel, id);
            }
            catch(int){
                cout << "O Aluno: "<< "\"" << name << "\"" << " ja existe" << endl;
            }
            
            getline(file, line);
            stringstream(line) >> numCourses;
            cout << "Inscrito em: " << numCourses << " cursos." << endl;

            for (int i = 0; i < numCourses; i++){
                try{
                    getline(file, courseId);
                    cout << "ID do curso: " << courseId << endl;
                    course = _system.findCourse(courseId);
                    _system.updateStudent(student, course);
                    cout << "O Curso " << "\"" << courseId << "\"" << ", foi adicionado ao Aluno: " << "\"" << name << "\"" << endl;
                }
                catch (int){
                    cout << "O Aluno: " << "\"" << name << "\"" << ", ja tem aulas nesse dia" << endl;
                }
            }
            cout << "================================"<< endl;
        }

        if (file.eof()){
            cout << endl << "#### Fim do Arquivo. Nao existem mais informacoes a serem adicionadas! ####" << endl;
            file.close();
            break;
        }
    }
}

//===============================================================//
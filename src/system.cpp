#include "system.h"

auto System::getDivergentDays(shared_ptr<Course> newCourse){

    //Função para filtrar os dias, para tratar e não ocorrer conflitos;
    return [=](shared_ptr<Course> course){
        for (size_t i = 0; i < 5; i++){
            if (course->getDays()[i] && newCourse->getDays()[i])
                return false;
        }
        return true;
    };
}

/* -------------------------------------------------------------------------- */
/*                                   Create                                   */
/* -------------------------------------------------------------------------- */
shared_ptr<Manager> System::setManager(string name, string cpf, string tel, string login, string senha) {
    shared_ptr<Manager> newManager = make_shared<Manager>(name, cpf, tel, login, senha);

    for (auto manager : managers) {
        if (*manager == *newManager) throw 1;
    }

    managers.push_back(newManager);
    return newManager;
}

shared_ptr<Classroom> System::setClassroom(string id, int capacity) {
    shared_ptr<Classroom> newClassroom = make_shared<Classroom>(id, capacity);

    if (capacity <= 0) throw 1;

    for (auto classroom : classrooms) {
        if (*classroom == *newClassroom) throw 2;
    }

    classrooms.push_back(newClassroom);

    return newClassroom;
}

shared_ptr<Course> System::setCourse(string id, string name, vector<bool> days) {
    shared_ptr<Course> newCourse = make_shared<Course>(id, name, days);

    for (auto course : courses) {
        if (*course == *newCourse) throw 1; //Ecxepction: Curso ja existente//
    }

    auto divergentDays = getDivergentDays(newCourse);

    // Acha uma sala com dias livres:
    auto availableClassroom = [&divergentDays](shared_ptr<Classroom> classroom) {
        auto it = find_if_not(classroom->getCourses().begin(), classroom->getCourses().end(), divergentDays);
        return it == classroom->getCourses().end() ? true : false;
    };

    auto classroomIt = find_if(classrooms.begin(), classrooms.end(), availableClassroom);
    if (classroomIt == classrooms.end()) throw 2;
    // =================================================================

    courses.push_back(newCourse);
    newCourse->setClassroom(*classroomIt);
    (**classroomIt).pushCourse(newCourse);
    return newCourse;
}

shared_ptr<Student> System::setStudent(string name, string cpf, string tel, string id) {
    shared_ptr<Student> newStudent = make_shared<Student>(name, cpf, tel, id);

    for (auto student : students) {
        if (*student == *newStudent) throw 1;
    }

    students.push_back(newStudent);
    return newStudent;
}

shared_ptr<Professor> System::setProfessor(string name, string cpf, string tel) {
    shared_ptr<Professor> newProfessor = make_shared<Professor>(name, cpf, tel);

    for (auto professor : professors) {
        if ((*professor) == (*newProfessor)) throw 1;
    }

    professors.push_back(newProfessor);

    return newProfessor;
}

/* -------------------------------------------------------------------------- */
/*                                    Read                                    */
/* -------------------------------------------------------------------------- */

vector<shared_ptr<Manager>>& System::getManagers() {
    return managers;
}

vector<shared_ptr<Classroom>>& System::getClassrooms(){
    return classrooms;
}

vector<shared_ptr<Professor>>& System::getProfessors() {
    return professors;
}

vector<shared_ptr<Course>>& System::getCourses(){
    return courses;
}

vector<shared_ptr<Student>>& System::getStudents(){
    return students;
}

shared_ptr<Student> System::findStudent(string id) {

    //Metodo que pesquisa por um aluno atraves do ID//
    for (auto student : students) {
        if (id == student->getId()) {
            return student;
        }
    }
    throw 1;
}

shared_ptr<Professor> System::findProfessor(string cpf) {
    //Metodo que pesquisa por um Professor atraves do ID//
    for (auto professor : professors) {
        if (cpf == professor->getCpf()) {
            return professor;
        }
    }
    throw 1;
}

shared_ptr<Course> System::findCourse(string id) {
    for (auto course : courses) {
        if (id == course->getId()) {
            return course;
        }
    }

    throw 1;
}

shared_ptr<Classroom> System::findClassroom(string id) {
    for (auto classroom : classrooms) {
        if (id == classroom->getId()) {
            return classroom;
        }
    }

    throw 1;
}

/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */

int System::updateProfessor(shared_ptr<Professor> professor, string tel) {
    professor->setTel(tel);
    return 0;
}

int System::updateProfessor(shared_ptr<Professor> professor, shared_ptr<Course> newCourse) {
    auto divergentDays = getDivergentDays(newCourse);

    // Verifica se o perofessor ja leciona em um dos dias:
    auto courseIt = find_if_not(professor->getCourses().begin(), professor->getCourses().end(), divergentDays);
    if (courseIt != professor->getCourses().end()) return 1;
    // =================================================================//

    courseIt = find(professor->getCourses().begin(), professor->getCourses().end(), newCourse);
    if (courseIt != professor->getCourses().end()) {
        professor->getCourses().erase(courseIt);
        newCourse->delProfessor();
        return 0;
    }

    newCourse->setProfessor(professor); // adicionando curso
    professor->pushCourse(newCourse);

    return 0;
}

int System::updateStudent(shared_ptr<Student> student, string tel) {
    student->setTel(tel);
    return 0;
}

int System::updateStudent(shared_ptr<Student> student, shared_ptr<Course> newCourse) {
    auto divergentDays = getDivergentDays(newCourse);

    // Verificando se o Aluno ja tem aulas naquele dia:
    auto courseIt = find_if_not(student->getCourses().begin(), student->getCourses().end(), divergentDays);
    if (courseIt != student->getCourses().end())
        return 1;  // Ja tem classes
    // =================================================================

    courseIt = find(student->getCourses().begin(), student->getCourses().end(), newCourse);  // curso ja existia
    if (courseIt != student->getCourses().end()) {                                           // deletar curso
        student->delCourse(newCourse);
        newCourse->delStudent(student);
        return 0;
    }

    // Comparar numero de estudantes com a capacidade da sala
    // =================================================================
    if (static_cast<int>(newCourse->getStudents().size()) == newCourse->getClassroom()->getCapacity()) {
        return 2;  // limite atingido.
    }
    // =================================================================

    newCourse->pushStudent(student);
    student->pushCourse(newCourse);

    return 0;
}

int System::updateCourse(shared_ptr<Course> course, string name){

    course->setName(name);
    return 0;
}

int System::updateCourse(shared_ptr<Course> course, shared_ptr<Professor> professor){

    return updateProfessor(professor, course);
}

int System::updateCourse(shared_ptr<Course> course, shared_ptr<Student> student){

    return updateStudent(student, course);
}


/* -------------------------------------------------------------------------- */
/*                                   Delete                                   */
/* -------------------------------------------------------------------------- */

int System::deleteIntance(shared_ptr<Professor> professor) {
    //Remove um professor dos cursos ministrados por ele//
    for (auto course : professor->getCourses()) {
        course->delProfessor();
    }
    professors.erase(remove(professors.begin(), professors.end(), professor), professors.end());
    return 0;
}

int System::deleteIntance(shared_ptr<Student> student) {
    //Remove um estudante de um curso//
    for (auto course : student->getCourses()) {
        course->delStudent(student);
    }
    students.erase(remove(students.begin(), students.end(), student), students.end());

    return 0;
}

int System::deleteIntance(shared_ptr<Course> course) {
    //Remove um curso de uma determinada sala//
    course->getClassroom()->delCourse(course);
    // Removendo um curso de um determinado professor//
    if (course->getProfessor() != nullptr) {
        course->getProfessor()->delCourse(course);
    }
    
    
    // Removendo estudantes do curso//
    for (auto student : course->getStudents()) {
        student->delCourse(course);
    }

    courses.erase(remove(courses.begin(), courses.end(), course), courses.end());

    return 0;
}

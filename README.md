# Sistema de Gestão de Salas de Aula em C++

Este projeto foi desenvolvido como parte da disciplina de Programação Orientada a Objetos lecionada na Universidade Federal de Ouro Preto - UFOP. O objetivo do projeto foi implementar um sistema de gestão de salas de aula em C++, seguindo conceitos de programação orientada a objetos.

O sistema permite o cadastro de alunos, professores, gestores, cursos e salas de aula. Para cadastrar um aluno, professor ou gestor no sistema, são solicitadas informações como nome, telefone e CPF. Os alunos também devem informar sobre matrícula e curso, enquanto os gestores devem ter informações de login e senha de acesso. Já os professores devem informar sobre o curso que irão ministrar. Cada curso só pode ser designado para um professor.

Os gestores têm acesso ao sistema para inserir, visualizar, atualizar e excluir dados. Para acessar o sistema, eles devem fazer login com um nome de usuário e senha que foram definidos com o padrão de `admin`. Alunos e professores podem acessar o sistema sem login e senha, mas só podem visualizar informações e não têm acesso a dados pessoais. Por exemplo, os professores podem visualizar a sala reservada para o curso, e os alunos matriculados. Os alunos podem visualizar o curso que ocorrerá em cada sala e o professor que ministrará o curso.

Com a implementação do sistema, torna-se possível gerenciar de forma mais eficiente a alocação das salas de aula, bem como o controle das informações de alunos, professores e gestores. Para desenvolver a aplicação, foram utilizados conceitos de programação orientada a objetos, tais como a definição de classes e objetos, encapsulamento de informações, herança e polimorfismo.

## Como Executar

Para executar o sistema, é necessário compilar o programa utilizando o Makefile presente no repositório. Para isso, basta executar o comando `make` no terminal a partir do diretório do projeto. Após a compilação, execute o arquivo `main.cpp` para iniciar o sistema.

**Caso haja alguma dependência faltando, é necessário instalar antes de compilar o programa.**

É importante destacar que o programa foi desenvolvido e testado em um ambiente Windows, portanto, o processo de compilação e execução pode variar em outros sistemas operacionais.

```
make
./main
```

Representação simples dos menus:
![Menu Image](https://i.imgur.com/lBqzxZE.png "Classroom Manager CRUD")

# Funcionalidades

O sistema possui diversas funcionalidades que permitem uma gestão completa das salas de aula. Dentre elas, destacam-se:

## Cadastro de Dados

O sistema permite o cadastro de diferentes tipos de dados, como alunos, professores, gestores, cursos e salas de aula. Cada um desses cadastros é realizado de forma independente e requer informações específicas.

## Consulta de Dados

É possível visualizar os dados cadastrados em todas as categorias. Os gestores possuem acesso total às informações, enquanto os alunos e professores possuem acesso apenas a algumas informações limitadas.

## Edição de Dados

Caso seja necessário atualizar alguma informação, o sistema permite a edição dos dados cadastrados. Para tanto, é necessário possuir acesso de gestor e fazer login no sistema.

## Exclusão de Dados

Caso seja necessário remover algum dado cadastrado, o sistema permite a exclusão dos mesmos. Apenas gestores têm permissão para realizar esta ação.

Em resumo, o sistema permite uma gestão completa das salas de aula e de seus integrantes, permitindo que gestores, professores e alunos possam acompanhar informações importantes relacionadas aos cursos e salas de aula.

    - Gerenciamento completo das salas de aula e seus integrantes;
    
    - Cadastro de alunos, professores, gestores, cursos e salas de aula;
    
    - Consulta de dados cadastrados;
    
    - Edição de dados cadastrados;
    
    - Exclusão de dados cadastrados;
    
    - Acompanhamento de informações importantes pelos gestores, professores e alunos, relacionadas aos cursos e salas de aula.


## Licença

Este projeto é licenciado sob a licença MIT - veja o arquivo LICENSE para mais detalhes.
[MIT License](./LICENSE)

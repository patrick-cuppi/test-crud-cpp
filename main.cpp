#include "Database.h"
#include <iostream>

void menu()
{
    Database db;
    int option;
    do
    {
        std::cout << "\n1. Criar Pessoa";
        std::cout << "\n2. Listar Pessoas";
        std::cout << "\n3. Atualizar Pessoa";
        std::cout << "\n4. Deletar Pessoa";
        std::cout << "\n5. Sair";
        std::cout << "\nEscolha uma opcao: ";
        std::cin >> option;

        if (option == 1)
        {
            std::string name, email, password;
            std::cout << "Nome: ";
            std::cin >> name;
            std::cout << "Email: ";
            std::cin >> email;
            std::cout << "Senha: ";
            std::cin >> password;
            db.createPerson(name, email, password);
        }
        else if (option == 2)
        {
            db.readPeople();
        }
        else if (option == 3)
        {
            int id;
            std::string name, email, password;
            std::cout << "ID da pessoa para atualizar: ";
            std::cin >> id;
            std::cout << "Novo Nome: ";
            std::cin >> name;
            std::cout << "Novo Email: ";
            std::cin >> email;
            std::cout << "Nova Senha: ";
            std::cin >> password;
            db.updatePerson(id, name, email, password);
        }
        else if (option == 4)
        {
            int id;
            std::cout << "ID da pessoa para deletar: ";
            std::cin >> id;
            db.deletePerson(id);
        }
    } while (option != 5);
}

int main()
{
    menu();
    return 0;
}
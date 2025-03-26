#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "Person.h"
#include <pqxx/pqxx>
#include <random>

class Database
{
private:
    pqxx::connection conn;
    int generateRandomId();

public:
    Database();
    void createPerson(std::string name, std::string email, std::string password);
    void readPeople();
    void updatePerson(int id, std::string newName, std::string newEmail, std::string newPassword);
    void deletePerson(int id);
};

#endif
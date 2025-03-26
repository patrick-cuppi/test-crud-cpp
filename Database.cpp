#include "Database.h"
#include <iostream>

Database::Database() : conn("dbname=test user=postgres password=postgres host=localhost port=5432")
{
    pqxx::work W(conn);
    W.exec("CREATE TABLE IF NOT EXISTS people (id SERIAL PRIMARY KEY, name TEXT, email TEXT UNIQUE, password TEXT);");
    W.commit();
}

int Database::generateRandomId()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1000, 9999);
    return distrib(gen);
}

void Database::createPerson(std::string name, std::string email, std::string password)
{
    int id = generateRandomId();
    pqxx::work W(conn);
    W.exec_params("INSERT INTO people (id, name, email, password) VALUES ($1, $2, $3, $4);", id, name, email, password);
    W.commit();
}

void Database::readPeople()
{
    pqxx::nontransaction N(conn);
    pqxx::result R = N.exec("SELECT id, name, email FROM people;");
    for (auto row : R)
    {
        std::cout << "ID: " << row["id"].as<int>() << ", Nome: " << row["name"].as<std::string>()
                  << ", Email: " << row["email"].as<std::string>() << std::endl;
    }
}

void Database::updatePerson(int id, std::string newName, std::string newEmail, std::string newPassword)
{
    pqxx::work W(conn);
    W.exec_params("UPDATE people SET name = $1, email = $2, password = $3 WHERE id = $4;", newName, newEmail, newPassword, id);
    W.commit();
}

void Database::deletePerson(int id)
{
    pqxx::work W(conn);
    W.exec_params("DELETE FROM people WHERE id = $1;", id);
    W.commit();
}
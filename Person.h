#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
public:
    int id;
    std::string name;
    std::string email;
    std::string password;

    Person(int id, std::string name, std::string email, std::string password);
};

#endif
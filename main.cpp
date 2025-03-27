#include "Database.h"
#include <crow.h>

int main()
{
    Database db;
    crow::SimpleApp app;

    CROW_ROUTE(app, "/people").methods(crow::HTTPMethod::Get)([&db]()
                                                              {
        std::ostringstream os;
        pqxx::nontransaction N(db.conn);
        pqxx::result R = N.exec("SELECT id, name, email FROM people;");
        crow::json::wvalue people;
        for (size_t i = 0; i < R.size(); ++i) {
            people[i]["id"] = R[i]["id"].as<int>();
            people[i]["name"] = R[i]["name"].as<std::string>();
            people[i]["email"] = R[i]["email"].as<std::string>();
        }
        return crow::response(people); });

    CROW_ROUTE(app, "/person").methods(crow::HTTPMethod::Post)([&db](const crow::request &req)
                                                               {
        auto data = crow::json::load(req.body);
        if (!data)
            return crow::response(400, "Invalid JSON");
        db.createPerson(data["name"].s(), data["email"].s(), data["password"].s());
        return crow::response(201, "Created"); });

    CROW_ROUTE(app, "/person/<int>").methods(crow::HTTPMethod::Put)([&db](int id, const crow::request &req)
                                                                    {
        auto data = crow::json::load(req.body);
        if (!data)
            return crow::response(400, "Invalid JSON");
        db.updatePerson(id, data["name"].s(), data["email"].s(), data["password"].s());
        return crow::response(200, "Updated"); });

    CROW_ROUTE(app, "/person/<int>").methods(crow::HTTPMethod::Delete)([&db](int id)
                                                                       {
        db.deletePerson(id);
        return crow::response(200, "Deleted"); });

    app.port(8080).multithreaded().run();
    return 0;
}
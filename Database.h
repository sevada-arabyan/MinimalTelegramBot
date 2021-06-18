#pragma once

#include <string>
#include <pqxx/pqxx>
#include "Task.h"
#include "User.h"

class Database {
public:
    Database(const std::string& db_name, const std::string& db_use, const std::string& db_pass);

    void AddUser(uint64_t user_id);
    // Returns new task id
    uint64_t AddTask(uint64_t user_id, const std::string& task_description);
    void ChangeTaskDescription(uint64_t task_id, const std::string& new_description);
    void ChangeTaskCompletionStatus(uint64_t task_id);
    //Returns User with all his tasks
    User GetUserWithTasks(uint64_t user_id);
    void RemoveTask(uint64_t task_id);

private:
    pqxx::connection conn;
};

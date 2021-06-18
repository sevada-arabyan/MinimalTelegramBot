#include "Database.h"

Database::Database(const std::string& db_name, const std::string& db_user, const std::string& db_pass) : conn("postgresql://" + db_user + ":" + db_pass + "@localhost/" + db_name) {}

void Database::AddUser(uint64_t user_id) {
    pqxx::work txn(conn);
    //That's bad and not insecure, but we'll return to it later
    txn.exec("INSERT INTO bot_users VALUES (" + std::to_string(user_id) + ")");
    //And we don't handle exceptional situations yet
    txn.commit();
}

User Database::GetUserWithTasks(uint64_t user_id) {
    pqxx::work txn(conn);
    //That's bad and not insecure, but we'll return to it later
    pqxx::result tasks = txn.exec(R"SQL(
        SELECT tasks.task_id, tasks.task_description, tasks.completed
        FROM tasks NATURAL INNER JOIN user_tasks NATURAL INNER JOIN bot_users 
        WHERE user_id = )SQL" + std::to_string(user_id) + ";");
    //And we don't handle exceptional situations yet
    User user(std::to_string(user_id));
    for (const auto& task: tasks) {
        uint64_t task_id = task[0].as<uint64_t>();
        std::string task_description = task[1].as<std::string>();
        bool completed = task[2].as<bool>();

        user.AddTask(std::to_string(task_id), std::move(task_description)); //Not exactly sure move will work there
        if (completed) { // That's ugly, because our model wasn't prepared for such usage
            user.ChangeTaskCompletionStatus(std::to_string(task_id));
        }
    }
    return user;
}

// Rest is up to you ;)
uint64_t Database::AddTask(uint64_t user_id, const std::string& task_description) {
	pqxx::work txn(conn);

	//txn.exec("INSERT INTO bot_users VALUES (" + std::to_string(user_id) + ")");
	txn.exec("WITH new_task_id AS (INSERT INTO tasks (task_description) VALUES ('" + task_description + "') RETURNING task_id)"
	"INSERT INTO user_tasks SELECT " + std::to_string(user_id) + ", task_id FROM new_task_id;");
	txn.commit();
    	return 0;
}

void Database::ChangeTaskDescription(uint64_t task_id, const std::string& new_description) {
	pqxx::work txn(conn);
	txn.exec("UPDATE tasks SET task_description = '" + new_description + "' WHERE task_id = " + std::to_string(task_id) + ";");
	txn.commit();
	return;
}

void Database::ChangeTaskCompletionStatus(uint64_t task_id) {
	pqxx::work txn(conn);
	txn.exec("UPDATE tasks SET completed = TRUE WHERE task_id = " + std::to_string(task_id) + ";");
	txn.commit();
    	return;
}

void Database::RemoveTask(uint64_t task_id) {
	pqxx::work txn(conn);
	txn.exec("DELETE FROM user_tasks WHERE task_id = " + std::to_string(task_id) + ";");
	txn.exec("DELETE FROM tasks WHERE task_id = " + std::to_string(task_id) + ";");
	txn.commit();
    	return;
}

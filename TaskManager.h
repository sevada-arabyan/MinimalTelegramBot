#pragma once
#include <string>

#include "User.h"

class TaskManager
{
	Vector<User> m_user{};
public:
	TaskManager();
	TaskManager(const Vector<User>& users);
		
	~TaskManager();

	void AddUser(const std::string& user_id);

	User* GetUser(const std::string& user_id);


	const User* GetUser(const std::string& user_id) const;

    // TODO make task_id out parameter
	// bool AddTask(const std::string& user_id, const std::string& task_description, std::string& task_id);
	bool AddTask(const std::string& user_id, const std::string& task_id, const std::string& task_description);

	bool ChangeTaskDescription(const std::string& user_id, const std::string& task_id, const std::string& task_description);

	bool MarkTaskDone(const std::string& user_id, const std::string& task_id);
	Task* GetUserTask(const std::string& user_id, const std::string& task_id);
	const std::string& GetTaskDescription(const std::string& user_id, const std::string& task_id);

	bool ChangeTaskCompletionStatus(const std::string& user_id, const std::string& task_id);
	bool GetTaskCompletionStatus(const std::string& user_id, const std::string& task_id, bool& is_successful);
	bool RemoveTask(const std::string& user_id, const std::string& task_id, bool& user_found);
	void PrintUsers(std::ostream& os);

	bool PrintUserTasks(std::ostream& os, const std::string& user_id);
	const Vector<Task>* GetUserTasks(const std::string& user_id);
};

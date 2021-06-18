#pragma once
#include <iostream>
#include "Task.h"
#include "Vector.h"
#include <string>

class User
{
	std::string m_id{};
	Vector<Task> m_tasks{};
public:
	User() = default;;
	User(const std::string& user_id);

	~User();

	const std::string& GetUserID() const;

	void AddTask(const std::string& task_id, const std::string& task_description);

	bool RemoveTask(const std::string& task_id);

	Task* GetTask(const std::string& task_id);

	bool ChangeTaskDescription(const std::string& task_id, const std::string& task_description);

	bool ChangeTaskCompletionStatus(const std::string& task_id);

	void PrintTasks(std::ostream& os) const;

	const Vector<Task>* GetTaskVector() const;
};

#pragma once
//#include <iostream>
#include <string>

class Task
{
	std::string m_task_id{};
	std::string m_description{};
	bool m_completed{ 0 };
public:
	Task();
	Task(const std::string& id);
	Task(const std::string& id, const std::string& description, const bool is_completed);
	~Task();

	bool operator==(const Task& tsk);
	bool operator==(const std::string& id);
	void SetTaskDescription(const std::string& description);
	void ChangeTaskCompletionStatus();
	bool IsTaskCompleted() const;
	const std::string& GetTaskID() const;
	const std::string& GetTaskDescription() const;
};

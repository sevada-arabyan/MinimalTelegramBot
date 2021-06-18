#include <iostream>
#include "Vector.h"
#include <string>
#include "User.h"

User::User(const std::string& user_id)
{
	m_id = user_id;
}

User::~User(){};

const std::string& User::GetUserID() const
{
	return m_id;
}

void User::AddTask(const std::string& task_id, const std::string& task_description)
{
	m_tasks.push_back(Task{ task_id, task_description, 0 });
}

bool User::RemoveTask(const std::string& task_id)
{
	return m_tasks.remove(Task{ task_id });
}

Task* User::GetTask(const std::string& task_id)
{
	for (int i{ 0 }; i < m_tasks.size(); ++i)
	{
		if (m_tasks[i].GetTaskID() == task_id)
		{
			return &m_tasks[i];
		}
	}
	return nullptr;
}

bool User::ChangeTaskDescription(const std::string& task_id, const std::string& task_description)
{
	if(Task* task = GetTask(task_id))
	{
		task->SetTaskDescription(task_description);
		return true;
	}
	else
	{
		return false;
	}
}

bool User::ChangeTaskCompletionStatus(const std::string& task_id)
{
	if(Task* task = GetTask(task_id))
	{
		GetTask(task_id)->ChangeTaskCompletionStatus();
		return true;
	}
	else
	{
		return false;
	}
}

void User::PrintTasks(std::ostream& os) const
{
	for (size_t i{ 0 }; i<m_tasks.size(); ++i)
	{
		os << m_tasks[i].GetTaskDescription() << ' ';
	}
	os << std::endl;
}

const Vector<Task>* User::GetTaskVector() const
{
	return &m_tasks;
}

#include <string>
#include "TaskManager.h"
//#include "User.h"
//#include "User.cpp"

TaskManager::TaskManager() = default;
TaskManager::TaskManager(const Vector<User>& users) :m_user{ users }{};
TaskManager::~TaskManager(){};

void TaskManager::AddUser(const std::string& user_id)
{
	m_user.push_back(User{ user_id });
}

User* TaskManager::GetUser(const std::string& user_id)
{
	for (size_t i{ 0 }; i < m_user.size(); ++i)
	{
		if (m_user[i].GetUserID() == user_id)
		{
			return &m_user[i];
		}
	}
//	std::cerr << "The user not found!" << std::endl;
	return nullptr;
}

const User* TaskManager::GetUser(const std::string& user_id) const
{
	for (size_t i{ 0 }; i < m_user.size(); ++i)
	{
		if (m_user[i].GetUserID() == user_id)
		{
			return &m_user[i];
		}
	}
	//std::cerr << "The user not found!" << std::endl;
	return nullptr;
}

bool TaskManager::AddTask(const std::string& user_id, const std::string& task_id, const std::string& task_description)
{
	if(User* user = GetUser(user_id))
	{
		user->AddTask(task_id, task_description);
		return true;
	}
	else
	{
		return false;
	}
}

bool TaskManager::ChangeTaskDescription(const std::string& user_id, const std::string& task_id, const std::string& task_description)
{
	if(User* user = GetUser(user_id))
	{
		user->ChangeTaskDescription(task_id, task_description);
		return true;
	}
	else
	{
		return false;
	}
}

bool TaskManager::MarkTaskDone(const std::string& user_id, const std::string& task_id)
{
	if(User* user = GetUser(user_id))
	{
		user->ChangeTaskCompletionStatus(task_id);
		return true;
	}
	else
	{
		return false;
	}
}

Task* TaskManager::GetUserTask(const std::string& user_id, const std::string& task_id)
{
	if(User* user = GetUser(user_id))
	{
		return user->GetTask(task_id);
	}
	else
	{
		return nullptr;
	}
//	*(GetUser(user_id)->GetTask(task_id));
}

void TaskManager::PrintUsers(std::ostream& os)
{
	for (size_t i{ 0 }; i < m_user.size(); ++i)
	{
		os << m_user[i].GetUserID() << ' ';
	}
	os << std::endl;
}

bool TaskManager::PrintUserTasks(std::ostream& os, const std::string& user_id)
{
	if(User* user = GetUser(user_id))
	{
		user->PrintTasks(std::cout);
		return true;
	}
	else
	{
		return false;
	}
}
const std::string& TaskManager::GetTaskDescription(const std::string& user_id, const std::string& task_id)
{

	if(User* user = GetUser(user_id))
		if(Task* task = user->GetTask(task_id))
			return task->GetTaskDescription();
	static const std::string not_found{""}; 
	return not_found;
}
bool TaskManager::ChangeTaskCompletionStatus(const std::string& user_id, const std::string& task_id)
{
	if(User* user = GetUser(user_id))
		if(Task* task = user->GetTask(task_id))
		{
			task->ChangeTaskCompletionStatus();
			return true;
		}
	return false;
}
bool TaskManager::GetTaskCompletionStatus(const std::string& user_id, const std::string& task_id, bool& is_successful)
{
	if(User* user = GetUser(user_id))
		if(Task* task = user->GetTask(task_id))
		{
			is_successful = true;
			return task->IsTaskCompleted();
		}
	is_successful = false;
	return false;
		
}
bool TaskManager::RemoveTask(const std::string& user_id, const std::string& task_id, bool& user_found)
{
	if(User* user = GetUser(user_id))
	{
		user_found = true;
		return user->RemoveTask(task_id);
	}
	user_found = false;
	return false;
}

const Vector<Task>* TaskManager::GetUserTasks(const std::string& user_id)
{
	if(User* user = GetUser(user_id))
        {
                return user->GetTaskVector();
        }
        else
	{
		return nullptr;
	}

}

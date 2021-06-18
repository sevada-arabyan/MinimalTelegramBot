#include "Task.h"
#include <string>

Task::Task() = default;
Task::Task(const std::string& id) : m_task_id{ id }, m_description{ "" }, m_completed{ false }{}
Task::Task(const std::string& id, const std::string& description, const bool is_completed) : m_task_id{ id }, m_description{ description }, m_completed{ is_completed }{}
Task::~Task(){};

bool Task::operator==(const Task& tsk)
{
	return ((m_task_id == tsk.m_task_id));
}

bool Task::operator==(const std::string& id)
{
	return m_task_id == id;
}

void Task::SetTaskDescription(const std::string& description)
{
	m_description = description;
}

void Task::ChangeTaskCompletionStatus()
{
	m_completed = !m_completed;
}

bool Task::IsTaskCompleted() const
{
	return m_completed;
}

const std::string& Task::GetTaskID() const
{
	return m_task_id;
}

const std::string& Task::GetTaskDescription() const
{
	return m_description;
}


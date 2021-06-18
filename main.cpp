/// This example demonstrates a minimal bot that just echoes back what it reads.

#include <libtelegram/libtelegram.h>
#include "TaskManager.h"

auto main()->int {
  std::string const token("914053381:AAF5wPgJrJye7WCL1mRffZp3z_kfL8Jkg-g");
  telegram::sender sender(token);
  telegram::listener::poll listener(sender);

  TaskManager taskManager;

  listener.set_callback_message([&](telegram::types::message const &message){   

    std::string user_id;
    if (!message.from) {
        sender.send_message(message.chat.id, "Error: No user id");
        return;
    }

    if (!message.text) {
        sender.send_message(message.chat.id, "Error: No message text");
        return;
    }

    user_id = std::to_string(message.from->id);
    
    User* user = taskManager.GetUser(user_id);

    if (!user) {
        taskManager.AddUser(user_id);
        user = taskManager.GetUser(user_id);
	user->AddTask("01", "Do Coding!");
	user->AddTask("02", "Some more coding!");
    }

    std::string command = *message.text; 
    size_t space = command.find(" ");
    std::string command_arg{""};
    command_arg = command.substr(space + 1, command.size()); 
    command = command.substr(0,space);
    if (command == "/list") {
        std::string message_out{};
        const Vector<Task>* tasks = user->GetTaskVector();
	
	if(tasks->size() == 0)
		sender.send_message(message.chat.id, "No task!");
	else{
	for (size_t i{0}; i<tasks->size(); ++i)
	{
		message_out+=(*tasks)[i].GetTaskID() + ": ";
		message_out+=(*tasks)[i].IsTaskCompleted()? "Completed task: " : "Uncompleted task: ";
		message_out+=(*tasks)[i].GetTaskDescription() + "\n";
	}
	sender.send_message(message.chat.id, message_out);
	}
	return;
		
    } else if (command == "/show") {
	if(user->GetTask(command_arg) == nullptr)
		sender.send_message(message.chat.id, "No such task available!");
	else {
		std::string mssge{""};
		mssge = user->GetTask(command_arg)->IsTaskCompleted()? "Completed Task: " : "Uncompleted task: ";
		mssge += user->GetTask(command_arg)->GetTaskDescription();
		sender.send_message(message.chat.id, mssge);
	}
        return;
    } else if (command == "/complete") {
	if (user->GetTask(command_arg)->IsTaskCompleted()) {
		sender.send_message(message.chat.id, "The indicated task is already completed!");
		return;
	}
	bool status_changed{user->ChangeTaskCompletionStatus(command_arg)};

	std::string mssge{status_changed? "The task with ID " + command_arg + " is completed!" : "No task with indicated ID is available!"};
	
	sender.send_message(message.chat.id, mssge);
        return;
    } else if (command == "/add") {
	    size_t space = command_arg.find(" ");

	size_t tasks_size{user->GetTaskVector()->size() + 1};
	std::string ssize{std::to_string(tasks_size)};
	if(tasks_size <= 9)
	       ssize = "0" + ssize;
        user->AddTask(ssize, command_arg);
	sender.send_message(message.chat.id, "A new task with ID " + ssize + " is added!");
        return;
    } else if (command == "/remove") {
	std::string mssge{""};
	if (user->RemoveTask(command_arg)) 
		mssge = "The indicated task is removed!";
	else mssge = "No such task available!";

        sender.send_message(message.chat.id, mssge);
        return;
    } else {
        sender.send_message(message.chat.id, "Error: unknown command " + command + ". Availalble commands: /show /add /complete /list /remove");
        return;
    }
  });
  listener.run();
  return EXIT_SUCCESS;
};

#pragma once

#include <string>
#include <vector>

struct TodoItem {
    int id;
    std::string title;
    std::string description;
    bool completed;

    TodoItem(int id, const std::string& title, const std::string& desc)
        : id(id), title(title), description(desc), completed(false) {}
};

class TodoManager {
private:
    std::vector<TodoItem> todos;
    int nextId;

public:
    TodoManager() : nextId(1) {}

    void addTodo(const std::string& title, const std::string& description);
    void completeTodo(int id);
    void removeTodo(int id);
    void listTodos() const;
    int getTodoCount() const;
};
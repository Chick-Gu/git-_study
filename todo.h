#pragma once

#include <string>
#include <vector>
#include <fstream>

enum class Priority {
    LOW,
    MEDIUM,
    HIGH,
    URGENT
};

struct TodoItem {
    int id;
    std::string title;
    std::string description;
    bool completed;
    Priority priority;
    std::string dueDate;
    std::vector<std::string> tags;

    TodoItem(int id, const std::string& title, const std::string& desc)
        : id(id), title(title), description(desc), completed(false), priority(Priority::MEDIUM) {}
};

class TodoManager {
private:
    std::vector<TodoItem> todos;
    int nextId;

    std::string priorityToString(Priority p) const;
    Priority stringToPriority(const std::string& s) const;

public:
    TodoManager() : nextId(1) {}

    void addTodo(const std::string& title, const std::string& description, 
                 Priority priority, const std::string& dueDate, const std::vector<std::string>& tags);
    void completeTodo(int id);
    void removeTodo(int id);
    void listTodos() const;
    void listTodosByPriority() const;
    void listTodosByDueDate() const;
    void addTag(int id, const std::string& tag);
    void removeTag(int id, const std::string& tag);
    void updatePriority(int id, Priority priority);
    void updateDueDate(int id, const std::string& dueDate);
    int getTodoCount() const;
    void saveTodos(const std::string& filename) const;
    void loadTodos(const std::string& filename);
    void searchTodos(const std::string& keyword) const;
    void filterByTag(const std::string& tag) const;
};

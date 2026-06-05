#include "todo.h"
#include <iostream>

void TodoManager::addTodo(const std::string& title, const std::string& description) {
    todos.emplace_back(nextId++, title, description);
    std::cout << "待办事项添加成功！ID: " << nextId - 1 << std::endl;
}

void TodoManager::completeTodo(int id) {
    for (auto& todo : todos) {
        if (todo.id == id) {
            todo.completed = true;
            std::cout << "待办事项 #" << id << " 已标记完成！" << std::endl;
            return;
        }
    }
    std::cout << "未找到 ID 为 " << id << " 的待办事项！" << std::endl;
}

void TodoManager::removeTodo(int id) {
    for (auto it = todos.begin(); it != todos.end(); ++it) {
        if (it->id == id) {
            todos.erase(it);
            std::cout << "待办事项 #" << id << " 已删除！" << std::endl;
            return;
        }
    }
    std::cout << "未找到 ID 为 " << id << " 的待办事项！" << std::endl;
}

void TodoManager::listTodos() const {
    if (todos.empty()) {
        std::cout << "暂无待办事项！" << std::endl;
        return;
    }

    std::cout << "\n===== 待办事项列表 =====" << std::endl;
    for (const auto& todo : todos) {
        std::cout << "[" << (todo.completed ? "✓" : " ") << "] ";
        std::cout << "#" << todo.id << " " << todo.title << std::endl;
        if (!todo.description.empty()) {
            std::cout << "    描述: " << todo.description << std::endl;
        }
    }
    std::cout << "========================\n" << std::endl;
}

int TodoManager::getTodoCount() const {
    return todos.size();
}
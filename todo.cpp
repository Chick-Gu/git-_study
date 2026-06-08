#include "todo.h"
#include <iostream>

void TodoManager::addTodo(const std::string& title, const std::string& description) {
    // 如果描述为空，添加默认描述
    std::string desc = description.empty() ? "暂无描述" : description;
    todos.emplace_back(nextId++, title, desc);
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

void TodoManager::saveTodos(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "无法打开文件: " << filename << std::endl;
        return;
    }
    
    for (const auto& todo : todos) {
        file << todo.id << "\n";
        file << todo.title << "\n";
        file << todo.description << "\n";
        file << todo.completed << "\n";
    }
    
    std::cout << "待办事项已保存到文件: " << filename << std::endl;
}

void TodoManager::loadTodos(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "文件不存在，将创建新的待办事项列表" << std::endl;
        return;
    }
    
    todos.clear();
    int id;
    std::string title, description;
    bool completed;
    
    while (file >> id) {
        file.ignore();  // 忽略换行符
        std::getline(file, title);
        std::getline(file, description);
        file >> completed;
        file.ignore();  // 忽略换行符
        
        todos.emplace_back(id, title, description);
        todos.back().completed = completed;
        
        if (id >= nextId) {
            nextId = id + 1;
        }
    }
    
    std::cout << "已从文件加载 " << todos.size() << " 个待办事项" << std::endl;
}

void TodoManager::searchTodos(const std::string& keyword) const {
    std::vector<TodoItem> results;
    
    for (const auto& todo : todos) {
        // 搜索标题和描述
        if (todo.title.find(keyword) != std::string::npos ||
            todo.description.find(keyword) != std::string::npos) {
            results.push_back(todo);
        }
    }
    
    if (results.empty()) {
        std::cout << "未找到包含 \"" << keyword << "\" 的待办事项" << std::endl;
        return;
    }
    
    std::cout << "\n===== 搜索结果（共 " << results.size() << " 条）=====" << std::endl;
    for (const auto& todo : results) {
        std::cout << "[" << (todo.completed ? "✓" : " ") << "] ";
        std::cout << "#" << todo.id << " " << todo.title << std::endl;
        if (!todo.description.empty()) {
            std::cout << "    描述: " << todo.description << std::endl;
        }
    }
    std::cout << "============================\n" << std::endl;
}
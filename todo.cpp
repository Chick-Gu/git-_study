#include "todo.h"
#include <iostream>
#include <algorithm>

std::string TodoManager::priorityToString(Priority p) const {
    switch(p) {
        case Priority::LOW: return "LOW";
        case Priority::MEDIUM: return "MEDIUM";
        case Priority::HIGH: return "HIGH";
        case Priority::URGENT: return "URGENT";
        default: return "MEDIUM";
    }
}

Priority TodoManager::stringToPriority(const std::string& s) const {
    if (s == "LOW") return Priority::LOW;
    if (s == "HIGH") return Priority::HIGH;
    if (s == "URGENT") return Priority::URGENT;
    return Priority::MEDIUM;
}

void TodoManager::addTodo(const std::string& title, const std::string& description, 
                         Priority priority, const std::string& dueDate, const std::vector<std::string>& tags) {
    std::string desc = description.empty() ? "暂无描述" : description;
    todos.emplace_back(nextId++, title, desc);
    todos.back().priority = priority;
    todos.back().dueDate = dueDate;
    todos.back().tags = tags;
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
        std::cout << "    优先级: " << priorityToString(todo.priority) << std::endl;
        if (!todo.dueDate.empty()) {
            std::cout << "    截止日期: " << todo.dueDate << std::endl;
        }
        if (!todo.tags.empty()) {
            std::cout << "    标签: ";
            for (size_t i = 0; i < todo.tags.size(); ++i) {
                std::cout << "#" << todo.tags[i];
                if (i < todo.tags.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "========================\n" << std::endl;
}

void TodoManager::listTodosByPriority() const {
    if (todos.empty()) {
        std::cout << "暂无待办事项！" << std::endl;
        return;
    }

    std::vector<TodoItem> sorted = todos;
    std::sort(sorted.begin(), sorted.end(), [](const TodoItem& a, const TodoItem& b) {
        return a.priority > b.priority;
    });

    std::cout << "\n===== 待办事项列表（按优先级排序）=====" << std::endl;
    for (const auto& todo : sorted) {
        std::cout << "[" << (todo.completed ? "✓" : " ") << "] ";
        std::cout << "#" << todo.id << " " << todo.title << std::endl;
        std::cout << "    优先级: " << priorityToString(todo.priority) << std::endl;
        if (!todo.dueDate.empty()) {
            std::cout << "    截止日期: " << todo.dueDate << std::endl;
        }
    }
    std::cout << "=======================================\n" << std::endl;
}

void TodoManager::listTodosByDueDate() const {
    if (todos.empty()) {
        std::cout << "暂无待办事项！" << std::endl;
        return;
    }

    std::vector<TodoItem> sorted = todos;
    std::sort(sorted.begin(), sorted.end(), [](const TodoItem& a, const TodoItem& b) {
        if (a.dueDate.empty()) return false;
        if (b.dueDate.empty()) return true;
        return a.dueDate < b.dueDate;
    });

    std::cout << "\n===== 待办事项列表（按截止日期排序）=====" << std::endl;
    for (const auto& todo : sorted) {
        std::cout << "[" << (todo.completed ? "✓" : " ") << "] ";
        std::cout << "#" << todo.id << " " << todo.title << std::endl;
        if (!todo.dueDate.empty()) {
            std::cout << "    截止日期: " << todo.dueDate << std::endl;
        } else {
            std::cout << "    截止日期: 无" << std::endl;
        }
        std::cout << "    优先级: " << priorityToString(todo.priority) << std::endl;
    }
    std::cout << "=========================================\n" << std::endl;
}

void TodoManager::addTag(int id, const std::string& tag) {
    for (auto& todo : todos) {
        if (todo.id == id) {
            auto it = std::find(todo.tags.begin(), todo.tags.end(), tag);
            if (it == todo.tags.end()) {
                todo.tags.push_back(tag);
                std::cout << "标签 \"" << tag << "\" 已添加到待办事项 #" << id << std::endl;
            } else {
                std::cout << "标签 \"" << tag << "\" 已存在！" << std::endl;
            }
            return;
        }
    }
    std::cout << "未找到 ID 为 " << id << " 的待办事项！" << std::endl;
}

void TodoManager::removeTag(int id, const std::string& tag) {
    for (auto& todo : todos) {
        if (todo.id == id) {
            auto it = std::find(todo.tags.begin(), todo.tags.end(), tag);
            if (it != todo.tags.end()) {
                todo.tags.erase(it);
                std::cout << "标签 \"" << tag << "\" 已从待办事项 #" << id << " 删除" << std::endl;
            } else {
                std::cout << "标签 \"" << tag << "\" 不存在！" << std::endl;
            }
            return;
        }
    }
    std::cout << "未找到 ID 为 " << id << " 的待办事项！" << std::endl;
}

void TodoManager::updatePriority(int id, Priority priority) {
    for (auto& todo : todos) {
        if (todo.id == id) {
            todo.priority = priority;
            std::cout << "待办事项 #" << id << " 的优先级已更新为 " << priorityToString(priority) << std::endl;
            return;
        }
    }
    std::cout << "未找到 ID 为 " << id << " 的待办事项！" << std::endl;
}

void TodoManager::updateDueDate(int id, const std::string& dueDate) {
    for (auto& todo : todos) {
        if (todo.id == id) {
            todo.dueDate = dueDate;
            std::cout << "待办事项 #" << id << " 的截止日期已更新为 " << dueDate << std::endl;
            return;
        }
    }
    std::cout << "未找到 ID 为 " << id << " 的待办事项！" << std::endl;
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
        file << priorityToString(todo.priority) << "\n";
        file << todo.dueDate << "\n";
        file << todo.tags.size() << "\n";
        for (const auto& tag : todo.tags) {
            file << tag << "\n";
        }
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
    std::string title, description, priorityStr, dueDate;
    bool completed;
    int tagCount;
    
    while (file >> id) {
        file.ignore();
        std::getline(file, title);
        std::getline(file, description);
        file >> completed;
        file.ignore();
        std::getline(file, priorityStr);
        std::getline(file, dueDate);
        file >> tagCount;
        file.ignore();
        
        todos.emplace_back(id, title, description);
        todos.back().completed = completed;
        todos.back().priority = stringToPriority(priorityStr);
        todos.back().dueDate = dueDate;
        
        for (int i = 0; i < tagCount; ++i) {
            std::string tag;
            std::getline(file, tag);
            todos.back().tags.push_back(tag);
        }
        
        if (id >= nextId) {
            nextId = id + 1;
        }
    }
    
    std::cout << "已从文件加载 " << todos.size() << " 个待办事项" << std::endl;
}

void TodoManager::searchTodos(const std::string& keyword) const {
    std::vector<TodoItem> results;
    
    for (const auto& todo : todos) {
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
        std::cout << "    优先级: " << priorityToString(todo.priority) << std::endl;
        if (!todo.dueDate.empty()) {
            std::cout << "    截止日期: " << todo.dueDate << std::endl;
        }
    }
    std::cout << "============================\n" << std::endl;
}

void TodoManager::filterByTag(const std::string& tag) const {
    std::vector<TodoItem> results;
    
    for (const auto& todo : todos) {
        if (std::find(todo.tags.begin(), todo.tags.end(), tag) != todo.tags.end()) {
            results.push_back(todo);
        }
    }
    
    if (results.empty()) {
        std::cout << "未找到包含标签 \"" << tag << "\" 的待办事项" << std::endl;
        return;
    }
    
    std::cout << "\n===== 标签 \"" << tag << "\" 的待办事项（共 " << results.size() << " 条）=====" << std::endl;
    for (const auto& todo : results) {
        std::cout << "[" << (todo.completed ? "✓" : " ") << "] ";
        std::cout << "#" << todo.id << " " << todo.title << std::endl;
        if (!todo.description.empty()) {
            std::cout << "    描述: " << todo.description << std::endl;
        }
        std::cout << "    优先级: " << priorityToString(todo.priority) << std::endl;
        if (!todo.dueDate.empty()) {
            std::cout << "    截止日期: " << todo.dueDate << std::endl;
        }
    }
    std::cout << "===========================================\n" << std::endl;
}

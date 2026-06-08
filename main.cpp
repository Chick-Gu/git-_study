#include "todo.h"
#include <iostream>
#include <string>
#include <vector>

void printMenu() {
    std::cout << "\n===== 待办事项管理器 v3.0 =====" << std::endl;
    std::cout << "1. 添加待办事项" << std::endl;
    std::cout << "2. 标记完成" << std::endl;
    std::cout << "3. 删除待办事项" << std::endl;
    std::cout << "4. 查看所有待办事项" << std::endl;
    std::cout << "5. 按优先级排序查看" << std::endl;
    std::cout << "6. 按截止日期排序查看" << std::endl;
    std::cout << "7. 添加标签" << std::endl;
    std::cout << "8. 删除标签" << std::endl;
    std::cout << "9. 更新优先级" << std::endl;
    std::cout << "10. 更新截止日期" << std::endl;
    std::cout << "11. 按标签筛选" << std::endl;
    std::cout << "12. 搜索待办事项" << std::endl;
    std::cout << "13. 保存到文件" << std::endl;
    std::cout << "14. 从文件加载" << std::endl;
    std::cout << "15. 退出" << std::endl;
    std::cout << "请输入选项: ";
}

Priority getPriorityFromUser() {
    int choice;
    std::cout << "请选择优先级:" << std::endl;
    std::cout << "1. LOW (低)" << std::endl;
    std::cout << "2. MEDIUM (中)" << std::endl;
    std::cout << "3. HIGH (高)" << std::endl;
    std::cout << "4. URGENT (紧急)" << std::endl;
    std::cout << "请输入选项: ";
    std::cin >> choice;
    
    switch(choice) {
        case 1: return Priority::LOW;
        case 3: return Priority::HIGH;
        case 4: return Priority::URGENT;
        default: return Priority::MEDIUM;
    }
}

std::vector<std::string> getTagsFromUser() {
    std::vector<std::string> tags;
    std::string tag;
    char addMore;
    
    std::cout << "添加标签（输入空行结束）:" << std::endl;
    std::cin.ignore();
    while (true) {
        std::cout << "请输入标签: ";
        std::getline(std::cin, tag);
        if (tag.empty()) break;
        tags.push_back(tag);
        std::cout << "继续添加标签? (y/n): ";
        std::cin >> addMore;
        std::cin.ignore();
        if (addMore != 'y' && addMore != 'Y') break;
    }
    return tags;
}

int main() {
    TodoManager manager;
    int choice;
    const std::string filename = "todos.txt";

    std::cout << "欢迎使用待办事项管理器 v3.0！" << std::endl;
    
    manager.loadTodos(filename);

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, desc, dueDate;
                Priority priority;
                std::vector<std::string> tags;
                
                std::cout << "请输入标题: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "请输入描述（可选）: ";
                std::getline(std::cin, desc);
                priority = getPriorityFromUser();
                std::cout << "请输入截止日期（格式: YYYY-MM-DD，可选）: ";
                std::getline(std::cin, dueDate);
                tags = getTagsFromUser();
                
                manager.addTodo(title, desc, priority, dueDate, tags);
                break;
            }
            case 2: {
                int id;
                std::cout << "请输入待办事项 ID: ";
                std::cin >> id;
                manager.completeTodo(id);
                break;
            }
            case 3: {
                int id;
                std::cout << "请输入待办事项 ID: ";
                std::cin >> id;
                manager.removeTodo(id);
                break;
            }
            case 4:
                manager.listTodos();
                break;
            case 5:
                manager.listTodosByPriority();
                break;
            case 6:
                manager.listTodosByDueDate();
                break;
            case 7: {
                int id;
                std::string tag;
                std::cout << "请输入待办事项 ID: ";
                std::cin >> id;
                std::cout << "请输入标签: ";
                std::cin.ignore();
                std::getline(std::cin, tag);
                manager.addTag(id, tag);
                break;
            }
            case 8: {
                int id;
                std::string tag;
                std::cout << "请输入待办事项 ID: ";
                std::cin >> id;
                std::cout << "请输入要删除的标签: ";
                std::cin.ignore();
                std::getline(std::cin, tag);
                manager.removeTag(id, tag);
                break;
            }
            case 9: {
                int id;
                std::cout << "请输入待办事项 ID: ";
                std::cin >> id;
                Priority priority = getPriorityFromUser();
                manager.updatePriority(id, priority);
                break;
            }
            case 10: {
                int id;
                std::string dueDate;
                std::cout << "请输入待办事项 ID: ";
                std::cin >> id;
                std::cout << "请输入新的截止日期（格式: YYYY-MM-DD）: ";
                std::cin.ignore();
                std::getline(std::cin, dueDate);
                manager.updateDueDate(id, dueDate);
                break;
            }
            case 11: {
                std::string tag;
                std::cout << "请输入要筛选的标签: ";
                std::cin.ignore();
                std::getline(std::cin, tag);
                manager.filterByTag(tag);
                break;
            }
            case 12: {
                std::string keyword;
                std::cout << "请输入搜索关键词: ";
                std::cin.ignore();
                std::getline(std::cin, keyword);
                manager.searchTodos(keyword);
                break;
            }
            case 13:
                manager.saveTodos(filename);
                break;
            case 14:
                manager.loadTodos(filename);
                break;
            case 15:
                manager.saveTodos(filename);
                std::cout << "感谢使用待办事项管理器！" << std::endl;
                break;
            default:
                std::cout << "无效选项，请重新输入！" << std::endl;
        }
    } while (choice != 15);

    return 0;
}

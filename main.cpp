#include "todo.h"
#include <iostream>
#include <string>

void printMenu() {
    std::cout << "\n===== 待办事项管理器 =====" << std::endl;
    std::cout << "1. 添加待办事项" << std::endl;
    std::cout << "2. 标记完成" << std::endl;
    std::cout << "3. 删除待办事项" << std::endl;
    std::cout << "4. 查看所有待办事项" << std::endl;
    std::cout << "5. 退出" << std::endl;
    std::cout << "请输入选项: ";
}

int main() {
    TodoManager manager;
    int choice;

    std::cout << "欢迎使用待办事项管理器！" << std::endl;

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, desc;
                std::cout << "请输入标题: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "请输入描述（可选）: ";
                std::getline(std::cin, desc);
                manager.addTodo(title, desc);
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
                std::cout << "感谢使用待办事项管理器！" << std::endl;
                break;
            default:
                std::cout << "无效选项，请重新输入！" << std::endl;
        }
    } while (choice != 5);

    return 0;
}
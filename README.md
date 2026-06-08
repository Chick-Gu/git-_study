# TodoManager - C++ 待办事项管理器

一个使用 C++ 编写的命令行待办事项管理程序，支持添加、完成、删除和查看待办事项。

## 项目概述

本项目是一个轻量级的待办事项管理器，采用纯 C++ 实现，无需外部依赖。适合初学者学习 C++ 类、STL 容器和命令行交互编程。

## 功能特性

| 功能 | 说明 |
|------|------|
| 添加待办事项 | 支持标题和可选描述 |
| 标记完成 | 将指定待办事项标记为已完成 |
| 删除待办事项 | 从列表中移除指定待办事项 |
| 查看列表 | 显示所有待办事项及其状态 |
| 保存到文件 | 将待办事项保存到 `todos.txt` 文件 |
| 从文件加载 | 从文件读取已保存的待办事项 |
| 自动持久化 | 程序启动/退出时自动加载/保存数据 |
| 默认描述 | 空描述自动填充为"暂无描述" |
| 搜索功能 | 按关键词搜索待办事项 |
| 优先级设置 | 支持 LOW/MEDIUM/HIGH 三级优先级 |
| 截止日期 | 支持设置任务截止日期 |
| 标签系统 | 支持添加多个自定义标签 |
| 按优先级排序 | 高优先级任务优先显示 |
| 过期提醒 | 自动检测并显示已过期任务 |
| 按标签筛选 | 按标签分类查看任务 |

## 项目结构

```
├── main.cpp          # 主程序入口，包含菜单和用户交互
├── todo.h            # 头文件，定义 TodoItem 结构体和 TodoManager 类
├── todo.cpp          # 实现文件，包含所有成员方法的实现
├── CMakeLists.txt    # CMake 构建配置文件
└── .gitignore        # Git 忽略文件配置
```

## 快速开始

### 编译项目

**方式一：使用 g++ 编译器**

```bash
g++ -std=c++11 main.cpp todo.cpp -o todo_manager
```

**方式二：使用 CMake（推荐）**

```bash
mkdir build
cd build
cmake ..
make
```

### 运行程序

```bash
./todo_manager        # Linux/macOS
todo_manager.exe      # Windows
```

---

## 代码详解

### 1. 数据结构 - todo.h

#### TodoItem 结构体

```cpp
// 优先级枚举
enum class Priority {
    LOW,
    MEDIUM,
    HIGH
};

struct TodoItem {
    int id;                    // 待办事项的唯一标识符
    std::string title;         // 待办事项的标题
    std::string description;   // 待办事项的详细描述（可选）
    bool completed;            // 完成状态标记
    Priority priority;         // 优先级（LOW/MEDIUM/HIGH）
    std::string dueDate;       // 截止日期（YYYY-MM-DD 格式）
    std::vector<std::string> tags;  // 标签列表

    // 构造函数，使用初始化列表初始化成员
    TodoItem(int id, const std::string& title, const std::string& desc)
        : id(id), title(title), description(desc), completed(false),
          priority(Priority::MEDIUM), dueDate("") {}
};
```

**设计说明：**
- `id` 使用 `int` 类型，从 1 开始自增
- 使用 `std::string` 存储文本内容
- `completed` 布尔值标记完成状态
- `priority` 使用枚举类实现类型安全的优先级
- `dueDate` 存储截止日期，格式为 YYYY-MM-DD
- `tags` 使用 `std::vector` 存储多个标签
- 构造函数使用**初始化列表**语法，提高效率

#### TodoManager 类

```cpp
class TodoManager {
private:
    std::vector<TodoItem> todos;  // 存储所有待办事项的容器
    int nextId;                    // 下一个可用的 ID

public:
    TodoManager() : nextId(1) {}   // 构造函数，初始化 nextId 为 1

    // 基础功能
    void addTodo(const std::string& title, const std::string& description);
    void completeTodo(int id);
    void removeTodo(int id);
    void listTodos() const;
    int getTodoCount() const;
    
    // 数据持久化
    void saveTodos(const std::string& filename) const;  // 保存到文件
    void loadTodos(const std::string& filename);        // 从文件加载
    
    // 高级功能
    void searchTodos(const std::string& keyword) const;  // 搜索待办事项
    void sortByPriority() const;                         // 按优先级排序
    void displayOverdueTodos() const;                    // 显示过期任务
    void addTagToTodo(int id, const std::string& tag);   // 添加标签
    void filterByTag(const std::string& tag) const;      // 按标签筛选
};
```

**设计说明：**
- 使用 `std::vector` 作为容器，支持动态大小
- `nextId` 保证每个待办事项有唯一 ID
- 所有成员函数声明在类内，实现放在 todo.cpp 中
- 方法按功能分组，提高可读性

---

### 2. 实现文件 - todo.cpp

#### 添加待办事项

```cpp
void TodoManager::addTodo(const std::string& title, const std::string& description) {
    // 使用 emplace_back 直接在 vector 末尾构造对象
    todos.emplace_back(nextId++, title, description);
    std::cout << "待办事项添加成功！ID: " << nextId - 1 << std::endl;
}
```

**要点：**
- `emplace_back` 比 `push_back` 效率更高，直接构造对象
- `nextId++` 先返回当前值再自增，确保新对象的 ID 正确
- 自增后的 `nextId` 为下一次使用做准备

#### 标记完成

```cpp
void TodoManager::completeTodo(int id) {
    // 遍历 vector 查找匹配的待办事项
    for (auto& todo : todos) {
        if (todo.id == id) {
            todo.completed = true;
            std::cout << "待办事项 #" << id << " 已标记完成！" << std::endl;
            return;
        }
    }
    // 未找到时输出错误信息
    std::cout << "未找到 ID 为 " << id << " 的待办事项！" << std::endl;
}
```

**要点：**
- 使用范围 for 循环遍历容器
- 使用引用 `auto&` 允许修改元素
- 找到后立即返回，避免不必要的遍历

#### 删除待办事项

```cpp
void TodoManager::removeTodo(int id) {
    for (auto it = todos.begin(); it != todos.end(); ++it) {
        if (it->id == id) {
            todos.erase(it);  // erase 会使迭代器失效
            std::cout << "待办事项 #" << id << " 已删除！" << std::endl;
            return;
        }
    }
    std::cout << "未找到 ID 为 " << id << " 的待办事项！" << std::endl;
}
```

**要点：**
- 使用迭代器而非范围 for 循环，因为需要调用 `erase`
- `erase` 会删除元素并返回下一个有效迭代器
- 注意迭代器失效问题（此处删除后直接返回）

#### 查看列表

```cpp
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
```

**要点：**
- `const` 成员函数承诺不修改对象状态
- `const auto&` 遍历，防止意外修改
- 三目运算符 `? :` 用于显示完成状态符号
- 空描述不显示，保持界面整洁

---

### 3. 主程序 - main.cpp

#### 菜单打印函数

```cpp
void printMenu() {
    std::cout << "\n===== 待办事项管理器 =====" << std::endl;
    std::cout << "1. 添加待办事项" << std::endl;
    std::cout << "2. 标记完成" << std::endl;
    std::cout << "3. 删除待办事项" << std::endl;
    std::cout << "4. 查看所有待办事项" << std::endl;
    std::cout << "5. 保存到文件" << std::endl;
    std::cout << "6. 从文件加载" << std::endl;
    std::cout << "7. 退出" << std::endl;
    std::cout << "8. 搜索待办事项" << std::endl;
    std::cout << "9. 按优先级排序" << std::endl;
    std::cout << "10. 查看过期待办" << std::endl;
    std::cout << "11. 添加标签" << std::endl;
    std::cout << "12. 按标签筛选" << std::endl;
    std::cout << "请输入选项: ";
}
```

#### 主循环

```cpp
int main() {
    TodoManager manager;
    int choice;
    const std::string filename = "todos.txt";  // 数据文件名

    std::cout << "欢迎使用待办事项管理器BETA版本！" << std::endl;

    // 程序启动时自动加载
    manager.loadTodos(filename);

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // 添加待办事项
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
                // 标记完成
                int id;
                std::cout << "请输入待办事项 ID: ";
                std::cin >> id;
                manager.completeTodo(id);
                break;
            }
            case 3: {
                // 删除待办事项
                int id;
                std::cout << "请输入待办事项 ID: ";
                std::cin >> id;
                manager.removeTodo(id);
                break;
            }
            case 4:
                manager.listTodos();
                break;
            case 5:  // 手动保存
                manager.saveTodos(filename);
                break;
            case 6:  // 手动加载
                manager.loadTodos(filename);
                break;
            case 7:  // 退出时自动保存
                manager.saveTodos(filename);
                std::cout << "感谢使用待办事项管理器！" << std::endl;
                break;
            default:
                std::cout << "无效选项，请重新输入！" << std::endl;
        }
    } while (choice != 7);

    return 0;
}
```

**关键设计：**
- `do-while` 循环确保菜单至少显示一次
- `switch-case` 处理多分支逻辑
- `std::cin.ignore()` 清除缓冲区，避免读取残留的换行符
- `std::getline()` 读取包含空格的整行输入

---

## 使用示例

```
欢迎使用待办事项管理器BETA版本！

===== 待办事项管理器 =====
1. 添加待办事项
2. 标记完成
3. 删除待办事项
4. 查看所有待办事项
5. 退出
请输入选项: 1
请输入标题: 学习 C++
请输入描述（可选）: 复习类和对象
待办事项添加成功！ID: 1

===== 待办事项管理器 =====
1. 添加待办事项
2. 标记完成
3. 删除待办事项
4. 查看所有待办事项
5. 退出
请输入选项: 1
请输入标题: 学习 Git
请输入描述（可选）: 掌握基本命令
待办事项添加成功！ID: 2

===== 待办事项管理器 =====
1. 添加待办事项
2. 标记完成
3. 删除待办事项
4. 查看所有待办事项
5. 退出
请输入选项: 4

===== 待办事项列表 =====
[ ] #1 学习 C++
    描述: 复习类和对象
[ ] #2 学习 Git
    描述: 掌握基本命令
========================

===== 待办事项管理器 =====
1. 添加待办事项
2. 标记完成
3. 删除待办事项
4. 查看所有待办事项
5. 退出
请输入选项: 2
请输入待办事项 ID: 1
待办事项 #1 已标记完成！

===== 待办事项管理器 =====
1. 添加待办事项
2. 标记完成
3. 删除待办事项
4. 查看所有待办事项
5. 退出
请输入选项: 4

===== 待办事项列表 =====
[✓] #1 学习 C++
    描述: 复习类和对象
[ ] #2 学习 Git
    描述: 掌握基本命令
========================

===== 待办事项管理器 =====
1. 添加待办事项
2. 标记完成
3. 删除待办事项
4. 查看所有待办事项
5. 退出
请输入选项: 5
感谢使用待办事项管理器！
```

---

## C++ 知识点总结

| 知识点 | 代码中的应用 |
|--------|-------------|
| **类封装** | `TodoManager` 类封装了所有业务逻辑 |
| **结构体** | `TodoItem` 结构体组织相关数据 |
| **枚举类** | `Priority` 枚举实现类型安全的优先级 |
| **构造函数初始化列表** | `TodoItem(int id, ...)` 使用初始化列表 |
| **STL 容器** | `std::vector<TodoItem>` 存储待办事项 |
| **迭代器** | `todos.begin()`, `todos.end()`, `erase()` |
| **范围 for 循环** | `for (const auto& todo : todos)` |
| **Lambda 表达式** | 用于排序比较函数 |
| **标准算法** | `std::sort`, `std::find` |
| **引用 & 常量引用 const&** | 避免拷贝，提高效率 |
| **string 处理** | `std::string`, `std::getline()` |
| **输入输出流** | `std::cin`, `std::cout` |
| **文件流** | `std::ofstream` 写入文件, `std::ifstream` 读取文件 |
| **日期时间处理** | `time_t`, `localtime`, `strftime` |
| **控制流程** | `switch-case`, `do-while` |

---

## 编译要求

- C++11 或更高标准
- 支持 GCC 4.8+ / Clang 3.3+ / MSVC 2015+

---

## 许可证

MIT License

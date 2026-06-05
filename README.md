# TodoManager

一个简单的 C++ 待办事项管理器，用于学习 Git 版本控制。

## 功能特性

- 添加待办事项（支持标题和描述）
- 标记待办事项为完成
- 删除待办事项
- 查看所有待办事项列表

## 项目结构

```
├── main.cpp      # 主程序入口
├── todo.h        # 头文件（类声明）
├── todo.cpp      # 实现文件（类方法）
├── CMakeLists.txt # CMake 构建配置
└── .gitignore    # Git 忽略文件
```

## 编译运行

### 使用 CMake（推荐）

```bash
mkdir build
cd build
cmake ..
make
./todo_manager
```

### 使用 g++

```bash
g++ -std=c++11 main.cpp todo.cpp -o todo_manager
./todo_manager
```

## 使用示例

```
===== 待办事项管理器 =====
1. 添加待办事项
2. 标记完成
3. 删除待办事项
4. 查看所有待办事项
5. 退出
请输入选项: 1
请输入标题: 学习 Git
请输入描述（可选）: 学习基本的 Git 命令
待办事项添加成功！ID: 1
```

## Git 学习步骤

### 1. 初始化本地仓库

```bash
git init
```

### 2. 添加文件到暂存区

```bash
git add .
```

### 3. 提交到本地仓库

```bash
git commit -m "Initial commit: 添加待办事项管理器"
```

### 4. 连接远程仓库

```bash
git remote add origin https://github.com/你的用户名/仓库名.git
```

### 5. 推送到远程仓库

```bash
git push -u origin main
```

## 许可证

MIT License

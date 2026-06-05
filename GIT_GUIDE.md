# GitHub 完整学习指南

## 一、GitHub 基础知识

### 1.1 核心概念

| 概念 | 说明 |
|------|------|
| **Repository (仓库)** | 存储项目的地方，相当于一个文件夹 |
| **Commit (提交)** | 每次代码修改的快照，记录了具体改了哪些内容 |
| **Branch (分支)** | 从主分支分离出来的工作副本，用于开发新功能 |
| **Merge (合并)** | 将分支的修改合并回主分支 |
| **Fork (派生)** | 在自己账号下创建他人项目的副本 |
| **Clone (克隆)** | 将远程仓库下载到本地 |
| **Push (推送)** | 将本地修改上传到远程仓库 |
| **Pull (拉取)** | 将远程仓库的修改下载到本地 |

### 1.2 GitHub 常用术语

```
- Issue (问题): 用于跟踪任务、Bug报告、功能建议
- Wiki: 项目的文档系统
- Star: 收藏项目，类似书签
- Watch: 关注项目，有更新会通知你
- Fork: 复制他人的仓库到自己账号
- Pull Request (PR): 请求将你的修改合并到原项目
- Review: 代码审查
- CI/CD: 持续集成/持续部署
```

### 1.3 GitHub 账号设置

**安装 Git：**
```bash
# Windows 下载地址: https://git-scm.com/download/win
# 安装后打开 Git Bash 配置身份
git config --global user.name "你的用户名"
git config --global user.email "你的邮箱"
```

**生成 SSH 密钥（用于免密登录）：**
```bash
ssh-keygen -t rsa -C "你的邮箱"
# 生成的公钥在 ~/.ssh/id_rsa.pub
# 将公钥添加到 GitHub -> Settings -> SSH Keys
```

---

## 二、Git 版本控制基础

### 2.1 Git 工作流程

```
┌─────────┐    ┌─────────┐    ┌─────────┐    ┌─────────┐
│ Working │ -> │  Staged │ -> │ Committed│ -> │  Remote │
│  Directory│   │ (暂存区) │   │ (本地仓库) │   │ (远程仓库) │
└─────────┘    └─────────┘    └─────────┘    └─────────┘
   git add        git commit      git push
```

### 2.2 基础命令

**初始化和克隆：**
```bash
# 在当前目录初始化新仓库
git init

# 克隆远程仓库
git clone https://github.com/用户名/仓库名.git
git clone git@github.com:用户名/仓库名.git  # SSH方式
```

**基本操作：**
```bash
git status          # 查看当前状态
git add 文件名       # 添加文件到暂存区
git add .           # 添加所有修改的文件
git commit -m "提交说明"  # 提交到本地仓库
git log             # 查看提交历史
git diff            # 查看未暂存的修改
```

**分支操作：**
```bash
git branch                    # 查看分支
git branch 新分支名            # 创建新分支
git checkout 分支名            # 切换分支
git checkout -b 新分支名       # 创建并切换到新分支
git merge 分支名              # 合并指定分支到当前分支
git branch -d 分支名           # 删除分支
```

**同步操作：**
```bash
git fetch      # 获取远程仓库的更新（不合并）
git pull       # 拉取并合并远程更新（相当于 fetch + merge）
git push       # 推送本地提交到远程仓库
git push -u origin 分支名  # 首次推送并设置上游分支
```

### 2.3 分支管理策略

**常用工作流：**

1. **Git Flow**：有明确的开发、发布、修复分支
   - `main`: 主分支，保持稳定
   - `develop`: 开发分支
   - `feature/xxx`: 功能分支
   - `hotfix/xxx`: 紧急修复分支
   - `release/xxx`: 发布分支

2. **GitHub Flow**：简单流程
   - 创建分支 -> 提交修改 -> 创建 PR -> 审查 -> 合并

3. **Trunk-Based Development**：所有人基于 main 分支开发

---

## 三、项目上传与协作

### 3.1 本地项目上传到 GitHub

**步骤：**

1. **在 GitHub 创建新仓库**
   - 点击右上角 `+` -> `New repository`
   - 填写仓库名称、描述、选择公开/私有
   - **不要**勾选 Initialize this repository with a README（我们已有项目）

2. **本地初始化并连接远程仓库**
   ```bash
   cd 你的项目目录
   git init
   git add .
   git commit -m "Initial commit"
   git remote add origin https://github.com/你的用户名/仓库名.git
   git push -u origin master
   ```

### 3.2 多人协作流程

**方式一：合作者模式（适合团队内部）**
```
1. 仓库所有者 -> Settings -> Manage access -> Invite a collaborator
2. 被邀请人接受邀请
3. 合作者可以直接 push 到该仓库
```

**方式二：Fork + Pull Request（适合开源贡献）**
```
1. 在 GitHub 上 Fork 别人的仓库到你账号
2. Clone 你 Fork 的仓库到本地
3. 创建新分支进行修改
4. Push 到你 Fork 的仓库
5. 在 GitHub 上创建 Pull Request
6. 原项目维护者审查并决定是否合并
```

### 3.3 解决冲突

当多人同时修改同一文件时会产生冲突：

```bash
# 1. 先拉取最新代码
git pull origin main

# 2. 如果有冲突，Git 会在文件中标记冲突部分
<<<<<<< HEAD
你的修改
=======
他人的修改
>>>>>>> 其他分支

# 3. 手动编辑解决冲突，删除标记符号
# 4. 标记冲突已解决
git add 冲突文件

# 5. 提交合并
git commit -m "解决冲突"

# 6. 推送到远程
git push
```

---

## 四、Pull Request 工作流

### 4.1 创建 Pull Request

1. **推送你的分支到远程**
   ```bash
   git checkout -b feature/新功能
   # 进行修改...
   git add .
   git commit -m "添加新功能"
   git push -u origin feature/新功能
   ```

2. **在 GitHub 上创建 PR**
   - 进入你的仓库页面
   - 点击 `Compare & pull request`
   - 填写 PR 标题和描述
   - 选择目标分支（通常是 main）
   - 点击 `Create pull request`

### 4.2 Pull Request 最佳实践

**描述模板：**
```markdown
## 描述
简要说明这次修改的内容

## 改了什么
- 功能A: 具体说明
- 修复B: 具体说明

## 为什么需要这个修改
解释动机和背景

## 相关 Issue
Closes #123
```

**PR 标题规范：**
- `feat:` 新功能
- `fix:` 修复 Bug
- `docs:` 文档修改
- `style:` 代码格式（不影响功能）
- `refactor:` 重构
- `test:` 测试相关
- `chore:` 构建/工具相关

示例：`feat: 添加用户登录功能`

### 4.3 代码审查

**审查者应该检查：**
- 代码逻辑是否正确
- 是否有潜在 Bug
- 是否符合项目规范
- 是否有测试覆盖
- 文档是否需要更新

**审查操作：**
- `Comment`: 一般性评论
- `Approve`: 批准合并
- `Request changes`: 要求修改后再合并

### 4.4 合并策略

| 策略 | 说明 | 适用场景 |
|------|------|----------|
| **Merge** | 保留所有提交历史 | 多人协作，保留完整历史 |
| **Squash and merge** | 压缩为单个提交 | 清理功能分支的多个小提交 |
| **Rebase and merge** | 变基后直接合并 | 保持线性历史 |

---

## 五、文档编写与项目管理

### 5.1 README.md 编写指南

README 是项目的入口文档，应该包含：

```markdown
# 项目名称

简短描述项目是什么、能做什么

## 特性
- 特性1
- 特性2

## 快速开始
### 安装
安装步骤

### 使用
基本用法示例

## 示例代码
```javascript
// 代码示例
```

## API 文档
接口说明

## 贡献指南
如何参与贡献

## 许可证
MIT / Apache 2.0 等
```

### 5.2 GitHub Wiki

每个仓库都有 Wiki 系统：
- 用于详细的项目文档
- 可以创建多个页面
- 支持 Markdown 编写

### 5.3 GitHub Issues 使用

**Issue 模板：**
```markdown
## Bug 报告
- 环境信息（操作系统、版本等）
- 复现步骤
- 预期行为
- 实际行为

## 功能请求
- 功能描述
- 使用场景
- 建议的解决方案
```

**Labels（标签）使用：**
- `bug`: Bug 报告
- `enhancement`: 功能增强
- `help wanted`: 需要帮助
- `good first issue`: 适合新手
- `documentation`: 文档相关
- `question`: 问题

**Milestones（里程碑）：**
- 将相关的 Issue 和 PR 组织在一起
- 设置截止日期
- 跟踪项目进度

### 5.4 GitHub Projects（项目管理）

类似 Trello 的看板工具：
- 创建 Project 看板
- 添加 Issue/PR 到看板
- 拖动卡片管理状态
- 可设置自动化规则

### 5.5 GitHub Actions（CI/CD）

自动化工作流示例：

```yaml
name: CI

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Set up Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
      - run: npm install
      - run: npm test
```

---

## 六、常用 GitHub 技巧

### 6.1 键盘快捷键

| 快捷键 | 功能 |
|--------|------|
| `t` | 在仓库中搜索文件 |
| `w` | 切换分支 |
| `l` | 打开标签页 |
| `s` | 聚焦搜索框 |
| `?` | 显示所有快捷键 |

### 6.2 GitHub CLI

```bash
# 安装 GitHub CLI
# Windows: winget install GitHub.cli

# 登录
gh auth login

# 创建 PR
gh pr create --title "标题" --body "描述"

# 查看 PR 状态
gh pr status

# 合并 PR
gh pr merge PR编号
```

### 6.3 GitHub Desktop

- 图形化 Git 工具
- 适合不熟悉命令行的初学者
- 可视化分支管理
- 官网：desktop.github.com

---

## 七、学习路径建议

### 第一阶段：入门（1-2天）
1. 创建 GitHub 账号
2. 熟悉仓库、提交、分支概念
3. 学会基本的 Git 命令
4. 尝试将本地项目上传到 GitHub

### 第二阶段：协作（3-5天）
1. 学会 Fork 和 Pull Request
2. 学习代码审查流程
3. 练习解决合并冲突
4. 参与开源项目贡献

### 第三阶段：进阶（1-2周）
1. 掌握分支管理策略
2. 学习 GitHub Actions
3. 学会使用 Projects 管理项目
4. 编写规范的 README 和文档

### 第四阶段：精通（持续学习）
1. 学习 Git 高级技巧（rebase、stash 等）
2. 深入理解 CI/CD 流程
3. 学习 DevOps 实践
4. 参与大型开源项目

---

## 八、推荐资源

- **官方文档**: docs.github.com
- **Git 官方文档**: git-scm.com/doc
- **GitHub Skills**: skills.github.com（官方交互教程）
- **Learn Git Branching**: learngitbranching.js.org（可视化学习）

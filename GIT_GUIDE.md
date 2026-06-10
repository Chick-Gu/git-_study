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
git commit -m "提交说明"  # 提交到本地仓库（-m 直接指定提交信息）
git log             # 查看提交历史
git diff            # 查看未暂存的修改
```

**`-m` 参数详解：**

`-m` 是 message 的缩写，用于在命令行中直接指定提交信息，无需打开编辑器。

```bash
# 使用 -m 快速提交
git commit -m "提交信息"

# 不使用 -m，会打开编辑器编写提交信息
git commit

# 多行提交信息
git commit -m "标题" -m "详细描述第一行" -m "详细描述第二行"
```

**提交信息规范（约定式提交）：**

| 前缀 | 说明 | 示例 |
|------|------|------|
| `feat:` | 新功能 | `feat: 添加用户登录功能` |
| `fix:` | 修复 Bug | `fix: 修复保存文件时的错误` |
| `docs:` | 文档更新 | `docs: 更新README说明` |
| `style:` | 代码格式 | `style: 调整代码缩进` |
| `refactor:` | 重构代码 | `refactor: 优化代码结构` |
| `test:` | 测试相关 | `test: 添加单元测试` |
| `chore:` | 构建/工具 | `chore: 更新构建配置` |

**查看提交历史：**
```bash
git log                     # 查看完整提交历史
git log --oneline           # 简洁显示（每行一个提交）
git log --oneline -5        # 只显示最近 5 个提交
git log --oneline --graph   # 带图形显示分支结构
git log --oneline --graph --all  # 显示所有分支的历史
git log --merges            # 只显示合并提交
git show <commit-hash>      # 查看特定提交的详细内容
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

## 四、查看合并记录

### 4.1 本地查看合并记录

**查看完整历史（带图形）：**
```bash
git log --oneline --graph --all
```
- 显示所有分支的提交历史
- 用图形展示分支合并结构
- 最直观的查看方式

**只查看合并提交：**
```bash
git log --merges
```
- 只显示 Merge commits
- 不显示普通提交

**查看特定提交详情：**
```bash
git show <commit-hash>
```
- 显示该提交的完整信息
- 包括修改的文件和具体内容

**查看当前分支历史：**
```bash
git log --oneline --graph
```
- 只显示当前分支的历史

### 4.2 GitHub 上查看合并记录

**方法一：Commits 页面**
1. 打开仓库页面
2. 点击 **"Commits"** 标签
3. 查看所有提交历史

**方法二：Network 图（可视化）**
1. 点击 **"Insights"**
2. 选择 **"Network"**
3. 可视化查看分支和合并结构

**方法三：Pull Requests**
1. 点击 **"Pull requests"** 标签
2. 查看 **"Closed"** 的 PR
3. 可以看到已合并的 PR 详情

---

## 五、Pull Request 工作流

### 5.1 创建 Pull Request

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

### 5.2 Pull Request 最佳实践

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

### 5.3 代码审查

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

### 5.4 合并策略

| 策略 | 说明 | 适用场景 |
|------|------|----------|
| **Merge** | 保留所有提交历史 | 多人协作，保留完整历史 |
| **Squash and merge** | 压缩为单个提交 | 清理功能分支的多个小提交 |
| **Rebase and merge** | 变基后直接合并 | 保持线性历史 |

---

## 六、文档编写与项目管理

### 6.1 README.md 编写指南

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

### 6.2 GitHub Wiki

每个仓库都有 Wiki 系统：
- 用于详细的项目文档
- 可以创建多个页面
- 支持 Markdown 编写

### 6.3 GitHub Issues 使用

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

### 6.4 GitHub Projects（项目管理）

类似 Trello 的看板工具：
- 创建 Project 看板
- 添加 Issue/PR 到看板
- 拖动卡片管理状态
- 可设置自动化规则

### 6.5 GitHub Actions（CI/CD）

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

## 七、常用 GitHub 技巧

### 7.1 键盘快捷键

| 快捷键 | 功能 |
|--------|------|
| `t` | 在仓库中搜索文件 |
| `w` | 切换分支 |
| `l` | 打开标签页 |
| `s` | 聚焦搜索框 |
| `?` | 显示所有快捷键 |

### 7.2 GitHub CLI

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

### 7.3 GitHub Desktop

- 图形化 Git 工具
- 适合不熟悉命令行的初学者
- 可视化分支管理
- 官网：desktop.github.com

### 7.4 GitHub Issues

#### 7.4.1 什么是 Issues

GitHub Issues 是 GitHub 内置的任务跟踪系统，用于：
- 跟踪待办事项和任务
- 报告和跟踪 Bug
- 记录功能请求
- 团队协作和讨论

#### 7.4.2 Issue 类型与标签

| 类型 | 说明 | 常用标签 |
|------|------|----------|
| Bug Report | 报告代码错误 | `bug`, `bugfix` |
| Feature Request | 请求新功能 | `enhancement`, `feature` |
| Documentation | 文档相关 | `documentation`, `docs` |
| Question | 问题咨询 | `question`, `help` |
| Help Wanted | 需要帮助 | `help wanted`, `good first issue` |

#### 7.4.3 Issue 关键字（提交信息中使用）

在提交信息或 PR 描述中使用以下关键字可以自动关联和关闭 Issue：

| 关键字 | 说明 | 示例 |
|--------|------|------|
| `closes` | 合并后关闭 Issue | `closes #2` |
| `fixes` | 合并后关闭 Issue（适合 Bug） | `fixes #5` |
| `resolves` | 合并后关闭 Issue | `resolves #8` |
| `references` | 关联但不关闭 | `references #10` |

**示例提交信息：**
```bash
git commit -m "feat: 添加搜索功能, closes #2"
git commit -m "fix: 修复空描述崩溃问题, fixes #5"
```

#### 7.4.4 Issue 模板

常见的 Issue 模板文件：
- `.github/ISSUE_TEMPLATE/bug_report.md` - Bug 报告模板
- `.github/ISSUE_TEMPLATE/feature_request.md` - 功能请求模板
- `.github/ISSUE_TEMPLATE/question.md` - 问题咨询模板

#### 7.4.5 完整工作流

```bash
# 1. 创建功能分支
git checkout -b feature/add-search

# 2. 实现功能并提交（关联 Issue）
git commit -m "feat: 添加搜索功能, closes #2"

# 3. 推送到远程
git push -u origin feature/add-search

# 4. 在 GitHub 创建 PR（会自动关联 Issue）

# 5. 合并 PR 后，Issue #2 会自动关闭
```

#### 7.4.6 GitHub CLI 操作 Issues

```bash
# 查看 Issues
gh issue list

# 创建 Issue
gh issue create --title "标题" --body "描述" --label "enhancement"

# 查看 Issue 详情
gh issue view 编号

# 关闭 Issue
gh issue close 编号

# 为 Issue 添加标签
gh issue edit 编号 --add-label "bug"
```

### 7.5 GitHub Projects（项目管理看板）

#### 7.5.1 什么是 GitHub Projects

GitHub Projects 是 GitHub 内置的项目管理工具，提供可视化任务管理：

| 功能 | 说明 |
|------|------|
| **看板视图 (Kanban)** | 可视化任务卡片管理 |
| **表格视图 (Table)** | 列表式任务管理 |
| **自动化工作流** | 自动移动卡片、关闭任务 |
| **与 Issues/PR 集成** | 无缝协作 |

#### 7.5.2 创建项目看板

**操作步骤：**
1. 打开仓库，点击顶部 **"Projects"** 标签
2. 点击 **"New project"** 按钮
3. 选择模板：**Kanban**（看板）或 **Table**（表格）
4. 填写项目名称和描述
5. 点击 **"Create project"**

#### 7.5.3 看板列配置

**推荐列顺序：**

| 列名 | 说明 | 使用场景 |
|------|------|----------|
| **To do** | 待办任务池 | 新任务、未规划 |
| **Ready** | 准备开始 | 已分析、可立即开始 |
| **In progress** | 进行中 | 正在开发 |
| **In Review** | 审查中 | PR 已提交，等待审查 |
| **Done** | 已完成 | 任务完成、PR 已合并 |

**添加自定义列：**
1. 点击列标题右侧的 **三个点图标 (...)** 
2. 选择 **"Add column"**
3. 输入列名并按 Enter
4. 拖拽调整列位置

#### 7.5.4 任务卡片操作

**创建卡片：**
- 点击列底部的 **"+"** 按钮
- 输入任务标题，按 Enter 创建
- 在看板创建卡片会自动生成仓库 Issue

**添加已有 Issue：**
- 点击输入框右侧的图标
- 选择 **"Add from repository"**
- 搜索并选择已有 Issue

**编辑卡片：**
- 点击卡片打开详情面板
- 添加描述、负责人、标签、里程碑等
- 关联 Issue 或 Pull Request

**移动卡片：**
- 用鼠标拖拽卡片到目标列
- 表示任务状态变更

#### 7.5.5 自动化工作流

**进入设置：**
- 点击项目右上角的 **齿轮图标**（Settings）
- 选择 **"Workflows"**

**可用自动化：**

| 工作流 | 触发条件 | 动作 |
|--------|----------|------|
| **Item added to project** | 新 Issue/PR 添加 | 移到指定列（如 To do） |
| **Item reopened** | Issue 重新打开 | 移到 To do |
| **Pull request ready for review** | PR 创建 | 移到 In Review |
| **Pull request merged** | PR 合并 | 移到 Done |
| **Issue closed** | Issue 关闭 | 移到 Done |

**启用自动化：**
1. 找到目标工作流
2. 点击开关启用（变为绿色）
3. 设置目标列

#### 7.5.6 卡片与 Issue 的关系

| 操作 | 结果 |
|------|------|
| 在看板创建新卡片 | 自动创建新 Issue |
| 添加已有 Issue | 卡片链接到该 Issue |
| 关闭 Issue | 卡片自动移到 Done（需启用自动化） |
| 删除卡片 | Issue 不会被删除 |
| 一个 Issue | 可出现在多个项目中 |

#### 7.5.7 GitHub CLI 操作 Projects

```bash
# 查看项目列表
gh project list

# 创建项目
gh project create "项目名称" --owner 用户名

# 添加 Issue 到项目
gh project item-add 项目编号 --url IssueURL

# 查看项目内容
gh project view 项目编号

# 编辑项目项
gh project item-edit 项目编号 --id 项目项ID --field-id 字段ID --value 值
```

#### 7.5.8 最佳实践

**项目命名建议：**
- `项目名 Development` - 开发任务看板
- `Bug Tracking` - Bug 追踪看板
- `Release v1.0` - 版本发布看板

**工作流程：**
```
创建 Issue → To do → Ready → In progress → In Review → Done
    │         │        │          │            │         │
  新任务    规划完成  开始编码   提交PR      审查通过   合并完成
```

**团队协作建议：**
- 为每个卡片指定负责人（Assignees）
- 使用标签分类任务类型
- 设置里程碑追踪进度
- 定期回顾看板状态

---

## 八、学习路径建议

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

## 九、Git 高级技巧

### 9.1 git rebase（变基操作）

**什么是变基？**

变基是将一系列提交移动或合并到新的基点上，使提交历史更加线性和清晰。

**基本用法：**
```bash
# 将当前分支变基到目标分支
git rebase 目标分支

# 交互式变基（编辑提交历史）
git rebase -i HEAD~5  # 修改最近 5 个提交
```

**交互式变基操作：**
```bash
git rebase -i HEAD~3
```

编辑器中会显示：
```
pick abc1234 第一个提交
pick def5678 第二个提交
pick ghi9012 第三个提交
```

可用命令：
- `pick` (p): 保留提交
- `reword` (r): 修改提交信息
- `edit` (e): 修改提交内容
- `squash` (s): 合并到前一个提交
- `fixup` (f): 合并到前一个提交（丢弃提交信息）
- `drop` (d): 删除提交

**rebase vs merge：**

| 操作 | 优点 | 缺点 |
|------|------|------|
| **merge** | 保留完整历史，安全 | 历史复杂，有合并节点 |
| **rebase** | 历史线性清晰 | 重写提交历史，可能丢失信息 |

**黄金法则：**
> 永远不要对已经推送到公共仓库的提交执行 rebase！

### 9.2 git stash（暂存工作）

**什么是 stash？**

临时保存当前工作目录的修改，以便切换分支或进行其他操作。

**基本用法：**
```bash
# 暂存当前修改
git stash

# 查看暂存列表
git stash list
# 输出示例: stash@{0}: WIP on feature: abc1234 添加新功能

# 恢复最近的暂存（并删除）
git stash pop

# 恢复暂存（不删除）
git stash apply

# 恢复指定的暂存
git stash apply stash@{1}

# 删除指定暂存
git stash drop stash@{0}

# 清除所有暂存
git stash clear

# 查看暂存内容
git stash show stash@{0}
```

**高级用法：**
```bash
# 暂存时添加描述
git stash push -m "未完成的功能开发"

# 暂存指定文件
git stash push 文件1 文件2

# 创建一个包含暂存内容的分支
git stash branch 新分支名
```

### 9.3 .gitignore 高级配置

**基本语法：**
```gitignore
# 注释（以 # 开头）
*.log        # 忽略所有 .log 文件
build/       # 忽略 build 目录
!.gitkeep    # 不忽略 .gitkeep 文件（用于保持空目录）
```

**常用配置模式：**
```gitignore
# 编译产物
*.o
*.obj
*.exe
build/
dist/
bin/

# IDE 配置
.vscode/
.idea/
*.swp
*.swo

# 操作系统文件
.DS_Store
Thumbs.db
*.tmp

# 依赖目录
node_modules/
vendor/

# 日志和缓存
*.log
*.cache
*.pid

# 特定文件
.env
.secrets
```

**全局 .gitignore：**
```bash
# 创建全局忽略文件
git config --global core.excludesfile ~/.gitignore_global

# 编辑全局忽略文件
nano ~/.gitignore_global
```

**匹配规则详解：**
```gitignore
pattern        # 匹配所有目录下的该模式
/pattern       # 只匹配根目录下的该模式
pattern/       # 只匹配目录
!pattern       # 取反（不忽略）
**/pattern     # 匹配任意深度的目录
pattern/**     # 匹配目录下的所有内容
```

### 9.4 git cherry-pick（挑选提交）

**什么是 cherry-pick？**

将指定的提交应用到当前分支。

**基本用法：**
```bash
# 挑选单个提交
git cherry-pick 提交哈希

# 挑选多个提交
git cherry-pick 提交1 提交2 提交3

# 交互式挑选
git cherry-pick --no-commit 提交哈希
# 修改后手动提交
git commit
```

**常见场景：**
- 将 hotfix 从一个分支应用到另一个分支
- 从其他分支获取特定的修复

### 9.5 git tag（标签管理）

**什么是标签？**

用于标记特定的提交（如版本发布）。

**创建标签：**
```bash
# 创建轻量标签（仅包含提交引用）
git tag v1.0.0

# 创建附注标签（包含详细信息）
git tag -a v1.0.0 -m "版本 1.0.0 发布"

# 为指定提交创建标签
git tag -a v1.0.0 提交哈希
```

**查看标签：**
```bash
# 列出所有标签
git tag

# 按模式筛选
git tag -l "v1.*"

# 查看标签详情
git show v1.0.0
```

**推送标签：**
```bash
# 推送单个标签
git push origin v1.0.0

# 推送所有标签
git push origin --tags
```

**删除标签：**
```bash
# 删除本地标签
git tag -d v1.0.0

# 删除远程标签
git push origin :v1.0.0
```

### 9.6 git fetch vs git pull

| 命令 | 说明 |
|------|------|
| `git fetch` | 下载远程更新到本地，但不合并 |
| `git pull` | 下载远程更新并合并到当前分支（fetch + merge） |

**使用场景：**
```bash
# 只想查看远程更新，不立即合并
git fetch origin
git diff origin/main

# 直接拉取并合并
git pull origin main

# 拉取后变基（保持线性历史）
git pull --rebase origin main
```

### 9.7 撤销操作

**撤销工作区修改：**
```bash
# 恢复单个文件
git checkout -- 文件名

# 恢复所有文件
git checkout .
```

**撤销暂存：**
```bash
git reset HEAD 文件名
```

**修改最后一次提交：**
```bash
# 修改提交信息
git commit --amend

# 添加遗漏的文件
git add 遗漏的文件
git commit --amend --no-edit
```

**回退提交：**
```bash
# 回退但保留修改（软重置）
git reset --soft HEAD~1

# 回退到指定提交（硬重置，慎用！）
git reset --hard 提交哈希
```

---

## 十、常用 Git 命令参数速查

### 10.1 git status 参数

```bash
git status              # 查看当前状态
git status -s           # 简洁模式（短格式输出）
git status -b           # 显示分支信息
git status --ignored    # 显示被忽略的文件
```

### 10.2 git add 参数

```bash
git add 文件名           # 添加指定文件
git add .               # 添加当前目录所有文件
git add -A              # 添加所有文件（包括删除的）
git add -u              # 只添加已跟踪的修改文件
git add -p              # 交互式添加（逐块选择）
```

### 10.3 git commit 参数

```bash
git commit -m "信息"     # 直接指定提交信息
git commit              # 打开编辑器编写提交信息
git commit -a           # 添加所有已跟踪文件并提交
git commit -am "信息"    # 组合：添加已跟踪文件 + 提交信息
git commit --amend      # 修改最后一次提交（追加修改）
git commit --no-verify  # 跳过提交前钩子检查
```

### 10.4 git log 参数

```bash
git log                 # 完整提交历史
git log --oneline       # 简洁显示（每行一个提交）
git log -n              # 显示最近 n 个提交（如 -5）
git log --graph         # 带图形显示分支结构
git log --all           # 显示所有分支的历史
git log --merges        # 只显示合并提交
git log --author="名字"  # 按作者筛选
git log --since="日期"   # 按时间筛选（如 --since="2026-01-01"）
git log --until="日期"   # 按时间筛选（如 --until="2026-06-06"）
git log -p              # 显示每次提交的差异
git log --stat          # 显示文件修改统计
```

**常用组合：**
```bash
git log --oneline --graph --all    # 最常用的查看方式
git log --oneline -5               # 最近 5 个提交
git log --oneline --author="CHICK-GU"  # 查看自己的提交
```

### 10.5 git branch 参数

```bash
git branch              # 查看本地分支
git branch -a           # 查看所有分支（包括远程）
git branch -r           # 只查看远程分支
git branch 分支名        # 创建新分支
git branch -d 分支名     # 删除已合并的分支
git branch -D 分支名     # 强制删除分支（未合并也可删除）
git branch -m 新名       # 重命名当前分支
git branch -m 旧名 新名   # 重命名指定分支
git branch -v            # 显示分支及最后一次提交
git branch --merged      # 显示已合并到当前分支的分支
git branch --no-merged   # 显示未合并的分支
```

### 10.6 git checkout 参数

```bash
git checkout 分支名      # 切换分支
git checkout -b 新分支名  # 创建并切换到新分支
git checkout 文件名       # 恢复文件到最新提交状态
git checkout -- 文件名    # 恢复文件（显式指定）
git checkout HEAD 文件名  # 恢复文件到 HEAD 状态
git checkout 提交哈希     # 切换到指定提交（游离状态）
```

### 10.7 git merge 参数

```bash
git merge 分支名         # 合并分支
git merge --no-ff 分支名  # 禁用快进合并（创建合并提交）
git merge --ff-only 分支名 # 只允许快进合并
git merge --abort        # 取消正在进行的合并
git merge --continue     # 解决冲突后继续合并
```

### 10.8 git push 参数

```bash
git push                 # 推送到上游分支
git push origin 分支名    # 推送到指定远程分支
git push -u origin 分支名 # 推送并设置上游分支
git push --force         # 强制推送（覆盖远程历史）
git push --force-with-lease # 安全强制推送
git push --all           # 推送所有分支
git push --tags          # 推送所有标签
git push origin --delete 分支名 # 删除远程分支
```

### 10.9 git pull 参数

```bash
git pull                 # 拉取并合并
git pull origin 分支名    # 拉取指定远程分支
git pull --rebase        # 拉取后变基（而非合并）
git pull --ff-only       # 只允许快进合并
```

### 10.10 git remote 参数

```bash
git remote               # 显示远程仓库名
git remote -v            # 显示远程仓库详细信息
git remote add origin URL # 添加远程仓库
git remote remove origin  # 删除远程仓库
git remote set-url origin URL # 修改远程仓库地址
git remote rename 旧名 新名 # 重命名远程仓库
```

### 10.11 git diff 参数

```bash
git diff                 # 查看未暂存的修改
git diff --staged        # 查看已暂存的修改
git diff --cached        # 同 --staged
git diff HEAD            # 查看与 HEAD 的差异
git diff 分支1 分支2      # 比较两个分支
git diff 提交1 提交2      # 比较两个提交
git diff --stat          # 只显示统计信息
git diff --name-only     # 只显示修改的文件名
```

### 10.12 git show 参数

```bash
git show                 # 显示最后一次提交
git show 提交哈希         # 显示指定提交
git show 提交哈希:文件名   # 显示指定提交中的文件内容
```

### 10.13 git reset 参数

```bash
git reset 文件名          # 取消暂存（保留修改）
git reset --hard         # 重置到 HEAD（丢弃所有修改）
git reset --soft         # 重置到 HEAD（保留修改在暂存区）
git reset --mixed        # 重置到 HEAD（保留修改在工作区）
git reset HEAD~n         # 回退 n 个提交
```

### 10.14 git restore 参数（Git 2.23+）

```bash
git restore 文件名        # 恢复工作区文件
git restore --staged 文件名 # 取消暂存
git restore --source=HEAD 文件名 # 从 HEAD 恢复
```

### 10.15 git stash 参数

```bash
git stash                # 暂存当前修改
git stash list           # 查看暂存列表
git stash pop            # 恢复并删除暂存
git stash apply          # 恢复但不删除暂存
git stash drop           # 删除暂存
git stash clear          # 清除所有暂存
```

---

## 十一、推荐资源

- **官方文档**: docs.github.com
- **Git 官方文档**: git-scm.com/doc
- **GitHub Skills**: skills.github.com（官方交互教程）
- **Learn Git Branching**: learngitbranching.js.org（可视化学习）

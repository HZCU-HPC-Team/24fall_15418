# 作业提交说明

## 1. 仓库结构

本仓库用于本次作业的代码提交，请按照以下步骤进行操作。

## 2. 提交步骤

### 2.1 Fork 仓库

首先，请 fork 此仓库到你自己的 GitHub 账户中。

### 2.2 Clone 仓库

将 fork 后的仓库 clone 到本地：

```bash
git clone https://github.com/你的GitHub用户名/仓库名.git
```

### 2.3 创建自己的分支

请使用以下命令创建一个以你名字拼音为标识的分支（例如：`li_ming`），确保每个人的分支命名唯一：

```bash
git checkout -b 你的名字拼音
```

### 2.4 提交作业代码

在你的分支中，将你的作业代码添加到指定的文件夹中，并使用以下命令提交你的更改：

```bash
git add .
git commit -m "提交作业: 姓名"
```

### 2.5 Push 到远程仓库

将你的本地分支 push 到 GitHub 远程仓库：

```bash
git push origin 你的名字拼音
```

### 2.6 提交 Pull Request

在 GitHub 上向主仓库提交 Pull Request，请确保你选择的是你自己创建的分支，并在 Pull Request 的描述中注明你的姓名。

## 3. 注意事项

- **请不要直接推送到主分支（master/main）**，所有提交应当通过 Pull Request 的方式进行。
- 确保提交的代码符合作业要求，所有文件必须放置在指定的文件夹内。

## 4. 其他

如果有任何问题，请联系助教或在项目的 Issue 中提出。
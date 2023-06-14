#include "ui.h"
#include "user.h"
#include "question.h"
#include "result.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

User inputUser()
{
    User user;
    printf("请输入用户名：");
    cin >> user.username;
    printf("请输入年级：");
    cin >> user.grade;
    printf("请输入学校：");
    cin >> user.school;
    return user;
}

User loginOrSignup(vector<User> &users)
{
    while (true)
    {
        cout << "欢迎使用数学口算比赛系统！" << endl;
        cout << "1.登录" << endl;
        cout << "2.注册" << endl;
        int c;
        cout << "请输入选项：";
        cin >> c;

        if (c == 1)
        {
            string name;
            cout << "请输入用户名：";
            cin >> name;
            for (size_t i = 0; i < users.size(); ++i)
            {
                User &u = users[i];
                if (u.username == name)
                {
                    cout << "登录成功 " << u.username << endl;
                    return u;
                }
            }
            cout << "未找到该用户" << endl;
        }
        else if (c == 2)
        {
            // 创建 User 对象，并设置相关属性
            User user = inputUser();
            cout << "用户注册成功 " << user.username << endl;
            users.push_back(user);
        }
        else
        {
            cout << "无效的选项，请重新输入" << endl;
            continue;
        }
    }
}

void displayMainMenu()
{
    printf("欢迎使用数学口算比赛系统！\n");
    printf("1. 开始比赛\n");
    printf("2. 查看比赛结果\n");
    printf("3. 查看个人历史比赛结果\n");
    printf("4. 单次比赛中，以学校为单位查看学校总成绩\n");
    printf("5. 设置参赛者年级难度级别\n");
    printf("6. 设置每题的答题时间\n");
    printf("0. 退出\n");
}

Result startCompetition(vector<Question> questions)
{
    int score = 0;
    time_t startTime = time(NULL); // 记录开始时间

    for (int i = 0; i < questions.size(); i++)
    {
        clearScreen();
        printf("===== 四则简单运算比赛 =====\n");
        cout <<"每题做对得5分，做错扣5分，当前得分" << score << endl; 

        Question &q = questions[i];
        cout << "题目 [" << i + 1 << "] " << q.expr << endl;
        printf("请输入答案：");
        int userAnswer;
        cin >> userAnswer;

        if (q.result == userAnswer)
        {
            score += 5; // 做对一题加5分
        }
        else
        {
            score -= 5; // 做错一题减5分
            cout << "正确答案是 " << q.result << endl;
        }

        getchar();
        getchar();
    }

    time_t endTime = time(NULL);                         // 记录结束时间
    int elapsedTime = (int)difftime(endTime, startTime); // 计算耗时时间

    printf("===== 四则简单运算比赛结束 =====\n");
    printf("本轮得分：%d\n", score);
    printf("本轮耗时：%d秒\n\n", elapsedTime);

    return Result(score, elapsedTime);
}

void startCompetition()
{
    int questionNumber = 5;
    int totalScore = 0;
    int totalTime = 0;

    vector<Question> simple = generateSimpleQuestions(questionNumber);
    Result resultSimple = startCompetition(simple);

    vector<Question> mixed = generateMixedQuestions(questionNumber);
    Result resultMixed = startCompetition(mixed);

    Result total = resultSimple + resultMixed;

    printf("比赛结束！\n");
    printf("总得分：%d\n", total.score);
    printf("总耗时：%d秒\n", total.elapsedTime);
}

void viewResults()
{
    printf("查看比赛结果！\n");
    // 调用结果模块的函数来显示比赛结果
    displayResult();
    printf("\n按任意键返回主菜单...");
    getchar();
    getchar();
}

void viewPersonalHistory()
{
    printf("查看个人历史比赛结果！\n");
    // 调用结果模块的函数来显示个人历史比赛结果
    displayPersonalHistory();
    printf("\n按任意键返回主菜单...");
    getchar();
    getchar();
}

void viewSchoolResults()
{
    printf("单次比赛中，以学校为单位查看学校总成绩！\n");
    // 调用结果模块的函数来显示学校总成绩和排名
    displaySchoolResults();
    printf("\n按任意键返回主菜单...");
    getchar();
    getchar();
}

void setDifficultyLevel()
{
    printf("设置参赛者年级难度级别！\n");
    // 调用用户模块的函数来设置参赛者年级难度级别
    printf("\n按任意键返回主菜单...");
    getchar();
    getchar();
}

void setQuestionTime()
{
    printf("设置每题的答题时间！\n");
    // 调用比赛模块的函数来设置每题的答题时间
    printf("\n按任意键返回主菜单...");
    getchar();
    getchar();
}

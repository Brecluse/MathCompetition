#include "ui.h"
#include "user.h"
#include "question.h"
#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

User inputUser() {
  User user;
  printf("请输入用户名：");
  cin >> user.username;
  printf("请输入年级：");
  cin >> user.grade;
  cin.ignore();
  printf("请输入学校：");
  cin >> user.school;
  return user;
}

User loginOrSignup(vector<User> &users) {
  while (true) {
    cout << "欢迎使用数学口算比赛系统！" << endl;
    cout << "1.登录" << endl;
    cout << "2.注册" << endl;
    int c;
    cout << "请输入选项：";
    cin >> c;
    cin.ignore();

    if (c == 1) {
      string name;
      cout << "请输入用户名：";
      cin >> name;
      for (int i = 0; i < users.size(); ++i) {
        User &u = users[i];
        if (u.username == name) {
          cout << "登录成功 " << u.username << endl;
          return u;
        }
      }
      cout << "未找到该用户" << endl;
    } else if (c == 2) {
      // 创建 User 对象，并设置相关属性
      User user = inputUser();
      cout << "用户注册成功 " << user.username << endl;
      users.push_back(user);
    } else {
      cout << "无效的选项，请重新输入" << endl;
      continue;
    }
  }
}

void displayMainMenu() {
  cout << "欢迎使用数学口算比赛系统！" << endl;
  cout << "1. 开始比赛" << endl;
  cout << "2. 查看个人历史比赛结果" << endl;
  cout << "0. 退出" << endl;
}

Record startCompetition(vector<Question> &questions) {
  int score = 0;
  time_t startTime = time(NULL); // 记录开始时间

  vector<QuestionRecord> answered;
  for (int i = 0; i < questions.size(); i++) {
    clearScreen();
    printf("===== 四则简单运算比赛 =====\n");
    cout << "每题做对得5分，做错扣5分，当前得分 " << score << endl;

    Question &q = questions[i];
    cout << "题目 [" << i + 1 << "] " << q.expr << endl;
    printf("请输入答案：");
    int userAnswer;
    cin >> userAnswer;
    cin.ignore();

    if (q.result == userAnswer) {
      score += 5; // 做对一题加5分
      answered.push_back(QuestionRecord(q, true));
    } else {
      score -= 5; // 做错一题减5分
      cout << "正确答案是 " << q.result << endl;
      answered.push_back(QuestionRecord(q, true));
    }
  }

  time_t endTime = time(NULL);                         // 记录结束时间
  int elapsedTime = (int) difftime(endTime, startTime); // 计算耗时时间

  printf("===== 四则简单运算比赛结束 =====\n");
  printf("本轮得分：%d\n", score);
  printf("本轮耗时：%d秒\n\n", elapsedTime);

  return Record(score, elapsedTime, answered);
}

void startCompetition(User &user, vector<Record> &results) {
  int questionNumber = 4 + user.grade;

  vector<Question> simple = generateSimpleQuestions(questionNumber);
  Record resultSimple = startCompetition(simple);

  vector<Question> mixed = generateMixedQuestions(questionNumber);
  Record resultMixed = startCompetition(mixed);

  Record total = resultSimple + resultMixed;

  cout << "比赛结束！" << endl;
  cout << "总得分：" << total.score << endl;
  cout << "总耗时：" << total.elapsedTime << "秒" << endl;

  results.push_back(total);
}

void viewPersonalHistory(User &user, vector<Record> &records) {
  if (records.empty()) {
    cout << user.username << " 没有参赛记录。" << endl;
    return;
  }
  // 从文件获取个人历史比赛结果并显示
  cout << user.username << " 的个人历史比赛结果：" << endl;
  for (int i = 0; i < records.size(); i++) {
    Record &r = records[i];
    cout << "比赛[" << i + 1 << "] 得分：" << r.score << " 耗时：" << r.elapsedTime << "秒" << endl;
  }
}

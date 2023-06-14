#include "ui.h"
#include "question.h"
#include "expr.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>

int main() {
  srand(time(NULL));
  vector<User> users;
  User::readFromFile(users, "users.bin");
  User user = loginOrSignup(users);
  User::saveToFile(users, "users.bin");

  while (true) {
    int choice;
    displayMainMenu(); // 显示主菜单
    cout << "请输入选项：";
    cin >> choice;
    if (choice == 0) {
      break;
    }
    switch (choice) {
      case 1:
        startCompetition(); // 开始比赛
        break;
      case 2:
        viewResults(); // 查看比赛结果
        break;
      case 3:
        viewPersonalHistory(); // 查看个人历史比赛结果
        break;
      case 4:
        viewSchoolResults(); // 以学校为单位查看学校总成绩
        break;
      case 5:
        setDifficultyLevel(); // 设置参赛者年级难度级别
        break;
      case 6:
        setQuestionTime(); // 设置每题的答题时间
        break;
      case 0:
        printf("感谢使用数学口算比赛系统！再见！\n");
        break;
      default:
        printf("无效的选项，请重新输入。\n");
        break;
    }

    printf("\n按任意键继续...");
    getchar();
    clearScreen();     // 清空终端显示
  };

  return 0;
}

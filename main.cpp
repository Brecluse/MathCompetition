#include "ui.h"
#include "question.h"
#include "expr.h"
#include "record.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;
const string userStorage = "users.bin";
const string recordStorageDir = "records/";

int main() {
  srand(time(NULL));
  vector<User> users;
  User::readFromFile(users, userStorage);
  User user = loginOrSignup(users);
  User::saveToFile(users, userStorage);
  string recordsPath = recordStorageDir + user.school + "/" + user.username + ".bin";
  fs::create_directories(fs::path(recordsPath).parent_path());
  vector<Record> records;
  Record::readFromFile(records, recordsPath);

  while (true) {
    int choice;
    displayMainMenu(); // 显示主菜单
    cout << "请输入选项：";
    cin >> choice;
    if (choice == 0) {
      printf("感谢使用数学口算比赛系统！再见！\n");
      break;
    }
    switch (choice) {
      case 1:
        startCompetition(records); // 开始比赛
        Record::saveToFile(records, recordsPath);
        break;
      case 2:
        viewPersonalHistory(user, records); // 查看比赛结果
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

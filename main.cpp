#include "ui.h"
#include "question.h"
#include "expr.h"
#include "record.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>

#if defined(_WIN32) || defined(WIN32)

#include <direct.h> // For Windows

#else
#include <sys/stat.h> // For Linux/Unix
#endif

bool createDirectories(const string &path);

const string userStorage = "users.bin";
const string recordStorageDir = "records/";

int main() {
  srand(time(NULL));
  vector<User> users;
  User::readFromFile(users, userStorage);
  User user = loginOrSignup(users);
  User::saveToFile(users, userStorage);
  string recordsPath = recordStorageDir + user.school + "/" + user.username + ".bin";
  createDirectories(recordsPath);
  vector<Record> records;
  Record::readFromFile(records, recordsPath);

  while (true) {
    int choice;
    displayMainMenu(); // 显示主菜单
    cout << "请输入选项：";
    cin >> choice;
    cin.ignore();
    if (choice == 0) {
      printf("感谢使用数学口算比赛系统！再见！\n");
      break;
    }
    switch (choice) {
      case 1:
        startCompetition(user, records); // 开始比赛
        Record::saveToFile(records, recordsPath);
        break;
      case 2:
        viewPersonalHistory(user, records); // 查看比赛结果
        break;
      case 3:
        viewAnswersHistory(user, records); // 查看比赛结果
        break;
      default:
        printf("无效的选项，请重新输入。\n");
        break;
    }

    printf("按任意键继续...");
    getchar();
    getchar();
    clearScreen(); // 清空终端显示
  };

  return 0;
}

bool createDirectories(const string &path) {
  string currentPath;
  for (int i = 0; i < path.length(); ++i) {
    if (path[i] == '/' || path[i] == '\\') {
      currentPath += path[i];
#if defined(_WIN32) || defined(WIN32)
      int status = _mkdir(currentPath.c_str());
#else
      int status = mkdir(currentPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
      if (status != 0 && errno != EEXIST) {
        cerr << "Failed to create directory: " << currentPath << endl;
        return false;
      }
    } else {
      currentPath += path[i];
    }
  }

  return true;
}

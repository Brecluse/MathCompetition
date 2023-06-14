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
    displayMainMenu(); // ��ʾ���˵�
    cout << "������ѡ�";
    cin >> choice;
    if (choice == 0) {
      printf("��лʹ����ѧ�������ϵͳ���ټ���\n");
      break;
    }
    switch (choice) {
      case 1:
        startCompetition(records); // ��ʼ����
        Record::saveToFile(records, recordsPath);
        break;
      case 2:
        viewPersonalHistory(user, records); // �鿴�������
        break;
      default:
        printf("��Ч��ѡ����������롣\n");
        break;
    }

    printf("\n�����������...");
    getchar();
    clearScreen();     // ����ն���ʾ
  };

  return 0;
}

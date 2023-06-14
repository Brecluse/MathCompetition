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
    displayMainMenu(); // ��ʾ���˵�
    cout << "������ѡ�";
    cin >> choice;
    if (choice == 0) {
      break;
    }
    switch (choice) {
      case 1:
        startCompetition(); // ��ʼ����
        break;
      case 2:
        viewResults(); // �鿴�������
        break;
      case 3:
        viewPersonalHistory(); // �鿴������ʷ�������
        break;
      case 4:
        viewSchoolResults(); // ��ѧУΪ��λ�鿴ѧУ�ܳɼ�
        break;
      case 5:
        setDifficultyLevel(); // ���ò������꼶�Ѷȼ���
        break;
      case 6:
        setQuestionTime(); // ����ÿ��Ĵ���ʱ��
        break;
      case 0:
        printf("��лʹ����ѧ�������ϵͳ���ټ���\n");
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

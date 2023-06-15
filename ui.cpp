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
  printf("�������û�����");
  cin >> user.username;
  printf("�������꼶��");
  cin >> user.grade;
  cin.ignore();
  printf("������ѧУ��");
  cin >> user.school;
  return user;
}

User loginOrSignup(vector<User> &users) {
  while (true) {
    cout << "��ӭʹ����ѧ�������ϵͳ��" << endl;
    cout << "1.��¼" << endl;
    cout << "2.ע��" << endl;
    int c;
    cout << "������ѡ�";
    cin >> c;
    cin.ignore();

    if (c == 1) {
      string name;
      cout << "�������û�����";
      cin >> name;
      for (int i = 0; i < users.size(); ++i) {
        User &u = users[i];
        if (u.username == name) {
          cout << "��¼�ɹ� " << u.username << endl;
          return u;
        }
      }
      cout << "δ�ҵ����û�" << endl;
    } else if (c == 2) {
      // ���� User ���󣬲������������
      User user = inputUser();
      cout << "�û�ע��ɹ� " << user.username << endl;
      users.push_back(user);
    } else {
      cout << "��Ч��ѡ�����������" << endl;
      continue;
    }
  }
}

void displayMainMenu() {
  cout << "��ӭʹ����ѧ�������ϵͳ��" << endl;
  cout << "1. ��ʼ����" << endl;
  cout << "2. �鿴������ʷ�������" << endl;
  cout << "0. �˳�" << endl;
}

Record startCompetition(vector<Question> &questions) {
  int score = 0;
  time_t startTime = time(NULL); // ��¼��ʼʱ��

  vector<QuestionRecord> answered;
  for (int i = 0; i < questions.size(); i++) {
    clearScreen();
    printf("===== ������������ =====\n");
    cout << "ÿ�����Ե�5�֣������5�֣���ǰ�÷� " << score << endl;

    Question &q = questions[i];
    cout << "��Ŀ [" << i + 1 << "] " << q.expr << endl;
    printf("������𰸣�");
    int userAnswer;
    cin >> userAnswer;
    cin.ignore();

    if (q.result == userAnswer) {
      score += 5; // ����һ���5��
      answered.push_back(QuestionRecord(q, true));
    } else {
      score -= 5; // ����һ���5��
      cout << "��ȷ���� " << q.result << endl;
      answered.push_back(QuestionRecord(q, true));
    }
  }

  time_t endTime = time(NULL);                         // ��¼����ʱ��
  int elapsedTime = (int) difftime(endTime, startTime); // �����ʱʱ��

  printf("===== ���������������� =====\n");
  printf("���ֵ÷֣�%d\n", score);
  printf("���ֺ�ʱ��%d��\n\n", elapsedTime);

  return Record(score, elapsedTime, answered);
}

void startCompetition(User &user, vector<Record> &results) {
  int questionNumber = 4 + user.grade;

  vector<Question> simple = generateSimpleQuestions(questionNumber);
  Record resultSimple = startCompetition(simple);

  vector<Question> mixed = generateMixedQuestions(questionNumber);
  Record resultMixed = startCompetition(mixed);

  Record total = resultSimple + resultMixed;

  cout << "����������" << endl;
  cout << "�ܵ÷֣�" << total.score << endl;
  cout << "�ܺ�ʱ��" << total.elapsedTime << "��" << endl;

  results.push_back(total);
}

void viewPersonalHistory(User &user, vector<Record> &records) {
  if (records.empty()) {
    cout << user.username << " û�в�����¼��" << endl;
    return;
  }
  // ���ļ���ȡ������ʷ�����������ʾ
  cout << user.username << " �ĸ�����ʷ���������" << endl;
  for (int i = 0; i < records.size(); i++) {
    Record &r = records[i];
    cout << "����[" << i + 1 << "] �÷֣�" << r.score << " ��ʱ��" << r.elapsedTime << "��" << endl;
  }
}

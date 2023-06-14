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
    printf("�������û�����");
    cin >> user.username;
    printf("�������꼶��");
    cin >> user.grade;
    printf("������ѧУ��");
    cin >> user.school;
    return user;
}

User loginOrSignup(vector<User> &users)
{
    while (true)
    {
        cout << "��ӭʹ����ѧ�������ϵͳ��" << endl;
        cout << "1.��¼" << endl;
        cout << "2.ע��" << endl;
        int c;
        cout << "������ѡ�";
        cin >> c;

        if (c == 1)
        {
            string name;
            cout << "�������û�����";
            cin >> name;
            for (size_t i = 0; i < users.size(); ++i)
            {
                User &u = users[i];
                if (u.username == name)
                {
                    cout << "��¼�ɹ� " << u.username << endl;
                    return u;
                }
            }
            cout << "δ�ҵ����û�" << endl;
        }
        else if (c == 2)
        {
            // ���� User ���󣬲������������
            User user = inputUser();
            cout << "�û�ע��ɹ� " << user.username << endl;
            users.push_back(user);
        }
        else
        {
            cout << "��Ч��ѡ�����������" << endl;
            continue;
        }
    }
}

void displayMainMenu()
{
    printf("��ӭʹ����ѧ�������ϵͳ��\n");
    printf("1. ��ʼ����\n");
    printf("2. �鿴�������\n");
    printf("3. �鿴������ʷ�������\n");
    printf("4. ���α����У���ѧУΪ��λ�鿴ѧУ�ܳɼ�\n");
    printf("5. ���ò������꼶�Ѷȼ���\n");
    printf("6. ����ÿ��Ĵ���ʱ��\n");
    printf("0. �˳�\n");
}

Result startCompetition(vector<Question> questions)
{
    int score = 0;
    time_t startTime = time(NULL); // ��¼��ʼʱ��

    for (int i = 0; i < questions.size(); i++)
    {
        clearScreen();
        printf("===== ������������ =====\n");
        cout <<"ÿ�����Ե�5�֣������5�֣���ǰ�÷�" << score << endl; 

        Question &q = questions[i];
        cout << "��Ŀ [" << i + 1 << "] " << q.expr << endl;
        printf("������𰸣�");
        int userAnswer;
        cin >> userAnswer;

        if (q.result == userAnswer)
        {
            score += 5; // ����һ���5��
        }
        else
        {
            score -= 5; // ����һ���5��
            cout << "��ȷ���� " << q.result << endl;
        }

        getchar();
        getchar();
    }

    time_t endTime = time(NULL);                         // ��¼����ʱ��
    int elapsedTime = (int)difftime(endTime, startTime); // �����ʱʱ��

    printf("===== ���������������� =====\n");
    printf("���ֵ÷֣�%d\n", score);
    printf("���ֺ�ʱ��%d��\n\n", elapsedTime);

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

    printf("����������\n");
    printf("�ܵ÷֣�%d\n", total.score);
    printf("�ܺ�ʱ��%d��\n", total.elapsedTime);
}

void viewResults()
{
    printf("�鿴���������\n");
    // ���ý��ģ��ĺ�������ʾ�������
    displayResult();
    printf("\n��������������˵�...");
    getchar();
    getchar();
}

void viewPersonalHistory()
{
    printf("�鿴������ʷ���������\n");
    // ���ý��ģ��ĺ�������ʾ������ʷ�������
    displayPersonalHistory();
    printf("\n��������������˵�...");
    getchar();
    getchar();
}

void viewSchoolResults()
{
    printf("���α����У���ѧУΪ��λ�鿴ѧУ�ܳɼ���\n");
    // ���ý��ģ��ĺ�������ʾѧУ�ܳɼ�������
    displaySchoolResults();
    printf("\n��������������˵�...");
    getchar();
    getchar();
}

void setDifficultyLevel()
{
    printf("���ò������꼶�Ѷȼ���\n");
    // �����û�ģ��ĺ��������ò������꼶�Ѷȼ���
    printf("\n��������������˵�...");
    getchar();
    getchar();
}

void setQuestionTime()
{
    printf("����ÿ��Ĵ���ʱ�䣡\n");
    // ���ñ���ģ��ĺ���������ÿ��Ĵ���ʱ��
    printf("\n��������������˵�...");
    getchar();
    getchar();
}

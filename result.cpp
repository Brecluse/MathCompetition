#include "result.h"
#include <stdio.h>
#include <stdlib.h>

void updateResult(int score, int elapsedTime) {
    Result result;
    result.score = score;
    result.elapsedTime = elapsedTime;

    // ��������浽�ļ������ݿ���
    saveResult(result);
}

void displayResult() {
    // ���ļ������ݿ��л�ȡ�������ʾ
    Result result = loadResult();

    printf("���������\n");
    printf("�÷֣�%d\n", result.score);
    printf("��ʱ��%d��\n", result.elapsedTime);
}

void displayPersonalHistory() {
    // ���ļ������ݿ��л�ȡ������ʷ�����������ʾ
    Result* results = loadPersonalResults();
    int count = getPersonalResultsCount();

    printf("������ʷ���������\n");
    for (int i = 0; i < count; i++) {
        printf("���� %d��\n", i + 1);
        printf("�÷֣�%d\n", results[i].score);
        printf("��ʱ��%d��\n", results[i].elapsedTime);
        printf("\n");
    }

    // �ͷ��ڴ�
    free(results);
}

void displaySchoolResults() {
    // ���ļ������ݿ��л�ȡѧУ�ܳɼ�����ʾ
    SchoolResult* schoolResults = loadSchoolResults();
    int count = getSchoolResultsCount();

    printf("ѧУ�ܳɼ���\n");
    for (int i = 0; i < count; i++) {
        printf("ѧУ %s��\n", schoolResults[i].school);
        printf("�ܷ֣�%d\n", schoolResults[i].totalScore);
        printf("ƽ����ʱ��%d��\n", schoolResults[i].averageTime);
        printf("\n");
    }

    // �ͷ��ڴ�
    free(schoolResults);
}

void saveResult(Result result) {
    // ��������浽�ļ������ݿ���
    // ������ʾ��ʵ�֣�����Ը���ʵ�����������Ӧ�Ĵ���
    FILE* file;
	file = fopen("result.txt", "w");
    if (file == NULL) {
        printf("�޷����ļ����б��棡\n");
        return;
    }

    fprintf(file, "%d\n%d\n", result.score, result.elapsedTime);

    fclose(file);
}

Result loadResult() {
    Result result;
    // ���ļ������ݿ��м��ؽ��
    // ������ʾ��ʵ�֣�����Ը���ʵ�����������Ӧ�Ĵ���
    FILE* file;
	file = fopen("result.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ����м��أ�\n");
        result.score = 0;
        result.elapsedTime = 0;
        return result;
    }

    fscanf(file, "%d", &result.score);
    fscanf(file, "%d", &result.elapsedTime);

    fclose(file);

    return result;
}

Result* loadPersonalResults() {
    Result* results = NULL;
    int count = 0;

    // ���ļ������ݿ��м��ظ�����ʷ�������
    // ������ʾ��ʵ�֣�����Ը���ʵ�����������Ӧ�Ĵ���

    // ���������ʷ���������������Ϊ "personal_results.txt" ���ı��ļ���
    FILE* file;
	file = fopen("personal_results.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ����м��أ�\n");
        return NULL;
    }

    // ��ȡ�������
    fscanf(file, "%d", &count);
    if (count <= 0) {
        printf("����Ч����ɼ��أ�\n");
        fclose(file);
        return NULL;
    }

    // ����洢������ڴ�
    results = (Result*)malloc(count * sizeof(Result));
    if (results == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        fclose(file);
        return NULL;
    }

    // ���ؽ������
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d", &results[i].score);
        fscanf(file, "%d", &results[i].elapsedTime);
    }

    fclose(file);

    return results;
}

int getPersonalResultsCount() {
    int count = 0;

    // ���ļ������ݿ��л�ȡ������ʷ�������������
    // ������ʾ��ʵ�֣�����Ը���ʵ�����������Ӧ�Ĵ���

    // ���������ʷ�������������������Ϊ "personal_results_count.txt" ���ı��ļ���
    FILE* file = fopen("personal_results_count.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ����м��أ�\n");
        return 0;
    }

    fscanf(file, "%d", &count);

    fclose(file);

    return count;
}

SchoolResult* loadSchoolResults() {
    SchoolResult* schoolResults = NULL;
    int count = 0;

    // ���ļ������ݿ��м���ѧУ�ܳɼ�
    // ������ʾ��ʵ�֣�����Ը���ʵ�����������Ӧ�Ĵ���

    // ����ѧУ�ܳɼ���������Ϊ "school_results.txt" ���ı��ļ���
    FILE* file = fopen("school_results.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ����м��أ�\n");
        return NULL;
    }

    // ��ȡ�������
    fscanf(file, "%d", &count);
    if (count <= 0) {
        printf("����Ч����ɼ��أ�\n");
        fclose(file);
        return NULL;
    }

    // ����洢������ڴ�
    schoolResults = (SchoolResult*)malloc(count * sizeof(SchoolResult));
    if (schoolResults == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        fclose(file);
        return NULL;
    }

    // ���ؽ������
    for (int i = 0; i < count; i++) {
        fscanf(file, "%s", schoolResults[i].school);
        fscanf(file, "%d", &schoolResults[i].totalScore);
        fscanf(file, "%d", &schoolResults[i].averageTime);
    }

    fclose(file);

    return schoolResults;
}

int getSchoolResultsCount() {
    int count = 0;

    // ���ļ������ݿ��л�ȡѧУ�ܳɼ�������
    // ������ʾ��ʵ�֣�����Ը���ʵ�����������Ӧ�Ĵ���

    // ����ѧУ�ܳɼ�������������Ϊ "school_results_count.txt" ���ı��ļ���
    FILE* file = fopen("school_results_count.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ����м��أ�\n");
        return 0;
    }

    fscanf(file, "%d", &count);

    fclose(file);

    return count;
}

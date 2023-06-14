#include "result.h"
#include <stdio.h>
#include <stdlib.h>

void updateResult(int score, int elapsedTime) {
    Result result;
    result.score = score;
    result.elapsedTime = elapsedTime;

    // 将结果保存到文件或数据库中
    saveResult(result);
}

void displayResult() {
    // 从文件或数据库中获取结果并显示
    Result result = loadResult();

    printf("比赛结果：\n");
    printf("得分：%d\n", result.score);
    printf("耗时：%d秒\n", result.elapsedTime);
}

void displayPersonalHistory() {
    // 从文件或数据库中获取个人历史比赛结果并显示
    Result* results = loadPersonalResults();
    int count = getPersonalResultsCount();

    printf("个人历史比赛结果：\n");
    for (int i = 0; i < count; i++) {
        printf("比赛 %d：\n", i + 1);
        printf("得分：%d\n", results[i].score);
        printf("耗时：%d秒\n", results[i].elapsedTime);
        printf("\n");
    }

    // 释放内存
    free(results);
}

void displaySchoolResults() {
    // 从文件或数据库中获取学校总成绩并显示
    SchoolResult* schoolResults = loadSchoolResults();
    int count = getSchoolResultsCount();

    printf("学校总成绩：\n");
    for (int i = 0; i < count; i++) {
        printf("学校 %s：\n", schoolResults[i].school);
        printf("总分：%d\n", schoolResults[i].totalScore);
        printf("平均耗时：%d秒\n", schoolResults[i].averageTime);
        printf("\n");
    }

    // 释放内存
    free(schoolResults);
}

void saveResult(Result result) {
    // 将结果保存到文件或数据库中
    // 这里是示例实现，你可以根据实际需求进行相应的处理
    FILE* file;
	file = fopen("result.txt", "w");
    if (file == NULL) {
        printf("无法打开文件进行保存！\n");
        return;
    }

    fprintf(file, "%d\n%d\n", result.score, result.elapsedTime);

    fclose(file);
}

Result loadResult() {
    Result result;
    // 从文件或数据库中加载结果
    // 这里是示例实现，你可以根据实际需求进行相应的处理
    FILE* file;
	file = fopen("result.txt", "r");
    if (file == NULL) {
        printf("无法打开文件进行加载！\n");
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

    // 从文件或数据库中加载个人历史比赛结果
    // 这里是示例实现，你可以根据实际需求进行相应的处理

    // 假设个人历史比赛结果保存在名为 "personal_results.txt" 的文本文件中
    FILE* file;
	file = fopen("personal_results.txt", "r");
    if (file == NULL) {
        printf("无法打开文件进行加载！\n");
        return NULL;
    }

    // 获取结果数量
    fscanf(file, "%d", &count);
    if (count <= 0) {
        printf("无有效结果可加载！\n");
        fclose(file);
        return NULL;
    }

    // 分配存储结果的内存
    results = (Result*)malloc(count * sizeof(Result));
    if (results == NULL) {
        printf("内存分配失败！\n");
        fclose(file);
        return NULL;
    }

    // 加载结果数据
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d", &results[i].score);
        fscanf(file, "%d", &results[i].elapsedTime);
    }

    fclose(file);

    return results;
}

int getPersonalResultsCount() {
    int count = 0;

    // 从文件或数据库中获取个人历史比赛结果的数量
    // 这里是示例实现，你可以根据实际需求进行相应的处理

    // 假设个人历史比赛结果数量保存在名为 "personal_results_count.txt" 的文本文件中
    FILE* file = fopen("personal_results_count.txt", "r");
    if (file == NULL) {
        printf("无法打开文件进行加载！\n");
        return 0;
    }

    fscanf(file, "%d", &count);

    fclose(file);

    return count;
}

SchoolResult* loadSchoolResults() {
    SchoolResult* schoolResults = NULL;
    int count = 0;

    // 从文件或数据库中加载学校总成绩
    // 这里是示例实现，你可以根据实际需求进行相应的处理

    // 假设学校总成绩保存在名为 "school_results.txt" 的文本文件中
    FILE* file = fopen("school_results.txt", "r");
    if (file == NULL) {
        printf("无法打开文件进行加载！\n");
        return NULL;
    }

    // 获取结果数量
    fscanf(file, "%d", &count);
    if (count <= 0) {
        printf("无有效结果可加载！\n");
        fclose(file);
        return NULL;
    }

    // 分配存储结果的内存
    schoolResults = (SchoolResult*)malloc(count * sizeof(SchoolResult));
    if (schoolResults == NULL) {
        printf("内存分配失败！\n");
        fclose(file);
        return NULL;
    }

    // 加载结果数据
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

    // 从文件或数据库中获取学校总成绩的数量
    // 这里是示例实现，你可以根据实际需求进行相应的处理

    // 假设学校总成绩数量保存在名为 "school_results_count.txt" 的文本文件中
    FILE* file = fopen("school_results_count.txt", "r");
    if (file == NULL) {
        printf("无法打开文件进行加载！\n");
        return 0;
    }

    fscanf(file, "%d", &count);

    fclose(file);

    return count;
}

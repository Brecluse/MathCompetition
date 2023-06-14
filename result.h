#ifndef RESULT_H
#define RESULT_H

struct Result
{
    int score;
    int elapsedTime;
    explicit Result(int scoreValue = 0, int elapsedTimeValue = 0)
        : score(scoreValue), elapsedTime(elapsedTimeValue) {}

    Result operator+(const Result &other) const
    {
        return Result(score + other.score, elapsedTime + other.elapsedTime);
    }
};

struct SchoolResult
{
    char school[50];
    int totalScore;
    int averageTime;
};

void saveResult(Result result);
Result loadResult();
void savePersonalResult(Result result);
Result *loadPersonalResults();
int getPersonalResultsCount();
void saveSchoolResult(SchoolResult schoolResult);
SchoolResult *loadSchoolResults();
int getSchoolResultsCount();
void updateResult(int score, int elapsedTime);

#endif /* RESULT_H */

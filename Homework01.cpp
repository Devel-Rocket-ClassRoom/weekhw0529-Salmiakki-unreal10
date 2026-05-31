#include <iostream>
#include <string>
#include "Homework01.h"
using namespace std;

bool IsLeapYear(int Year)
{
    return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
}

void Homework01_Run()
{
    int Year, Month, Day;

    cout << "년 월 일 입력 : ";
    cin >> Year >> Month >> Day;

    int TotalDays = 0;

    // 이전 년도들의 일수 더하기
    for (int y = 1; y < Year; y++)
    {
        if (IsLeapYear(y))
            TotalDays += 366;
        else
            TotalDays += 365;
    }

    // 각 달의 일수
    int MonthDays[12] =
    {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    // 이전 달들의 일수 더하기
    for (int m = 1; m < Month; m++)
    {
        TotalDays += MonthDays[m - 1];

        // 윤년 2월 보정
        if (m == 2 && IsLeapYear(Year))
            TotalDays++;
    }

    // 현재 달의 지난 날짜 더하기
    TotalDays += Day - 1;

    string WeekDay[7] =
    {
        "월요일", "화요일", "수요일", "목요일",
        "금요일", "토요일", "일요일"
    };

    cout << WeekDay[TotalDays % 7] << endl;

}
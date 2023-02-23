#include <stdio.h>
#define INITMONTH 4
#define INITDAY 4

void switchWeek(int weekday)
{
    switch (weekday)
    {
    case 0:
        printf("星期天\n");
        break;
    case 1:
        printf("星期一\n");
        break;
    case 2:
        printf("星期二\n");
        break;
    case 3:
        printf("星期三\n");
        break;
    case 4:
        printf("星期四\n");
        break;
    case 5:
        printf("星期五\n");
        break;
    case 6:
        printf("星期六\n");
        break;
    default:
        printf("输入错误\n");
        break;
    }
}

int countD_Day(int difference, int run, int initD_Day)
{
    int result = (difference + run + initD_Day) % 7;
    printf("该年的D-Day是：");
    switchWeek(result);
    return result;
}

int countMonthDay(int month, int run, int countday)
{

    int monthMore[7] = {1, 3, 5, 7, 8, 10, 12};
    int boolean = 0;

    for (unsigned int j = 0; j < sizeof(monthMore) / sizeof(monthMore[0]); j++)
    {
        if (month == monthMore[j])
        {
            boolean = 1;
        }
    }
    if (boolean == 1)
    {
        countday = countday + 31;
    }
    else if (month == 2)
    {
        countday = run == 0 ? countday + 28 : countday + 29;
    }
    else
    {
        countday = countday + 30;
    }
    return countday;
}

int count(int month, int day, int run)
{
    int countday = 0;
    if (month > INITMONTH)
    {
        countday = -INITDAY;
        for (int i = INITMONTH; i < month; i++)
        {
            countday = countMonthDay(i, run, countday);
        }
        countday = countday + day;
    }
    else if (month < INITMONTH)
    {
        countday = INITDAY;
        for (int i = month; i < INITMONTH; i++)
        {
            countday = countMonthDay(i, run, countday);
        }
        countday = countday - day;
    }
    else
    {
        countday = day == INITDAY ? countday : (day > INITDAY ? day - INITDAY : INITDAY - day);
    }
    return countday % 7;
}

int main()
{
    int switchD_Day[4] = {2, 7, 5, 3};
    int endYear, endMonth, endDay, endD_day;

    printf("用于算出具体年月日是星期几\n");
    printf("请输入你要查询的年，月，日（回车分隔）\n");
    scanf("%d", &endYear);
    scanf("%d", &endMonth);
    scanf("%d", &endDay);

    int initYear = endYear / 100 * 100;
    int run = 0;
    if (endYear > initYear)
    {
        for (int i = initYear + 1; i <= endYear; i++)
        {
            if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
            {
                run++;
            }
        }
        endD_day = countD_Day(endYear - initYear, run, switchD_Day[initYear / 100 % 4]);
    }
    else if (endYear == initYear)
    {
        printf("该年的D—Day是");
        switchWeek(switchD_Day[initYear / 100 % 4]);
    }

    run = ((endYear % 4 == 0 && endYear % 100 != 0) || endYear % 400 == 0) ? run++ : 0;

    int result = count(endMonth, endDay, run);
    if (endMonth < INITMONTH)
    {
        result = (endD_day - result + 7) % 7;
    }
    else
    {
        result = (result + endD_day) % 7;
    }

    printf("%d年%d月%d日是", endYear, endMonth, endDay);
    switchWeek(result);
    getchar();
}
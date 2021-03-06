/*
Name:打印任意月的日历
Copyright: Free
Author: Joker Lee
Date: 21-11-21 20:30
Description: 打印任何一个月的日历
 */
#include <stdio.h>
#include <stdlib.h>

int _getWeekDay( int, int, int ); //计算某年某月某日是星期几
int _getMonthDays( int, int ); //计算某年某月有几天
int _getDaysToyear( int, int, int ); //计算某月某日是该年的第几天
void _printMonthCalender( int, int ); //打印日历
int _checkLeap( int ); //判断某年是否为闰年

int main()
{
    int yr, mth, dy; //年月日

    printf( "plese input the date(YYYY-MM):\n" );
    scanf( "%d-%d", &yr, &mth ); //读入年月

    _printMonthCalender( yr, mth ); //调用打印函数

    system( "pause" );
    return 0;
}

//-------------------------------------------------------------------------

int _getMonthDays( int year, int month )
{
    if ( month == 2 )
    {
        //处理2月
        if ( _checkLeap( year ) == 1 )
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else
    {
        switch ( month )
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                //大月
                return 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                //小月
                return 30;
                break;
        }
    }
}

//-------------------------------------------------------------------------


int _getDaysToyear( int year, int month, int day )
{
    int sum = 0, i;

    for ( i = 1; i < month; i++ )
    {
        //循环直到输入的月份
        sum += _getMonthDays( year, i );
    }
    sum += day;
    return sum;
}

//-------------------------------------------------------------------------

int _getWeekDay( int year, int month, int day )
{
    int days = 0, firstDay;

    days = ( year - 1 ) *365+( year - 1 ) / 400+( year - 1 ) / 4-( year - 1 ) /
            100;
    //计算今年以前所有年共有多少天
    days += _getDaysToyear( year, month, day ); //计算某月某日是该年的第几天
    days += day; //总合加上本月已过天数

    return ( days - 1 ) % 7; //返回本日是星期几
}

//-------------------------------------------------------------------------


int _checkLeap( int y )
{
    int isLeap = 0;
    if ( y % 4 == 0 && y % 100 != 0 || y % 400 == 0 )
    {
        isLeap = 1;
    }

    return isLeap;
}

//-------------------------------------------------------------------------

void _printMonthCalender( int year, int month )
{
    int day = 1, firstD, temp;
    //firstD储存某月的一天是星期几;temp控制日历第一行的缩进

    printf( "\t\t\t%d-%d\n", year, month ); //日历标题
    printf( "Sun.\tMon.\tTue.\tWed.\tThu.\tFri.\tSat.\t\n" ); //表头

    firstD = _getWeekDay( year, month, 1 ); //调用函数计算本月第一天是星期几
    temp = firstD;
    while ( day <= _getMonthDays( year, month ))
    {
        //打印本月的每一天
        while ( temp >= 1 )
        {
            //控制第一天前的缩进
            printf( "\t" );
            temp--;
        }
        printf( "%d\t", day );
        if (( firstD + day ) % 7 == 0 )
        //换行控制(周六)
        {
            printf( "\n" );
        }

        day++;
    }
    printf( "\n" );

}

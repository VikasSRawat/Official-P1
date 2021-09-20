#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define max 20
#define LEAP(i) i%400==0||i%4==0&&i%100!=0
int get_code( void )//gets ascii code for the arrow keys
{
    int ch = getch();
    if ( ch == 0 || ch == 224 )
        ch = getch();
    return ch;
}
int getremdaysinyear(int mon,char s[max])//gets the remaining days of the year and the month string
{
    if(mon==1)
    {
        strcpy(s,"January");
        return 0;
    }
    else if(mon==2)
    {
        strcpy(s,"February");
        return 31;
    }
    else if(mon==3)
    {
        strcpy(s,"March");
        return 59;
    }
    else if(mon==4)
    {
        strcpy(s,"April");
        return 90;
    }
    else if(mon==5)
    {
        strcpy(s,"May");
        return 120;
    }
    else if(mon==6)
    {
        strcpy(s,"June");
        return 151;
    }
    else if(mon==7)
    {
        strcpy(s,"July");
        return 181;
    }
    else if(mon==8)
    {
        strcpy(s,"August");
        return 212;
    }
    else if(mon==9)
    {
        strcpy(s,"September");
        return 243;
    }
    else if(mon==10)
    {
        strcpy(s,"October");
        return 273;
    }
    else if(mon==11)
    {
        strcpy(s,"November");
        return 304;
    }
    else if(mon==12)
    {
        strcpy(s,"December");
        return 334;
    }
    else
    {
        printf("Please enter a valid month you dickhead\n");
    }
}
void print(int f,int year,int month,char s[max])//prints the calendar
{
    //for calculating the total days of the month
    int nods=31;
    if(month==4||month==6||month==9||month==11)
        nods=30;
    else if(month==2)
    {
        if(year%400==0||year%4==0&&year%100!=0)
            nods=29;
        else
            nods=28;
    }
    //printf("%d",nods);
    printf("\t\t\t%s   %d\n\n",s,year);
    printf("\tMON    TUE    WED    THU    FRI    SAT    SUN\n");
    //Setting the space for the 1st day
    if(f==0)
        printf("\t 1     ");
    else if(f==1)
        printf("\t        1     ");
    else if(f==2)
        printf("\t               1     ");
    else if(f==3)
        printf("\t                      1     ");
    else if(f==4)
        printf("\t                             1     ");
    else if(f==5)
        printf("\t                                    1     ");
    else if(f==6)
        printf("\t                                           1     ");
    if(f<6)
        f++;
    else
    {
        printf("\n\t");
        f=0;
    }
    for(int i=2;i<=nods;i++)//printing the number of days
    {
        //spacing difference for dates with single days
        if(i<=9)
            printf(" %d  ",i);
        else
            printf(" %d ",i);
        printf("   ");//space between 2 dates
        f++;
        if(f==7)//when the date reaches sunday it jumps to the next line
        {
            printf("\n\t");
            f=0;
        }
    }
}
void getday(int year,int month)//calculates the number of days and checks on which day does the 1st day of the month lands on and sends it to print

{
    int lp=0;
    int yr=year-1900;
    int days=yr*365;//calculating the total number of days between the years
    char s[max];
    if(LEAP(year))//checks if the year which entered is leap or not
        if(month>2)//checks if the month in that year is more than february,if it is than it adds 1 extra day for the leap year
            lp=1;
    for(int i=1900;i<year;i++)//calculating the total number of leap days in between the years to add into it
        if(LEAP(i))
            lp++;
    int j=getremdaysinyear(month,s);//gets the remaining number of days in the year
    days=days+j+lp;
    //printf("%d\n",days);
    days=days%7;//on which day 1st lands on
    //printf("%d\n",days);
    print(days,year,month,s);
}
void yearandmon(int year,int mon)//For getting the year and month and to check if the year entered is above 1900 or not and sends it to getday
{

    getday(year,mon);
    while(1)//for navigating the calendar
    {
        printf("\n\n");
        printf("\n\n\tUP - SAME MONTH,PREVIOUS YEAR\n\tDOWN - SAME MONTH,NEXT YEAR\n\tRIGHT - SAME YEAR,NEXT MONTH\n\tLEFT - SAME YEAR,PREVIOUS MONTH\n\tSPACE - FOR EXITING THE CALENDARn\n");
        int ch=get_code();
        system("cls");//clears the screen
        if(ch==72)//up,getting the previous year
        {
            //printf("%d",ch);
            if((year-1)<1900)
                printf("Cannot get below this year\nEnter something else");
            else
                getday(--year,mon);
        }
        if(ch==80)//down,getting the next year
        {
            //printf("%d",ch);
            getday(++year,mon);
        }
        if(ch==77)//right,getting the next month
        {
            //printf("%d",ch);
            if((mon+1)>12)//if the month is december and then goes to the next month then it goes to the next yeard
            {
                mon=1;
                getday(++year,mon);
            }
            else
                getday(year,++mon);
        }
        if(ch==75)//left
        {
            //printf("%d",ch);
            if((mon-1)<1)//if the month is january and then goes to the previous month then it goes to the previous year
            {
                mon=12;
                year--;
                getday(year,mon);
            }
            else
                getday(year,--mon);
        }
        if(ch==32)//for exiting the leap year
        {
            printf("\n\nThank you for viewing the calendar
                   \n");
            exit(1);
        }

    }
}
int main()
{
    fflush(stdin);
    int year,mon;
    printf("Please Enter the year which is after 1899 : ");
    scanf("%d",&year);
    if(year<1900)
    {
        printf("You dickhead enter a year which is after 1899");
        exit(1);
    }
    printf("Enter the number of the month : ");
    scanf("%d",&mon);
    //printf("%d %d\n\n",year,mon);
    yearandmon(year,mon);//goes to the main part of the program
    return 0;
}

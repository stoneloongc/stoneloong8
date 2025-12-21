#include<stdio.h>
typedef struct Birthday{
    int year;
    int month;
    int day;
}Birthday;
typedef struct Student{
    int age;
    char *name;
    int id;
    float score;
    Birthday birthday;
}Student;

void card(Student *stu,int len)
{
    for(int i=0;i<len;i++)
    {
        {   
            printf("年龄:%d\t名字%s\t:学号:%d\t分数:%f\t生日:%d-%d-%d\n",
            (stu+i)->age,(stu+i)->name,(stu+i)->id,(stu+i)->score,
            (stu+i)->birthday.year,(stu+i)->birthday.month,(stu+i)->birthday.day);
        }  //->代表对指针解引用
    }
}
int main()
{
    Student students[]={
                    {19,"Tim",1001,100,{2000,9,1}},
                    {20,"T0m",1002,95,{2000,8,1}},
                    {19,"Tm",1003,100,{2000,7,1}},
                    };
    int len =sizeof(students)/sizeof(students[0]);
    card(students,len);
    return 0;
}
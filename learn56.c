//结构体
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

void card(Student stu)
{
    printf("年龄:%d\t名字%s\t:学号:%d\t分数:%f\t生日:%d-%d-%d\n",
        stu.age,stu.name,stu.id,stu.score,stu.birthday.year,stu.birthday.month,stu.birthday.day);
}
int main()
{
    Student stu1={19,"Tim",1001,100,{2000,9,1}};
    card(stu1);
    return 0;
}
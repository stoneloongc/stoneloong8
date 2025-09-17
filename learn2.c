/*#include<stdio.h>//自己理解写的（问题：if由于逐级实现，运行到正确结束if语句，可通过<=完成本体要求；
scanf中输出的为double输入的应用lf；float用f，printf均可;.1f/.1lf;.2f/.2lf......前面的数字代表输出的小数点位数）
int main ()
{
    double i;
    double bouns1,bouns2,bouns;
    printf("你的总营业额");
    scanf("%lf",&i);
    bouns1=100000*0.1;
    bouns2=bouns1+100000*0.075;
    if(i<=100000)
    {
        bouns=i*0.1;
    }
    else if(100000<i<=200000)
    {
        bouns=bouns1+(i-100000)*0.075;
    }
    else 
    {
        bouns=bouns2+(i-200000)*0.03;
    }
    printf("你的总利润%lf\n",bouns);
    return 0;
}*/
#include<stdio.h>
int main()
{
    double i;
    double bonus1,bonus2,bonus4,bonus6,bonus10,bonus;
    printf("你的净利润是：\n");
    scanf("%lf",&i);
    bonus1=100000*0.1;
    bonus2=bonus1+100000*0.075;
    bonus4=bonus2+200000*0.05;
    bonus6=bonus4+200000*0.03;
    bonus10=bonus6+400000*0.015;
    if(i<=100000) {
        bonus=i*0.1;
    } else if(i<=200000) {
        bonus=bonus1+(i-100000)*0.075;
    } else if(i<=400000) {
        bonus=bonus2+(i-200000)*0.05;
    } else if(i<=600000) {
        bonus=bonus4+(i-400000)*0.03;
    } else if(i<=1000000) {
        bonus=bonus6+(i-600000)*0.015;
    } else if(i>1000000) {
        bonus=bonus10+(i-1000000)*0.01;
    }
    printf("提成为：bonus=%lf\n",bonus);
 
   
}


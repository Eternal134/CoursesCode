//  通讯录模拟系统

#include<stdio.h>
#include<string.h>
#include<math.h>

#define M 20

typedef struct Info
{
    char tele[15];
    char add[15];
    char name[15];
    int flag = 0;       //flag标记该空间是否已被填充，如果已被填充，flag置为1
}Info;

int Hash(char tele[15])
{   //哈希函数的构造：手机号数字之和再取余M
    int i, sum = 0;
    for(i = 0; i < strlen(tele); i ++)
    {
        sum += tele[i] - '0';
    }
    return sum % M;
}

void EnHashList(Info address[M], Info info)
{
    int i, h = Hash(info.tele);
    if(address[h].flag == 0)
    {   //如果哈希值处还没有元素，将该元素保存到该位置
        info.flag = 1;
        address[h] = info;
        return ;
    }
    else
    {
        for(i = 1; i < sqrt(M); i ++)
        {   //二次探测法处理冲突
            h = int(h + pow(-1, i+1) * pow(i, 2) + M) % M;
            if(address[h].flag == 0)
            {
                info.flag = 1;
                address[h] = info;
                return ;
            }
            h = int(h + pow(-1, i) * pow(i, 2) + M) % M;
            if(address[h].flag == 0)
            {
                info.flag = 1;
                address[h] = info;
                return ;
            }
        }
    }
    printf("录入通讯录失败！\n");
}

int SearchHash(Info address[M], char tele[15])
{
    int h, i;
    h = Hash(tele);
    if(strcmp(tele, address[h].tele) == 0)
    {
        return h;
    }
    else
    {
        for(i = 1; i < sqrt(M); i ++)
        {   //二次探测法处理冲突
            h = int(h + pow(-1, i+1) * pow(i, 2) + M) % M;
            if(strcmp(tele, address[h].tele) == 0)
            {
                return h;
            }
            h = int(h + pow(-1, i) * pow(i, 2) + M) % M;
            if(strcmp(tele, address[h].tele) == 0)
            {
                return h;
            }
        }
    }
    printf("通讯录里没有该人\n");
    return -1;
}

int main()
{
    Info address[M];
    Info info;
    char tele[15];
    int i, f, h;
    while(1)
    {
        printf("\n选择功能：\n1. 录入新的联系人\n2. 查询联系人\n3. 显示所有的联系人\n4. 退出系统\n：");
        scanf("%d", &f);
        getchar();
        if(f == 4)
        {
            break;
        }
        switch(f)
        {
            case 1:

                printf("\n依次输入新建联系人的名称、电话号码和地址\n");
                
                gets(info.name);
                gets(info.tele);
                gets(info.add);
                EnHashList(address, info);                  //把这个联系人的信息保存到哈希表中
                printf("联系人已保存到通讯录！\n\n");
                break;

            case 2:

                printf("\n输入你要查询的联系人的手机号：\n");
                gets(tele);
                h = SearchHash(address, tele);          //找到手机号对应的元素在哈希表中的位置
                printf("\n该联系人的具体信息为：\n%s\n%s\n%s\n", address[h].name, address[h].tele, address[h].add);
                break;

            case 3:

                printf("\n您的通讯录中所有联系人的信息如下：\n");
                for(i = 0; i < M; i ++)
                {
                    if(address[i].flag)         //输出哈希表中flag为1的元素
                    {
                        printf("\n%s\n%s\n%s\n", address[i].name, address[i].tele, address[i].add);
                    }
                }
                break;
        }
    }
    return 0;
}
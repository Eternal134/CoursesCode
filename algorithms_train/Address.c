//  通讯录模拟系统

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define M 50

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

void GetAdd(Info address[], FILE *fp)
{   //从文件中获得联系人列表
    rewind(fp);
    Info info;
    while(!feof(fp))
    {
        fscanf(fp, "%s\n%s\n%s\n", info.name, info.tele, info.add);
        EnHashList(address, info);      //保存到哈希表
    }
}

void fPut(Info address[], FILE *fp)
{   //将哈希表中的内容输出到文件
    fp = fopen("add.txt", "wb");        //重新打开文件可以清空文件内容
    int i;
    for(i = 0; i < M; i ++)
    {
        if(address[i].flag)
        {
            fprintf(fp, "%s\n%s\n%s\n", address[i].name, address[i].tele, address[i].add);
        }
    }
}

int main()
{
    Info address[M];
    Info info;
    char tele[15], name[15];
    int i, f, h;

    FILE *fp;
    if((fp = fopen("add.txt", "rb+")) == NULL)
    {   //二进制读写方式打开文件，如果发生错误，返回错误信息
        printf("can't open file");
        exit(0);
    }

    GetAdd(address, fp);        //用文件中的联系人列表初始化哈希表

    while(1)
    {
        printf("\n选择功能：\n1. 录入新的联系人\n2. 查询联系人\n3. 显示所有的联系人\n4. 删除联系人\n5. 退出系统\n>>> ");
        scanf("%d", &f);
        getchar();
        if(f == 5)
        {
            break;
        }
        switch(f)
        {
            case 1:
                //新增联系人
                printf("\n依次输入新建联系人的名称、电话号码和地址\n>>> ");
                gets(info.name);
                gets(info.tele);
                gets(info.add);
                EnHashList(address, info);                  //把这个联系人的信息保存到哈希表中
                printf("联系人已保存到通讯录！\n\n");
                break;

            case 2:
                //查找联系人
                printf("\n输入你要查询的联系人的姓名：\n>>> ");
                gets(name);
                for(i = 0; i < M; i ++)
                {
                    if(address[i].flag && strcmp(address[i].name, name) == 0)
                    {
                        break;
                    }
                }
                if(i == M)
                {   //如果i值等于M，代表上一个循环没有提前结束，表示通讯录中没有此人
                    printf("该联系人不存在！\n");
                    break;
                }
                else
                {
                    printf("\n该联系人的具体信息为：\n姓名：%s\n电话：%s\n地址：%s\n", 
                        address[i].name, address[i].tele, address[i].add);
                }
                break;

            case 3:
                //查看全部联系人信息
                printf("\n您的通讯录中所有联系人的信息如下：\n");
                for(i = 0; i < M; i ++)
                {
                    if(address[i].flag)         //输出哈希表中flag为1的元素
                    {
                        printf("\n姓名:%s\n电话：%s\n地址:%s\n", address[i].name, address[i].tele, address[i].add);
                    }
                }
                break;

            case 4:
                //删除联系人
                printf("\n输入想要删除的联系人的姓名:\n>>> ");
                gets(name);
                for(i = 0; i < M; i ++)
                {   //遍历哈希表，找到该联系人
                    if(address[i].flag && strcmp(address[i].name, name) == 0)
                    {
                        address[i].flag = 0;        //将flag置为0，表示删除
                    }
                }
                printf("联系人已被删除\n");
                break;
        }
    }

    fPut(address, fp);          //把联系人信息输出到文件中
    fclose(fp);             //关闭文件
    return 0;
}

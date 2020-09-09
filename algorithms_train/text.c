#include<stdio.h>
#include<string.h>
int main()
{
    char s[50];
    gets (s);
    int i, j, k;
    char temp;
    for(i = 0; s[i] != 0; i ++)
    {
        k = i;
        for(j = i; s[j] != 0; j ++)
        {
            if(s[j] > s[k]) k = j;
        }
        temp = s[i];
        s[i] = s[k];
        s[k] = temp;
    }
    puts(s);
    return 0;
}
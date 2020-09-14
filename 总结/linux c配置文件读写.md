# linux c配置文件读写

读

```c
#include <iostream>
#include <stdio.h>
#include <string.h>

typedef struct{
char LocalNatIP[128];
char LocalNatGKIP[128];
char LocalBackUpIP[128];
char RemoteBackUpIP[128];
char BackupPort[128];
char BSID[128];
char CellID[128];
char MyGKF[128];
char MyGKPN[128];
char LocalNetwork[128];
char ControlChanNum[128];
char ServiceChanNum[128];
char DialNumLen[128];
char NbrAGW1[128];
char NbrAGW2[128];
char NbrAGW3[128];
char NbrAGW4[128];
char NbrAGW5[128];
char ReTransMsgConfig[128];
char AuthenType[128];
}conf;

conf config;

int readConfig(char* file)
{
        char info[37][128] = {0};
        char name[128] = {0};
        int i = 0;
        int j = 0;
        FILE* fp = NULL;
        fp = fopen(file, "r");

        if (fp == NULL)
        {
                printf("fail to open conf file\n");
                return -1;
        }

        char*temp = NULL;
        while(1)
        {

                if(feof(fp))break;
                bzero(name, 0);
                fgets(name, 128, fp);
                strtok_r(name, ":", &temp);
                j = strlen(temp);
                temp[j - 1] = 0;
                strncpy(info[i], temp, 128);
                i++;
        }
        j = i - 1;

		strncpy(config.LocalNatIP, info[0], 128);
        strncpy(config.LocalNatGKIP, info[1], 128);
        strncpy(config.LocalBackUpIP, info[2], 128);
        strncpy(config.RemoteBackUpIP, info[3], 128);
        strncpy(config.BackupPort, info[4], 128);
        strncpy(config.BSID, info[6], 128);
        strncpy(config.CellID, info[7], 128);
        strncpy(config.MyGKF, info[8], 128);
        strncpy(config.MyGKPN, info[9], 128);
        strncpy(config.LocalNetwork, info[10], 128);
        strncpy(config.ControlChanNum, info[11], 128);
        strncpy(config.ServiceChanNum, info[12], 128);
        strncpy(config.DialNumLen, info[14], 128);

        char *tempName = NULL;
        strncpy(name, info[17], 128);
        tempName = strtok_r(name, "|", &temp);
        strncpy(config.NbrAGW1, tempName, 128);
        tempName = strtok_r(NULL, "|", &temp);
        strncpy(config.NbrAGW2, tempName, 128);
        tempName = strtok_r(NULL, "|", &temp);
        strncpy(config.NbrAGW3, tempName, 128);
        tempName = strtok_r(NULL, "|", &temp);
        strncpy(config.NbrAGW4, tempName, 128);
        tempName = strtok_r(NULL, "|", &temp);
        strncpy(config.NbrAGW5, tempName, 128);

        strncpy(config.ReTransMsgConfig, info[22], 128);
        strncpy(config.AuthenType, info[33], 128);
        return 0;
}

int main()
{
        using namespace std;
        readConfig("agw_funcPara.config");

        //test
        cout<<config.LocalNatIP <<endl;
        cout<<config.LocalNatGKIP<<endl;
        cout<<config.LocalBackUpIP<<endl;
        cout<<config.RemoteBackUpIP<<endl;
        cout<<config.BackupPort<<endl;
        cout<<config.BSID<<endl;
        cout<<config.CellID<<endl;
        cout<<config.MyGKF<<endl;
        cout<<config.MyGKPN<<endl;
        cout<<config.LocalNetwork<<endl;
        cout<<config.ControlChanNum <<endl;
        cout<<config.ServiceChanNum<<endl;
        cout<<config.DialNumLen<<endl;
        cout<<config.NbrAGW1<<endl;
        cout<<config.NbrAGW2<<endl;
        cout<<config.NbrAGW3<<endl;
        cout<<config.NbrAGW4<<endl;
        cout<<config.NbrAGW5<<endl;
        cout<<config.ReTransMsgConfig<<endl;
        cout<<config.AuthenType<<endl;

        return 0;
}

```

```c
结果
   
```

```c

192.170.0.1
168.4.52.1
192.168.4.8
192.168.4.7
6666
1
1
101
101
198
1
4
2
102
102
81
234
2
0x0
0

```

改写IP

```c
#include <string.h>
#include <stdio.h>
#include <iostream>

int write(char *file, char *des, char *after)
{
        int c = -1;
        int c1 = -1;
        int line = -1;
        int ch = -1;
        if("LocalNatIP" == des)
        {
                line = 1;
        }
        else if("LocalNatGKIP" == des)
        {
                line = 2;
        }
        else if("LocalBackUpIP" == des)
        {
                line = 3;
        }
        else{
                printf("wrong IP.\n");
                return -1;
        }
        FILE* fp = NULL;
        fp = fopen(file, "r+");
        if(NULL == fp)
        {
                printf("failed to open file.\n");
                return -2;
        }

        int i = 0;
        while(i!=line)
        {
                ch=fgetc(fp);
                if(ch=='\n')
                {
                        i++;
                }
        }

        c=ftell(fp);

        while(fgetc(fp)!='\n')
        {
                c1=ftell(fp);
        }

        fseek(fp,c,SEEK_SET);

        int cnt=c1-c;

        for(i=0;i<cnt;i++)
        {
                if( i < strlen(des))fputc(des[i],fp);
                else if(i == strlen(des))fputc(':',fp);
                else if(i < strlen(des) + 1 + strlen(after))fputc(after[i - 1 - strlen(des)], fp);
                else fputc(' ',fp);
        }


        if(fclose(fp)==0)
                printf("文件关闭成功!\n");
        else
                printf("文件关闭失败!\n");
        return 0;


}

int main()
{
        write("test.config", "LocalNatGKIP", "0.0.0.0");
        return 0;
}
    
```


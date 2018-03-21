#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <time.h>
#include<string.h>
#include <mmsystem.h>
#include<io.h> //findfirst的头文件
#pragma comment(lib, "WINMM.LIB")  //#pragma 是一条编译器指令 导入winmm.lib库
//宏定义
#define SINGLE_LOOP					1					// 单曲循环
#define ORDER_LOOP					2					// 顺序播放
#define RANDOM_LOOP					3					// 随机播放
//全局变量
struct _finddata_t F[50];
int totalMusicCount,numPlayMusicNow,lnumPlayMusicNow,iLoopType=2;
//函数声明
void menu();
void playmusic(struct _finddata_t F[],int lnumPlayMusicNow);
void pausemusic(struct _finddata_t F[],int lnumPlayMusicNow);
void resumemusic(struct _finddata_t F[],int lnumPlayMusicNow);
void closemusic(struct _finddata_t F[],int lnumPlayMusicNow);
void JumpMusic(int num,int iLoopType);
void playmode();
//主函数
int main()
{
    FILE *fp1=fopen("mp3历史记录.txt","r");      //读取上次播放记录
    int i,j=0,k;
    char n[100];
    long Handle;
    struct _finddata_t F[50];
    menu();
    //显示歌曲列表
    k=Handle=_findfirst("*.mp3",&F[j]);     //目录操作
    printf("\n★  歌曲列表   \n");
    while(k!=-1L)
    {
        printf("%d. %s\n",j+1,F[j].name);
        j++;
        k = _findnext(Handle, &F[j] );
    }
    totalMusicCount=j;
    _findclose(Handle);
    fscanf(fp1,"%d%d",&lnumPlayMusicNow,&iLoopType);     //上次关闭前播放的歌曲，播放模式
    if(fp1==NULL)
        playmusic(F,0);
    else
        playmusic(F,lnumPlayMusicNow);
    if(iLoopType==1)
        printf("★ 当前播放模式： 单曲循环\n");
    else if(iLoopType==2)
        printf("★ 当前播放模式： 顺序循环\n");
    else if(iLoopType==3)
        printf("★ 当前播放模式： 随机循环\n");
    for(i=0;; i++)     //无限循环，可以不断输入命令
    {
        printf("\n★  请选择您的操作:");
        scanf("%s",n);        //使用字符串存储选择，可处理异常操作
        if(strcmp(n,"1")==0)
        {
            printf("★  请输入要播放的歌曲序号：");
            scanf("%d",&numPlayMusicNow);
            if(numPlayMusicNow>0&&numPlayMusicNow<=totalMusicCount)   //确保输入序号合法
            {
                closemusic(F,lnumPlayMusicNow);
                lnumPlayMusicNow=numPlayMusicNow-1;
                playmusic(F,lnumPlayMusicNow);
            }
            else
                printf("非法的歌曲序号!");
        }
        else if(strcmp(n,"2")==0)
            pausemusic(F,lnumPlayMusicNow);
        else if(strcmp(n,"3")==0)
            resumemusic(F,lnumPlayMusicNow);
        else if(strcmp(n,"4")==0)
            JumpMusic(-1,iLoopType,F);
        else if(strcmp(n,"5")==0)
            JumpMusic(1,iLoopType,F);
		else if(strcmp(n,"p")==0)
            JumpMusic(-1,iLoopType,F);
        else if(strcmp(n,"n")==0)
            JumpMusic(1,iLoopType,F);
        else if(strcmp(n,"6")==0)
            playmode();
        else if(strcmp(n,"7")==0)
            menu();
        else if(strcmp(n,"8")==0)
        {
            FILE *fp2=fopen("mp3历史记录.txt","w");    //关闭前将该次使用记录写入文件
            fprintf(fp2,"%d %d",lnumPlayMusicNow,iLoopType);
            fclose(fp2);
            return 0;
        }
        else
            printf("您的选择有误!");
    }
    fclose(fp1);
    return 0;
}
/***
     程序功能：显示主菜单
     输入参数：无
     作者：nc
***/
void menu()
{
    printf("|★★★★★★★★★  主菜单  ★★★★★★★★★|\n");
    printf("|★------------------------------------------★|\n");
    printf("|★               1. 搜索                    ★|\n");
    printf("|★               2. 暂停                    ★|\n");
    printf("|★               3. 继续                    ★|\n");
    printf("|★               4.上一曲（p）              ★|\n");
    printf("|★               5.下一曲（n）              ★|\n");
    printf("|★               6.播放模式                 ★|\n");
    printf("|★               7.显示菜单                 ★|\n");
    printf("|★               8.退出                     ★|\n");
    printf("|★★★★★★★★★★★★★★★★★★★★★★★|\n");

}
/***
     程序功能：播放音乐
     输入参数：存储歌曲信息的结构体，要播放的歌曲序号
     作者：nc
***/
void playmusic(struct _finddata_t F[],int lnumPlayMusicNow)
{
    char s1[200],s2[200];
    printf("★ 当前播放：%d. %s\n",lnumPlayMusicNow+1,F[lnumPlayMusicNow].name);
    sprintf(s1,"play %s",F[lnumPlayMusicNow].name);    //将歌曲名写入s1字符串
    mciSendString(s1,NULL,0,NULL);
}
/***
     程序功能：暂停播放
     输入参数：存储歌曲信息的结构体，要播放的歌曲序号
     作者：nc
***/
void pausemusic(struct _finddata_t F[],int lnumPlayMusicNow)
{
    char s[200];
    sprintf(s,"pause %s",F[lnumPlayMusicNow].name);
    mciSendString(s,NULL,0,NULL);
}
/***
     程序功能：恢复播放
     输入参数：存储歌曲信息的结构体，要播放的歌曲序号
     作者：nc
***/
void resumemusic(struct _finddata_t F[],int lnumPlayMusicNow)
{
    char s[200];
    sprintf(s,"resume %s",F[lnumPlayMusicNow].name);
    mciSendString(s,NULL,0,NULL);
}
/***
     程序功能：停止播放
     输入参数：存储歌曲信息的结构体，要播放的歌曲序号
     作者：nc
***/
void closemusic(struct _finddata_t F[],int lnumPlayMusicNow)
{
    char s[200];
    sprintf(s,"close %s",F[lnumPlayMusicNow].name);
    mciSendString(s,NULL,0,NULL);
}
/***
     程序功能：上一首 / 下一首跳转控制
     输入参数：当前歌曲序号，播放模式，存储歌曲信息的结构体
     作者：nc
***/
void JumpMusic(int num,int iLoopType,struct _finddata_t F[])
{
    if(num==-1)    //上一曲
    {
        if(iLoopType==RANDOM_LOOP)     //根据播放模式确定跳转方式
        {
            closemusic(F,lnumPlayMusicNow);
            lnumPlayMusicNow = rand() % (totalMusicCount);
            playmusic(F,lnumPlayMusicNow);
        }
        else if(iLoopType==ORDER_LOOP)
        {
            if(lnumPlayMusicNow > 0)
            {
                lnumPlayMusicNow = lnumPlayMusicNow - 1;
                closemusic(F,lnumPlayMusicNow+1);
                playmusic(F,lnumPlayMusicNow);
            }
            else if(lnumPlayMusicNow==0)
            {
                lnumPlayMusicNow = totalMusicCount - 1;
                closemusic(F,0);
                playmusic(F,lnumPlayMusicNow);
            }
        }
        else if(iLoopType==SINGLE_LOOP)
        {
            closemusic(F,lnumPlayMusicNow);
            playmusic(F,lnumPlayMusicNow);
        }
    }
    else if(num==1)   //下一曲
    {
        if(iLoopType==RANDOM_LOOP)
        {
            closemusic(F,lnumPlayMusicNow);
            lnumPlayMusicNow = rand() % (totalMusicCount);
            playmusic(F,lnumPlayMusicNow);
        }
        else if(iLoopType==ORDER_LOOP)
        {
            if(lnumPlayMusicNow == totalMusicCount-1)
            {
                lnumPlayMusicNow = 0;
                closemusic(F,totalMusicCount-1);
                playmusic(F,lnumPlayMusicNow);
            }
            else
            {
                lnumPlayMusicNow = lnumPlayMusicNow + 1;
                closemusic(F,lnumPlayMusicNow-1);
                playmusic(F,lnumPlayMusicNow);
            }
        }
        else if(iLoopType==SINGLE_LOOP)
        {
            closemusic(F,lnumPlayMusicNow);
            playmusic(F,lnumPlayMusicNow);
        }
    }
}
/***
     程序功能：播放模式
     输入参数：无
     作者：nc
***/
void playmode()
{
    int mode;
    printf("★  请选择播放模式：\n");
    printf("    1.单曲循环\n");
    printf("    2.顺序播放\n");
    printf("    3.随机播放\n");
    scanf("%d",&mode);
    if(mode==1)
        iLoopType=SINGLE_LOOP;
    else if(mode==2)
        iLoopType= ORDER_LOOP ;
    else if(mode==3)
        iLoopType=RANDOM_LOOP;
}

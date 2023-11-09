#include "register.h"
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

#define MAXSIZE 20

int RegisterTeacherUser()
{
	/*变量定义*/
	char uid[MAXSIZE],passwd[MAXSIZE],username[MAXSIZE],usex[MAXSIZE],uage[MAXSIZE];
	sqlite3 *db_point=NULL;
	char sql[100];
	int rs,class;
	/*设置用户*/
	printf("请输入你的教工号[字符限制:1~7]:");
	scanf("%s",uid);
	printf("请设置你的密码[字符限制:1~7]:");
	scanf("%s",passwd);
	
	if(strlen(uid)>8&&strlen(passwd)>7)
	{
		puts("不符合字符规定...");
		return 0;
	}
	
	/*进行数据库操作*/
    	rs=sqlite3_open("SMS.db",&db_point); // 创建默认的数据库，并且将db_point数据库连接对象指针指向创建好且打开的数据库对象
    	if(rs != SQLITE_OK)
    	{
        	perror("数据库打开失败");
        	getchar();getchar();
        	system("clear");
        	return -1; // 返回-1 ，表示打开数据库失败
    	}
    	/*执行创建用户并初始化默认用户语句*/
    	sprintf(sql,"insert into user values(2,'%s','%s');",uid,passwd);
    	// SQL语句对象的原始SQL语句字符串
    	rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
    	if( rs != SQLITE_OK )
    	{
      		printf("添加用户失败\n");
      		getchar();getchar();
      		system("clear");
      		return -1; // 返回-1 ，表示初始化失败
    	}
   	/*设置用户信息*/
	printf("请输入你的名字[字符限制:1~7]:");
	scanf("%s",username);
	printf("请输入你的性别[男/女]:");
	scanf("%s",usex);
	printf("请输入你的年龄:");
	scanf("%s",uage);
	printf("请输入你管理的班级号:");
	scanf("%d",&class);
	
	/*初始化语句*/
	strcpy(sql, "");
	
	/*执行创建用户并初始化默认用户语句*/
    	sprintf(sql,"insert into teacher values('%s','%s','%s','%s',%d);",uid,username,usex,uage,class);
    	// SQL语句对象的原始SQL语句字符串
    	rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
    	if( rs != SQLITE_OK )
    	{
      		printf("添加用户失败\n");
      		getchar();getchar();
      		system("clear");
      		return -1; // 返回-1 ，表示初始化失败
    	}
	puts("完成用户注册,按Enter键盘进行下一步...");getchar();getchar();system("clear");
    	sqlite3_close(db_point);
}


int RegisterStudentUser()
{
	/*变量定义*/
	char uid[MAXSIZE],passwd[MAXSIZE],username[MAXSIZE],usex[MAXSIZE],uage[MAXSIZE],Cgrade[MAXSIZE],Mgrade[MAXSIZE],Egrade[MAXSIZE];
	sqlite3 *db_point=NULL;
	char sql[100];
	int rs,class;
	/*设置用户*/
	printf("请输入你的学号[字符限制:1~7]:");
	scanf("%s",uid);
	printf("请设置你的密码[字符限制:1~7]:");
	scanf("%s",passwd);
	
	if(strlen(uid)>8&&strlen(passwd)>8)
	{
		puts("不符合字符规定...");
		return 0;
	}
	
	/*进行数据库操作*/
    	rs=sqlite3_open("SMS.db",&db_point); // 创建默认的数据库，并且将db_point数据库连接对象指针指向创建好且打开的数据库对象
    	if(rs != SQLITE_OK)
    	{
        	perror("数据库打开失败");
        	getchar();getchar();
        	system("clear");
        	return -1; // 返回-1 ，表示打开数据库失败
    	}
    	/*执行创建用户并初始化默认用户语句*/
    	sprintf(sql,"insert into user values(3,'%s','%s');",uid,passwd);
    	// SQL语句对象的原始SQL语句字符串
    	rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
    	if( rs != SQLITE_OK )
    	{
      		printf("添加用户失败\n");
      		getchar();getchar();
      		system("clear");
      		return -1; // 返回-1 ，表示初始化失败
    	}
   	/*设置用户信息*/
	printf("请输入你的名字[字符限制:1~7]:");
	scanf("%s",username);
	printf("请输入你的性别[男/女]:");
	scanf("%s",usex);
	printf("请输入你的年龄:");
	scanf("%s",uage);
	printf("请输入你的班级号:");
	scanf("%d",&class);
	
	/*初始化语句*/
	strcpy(sql, "");
	
	/*执行创建用户并初始化默认用户语句*/
    	sprintf(sql,"insert into student values('%s','%s','%s','%s',NULL,NULL,NULL,%d);",uid,username,usex,uage,class);
    	// SQL语句对象的原始SQL语句字符串
    	rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
    	if( rs != SQLITE_OK )
    	{
      		printf("添加用户失败\n");
      		getchar();getchar();
      		system("clear");
      		return -1; // 返回-1 ，表示初始化失败
    	}
	puts("完成用户注册,按Enter键盘进行下一步...");getchar();getchar();system("clear");
    	sqlite3_close(db_point);
}

void RegisterOption()
{
	int i;
	while(1)
	{
		printf("<-----注册界面----->\n");
		printf("---------------------\n");
		printf("1、学生注册\n");
		printf("2、教师注册\n");
		printf("3、退出注册\n");	
		printf("---------------------\n");
		printf("请输入你想操作的序号：");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
				system("clear");
				RegisterStudentUser();
				break;
			case 2:
				system("clear");
				RegisterTeacherUser();
				break;
			case 3:printf("3 quit\n");system("clear");return 0;
			default: printf("输入序号有误,请重新输入序号(按Enter键进行下一步)...\n");getchar();getchar();system("clear");
		}
	}
}


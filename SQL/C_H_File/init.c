#include "init.h"
#include <sqlite3.h>
#include <unistd.h>
#include <fcntl.h>

void DatabaseInit()
{
	/*函数声明*/
	int InitUserInformation();
	
	if(access("SMS.db",F_OK)==0)
	{
		printf("已经存在数据库，无需初始化配置\n");
		sleep(1);
	}
	else
	{
		if(InitUserInformation()==-1)
		{
			printf("初始化配置失败\n");
		}
		else
		{
			printf("初始化配置成功\n");
		}
	}
	puts("请按Enter键进行下一步...");
    	getchar();
    	system("clear");
}

int InitUserInformation()
{
    /*创建默认数据库*/
    sqlite3 *db_point = NULL; // 定义一个sqlite3数据库连接对象指针    
    int r = sqlite3_open("SMS.db",&db_point); // 创建默认的数据库，并且将db_point数据库连接对象指针指向创建好且打开的数据库对象
    if(r != SQLITE_OK)
    {
        perror("数据库创建失败");
        return -1; // 返回-1 ，表示初始化失败
    }
    
    /*执行创建用户并初始化默认用户语句*/
    char *sql = "CREATE TABLE user(ip int(4) check(ip in(1,2,3)),uid varchar(8),upass varchar(8),primary key(uid));"; // SQL语句对象的原始SQL语句字符串
    r = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
    if( r != SQLITE_OK )
    {
      printf("创建用户表格失败\n");
      return -1; // 返回-1 ，表示初始化失败
    }
   else
    {
      printf("创建用户表格成功\n");
    }
    
    sql = "insert into user values(1,'admin','admin');"; // SQL语句对象的原始SQL语句字符串
    r = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
    if( r != SQLITE_OK )
    {
      printf("初始化默认用户失败\n");
      return -1; // 返回-1 ，表示初始化失败
    }
   else
    {
      printf("初始化默认用户成功\n");
    }
    
        /*执行创建教师信息语句*/
    sql = "CREATE TABLE teacher(uid int(4),uname varchar(255),usex varchar(255) check(usex in ('男','女')),uage varchar(255),class int(4),primary key(uid),foreign key(uid) references user(uid));"; // SQL语句对象的原始SQL语句字符串
    r = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
    if( r != SQLITE_OK )
    {
      printf("创建教师信息表格失败\n");
      return -1; // 返回-1 ，表示初始化失败
    }
   else
    {
      printf("创建教师信息表格成功\n");
    }
    
    /*执行创建学生信息语句*/
    sql = "CREATE TABLE student(uid int(4),uname varchar(255),usex varchar(255) check(usex in ('男','女')),uage varchar(255),Cgrade int(4),Mgrade int(4),Egrade int(4),class int(4),primary key(uid),foreign key(class) references teacher(class),foreign key(uid) references user(uid));"; // SQL语句对象的原始SQL语句字符串
    r = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
    if( r != SQLITE_OK )
    {
      printf("创建学生信息表格失败\n");
      return -1; // 返回-1 ，表示初始化失败
    }
   else
    {
      printf("创建学生信息表格成功\n");
    }

    /*收尾处理*/
    sqlite3_close(db_point);      // 关闭打开了的数据库

    return 0; // 表示没有错误
}

#include "insert.h"
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 20

/*存在回调函数*/
int IsExist_cal_handle1(void *flag, int argc, char** argv, char **colname)
{
    int i = *(int*)(flag);
    *(int *)(flag) = i + 1;
    return 0;
}

int AddAdmin()
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	char uid[MAXSIZE],upass[MAXSIZE];
	char sql[100];
	int rs,i;
	int flag = 0;    /* 用于回调函数计数*/
	
	/*数据库查询*/
	rs=sqlite3_open("SMS.db",&db_point); // 创建默认的数据库，并且将db_point数据库连接对象指针指向创建好且打开的数据库对象
	if(rs != SQLITE_OK)
    	{
        	perror("数据库打开失败，按Enter键进行下一步...");
        	getchar();getchar();
        	system("clear");
        	sqlite3_close(db_point);
        	return 0; // 返回-1 ，表示打开数据库失败
    	}
    	else
    	{
    		printf("请添加管理员的用户名、密码[字符限定1～7]:\n");
    		scanf("%s%s",uid,upass);
    		sprintf(sql,"insert into user values(1,'%s','%s');",uid,upass);
    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
	        if( rs != SQLITE_OK )
	        { 
	        	printf("插入失败\n");
	      		return 0; // 返回-1 ，表示初始化失败
	    	}
	    	else
	    	{
			printf("插入成功\n");		    	
	    	}
    		sqlite3_close(db_point);
    		return 1;
         }
}

int AddTeacher()
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	char uid[MAXSIZE],upass[MAXSIZE],uname[MAXSIZE],usex[MAXSIZE],uage[MAXSIZE],class[MAXSIZE];
	char sql[100];
	int rs,i;
	int flag = 0;    /* 用于回调函数计数*/
	
	/*数据库查询*/
	rs=sqlite3_open("SMS.db",&db_point); // 创建默认的数据库，并且将db_point数据库连接对象指针指向创建好且打开的数据库对象
	if(rs != SQLITE_OK)
    	{
        	perror("数据库打开失败，按Enter键进行下一步...");
        	getchar();getchar();
        	system("clear");
        	sqlite3_close(db_point);
        	return 0; // 返回-1 ，表示打开数据库失败
    	}
    	else
    	{
    		printf("请添加教师的信息:\n");
    		printf("信息[教工号[字符限定1～7]、默认密码[字符限定1～7]、姓名、性别(男/女)、年龄、管理班级]\n");
    		scanf("%s%s%s%s%s%s",uid,upass,uname,usex,uage,class);
    		sprintf(sql,"insert into user values(2,'%s','%s');",uid,upass);
    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
	        if( rs != SQLITE_OK )
	        { 
	        	printf("插入失败\n");
	      		return 0; // 返回-1 ，表示初始化失败
	    	}
	   	strcpy(sql,"");
    		sprintf(sql,"insert into teacher values('%s','%s','%s','%s','%s');",uid,uname,usex,uage,class);
    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
	        if( rs != SQLITE_OK )
	        { 
	        	printf("插入失败\n");
	      		return 0; // 返回-1 ，表示初始化失败
	    	}
	    	else
	    	{
			printf("插入成功\n");		    	
	    	}
    		sqlite3_close(db_point);
    		return 1;
         }
}

int AddStudent()
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	char uid[MAXSIZE],upass[MAXSIZE],uname[MAXSIZE],usex[MAXSIZE],uage[MAXSIZE],Cgrade[MAXSIZE],Mgrade[MAXSIZE],Egrade[MAXSIZE],class[MAXSIZE];
	char sql[100];
	int rs,i;
	int flag = 0;    /* 用于回调函数计数*/
	
	/*数据库查询*/
	rs=sqlite3_open("SMS.db",&db_point); // 创建默认的数据库，并且将db_point数据库连接对象指针指向创建好且打开的数据库对象
	if(rs != SQLITE_OK)
    	{
        	perror("数据库打开失败，按Enter键进行下一步...");
        	getchar();getchar();
        	system("clear");
        	sqlite3_close(db_point);
        	return 0; // 返回-1 ，表示打开数据库失败
    	}
    	
    	printf("请输入学生学号:");
    	scanf("%s",uid);
    	
	/*执行创建用户并初始化默认用户语句*/
    	sprintf(sql,"select * from user where exists(select * from user where uid='%s');",uid);
    	// SQL语句对象的原始SQL语句字符串
    	rs = sqlite3_exec(db_point,sql,IsExist_cal_handle1,&flag,NULL);
    	if( rs != SQLITE_OK )
    	{
      		printf("插入失败，按Enter键进行下一步...\n");
      		getchar();getchar();
      		system("clear");
      		sqlite3_close(db_point);
      		return 0; // 返回-1 ，表示初始化失败
    	}
	else
	 {
        	if (flag == 0 )
        	 {     /* 结果不存在*/
            		printf("数据库里没有该名学生，请添加他/她的信息(如果没有成绩请输入NULL):\n");
            		printf("信息[默认密码[字符限定1～7]、姓名、性别(男/女)、年龄、班级(老师的管理班级)、语文成绩、数学成绩、英语成绩]\n");
      	    		scanf("%s%s%s%s%s%s%s%s",upass,uname,usex,uage,class,Cgrade,Mgrade,Egrade);
      	    		strcpy(sql,"");
      	    		sprintf(sql,"insert into user values(3,'%s','%s');",uid,upass);
      	    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
		        if( rs != SQLITE_OK )
		        { 
		        	printf("插入失败\n");
		      		return 0; // 返回-1 ，表示初始化失败
		    	}
		   	strcpy(sql,"");
      	    		sprintf(sql,"insert into student values('%s','%s','%s','%s','%s','%s','%s','%s');",uid,uname,usex,uage,Cgrade,Mgrade,Egrade,class);
      	    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
		        if( rs != SQLITE_OK )
		        { 
		        	printf("插入失败\n");
		      		return 0; // 返回-1 ，表示初始化失败
		    	}
		    	else
		    	{
				printf("插入成功\n");		    	
		    	}
            		sqlite3_close(db_point);
            		return 1;
        	} 
        	else
        	{      /* 结果存在*/
            		printf("数据库里有该名学生，请添加他/她的成绩(如果没有成绩请输入NULL):\n");
            		printf("信息[语文成绩、数学成绩、英语成绩]\n");
      	    		scanf("%s%s%s",Cgrade,Mgrade,Egrade);
      	  		strcpy(sql,"");
      	    		sprintf(sql,"insert into student(Cgrade,Mgrade,Egrade) values('%s','%s','%s');",Cgrade,Mgrade,Egrade);
      	    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
		        if( rs != SQLITE_OK )
		        { 
		        	printf("插入失败\n");
		      		return 0; // 返回-1 ，表示初始化失败
		    	}
		    	else
		    	{
				printf("插入成功\n");		    	
		    	}
            		sqlite3_close(db_point);
            		return 1;
        	}
        }
	
}


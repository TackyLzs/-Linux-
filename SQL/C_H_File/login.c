#include "login.h"
#include "menu.h"
#include "register.h"
#include <sqlite3.h>
#include <stdio.h>

#define MAXSIZE 15

//登入界面选项函数
void LoginOption()
{
	int i;
	char uid[MAXSIZE],passwd[MAXSIZE];
	while(1)
	{
		printf("<-----登入界面----->\n");
		printf("---------------------\n");
		printf("1、登入账号\n");
		printf("2、注册账号\n");
		printf("3、退出系统\n");	
		printf("---------------------\n");
		printf("请输入你想操作的序号：");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
				system("clear");
				/*输入用户名和密码*/
				printf("请输入你的学号/教工号/管理员用户名:");
				scanf("%s",uid);
				printf("请输入你的密码:");
				scanf("%s",passwd);
				CheckUser(uid,passwd);
				break;
			case 2:
				system("clear");
				RegisterOption();
				break;
			case 3:printf("欢迎下次使用系统...\n");sleep(1);system("clear");return 0;
			default: printf("输入序号有误,请重新输入序号(按Enter键进行下一步)...\n");getchar();system("clear");
		}
	}
}
/*存在回调函数*/
int IsExist_cal_handle(void *flag, int argc, char** argv, char **colname)
{
    int i = *(int*)(flag);
    *(int *)(flag) = i + 1;
    return 0;
}


int CheckUser(char *uid,char *passwd)
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	char sql[100];
	int rs;
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
    	/*执行创建用户并初始化默认用户语句*/
    	sprintf(sql,"select * from user where exists(select * from user where uid='%s' and upass='%s');",uid,passwd);
    	// SQL语句对象的原始SQL语句字符串
    	rs = sqlite3_exec(db_point,sql,IsExist_cal_handle,&flag,NULL);
    	if( rs != SQLITE_OK )
    	{
      		printf("登入失败，按Enter键进行下一步...\n");
      		getchar();getchar();
      		system("clear");
      		sqlite3_close(db_point);
      		return 0; // 返回-1 ，表示初始化失败
    	}
	else
	 {
        	if (flag == 0 )
        	 {     /* 结果不存在*/
            		printf("登入失败，按Enter键进行下一步...\n");
      	    		getchar();getchar();
      	    		system("clear");
            		sqlite3_close(db_point);
        	} 
        	else
        	{      /* 结果存在*/
            		printf("登入成功，按Enter键进行下一步...\n");
      	    		getchar();getchar();
      	    		system("clear");
            		sqlite3_close(db_point);
            		MenuOption(uid,passwd);
        	}
        }
}

//用户菜单界面选项函数
void MenuOption(char *uid,char *passwd)
{
	JudgeId(uid,passwd);
}

int JudgeId(char *uid,char *passwd)
{
	sqlite3 *db_point=NULL;
	char *errMsg;
    	char **dbResult; 
	char sql[100];
	int rs,result,nRow = 0, nColumn = 0;
	rs=sqlite3_open("SMS.db",&db_point); // 创建默认的数据库，并且将db_point数据库连接对象指针指向创建好且打开的数据库对象
	
    	if(rs != SQLITE_OK)
    	{
        	perror("数据库打开失败，按Enter键进行下一步...");
        	getchar();getchar();
        	system("clear");
        	sqlite3_close(db_point);
        	return 0; // 返回-1 ，表示打开数据库失败
    	}
    	sprintf(sql,"select * from user where uid='%s' and upass='%s';",uid,passwd);
	//sprintf(sql,"select * from user");
	/*数据库取出权限值*/
	rs = sqlite3_get_table(db_point,sql,&dbResult,&nRow,&nColumn,&errMsg);
	//printf("%d %d\n",nRow,nColumn);
	if(rs == SQLITE_OK)
	    {
		result = atoi(dbResult[1*nColumn+1-1]);
		sqlite3_free_table(dbResult);
	    }
	else
	    {
		printf("取值失败(按Enter键进行下一步)...");
	    }
	
	sqlite3_close(db_point);
    	switch(result)
    	{
    		case 1:AdminMenuOption(uid);break;
    		case 2:TeacherMenuOption(uid);break;
    		case 3:studentMenuOption(uid);break;
    		default:printf("权限有误(按Enter键进行下一步)...\n");getchar();system("clear"); 
    	}
}



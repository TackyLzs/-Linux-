#include "delete.h"
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 20

/*存在回调函数*/
int IsExist_cal_handle2(void *flag, int argc, char** argv, char **colname)
{
    int i = *(int*)(flag);
    *(int *)(flag) = i + 1;
    return 0;
}

int DeleteAdmin(char *Selfuid,int i)
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	char uid[MAXSIZE];
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
    	else
    	{  
    		if(i==1)
    		{
    			printf("请输入要删除的管理员用户名:\n");	
    		}		
    		if(i==2)
    		{
    			printf("请输入要删除的教师教工号:\n");
    		}
		scanf("%s",uid);
		if(i==1&&strcmp(Selfuid,uid)==0)
		{
			printf("不能删除当前账号,若要删除当前账号，请在注销选项完成...\n");
			return 0;
		}
    			sprintf(sql,"select * from user where exists(select * from user where uid='%s' and ip=%d);",uid,i);
	    		// SQL语句对象的原始SQL语句字符串
	    		rs = sqlite3_exec(db_point,sql,IsExist_cal_handle2,&flag,NULL);
	    		if( rs != SQLITE_OK )
	    		{
	      			printf("删除失败...\n");
	      			return 0; // 返回-1 ，表示初始化失败
	    		}
	    		else
	    		{
	    			if(flag==0)
	    			{
	    				printf("不存在此用户...\n");
			      		return 0; // 返回-1 ，表示初始化失败
	    			}
	    			else
	    			{
	    				if(i==1)
	    				{
	    					strcpy(sql,"");
			    			sprintf(sql,"delete from user where uid='%s';",uid);
				    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
						if( rs != SQLITE_OK )
						{ 
							printf("删除失败\n");
					      		return 0; // 返回-1 ，表示初始化失败
					    	}
					    	else
					    	{
							printf("删除成功\n");		    	
					    	}
				    		sqlite3_close(db_point);
				    		return 1;
	    				}
	    				if(i==2)
	    				{
	    					strcpy(sql,"");
			    			sprintf(sql,"delete from user where uid='%s';",uid);
				    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
						if( rs != SQLITE_OK )
						{ 
							printf("删除失败\n");
					      		return 0; // 返回-1 ，表示初始化失败
					    	}
					    	strcpy(sql,"");
			    			sprintf(sql,"delete from teacher where uid='%s';",uid);
				    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
						if( rs != SQLITE_OK )
						{ 
							printf("删除失败\n");
					      		return 0; // 返回-1 ，表示初始化失败
					    	}
					    	
					    	else
					    	{
							printf("删除成功\n");		    	
					    	}
				    		sqlite3_close(db_point);
				    		return 1;
	    				}
	    				
	    			}
	    		}  					
         }
}

int DeleteTeacher(char *Selfuid)
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	char uid[MAXSIZE];
	char *zErrMsg = 0;
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
    		printf("请输入要删除的学生学号:\n");
    		scanf("%s",uid) ;
    		sprintf(sql,"select * from student,teacher x where exists(select * from student where student.uid='%s' and student.class=(select class from teacher y where y.uid='%s'));",uid,Selfuid);
    		// SQL语句对象的原始SQL语句字符串
    		rs = sqlite3_exec(db_point,sql,IsExist_cal_handle2,&flag,NULL);
    		if( rs != SQLITE_OK )
    		{
      			printf("删除失败\n");
      			sqlite3_close(db_point);
      			return 0; // 返回-1 ，表示初始化失败
    		}
    		else
    		{
    			if(flag==0)
    			{
    				printf("不存在此学生\n");
    				sqlite3_close(db_point);
		      		return 0; // 返回-1 ，表示初始化失败
    			}
    			else
    			{
    				strcpy(sql,"");
	    			sprintf(sql,"delete from student where uid='%s';",uid);
		    		rs = sqlite3_exec(db_point,sql,NULL,NULL,&zErrMsg);
				if( rs != SQLITE_OK )
				{ 
					//puts(zErrMsg);
					printf("删除失败\n");
					sqlite3_close(db_point);
			      		return 0; // 返回-1 ，表示初始化失败
			    	}
			    	strcpy(sql,"");
	    			sprintf(sql,"delete from user where uid='%s';",uid);
		    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				if( rs != SQLITE_OK )
				{ 
					printf("删除失败\n");
					sqlite3_close(db_point);
			      		return 0; // 返回-1 ，表示初始化失败
			    	}
			    	else
			    	{
			    		printf("删除成功\n");	
			    	}
		    		sqlite3_close(db_point);
		    		return 1;
    			}
    		}  				
         }
}

int SelfDeleteStudent(char *uid)
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	//char uid[MAXSIZE];
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
    		//printf("请输入要删除的学生学号:\n");
    		//scanf("%s",uid) ;
    		sprintf(sql,"select * from user where exists(select * from user where uid='%s');",uid);
    		// SQL语句对象的原始SQL语句字符串
    		rs = sqlite3_exec(db_point,sql,IsExist_cal_handle2,&flag,NULL);
    		if( rs != SQLITE_OK )
    		{
      			printf("删除失败，按Enter键进行下一步...\n");
      			getchar();getchar();
      			system("clear");
      			sqlite3_close(db_point);
      			return 0; // 返回-1 ，表示初始化失败
    		}
    		else
    		{
    			if(flag==0)
    			{
    				printf("不存在此学生,按Enter键进行下一步...\n");
    				getchar();getchar();
		      		system("clear");
		      		sqlite3_close(db_point);
		      		return 0; // 返回-1 ，表示初始化失败
    			}
    			else
    			{
    				strcpy(sql,"");
	    			sprintf(sql,"delete from student where uid='%s';",uid);
		    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				if( rs != SQLITE_OK )
				{ 
					printf("注销失败\n");
			      		return 0; // 返回-1 ，表示初始化失败
			    	}
			    	strcpy(sql,"");
	    			sprintf(sql,"delete from user where uid='%s';",uid);
		    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				if( rs != SQLITE_OK )
				{ 
					printf("注销失败\n");
			      		return 0; // 返回-1 ，表示初始化失败
			    	}
			    	else
			    	{
			    		printf("注销成功\n");	
			    	}
		    		sqlite3_close(db_point);
		    		return 1;
    			}
    		}  				
         }
}

int SelfDeleteTeacher(char *uid)
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	//char uid[MAXSIZE];
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
    		//printf("请输入要删除的学生学号:\n");
    		//scanf("%s",uid) ;
    		sprintf(sql,"select * from user where exists(select * from user where uid='%s');",uid);
    		// SQL语句对象的原始SQL语句字符串
    		rs = sqlite3_exec(db_point,sql,IsExist_cal_handle2,&flag,NULL);
    		if( rs != SQLITE_OK )
    		{
      			printf("删除失败，按Enter键进行下一步...\n");
      			getchar();getchar();
      			system("clear");
      			sqlite3_close(db_point);
      			return 0; // 返回-1 ，表示初始化失败
    		}
    		else
    		{
    			if(flag==0)
    			{
    				printf("不存在此教师,按Enter键进行下一步...\n");
    				getchar();getchar();
		      		system("clear");
		      		sqlite3_close(db_point);
		      		return 0; // 返回-1 ，表示初始化失败
    			}
    			else
    			{
    				strcpy(sql,"");
	    			sprintf(sql,"delete from student where uid='%s';",uid);
		    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				if( rs != SQLITE_OK )
				{ 
					printf("注销失败\n");
			      		return 0; // 返回-1 ，表示初始化失败
			    	}
			    	strcpy(sql,"");
	    			sprintf(sql,"delete from user where uid='%s';",uid);
		    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				if( rs != SQLITE_OK )
				{ 
					printf("注销失败\n");
			      		return 0; // 返回-1 ，表示初始化失败
			    	}
			    	else
			    	{
			    		printf("注销成功\n");	
			    	}
		    		sqlite3_close(db_point);
		    		return 1;
    			}
    		}  				
         }
}

int SelfDeleteAdmin(char *uid)
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	//char uid[MAXSIZE];
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
    		//printf("请输入要删除的学生学号:\n");
    		//scanf("%s",uid) ;
    		sprintf(sql,"select * from user where exists(select * from user where uid='%s');",uid);
    		// SQL语句对象的原始SQL语句字符串
    		rs = sqlite3_exec(db_point,sql,IsExist_cal_handle2,&flag,NULL);
    		if( rs != SQLITE_OK )
    		{
      			printf("删除失败，按Enter键进行下一步...\n");
      			getchar();getchar();
      			system("clear");
      			sqlite3_close(db_point);
      			return 0; // 返回-1 ，表示初始化失败
    		}
    		else
    		{
    			if(flag==0)
    			{
    				printf("不存在此管理员,按Enter键进行下一步...\n");
    				getchar();getchar();
		      		system("clear");
		      		sqlite3_close(db_point);
		      		return 0; // 返回-1 ，表示初始化失败
    			}
    			else
    			{
    				strcpy(sql,"");
	    			sprintf(sql,"delete from student where uid='%s';",uid);
		    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				if( rs != SQLITE_OK )
				{ 
					printf("注销失败\n");
			      		return 0; // 返回-1 ，表示初始化失败
			    	}
			    	strcpy(sql,"");
	    			sprintf(sql,"delete from user where uid='%s';",uid);
		    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				if( rs != SQLITE_OK )
				{ 
					printf("注销失败\n");
			      		return 0; // 返回-1 ，表示初始化失败
			    	}
			    	else
			    	{
			    		printf("注销成功\n");	
			    	}
		    		sqlite3_close(db_point);
		    		return 1;
    			}
    		}  				
         }
}


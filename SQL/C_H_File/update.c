#include "update.h"
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 20

/*存在回调函数*/
int IsExist_cal_handle3(void *flag, int argc, char** argv, char **colname)
{
    int i = *(int*)(flag);
    *(int *)(flag) = i + 1;
    return 0;
}

int UpdateAdmin(char *Selfuid,int i)
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	char uid[MAXSIZE],upass[MAXSIZE],uname[MAXSIZE],usex[MAXSIZE],uage[MAXSIZE],class[MAXSIZE];
	char sql[100];
	int rs,j;
	char *zErrMsg = 0;
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
    			printf("请输入要更改的管理员信息:\n");
    			puts("-------------------------------");
    			puts("1、用户名");
    			puts("2、密码");
    			puts("-------------------------------");
    			scanf("%d",&j);
    			switch(j)
    			{
    				case 1:
    					puts("请输入你更改后的用户名[字符限制:1~7]:");
			    		scanf("%s",uid);
			    		sprintf(sql,"update user set uid='%s' where uid='%s';",uid,Selfuid);
			    		// SQL语句对象的原始SQL语句字符串
			    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
			    		if( rs != SQLITE_OK )
			    		{
			      			printf("更新失败\n");
			      			sqlite3_close(db_point);
			      			return 0; // 返回-1 ，表示初始化失败
			    		}
			    		else
			    		{
			    			printf("更新成功\n");
			    			sqlite3_close(db_point);
			    		}
    					return 1;
    					break;
    				case 2:
    					puts("请输入你更改后的密码[字符限制:1~7]:");
			    		scanf("%s",upass);
			    		sprintf(sql,"update user set upass='%s' where uid='%s';",upass,Selfuid);
			    		// SQL语句对象的原始SQL语句字符串
			    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
			    		if( rs != SQLITE_OK )
			    		{
			      			printf("更新失败\n");
			      			sqlite3_close(db_point);
			      			return 0; // 返回-1 ，表示初始化失败
			    		}
			    		else
			    		{
			    			printf("更新成功\n");
			    			sqlite3_close(db_point);
			    		}
    					return 1;
    				default:puts("更改失败，请重新选择更改选项...");sleep(1);return 0;
    			}		
    		}		
    		if(i==2)
    		{
    			puts("请输入要更改信息的教工号:");
    			scanf("%s",uid);
    			sprintf(sql,"select * from teacher where uid='%s';",uid);
			rs = sqlite3_exec(db_point,sql,IsExist_cal_handle3,&flag,&zErrMsg);
			if( rs != SQLITE_OK )
	    		{	
	    			puts(zErrMsg);
	      			printf("删除失败\n");
	      			sqlite3_close(db_point);
	      			return 0; // 返回-1 ，表示初始化失败
	    		}
	    		else
	    		{
	    			if(flag==0)
	    			{
	    				printf("不存在此老师信息\n");
	    				sqlite3_close(db_point);
			      		return 0; // 返回-1 ，表示初始化失败
	    				
	    			}
	    			else
	    			{
	    				printf("请输入要更改的教师信息:\n");
		    			puts("-------------------------------");
		    			puts("1、密码");
		    			puts("2、姓名");
		    			puts("3、年龄");
		    			puts("4、性别");
		    			puts("5、管理班级");
		    			puts("-------------------------------");
		    			scanf("%d",&j);
		    			
		    			switch(j)
		    			{
		    				case 1:
		    					puts("请输入你更改后的密码[字符限制:1~7]:");
					    		scanf("%s",upass);
					    		sprintf(sql,"update user set upass='%s' where uid='%s';",upass,uid);
					    		// SQL语句对象的原始SQL语句字符串
					    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
					    		if( rs != SQLITE_OK )
					    		{
					      			printf("更新失败\n");
					      			sqlite3_close(db_point);
					      			return 0; // 返回-1 ，表示初始化失败
					    		}
					    		else
					    		{
					    			printf("更新成功\n");
					    			sqlite3_close(db_point);
					    		}
		    					return 1;
		    				case 2:
		    					puts("请输入你更改后的姓名[字符限制:1~7]:");
					    		scanf("%s",uname);
					    		sprintf(sql,"update teacher set uname='%s' where uid='%s';",uname,uid);
					    		// SQL语句对象的原始SQL语句字符串
					    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
					    		if( rs != SQLITE_OK )
					    		{
					      			printf("更新失败\n");
					      			sqlite3_close(db_point);
					      			return 0; // 返回-1 ，表示初始化失败
					    		}
					    		else
					    		{
					    			printf("更新成功\n");
					    			sqlite3_close(db_point);
					    		}
		    					return 1;
		    				case 3:
		    					puts("请输入你更改后的年龄:");
					    		scanf("%s",uage);
					    		sprintf(sql,"update teacher set uage='%s' where uid='%s';",uage,uid);
					    		// SQL语句对象的原始SQL语句字符串
					    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
					    		if( rs != SQLITE_OK )
					    		{
					      			printf("更新失败\n");
					      			sqlite3_close(db_point);
					      			return 0; // 返回-1 ，表示初始化失败
					    		}
					    		else
					    		{
					    			printf("更新成功\n");
					    			sqlite3_close(db_point);
					    		}
		    					return 1;
		    				case 4:
		    					puts("请输入你更改后的性别:");
					    		scanf("%s",usex);
					    		sprintf(sql,"update teacher set usex='%s' where uid='%s';",usex,uid);
					    		// SQL语句对象的原始SQL语句字符串
					    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
					    		if( rs != SQLITE_OK )
					    		{
					      			printf("更新失败\n");
					      			sqlite3_close(db_point);
					      			return 0; // 返回-1 ，表示初始化失败
					    		}
					    		else
					    		{
					    			printf("更新成功\n");
					    			sqlite3_close(db_point);
					    		}
		    					return 1;
		    				case 5:
		    					puts("请输入你更改后的管理班级:");
					    		scanf("%s",class);
					    		sprintf(sql,"update teacher set class='%s' where uid='%s';",class,uid);
					    		// SQL语句对象的原始SQL语句字符串
					    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
					    		if( rs != SQLITE_OK )
					    		{
					      			printf("更新失败\n");
					      			sqlite3_close(db_point);
					      			return 0; // 返回-1 ，表示初始化失败
					    		}
					    		else
					    		{
					    			printf("更新成功\n");
					    			sqlite3_close(db_point);
					    		}
		    					return 1;
		    				default:puts("更改失败，请重新选择更改选项...");sleep(1);return 0;
		    			}	
	    			}
	    		}	
    		}
							
         }
}


int UpdateTeacher(char *Selfuid)
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	char uid[MAXSIZE],upass[MAXSIZE],uname[MAXSIZE],usex[MAXSIZE],uage[MAXSIZE],class[MAXSIZE],Cgrade[MAXSIZE],Mgrade[MAXSIZE],Egrade[MAXSIZE];
	char sql[200];
	int rs,j;
	char *zErrMsg = 0;
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
		puts("请输入要更改信息的学号:");
		scanf("%s",uid);
		sprintf(sql,"select * from student,teacher where student.uid='%s' and teacher.uid='%s' and student.class=teacher.class;",uid,Selfuid);
		rs = sqlite3_exec(db_point,sql,IsExist_cal_handle3,&flag,&zErrMsg);
    		if( rs != SQLITE_OK )
    		{
    			puts(zErrMsg);
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
				printf("请输入要更改的学生信息:\n");
				puts("-------------------------------");
				puts("1、密码");
				puts("2、姓名");
				puts("3、年龄");
				puts("4、性别");
				puts("5、成绩");
				puts("6、所在班级");
				puts("-------------------------------");
				scanf("%d",&j);
				switch(j)
				{
					case 1:
						puts("请输入你更改后的密码[字符限制:1~7]:");
				    		scanf("%s",upass);
				    		sprintf(sql,"update user set upass='%s' where uid='%s';",upass,uid);
				    		// SQL语句对象的原始SQL语句字符串
				    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				    		if( rs != SQLITE_OK )
				    		{
				      			printf("更新失败\n");
				      			sqlite3_close(db_point);
				      			return 0; // 返回-1 ，表示初始化失败
				    		}
				    		else
				    		{
				    			printf("更新成功\n");
				    			sqlite3_close(db_point);
				    			return 1;
				    		}
						
					case 2:
						puts("请输入你更改后的姓名[字符限制:1~7]:");
				    		scanf("%s",uname);
				    		sprintf(sql,"update student set uname='%s' where uid='%s';",uname,uid);
				    		// SQL语句对象的原始SQL语句字符串
				    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				    		if( rs != SQLITE_OK )
				    		{
				      			printf("更新失败\n");
				      			sqlite3_close(db_point);
				      			return 0; // 返回-1 ，表示初始化失败
				    		}
				    		else
				    		{
				    			printf("更新成功\n");
				    			sqlite3_close(db_point);
				    		}
						return 1;
					case 3:
						puts("请输入你更改后的年龄:");
				    		scanf("%s",uage);
				    		sprintf(sql,"update student set uage='%s' where uid='%s';",uage,uid);
				    		// SQL语句对象的原始SQL语句字符串
				    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				    		if( rs != SQLITE_OK )
				    		{
				      			printf("更新失败\n");
				      			sqlite3_close(db_point);
				      			return 0; // 返回-1 ，表示初始化失败
				    		}
				    		else
				    		{
				    			printf("更新成功\n");
				    			sqlite3_close(db_point);
				    		}
						return 1;
					case 4:
						puts("请输入你更改后的性别:");
				    		scanf("%s",usex);
				    		sprintf(sql,"update student set usex='%s' where uid='%s';",usex,uid);
				    		// SQL语句对象的原始SQL语句字符串
				    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				    		if( rs != SQLITE_OK )
				    		{
				      			printf("更新失败\n");
				      			sqlite3_close(db_point);
				      			return 0; // 返回-1 ，表示初始化失败
				    		}
				    		else
				    		{
				    			printf("更新成功\n");
				    			sqlite3_close(db_point);
				    		}
						return 1;
					case 5:
						puts("请输入你更改后的语文、数学、英语成绩[没有成绩请输入NULL]:");
				    		scanf("%s%s%s",Cgrade,Mgrade,Egrade);
				    		sprintf(sql,"update student set Cgrade='%s',Mgrade='%s',Egrade='%s' where uid='%s';",Cgrade,Mgrade,Egrade,uid);
				    		// SQL语句对象的原始SQL语句字符串
				    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				    		if( rs != SQLITE_OK )
				    		{
				      			printf("更新失败\n");
				      			sqlite3_close(db_point);
				      			return 0; // 返回-1 ，表示初始化失败
				    		}
				    		else
				    		{
				    			printf("更新成功\n");
				    			sqlite3_close(db_point);
				    		}
						return 1;
					case 6:
						puts("请输入你更改后的所在班级:");
				    		scanf("%s",class);
				    		sprintf(sql,"update teacher set class='%s' where uid='%s';",class,uid);
				    		// SQL语句对象的原始SQL语句字符串
				    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
				    		if( rs != SQLITE_OK )
				    		{
				      			printf("更新失败\n");
				      			sqlite3_close(db_point);
				      			return 0; // 返回-1 ，表示初始化失败
				    		}
				    		else
				    		{
				    			printf("更新成功\n");
				    			sqlite3_close(db_point);
				    		}
						return 1;
					default:puts("更改失败，请重新选择更改选项...");sleep(1);return 0;
				}		
			}
		}
	}
}


int UpdateStudent(char *uid)
{
	/*变量定义*/
	sqlite3 *db_point=NULL;
	char upass[MAXSIZE];
	char *zErrMsg = 0;
	char sql[100];
	int rs,i;
	
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
    		puts("请输入你更改后的密码[字符限制:1~7]:");
    		scanf("%s",upass);
    		sprintf(sql,"update user set upass='%s' where uid='%s';",upass,uid);
    		// SQL语句对象的原始SQL语句字符串
    		rs = sqlite3_exec(db_point,sql,NULL,NULL,NULL);
    		if( rs != SQLITE_OK )
    		{
      			printf("更新失败\n");
      			sqlite3_close(db_point);
      			return 0; // 返回-1 ，表示初始化失败
    		}
    		else
    		{
    			printf("更新成功\n");
    			sqlite3_close(db_point);
      			return 1;
    		}
    		
    	}
    	
}

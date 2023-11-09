#include "select.h"
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>


void ShowAdminTable(int k)
{
	   sqlite3 *db=NULL;
	   char *errMsg = 0;
	   int rs,nRow = 0, nColumn = 0,i,j;
	   char *sql;
	   char **dbResult;
	   //const char* data = "Callback function called";

	   /* Open database */
	   rs = sqlite3_open("SMS.db", &db);
	   if( rs ){
	      fprintf(stderr, "打不开数据库: %s\n", sqlite3_errmsg(db));
	      return 0;
	   }
	   if(k==1)
	   {
	   	strcpy(sql,"SELECT * from user;");
	   }
	   if(k==2)
	   {
	   	strcpy(sql,"SELECT * from teacher;");
	   }
	   /* Create SQL statement */
	   

	   /* Execute SQL statement */
	   /*数据库取出权限值*/
		rs = sqlite3_get_table(db,sql,&dbResult,&nRow,&nColumn,&errMsg);
		//printf("%d %d\n",nRow,nColumn);
		if(rs == SQLITE_OK)
		    {
		    	printf("---------------------------------\n");
		    	for(i=1;i<=nColumn;i++)
		    	{
		    		printf("%s \t",dbResult[0*nColumn+i-1]);
		    	}
		    	printf("\n---------------------------------\n");
		    	for(i=1;i<=nRow;i++)
		    	{
		    		for(j=1;j<=nColumn;j++)
		    		{
		    			printf("%s \t",dbResult[i*nColumn+j-1]);
		    		}
		    		printf("\n---------------------------------\n");
		    	}			
			sqlite3_free_table(dbResult);
		    }
		else
		    {
			printf("取值失败(按Enter键进行下一步)...");
			getchar();
		    }
		    
 	   printf("\n请按Enter键进行下一步...\n");
 	   getchar();getchar();
 	   
	   sqlite3_close(db);
	   
	   return 0;
}


void ShowStudentTable(char *Selfuid)
{
	   sqlite3 *db=NULL;
	   char *errMsg = 0;
	   int rs,nRow = 0, nColumn = 0,i,j;
	   char *sql;
	   char **dbResult;
	   //const char* data = "Callback function called";

	   /* Open database */
	   rs = sqlite3_open("SMS.db", &db);
	   if( rs ){
	      fprintf(stderr, "打不开数据库: %s\n", sqlite3_errmsg(db));
	      return 0;
	   }
	   
	   /* Create SQL statement */
	   sprintf(sql,"SELECT Cgrade,Mgrade,Egrade from student where student.uid='%s';",Selfuid);

	   /* Execute SQL statement */
	   /*数据库取出权限值*/
		rs = sqlite3_get_table(db,sql,&dbResult,&nRow,&nColumn,&errMsg);
		//printf("%d %d\n",nRow,nColumn);
		if(rs == SQLITE_OK)
		    {
		    	printf("---------------------------------\n");
		    	for(i=1;i<=nColumn;i++)
		    	{
		    		printf("%s \t",dbResult[0*nColumn+i-1]);
		    	}
		    	printf("\n---------------------------------\n");
		    	for(i=1;i<=nRow;i++)
		    	{
		    		for(j=1;j<=nColumn;j++)
		    		{
		    			printf("%s \t",dbResult[i*nColumn+j-1]);
		    		}
		    		printf("\n---------------------------------\n");
		    	}
			
			sqlite3_free_table(dbResult);
		    }
		else
		    {
			printf("取值失败(按Enter键进行下一步)...");
			getchar();
		    }
	   sqlite3_close(db);
	   
	   printf("\n请按Enter键进行下一步...\n");
 	   getchar();getchar();
	   
	   return 0;
}


void ShowTeacherTable(char *Selfuid)
{
	   sqlite3 *db=NULL;
	   char *errMsg = 0;
	   int rs,nRow = 0, nColumn = 0,i,j;
	   char *sql;
	   char **dbResult;
	   //const char* data = "Callback function called";

	   /* Open database */
	   rs = sqlite3_open("SMS.db", &db);
	   if( rs ){
	      fprintf(stderr, "打不开数据库: %s\n", sqlite3_errmsg(db));
	      return 0;
	   }
	   
	   /* Create SQL statement */
	   sprintf(sql,"SELECT distinct student.* from student,teacher where student.class=(select class from teacher where uid='%s');",Selfuid);

	   /* Execute SQL statement */
	   /*数据库取出权限值*/
		rs = sqlite3_get_table(db,sql,&dbResult,&nRow,&nColumn,&errMsg);
		//printf("%d %d\n",nRow,nColumn);
		if(rs == SQLITE_OK)
		    {
		    	printf("-----------------------------------------------\n");
		    	for(i=1;i<=nColumn;i++)
		    	{
		    		printf("%s \t",dbResult[0*nColumn+i-1]);
		    	}
		    	printf("\n-----------------------------------------------\n");
		    	for(i=1;i<=nRow;i++)
		    	{
		    		for(j=1;j<=nColumn;j++)
		    		{
		    			printf("%s \t",dbResult[i*nColumn+j-1]);
		    		}
		    		printf("\n-----------------------------------------------\n");
		    	}
			
			sqlite3_free_table(dbResult);
		    }
		else
		    {
			printf("取值失败(按Enter键进行下一步)...");
			getchar();
		    }
		    
	   printf("\n请按Enter键进行下一步...\n");
 	   getchar();getchar();
	   sqlite3_close(db);
	   return 0;
}

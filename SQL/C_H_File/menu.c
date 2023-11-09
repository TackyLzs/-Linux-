#include "menu.h"
#include "insert.h"
#include "delete.h"
#include "update.h"
#include "select.h"
#include <sqlite3.h>
#include <stdio.h>

void AdminMenuOption(char *uid)
{
	int i;
	while(1)
	{
		printf("<------管理员界面------>\n");
		printf("1、增加教师数据\n");
		printf("2、删除教师数据\n");
		printf("3、更改教师数据\n");
		printf("4、查询教师数据\n");
		printf("5、增加管理员数据\n");
		printf("6、删除管理员数据\n");
		printf("7、更改管理员数据\n");
		printf("8、查询管理员数据\n");
		printf("9、注销用户\n");
		printf("10、退出系统\n");	
		printf("------------------------\n");
		printf("请输入你想操作的序号：");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
				system("clear");
				AddTeacher();
				sleep(1);
				system("clear");
				break;
			case 2:
				system("clear");
				DeleteAdmin(uid,2);
				sleep(1);
				system("clear");
				break;
			case 3:
				system("clear");
				UpdateAdmin(uid,2);
				sleep(1);
				system("clear");
				break;
			case 4:
				system("clear");
				ShowAdminTable(2);
				sleep(1);
				system("clear");
				break;
			case 5:
				system("clear");
				AddAdmin();
				sleep(1);
				system("clear");
				break;
			case 6:
				system("clear");
				DeleteAdmin(uid,1);
				sleep(1);
				system("clear");
				break;
			case 7:
				system("clear");
				UpdateAdmin(uid,1);
				sleep(1);
				system("clear");
				break;
			case 8:
				system("clear");
				ShowAdminTable(1);
				sleep(1);
				system("clear");
				break;
			case 9:
				system("clear");
				SelfDeleteAdmin(uid);
				sleep(1);
				system("clear");
				exit(0);
			case 10:system("clear");puts("欢迎下次使用本系统...");sleep(1);system("clear");exit(0);system("clear");
			default: printf("输入序号有误,请重新输入序号...\n");
		}
	}
}

void TeacherMenuOption(char *uid)
{
	int i;
	while(1)
	{
		printf("<-------教师界面------->\n");
		printf("1、增加学生数据\n");
		printf("2、删除学生数据\n");
		printf("3、更改学生数据\n");
		printf("4、查询学生数据\n");
		printf("5、注销用户\n");
		printf("6、退出系统\n");	
		printf("------------------------\n");
		printf("请输入你想操作的序号：");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
				system("clear");
				AddStudent();
				sleep(1);
				system("clear");
				break;
			case 2:
				system("clear");
				DeleteTeacher(uid);
				sleep(1);
				system("clear");
				break;
			case 3:
				system("clear");
				UpdateTeacher(uid);
				sleep(1);
				system("clear");
				break;
			case 4:
				system("clear");
				ShowTeacherTable(uid);
				sleep(1);
				system("clear");
				break;
			case 5:
				system("clear");
				SelfDeleteTeacher(uid);
				sleep(1);
				system("clear");
				exit(0);
			case 6:system("clear");puts("欢迎下次使用本系统...");sleep(1);system("clear");exit(0);system("clear");
			default: printf("输入序号有误,请重新输入序号...\n");
		}
	}
}

void studentMenuOption(char *uid)
{
	int i;
	while(1)
	{
		printf("<-------学生界面------->\n");
		printf("1、查询成绩\n");
		printf("2、修改密码\n");
		printf("3、注销用户\n");
		printf("4、退出系统\n");	
		printf("------------------------\n");
		printf("请输入你想操作的序号：");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
				system("clear");
				ShowStudentTable(uid);
				sleep(1);
				system("clear");
				break;
			case 2:
				system("clear");
				UpdateStudent(uid);
				sleep(1);
				system("clear");
				break;
			case 3:
				system("clear");
				SelfDeleteStudent(uid);
				sleep(1);
				system("clear");
				exit(0);
			case 4:system("clear");puts("欢迎下次使用本系统...");sleep(1);system("clear");exit(0);
			default: printf("输入序号有误,请重新输入序号...\n");
		}
	}
}





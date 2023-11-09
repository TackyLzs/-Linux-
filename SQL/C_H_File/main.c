#include "main.h"
#include "login.h"
#include "init.h"
//主函数
int main()
{	
	system("clear");
	//1、数据库配置初始化
	DatabaseInit();
	//2、开始登入界面
	LoginOption();
}


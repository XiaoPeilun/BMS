#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>


#define STU_FORMAT "%-1d %-11s %-24s %-24s %-15s %-24s %-4s %-15s %-24s "
#define STU_INPUT student[i].flag,student[i].num,student[i].password,student[i].email,student[i].telnum,student[i].major,student[i].gender,student[i].name,student[i].faculty


#define ADM_FORMAT "%-24s %-24s %-24s %-24s"
#define ADM_INPUT admin[i].num,admin[i].password,admin[i].email,admin[i].name

#define RECORD_FORMAT "%-d %-d %-10s %-11s %-24s %-24s %-4d %-4d %-4d %-4d %-4d %-4d %-10ld %-4d %-4d %-4d %-4d %-4d %-4d %-ld"

#define BOOK_FORMAT "%-3d %-3d %-8.2lf %-8.2lf  %-10s %-25s %-25s %-25s %-25s %-5s %-s"

#define ADMINMAX   10 	/*假设管理员上限10人*/
#define STUDENTMAX 50	/*假设学生上限50人*/
#define RECORDMAX  1000 /*假设借阅记录上限1000条*/
#define BOOKMAX    100  /*假设书本上限100本*/

#define STRSIZE 25  /*一般字符串长度*/

struct STUDENT
{
	int flag;         	 		/*0 表示正常 ， 1表示被管理员冻结*/
	char num[STRSIZE]; 			/*学号*/
	char password[STRSIZE];  	/*密码*/
	char email[STRSIZE];  		/*邮箱*/
	char telnum[STRSIZE];  		/*电话号码*/
	char major[STRSIZE]; 		/*专业*/
	char gender[STRSIZE]; 		/*性别*/
	char name[STRSIZE];  		/*姓名*/
	char faculty[STRSIZE]; 		/*学院*/
}student[STUDENTMAX];			/*STUDENTMAX可以修改*/
int student_count = 0;  		 /*记录学生人数*/
int student_current = 0;		 /*如果当前为学生登录端，记录当前学生在结构体中位置*/
						 	 	 /*如果当前为管理员登录端，记录修改学生*/


struct ADMIN
{
		char num[STRSIZE];      	/*工号*/
		char password[STRSIZE];		/*密码*/
		char email[STRSIZE];		/*邮箱*/
		char name[STRSIZE];			/*姓名*/	
}admin[ADMINMAX];
int admin_count = 0;
int admin_current = 0;

struct Book
{
	int number;						/*图书总数量*/
	int frequency;     				/*借阅次数*/
	double totaltime;       		/*单位为小时*/
	double price;					/*价格*/
	char book_num[STRSIZE];    		/*图书编号*/
	char publishinghouse[STRSIZE];	/*出版社*/
	char name[STRSIZE];				/*书名*/
	char author[STRSIZE];			/*作者*/
	char date[STRSIZE];  			/*出版日期*/
	char location[STRSIZE];			/*书架*/
	char brief[120];				/*简介*/
}book[BOOKMAX];
int book_count = 0;

struct Time
{
    int year,month,day;
    int hour,minute,second;
    time_t rawtime;				/*从某一时刻到现在时间的秒数*/
};

struct Record
{
	int b_r;					/*借阅还是续借？0为借阅，1为续借*/
	int back;              		/*是否已还？0为未还，1为已还*/
	char book_num[STRSIZE];		/*书的编号*/
	char student_num[STRSIZE];	/*学生学号*/
	char book_name[STRSIZE];	/*书名*/
	char student_name[STRSIZE];	/*学生姓名*/
	struct Time borrowtime; 	/*借阅或续借时间*/
	struct Time backtime;		/*归还时间*/
}record[RECORDMAX];
int record_count= 0;


time_t logintime ;    /*记录登录时间*/


/**************************最开始界面，选择身份**************************/
int StartMenu();

void Stu_Login();
void Show_Student();
int Show_StudentMenu();
void Show_Freeze();

void Admin_Login();
void Show_Admin();
int Show_AdminMenu();

/*载入学生和管理员信息*/
void Load_StuInfo();
void Load_AdminInfo();
void Load_BookInfo();
void Load_RecordInfo();


/***************************退出及注销****************************/
void Quit();/*退出*/
void Logout();/*注销*/



/****记录登录时间，作为判断是否出馆依据(默认退出程序之后代表出馆)****/
void LoginTime();


/************************学生功能菜单二级菜单**************************/

void Book_Borrow();    /*图书借阅*/
void Book_Revert();    /*图书归还*/
void Book_Renew();    /*图书续借*/
void Record_Check();  /*查询借阅结果*/
void Record_Delete() ;   /*借阅记录删除*/

void Book_StuInquiry();    /*图书查询*/
int Book_StuInquiry_Menu(); /*图书查询菜单*/

void StudentInfo_Modify() ;/*学生信息修改*/
int StuInfo_Modify_Menu();/*学生信息修改菜单*/

/**********************三级功能************************/

void StuInfo_Modify_Password(); /*改密码*/
void StuInfo_Modify_Email();/*改邮箱*/
void StuInfo_Modify_Tel();/*改电话号码*/

void Book_Inquiry_Byauthor(); /*根据作者查询图书*/
void Book_Inquiry_Byname2();   /*根据名字查询图书*/
void Frequency_Inordering2();  /*根据借阅次数排序*/
void Price_Inordering(); /*根据价格排序*/


int Stu_IdCheck(char *); /*学号检查*/
int Stu_PasswdCheck(char *);/*密码检查*/

int SearchnumByname(char *);  /*通过书名找到图书编号*/
int CheckIfborrow(char *);   /*判断该书是否已被此人借阅*/
int JudgeStuBorrow(char *) ; /*判断学生是否正在借阅该书*/
int JudgeIftwice(char *);/*判断是否续借超过两次*/

/************************************************************************/

/*管理员功能菜单二级功能*/
/********************************/
int AdminInfo_Modify_Menu();/*管理员信息修改*/
void AdminInfo_Modify();/**/
void AdminInfo_Modify_Password();/**/
void AdminInfo_Modify_Email();/**/

/********************************/

void BookManagement();/*图书管理*/
int BookManagement_Menu();/*图书管理菜单*/

void Book_Inquiry();/*图书查询*/
int Book_Inquiry_Menu();/**/
void Book_Inquiry_Bypublishinghouse();/*通过出版社查询图书*/
void Book_Inquiry_Byname();/*通过名字查询图书*/

void Book_Add();	/*图书添加*/
void Book_Delete();	/*图书删除*/
void Book_Modify();	/*图书修改*/
/********************************/
int BorrowManagement_Menu();/*借阅管理*/
void BorrowManagement();/**/


int BorrowInfo_Show_Menu();/*查询借阅情况*/
void BorrowInfo_Show();/**/
void Borrow_AllShow();/*查询所有图书借阅情况*/
void StudentBorrowInfo_Show();/*查询借阅图书学生情况*/
void OverdueStudent_Show();/*查询未还书学生*/
void OverdueBook_Show();/*查询未还书图书*/

void BorrowInfo_Count();/*统计借阅信息*/
int BorrowInfo_Count_Menu();/*统计借阅信息菜单*/
void Major_Inordering();/*排序专业内借阅量*/
void Frequency_Inordering();/*按借阅次数排序*/
void Time_Inordering();/*按借阅时长排序*/

void AccountManagement();/*账号管理*/
int AccountManagement_Menu();/**/
void Freeze();/*冻结账号*/
void Unfreeze();/*解冻账号*/
/********************************/

int Check_Freeze();/*监测账号是否被冻结*/
int Admin_IdCheck(char *);/*工号检测*/
int Admin_PasswdCheck(char *);/*密码检测*/
int Numberexist(char *);/*检测书的编号是否重复*/
int Numberformat_check(char *) ;/*检测书编号的格式*/
int Locationexist(char *);/*检测书架位置是否重复*/

int IdformatJudge(char *);/*账号格式检测*/
int Telformat_check(char *);/*电话号码格式检测*/
int EmailFormat_check(char *);/*邮箱格式检测*/
int CheckBookborrow(char *);

/*****************************主函数*******************************/

int main()
{
	int student_admin_choose;

	Load_StuInfo();
	Load_AdminInfo();
	Load_BookInfo();
	Load_RecordInfo();
	LoginTime();

	student_admin_choose = StartMenu();

	if(student_admin_choose == 1 )
	{
		Stu_Login();
		Show_Student();
	}

	if(student_admin_choose == 2 )
	{
		Admin_Login();
		Show_Admin();
	}

	return 0;
}

/***********************************初始信息读入******************************/

void Load_StuInfo()
{
	FILE *fp;
	int i = 0 ;   /*循环变量*/

	if((fp = fopen("student_info.txt","r")) == NULL)
		{
			printf("无法打开该文件\n");
			exit(1);
		}

	while(!feof(fp))
	{
		fscanf(fp,"%d%s%s%s%s%s%s%s%s",&student[i].flag,student[i].num,student[i].password,student[i].email,student[i].telnum,student[i].major,student[i].gender,student[i].name,student[i].faculty);
		i++;
	}

	student_count = i - 1 ;

	fclose(fp);
}

void Load_AdminInfo()
{
	FILE *fp;
	int i = 0 ;   /*循环变量*/

	if((fp = fopen("admin_info.txt","r")) == NULL)
		{
			printf("无法打开该文件\n");
			exit(1);
		}

	while(! feof(fp))
	{
		fscanf(fp,"%s%s%s%s",admin[i].num,admin[i].password,admin[i].email,admin[i].name);
		i++;
	}

	admin_count = i - 1 ;

	fclose(fp);
}

void Load_BookInfo()
{
	FILE *fp;
	int i = 0 ;   /*循环变量*/

	if((fp = fopen("book_info.txt","r")) == NULL)
		{
			printf("无法打开该文件\n");
			exit(1);
		}

	while(! feof(fp))
	{
		fscanf(fp,"%d%d%lf%lf%s%s%s%s%s%s%s",&book[i].number,&book[i].frequency,&book[i].totaltime,&book[i].price,book[i].book_num,book[i].publishinghouse,book[i].name,book[i].author,book[i].date,book[i].location,book[i].brief);
		i++;
	}

	book_count = i - 1;

	fclose(fp);
}

void Load_RecordInfo()
{
	FILE *fp;
	int i = 0 ;   /*循环变量*/

	if((fp = fopen("record_info.txt","r")) == NULL)
		{
			printf("无法打开该文件\n");
			exit(1);
		}

	while(! feof(fp))
	{
		fscanf(fp,"%d%d%s%s%s%s%d%d%d%d%d%d%ld%d%d%d%d%d%d%ld",&record[i].b_r,&record[i].back,record[i].book_num,record[i].student_num,record[i].book_name,record[i].student_name,&record[i].borrowtime.year,&record[i].borrowtime.month,&record[i].borrowtime.day,&record[i].borrowtime.hour,&record[i].borrowtime.minute,&record[i].borrowtime.second,&record[i].borrowtime.rawtime,&record[i].backtime.year,&record[i].backtime.month,&record[i].backtime.day,&record[i].backtime.hour,&record[i].backtime.minute,&record[i].backtime.second,&record[i].backtime.rawtime);
		i++;
	}
	record_count = i - 1 ;

	fclose(fp);
}
/***********************************************************************/

void LoginTime()     /*记录登录时间，作为判断是否出馆依据(默认退出程序之后代表出馆)*/
{
    time_t nowtime;

    time( &nowtime );

	logintime = nowtime;

}


/***********************************************************************/

int StartMenu()
{
	int choice;
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t╔═══════════════════════════════╗\n");
	printf("\t║                      欢迎访问图书馆借阅系统                  ║\n");
	printf("\t╠═══════════════════════════════╣\n");
	printf("\t║\t\t\t1 - 学生入口                            ║\n");
	printf("\t║\t\t\t2 - 管理员入口                          ║\n");
	printf("\t╚═══════════════════════════════╝\n");
	printf("\n\t\t  请输入你的选择：");

	do{
		fflush(stdin);
		scanf("%d",&choice);
		if(choice < 1 || choice > 2)
		printf("\t\t  您的输入有误,请重新输入:");

	}while(choice < 1 || choice > 2);

	fflush(stdin);

	return choice;
}


/******************************注销与退出******************************/
void Logout()
{
	fflush(stdin);
	main();
}

void Quit()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t╔════════════════════════════════╗\n");
	printf("\t║                 谢谢使用图书馆借阅系统 !                       ║\n");
	printf("\t╠════════════════════════════════╣\n");
	printf("\t║\t\t\t                                          ║\n");
	printf("\t║\t\t\t按任意键退出....                          ║\n");
	printf("\t║\t\t\t                                          ║\n");
	printf("\t╚════════════════════════════════╝\n");
	fflush(stdin);
	getch();
	exit(0);
}

/*********************************管理员端*****************************/
void Show_Admin()
{
	switch(Show_AdminMenu())
	{
		case 1  : BookManagement();break;
		case 2  : BorrowManagement();break;
		case 3  : BorrowInfo_Count();break;
		case 4  : AdminInfo_Modify();break;
		case 5  : Logout();break;
		case 6  : Quit();break;
	}
}

int Show_AdminMenu()
{
		int choice;
		
		fflush(stdin);
	 	system("cls");
	    printf("\n\n\n\n\n");
	    printf("\t╔════════════════════════════════╗\n");
	    printf("\t║              欢迎访问图书馆借阅系统 （管理员端）               ║\n");
	    printf("\t╠════════════════════════════════╣\n");
	    printf("\t║\t\t1  - 图书管理                                     ║\n");
	    printf("\t║\t\t2  - 借阅管理                                     ║\n");
	    printf("\t║\t\t3  - 借阅信息统计                                 ║\n");
	    printf("\t║\t\t4  - 个人信息修改                                 ║\n");
	    printf("\t║\t\t5  - 注销                                         ║\n");
	    printf("\t║\t\t6  - 退出                                         ║\n");
	    printf("\t╚════════════════════════════════╝\n");
	    printf("\t\t  请输入你的选择(1-6):");

	    do{
	    		fflush(stdin);
	    		scanf("%d", &choice);

	    		if(choice < 1 || choice > 6)
	    		printf("\t\t  您的输入有误,请重新输入:");

	    }while(choice < 1 || choice > 6);

	    fflush(stdin);

	    return choice;
}

void Admin_Login()
{
		char id[STRSIZE];
		char passwd[STRSIZE];

		system("cls");
		printf("\n\n\n\n\n");
		printf("\t╔═══════════════════════════════╗\n");
		printf("\t║            欢迎访问图书馆借阅系统 （管理员端）               ║\n");
		printf("\t╠═══════════════════════════════╣\n");
		printf("\t\t  请输入您的工号（ 10 位数字）：");

		scanf("%s",id);

		while(IdformatJudge(id) || Admin_IdCheck(id))
		{
			fflush(stdin);
			printf("\t\t  工号错误，请输入正确工号：");
			scanf("%s",id);
		}

		printf("\t\t  请输入您的密码 ：");

		scanf("%s",passwd);

		while(Admin_PasswdCheck(passwd))
		{
				fflush(stdin);
				printf("\t\t  密码错误，请输入正确密码：");
				scanf("%s",passwd);
		}

		printf("\t\t  登陆成功，按任意键继续.");
		getch();
}


/**********图书借阅管理二级菜单************/

void BorrowManagement()
{
	switch(BorrowManagement_Menu())
	{
	case 1 : BorrowInfo_Show();break;
	case 2 : AccountManagement();break;
	case 3 : Show_Admin();
	}
}

int BorrowManagement_Menu()
{
	int choice;

	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t╔════════════════════════════╗\n");
	printf("\t\t║                    图书借阅管理                        ║\n");
	printf("\t\t╠════════════════════════════╣\n");
    printf("\t\t║\t\t1  - 借阅情况查询                         ║\n");
	printf("\t\t║\t\t2  - 借阅账户管理                         ║\n");
	printf("\t\t║\t\t3  - 返回上一级菜单                       ║\n");
	printf("\t\t╚════════════════════════════╝\n");
	printf("\t\t  请输入你的选择(1-3):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 3)
		    		printf("\t\t  您的输入有误,请重新输入:");

	}while(choice < 1 || choice > 3);

	fflush(stdin);

	return choice;
}

/*******借阅账户管理三级菜单******/

void AccountManagement()
{
	switch(AccountManagement_Menu())
	{
		case 1 : Freeze();break;
		case 2 : Unfreeze();break;
		case 3 : BorrowManagement();break;
	}
}


int AccountManagement_Menu()
{
	int choice;
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t╔════════════════════════════╗\n");
	printf("\t\t║                    借阅账号管理                        ║\n");
	printf("\t\t╠════════════════════════════╣\n");
    printf("\t\t║\t\t1  - 账号冻结                             ║\n");
	printf("\t\t║\t\t2  - 账号解冻                             ║\n");
	printf("\t\t║\t\t3  - 返回上一级菜单                       ║\n");
	printf("\t\t╚════════════════════════════╝\n");
	printf("\t\t  请输入你的选择(1-3):");

	do
	{
		 fflush(stdin);
		 scanf("%d", &choice);

		 if(choice < 1 || choice > 3)
		     printf("\t\t  您的输入有误,请重新输入:");

	}while(choice < 1 || choice > 3);

	fflush(stdin);

	return choice;
}

/*四级功能学生账户冻结*/
void Freeze()
{
	int i;
	char id[STRSIZE];
	char choice1,choice2;
	FILE *fp;

	printf("\n\t\t  请输入要冻结的学号：");
	scanf("%s",id);

	while(IdformatJudge(id) || Stu_IdCheck(id))
	{
		fflush(stdin);
		printf("\t\t  未找到输入学号，请再次输入：");
		scanf("%s",id);
	}

	printf("\t\t  成功找到该学号，是否要冻结？(y or n) ");

	do
	{
		fflush(stdin);
		scanf("%c", &choice1);

		if(choice1 != 'y' && choice1 != 'n')
			   printf("\t\t  您的输入有误,请重新选择:");

	}while(choice1 != 'y' && choice1 != 'n');


	if(choice1 == 'y')
	{
		if(Check_Freeze() == 1)
		{

			printf("\t\t  该账户已被冻结..");
			printf("\t\t  是否继续冻结其他账户？(y or n): ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice2);

				if(choice2 != 'y' && choice2 != 'n')
						   printf("\t\t  您的输入有误,请重新选择:");

			}while(choice2 != 'y' && choice2 != 'n');

			if(choice2 == 'y')
			{
				Freeze();
			}
			else
			{
				 printf("\t\t  按任意键返回上一级菜单...");
				 getch();
				 AccountManagement();
			}
		}
		else
		{
			student[student_current].flag = 1 ;

			if((fp = fopen("student_info.txt","w")) == NULL)
				{
					printf("无法打开该文件\n");
					exit(1);
				}

			for(i = 0 ; i < student_count; i++)
			{
				fprintf(fp,STU_FORMAT,STU_INPUT);
				fputs("\n",fp);
			}
			fclose(fp);

			printf("\t\t  该账户已成功被冻结.");
			printf("\n\t\t  是否继续冻结其他账户？(y or n): ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice2);

				if(choice2 != 'y' && choice2 != 'n')
					printf("\t\t  您的输入有误,请重新选择:");

			}while(choice2 != 'y' && choice2 != 'n');

			if(choice2 == 'y')
				{
					Freeze();
				}
				else
				{
					printf("\t\t  按任意键返回上一级菜单...");
					getch();
					AccountManagement();
				}

		}
	}

	else
	{
		printf("\t\t  按任意键返回上一级菜单...");
		getch();
		AccountManagement();
	}
}

/*四级功能学生账户解冻*/

void Unfreeze()
{
	char id[STRSIZE];
	char choice1,choice2;
	int i ;
	FILE *fp;

	printf("\n\t\t  请输入要解冻的学号：");
	scanf("%s",id);

	while(IdformatJudge(id) || Stu_IdCheck(id))
		{
			fflush(stdin);
			printf("\t\t  未找到输入学号，请再次输入：");
			scanf("%s",id);
		}

	for( i = 0 ;  i < student_count ; i++)
	{
		if(strcmp(student[i].num , id) == 0 )
		{
			student_current = i ;
			break;
		}
	}

				if(Check_Freeze() == 0)
				{
					printf("\t\t  该账户未被冻结..");
					printf("\t\t  是否继续解冻其他账户？(y or n): ");

					do
					{
						fflush(stdin);
						scanf("%c", &choice2);

						if(choice2 != 'y' && choice2 != 'n')
								   printf("\t\t  您的输入有误,请重新选择:");

					}while(choice2 != 'y' && choice2 != 'n');

					if(choice2 == 'y')
					{
						Unfreeze();
					}
					else
					{
						 printf("\t\t  按任意键返回上一级菜单...");
						 getch();
						 AccountManagement();
					}
				}

	printf("\t\t  成功找到该学号，是否要解冻？(y or n) ");

		do
		{
			fflush(stdin);
			scanf("%c", &choice1);

			if(choice1 != 'y' && choice1 != 'n')
				   printf("\t\t  您的输入有误,请重新选择:");

		}while(choice1 != 'y' && choice1 != 'n');


		if(choice1 == 'y')
		{

				student[student_current].flag = 0 ;

				if((fp = fopen("student_info.txt","w")) == NULL)
							{
								printf("无法打开该文件\n");
								exit(1);
							}

						for(i = 0 ; i < student_count; i++)
						{
							fprintf(fp,STU_FORMAT,STU_INPUT);
							fputs("\n",fp);
						}
				fclose(fp);

				printf("\t\t  该账户已成功被解冻.");
				printf("\n\t\t  是否继续解冻其他账户？(y or n): ");

				do
				{
					fflush(stdin);
					scanf("%c", &choice2);

					if(choice2 != 'y' && choice2 != 'n')
						printf("\t\t  您的输入有误,请重新选择:");

				}while(choice2 != 'y' && choice2 != 'n');

				if(choice2 == 'y')
					{
						Unfreeze();
					}
				else
					{
						printf("\t\t  按任意键返回上一级菜单...");
						getch();
						AccountManagement();
					}
			
		}

		else
		{
			printf("\t\t  按任意键返回上一级菜单...");
			getch();
			AccountManagement();
		}
}

int Check_Freeze()   /*如果被冻结返回1 ，未被冻结返回0 */
{
	if(student[student_current].flag == 1 )
		return 1;

	return 0;
}

/*******借阅信息查看三级菜单*********/

void BorrowInfo_Show()
{
		switch(BorrowInfo_Show_Menu())
	{
		case 1 : Borrow_AllShow();break;
		case 2 : StudentBorrowInfo_Show();break;
		case 3 : OverdueBook_Show();break;
		case 4 : OverdueStudent_Show();break;
		case 5 : BorrowManagement();break;
	}
}


int BorrowInfo_Show_Menu()
{
	int choice;

	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t╔════════════════════════════╗\n");
	printf("\t\t║                      借阅情况查询                      ║\n");
	printf("\t\t╠════════════════════════════╣\n");
    printf("\t\t║\t\t1  - 查看所有图书借阅情况                 ║\n");
	printf("\t\t║\t\t2  - 查询借阅图书学生信息                 ║\n");
	printf("\t\t║\t\t3  - 查询超期未还图书                     ║\n");
	printf("\t\t║\t\t4  - 查询超期未还学生                     ║\n");
	printf("\t\t║\t\t5  - 返回上一级菜单                       ║\n");
	printf("\t\t╚════════════════════════════╝\n");
	printf("\t\t  请输入你的选择(1-5):");

	do
	{
		 fflush(stdin);
		 scanf("%d", &choice);

		 if(choice < 1 || choice > 5)
		     printf("\t\t  您的输入有误,请重新输入:");

	}while(choice < 1 || choice > 5);

	fflush(stdin);

	return choice;
}

/*三级功能 查看所有图书借阅情况*/
void Borrow_AllShow()
{
	int i ;	/*循环变量,控制book*/
	int j ; /*循环变量，控制record*/
	int n ;
	
	Load_RecordInfo();
	Load_BookInfo();

	printf("\n\n (注 ：以下依次是书名，图书编号，在馆数量，已借数量，作者，价格，出版社，出版时间，书架位置，图书简介 ) \n\n ");

	for( i = 0 ; i < book_count ; i++)
	{
		n = 0;

		for( j = 0 ; j < record_count ; j++)
		{
			if(strcmp(record[j].book_num,book[i].book_num ) == 0 )
				{
					if(record[j].back == 0)
						{
							n++;
						}
				}
		}

		if( n > 0)
					printf(" %-20s\t%s\t%d\t%d\t%-10s\t%.2lf\t%s\t%s\t%s\t%s\n",book[i].name,book[i].book_num,book[i].number-n,n,book[i].author,book[i].price,book[i].publishinghouse,book[i].date,book[i].location,book[i].brief);

	}

	printf("\n\n 以上仅显示已借阅图书信息. ");
	printf(" 按任意键返回上一级菜单. ");
	getch();

	BorrowInfo_Show();

}

/*四级功能查询借阅图书学生信息*/

void StudentBorrowInfo_Show()
{
	char stu_name[STRSIZE];
	char book_name[STRSIZE];

	int i ;	
	int j ; 
	int n  = 0 ;

	printf("\t\t  查询借某书的某位同学，请输入要查询的学生姓名:");
	scanf("%s",stu_name);
	printf("\t\t  请输入要查询的书名:");
	scanf("%s",book_name);

	printf("\n");

	for( j = 0 ; j < record_count ; j++)
	{
		if(strcmp(stu_name,record[j].student_name) == 0)
		{
			if(strcmp(book_name,record[j].book_name) == 0)
			{
				for( i = 0 ; i < student_count ; i++)
				{
					if(strcmp(student[i].name,record[j].student_name) == 0)
					{
						if(record[j].back == 0)
						{
							n++;
							printf("该生于%d年%d月%d日%d时借阅该书.\n\n",record[j].borrowtime.year,record[j].borrowtime.month,record[j].borrowtime.day,record[j].borrowtime.hour);
							printf(" 以下是该生的详细信息: \n");
							printf("（注：下列一次是学生姓名，学号，邮箱，电话号码，专业，性别，学院）\n\n");
							printf(" %s\t%s\t%s\t%s\t%s\t%s\t%s\t",student[i].name,student[i].num,student[i].email,student[i].telnum,student[i].major,student[i].gender,student[i].faculty);
							break;
						}
					}
				}
			}
		}
	}

	if( n > 0)
	{
		printf("\n\n 按任意键返回上一级菜单.. ");
		getch();
		BorrowInfo_Show();
	}

	if( n == 0)
	{
		printf("\t\t 无此学生借此书的记录. ");
		printf("\n\t\t 按任意键返回上一级菜单.. ");
		getch();
		BorrowInfo_Show();
	}


}


/*四级功能查询超期未还图书*/

void OverdueBook_Show()
{
	int i;
	int n = 0 ; 	/*计数*/
    
	time_t nowtime;

	time( &nowtime );

	Load_RecordInfo();
	Load_BookInfo();

	printf(" 查询结果如下: \n");
	printf("（注：下列依次显示的是 书名，图书编号，借阅者，借阅者学号，借阅时间）\n\n");

	for(i = 0 ; i < record_count ; i++)
	{
		if(record[i].back == 0 )
		{
			if(( nowtime - record[i].borrowtime.rawtime)  >= 2592000)/* 30天 * 24小时/天 * 60分/小时 * 60秒/分 = 2592000秒*/
			{
				printf(" %-20s\t%s\t%s\t%s\t%4d年%2d月%2d日%2d时%2d分\n",record[i].book_name,record[i].book_num,record[i].student_name,record[i].student_num,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour,record[i].borrowtime.minute);
				n++;
			}
		}

	}

	if( n == 0)
	{
		printf(" 没有超期未还图书！按任意键返回上一级菜单..");
		getch();
		BorrowInfo_Show();
	}

	if( n > 0)
	{
		printf(" 查找完毕！按任意键返回上一级菜单..");
		getch();
		BorrowInfo_Show();
	}
}

/*四级功能查询超期未还学生 */

void OverdueStudent_Show()
{
	int i;
	int n = 0 ; 	/*计数*/
    time_t nowtime;

	time( &nowtime );

	printf(" 查询结果如下: \n");
	printf("（注：下列依次显示的是 书名，图书编号，借阅者，借阅者学号，借阅时间）\n\n");

	for(i = 0 ; i < record_count ; i++)
	{
		if(( nowtime - record[i].borrowtime.rawtime)  >= 2592000)/* 30天 * 24小时/天 * 60分/小时 * 60秒/分 = 2592000秒*/
		{
			if(record[i].back == 0)
			{
				printf(" %-20s\t%s\t%s\t%s\t%4d年%2d月%2d日%2d时%2d分\n",record[i].book_name,record[i].book_num,record[i].student_name,record[i].student_num,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour,record[i].borrowtime.minute);
				n++;
			}

		}
	}

	if( n == 0)
	{
		printf(" 没有超期未的学生！按任意键返回上一级菜单..");
		getch();
		BorrowInfo_Show();
	}

	if( n > 0)
	{
		printf(" 查找完毕！按任意键返回上一级菜单..");
		getch();
		BorrowInfo_Show();
	}
}


/*******二级菜单借阅信息统计*******/
void BorrowInfo_Count()
{
	switch(BorrowInfo_Count_Menu())
	{
	case 1 : Time_Inordering();break;
	case 2 : Frequency_Inordering();break;
	case 3 : Major_Inordering();break;
	case 4 : Show_Admin();
	}
}

int BorrowInfo_Count_Menu()
{
	int choice;

	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t╔════════════════════════════╗\n");
	printf("\t\t║                    图书借阅信息统计                    ║\n");
	printf("\t\t╠════════════════════════════╣\n");
    printf("\t\t║\t\t1  - 按借阅时长排序                       ║\n");
	printf("\t\t║\t\t2  - 按借阅次数排序                       ║\n");
	printf("\t\t║\t\t3  - 按专业统计                           ║\n");
	printf("\t\t║\t\t4  - 返回上一级菜单                       ║\n");
	printf("\t\t╚════════════════════════════╝\n");
	printf("\t\t  请输入你的选择(1-4):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 4)
		    		printf("\t\t  您的输入有误,请重新输入:");

	}while(choice < 1 || choice > 4);

	fflush(stdin);

	return choice;
}

/* 三级功能 按借阅时长排序 */

void Time_Inordering()   	 /*冒泡算法*/
{
	int i , j ; /* 循环变量 */

	struct Book temp[BOOKMAX] ;
	struct Book t;
	Load_BookInfo();

	for( i = 0 ; i < book_count ; i++)
	{
		temp[i] = book[i];
	}

	for( j = 0 ; j < book_count - 1; j++)
	{
		for( i = 0 ; i < book_count - 1 -j ; i++)
		{
			if(temp[i].totaltime < temp[i+1].totaltime)
			{
				t = temp[i]  ;
				temp[i]  =temp[i+1];
				temp[i+1] = t ;
			}
		}
	}
	printf("\n 借阅时间由多到少的是 : \n");

	printf("（注 ： 以下依次是书名，编号，借阅时长，存放书架，图书总量）\n\n");

	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %-20s\t%s\t%.2lf\t%s\t%d\n",temp[i].name,temp[i].book_num,temp[i].totaltime,temp[i].location,temp[i].number);
	}

	printf(" \n 按任意键返回上一级菜单.. ");
	getch();
	BorrowInfo_Count();
}

/* 三级功能 按借阅次数排序 */
void Frequency_Inordering()   	 /*冒泡算法*/
{
	int i , j ; /* 循环变量 */

	struct Book temp[BOOKMAX],t;
	Load_BookInfo();

	for( i = 0 ; i < book_count ; i++)
	{
		temp[i] = book[i];
	}

	for( j = 0 ; j < book_count - 1; j++)
	{
		for( i = 0 ; i < book_count - 1 -j ; i++)
		{
			if(temp[i].frequency < temp[i+1].frequency)
			{
				t = temp[i] ;
				temp[i] =temp[i+1];
				temp[i+1] = t ;
			}
		}
	}
	printf("\n 借阅次数由多到少的是 : \n");
	printf("（注 ： 以下依次是书名，编号，借阅次数，存放书架，图书总量）\n\n");
	
	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %-20s\t%s\t%d\t%s\t%d\n",temp[i].name,temp[i].book_num,temp[i].frequency,temp[i].location,temp[i].number);
	}

	printf("\n 以上为排序结果，按任意键返回上一级菜单.. ");
	getch();
	BorrowInfo_Count();
}

/* 三级功能 按专业统计排序 */

void Major_Inordering()
{
	struct Book book_copy[BOOKMAX],t;           /*借用复制图书信息frequency表示专业阅读量*/
	struct STUDENT student_copy[STUDENTMAX];
	int i , j = 0 , k ;
	char  major[STRSIZE];
	int count;    /*储存这个专业的学生个数*/

	Load_RecordInfo();
	Load_BookInfo();
	
	printf("\n 请输入想要查询的专业（全称）: ");
	gets(major);
	fflush(stdin);

	for(i = 0 ; i < student_count ; i++)
	{
		if(strcmp(major,student[i].major) == 0)
		{
			student_copy[j] = student[i];
			j++;
		}
	}
	
	count = j;

	for(i = 0 ; i < book_count ; i++)
	{
		book_copy[i] = book[i];
		book_copy[i].frequency = 0 ;
	}
	
	for(i = 0 ; i < book_count ; i++)
	{
		for( j = 0 ; j < count ; j++)
		{
			for( k = 0 ; k < record_count ; k++)
			{
				if(strcmp(student_copy[j].num,record[k].student_num) == 0 )
				{
					if(strcmp(book_copy[i].book_num,record[k].book_num) == 0 )
					{
						if(record[k].back == 1)
							book_copy[i].frequency++;
					}
				}
			}
		}
	}

	for( j = 0 ; j < book_count - 1; j++)
	{
		for( i = 0 ; i < book_count - 1 -j ; i++)
		{
			if(book_copy[i].frequency < book_copy[i+1].frequency)
			{
				t = book_copy[i] ;
				book_copy[i] =book_copy[i+1];
				book_copy[i+1] = t ;
			}
		}
	}
	printf(" 本专业借阅次数由多到少的是 :\n");

	printf("（注 ： 以下依次是书名，编号，借阅次数，存放书架，在馆数目）\n\n");
	
	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %-20s\t%s\t%d\t%s\t%d\n",book_copy[i].name,book_copy[i].book_num,book_copy[i].frequency,book_copy[i].location,book_copy[i].number);
	}

	printf("\n 以上为排序结果，按任意键返回上一级菜单.. ");
	getch();
	BorrowInfo_Count();

}

/*********************************************************************/


/****************************图书管理三级菜单*****************************/

void BookManagement()
{
	switch(BookManagement_Menu())
	{
	case 1 : Book_Inquiry();break;
	case 2 : Book_Add();break;
	case 3 : Book_Modify();break;
	case 4 : Book_Delete();break;
	case 5 : Show_Admin();break;
	}
}


int BookManagement_Menu()
{
	int choice;

	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t╔════════════════════════════╗\n");
	printf("\t\t║                    图书信息管理                        ║\n");
	printf("\t\t╠════════════════════════════╣\n");
    printf("\t\t║\t\t1  - 查询图书                             ║\n");
	printf("\t\t║\t\t2  - 增添图书                             ║\n");
	printf("\t\t║\t\t3  - 修改图书信息                         ║\n");
	printf("\t\t║\t\t4  - 删除图书                             ║\n");
	printf("\t\t║\t\t5  - 返回上一级菜单                       ║\n");
	printf("\t\t╚════════════════════════════╝\n");
	printf("\t\t  请输入你的选择(1-5):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 5)
		    		printf("\t\t  您的输入有误,请重新输入:");

	}while(choice < 1 || choice > 5);

	fflush(stdin);

	return choice;
}

/*********四级功能图书查询***********/

void Book_Inquiry()
{
	switch(Book_Inquiry_Menu())
	{
	case 1 : Book_Inquiry_Bypublishinghouse();break;
	case 2 : Book_Inquiry_Byname()	;break;
	case 3 : BookManagement();break;
	}
}


int Book_Inquiry_Menu()
{
	int choice;

	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t╔════════════════════════════╗\n");
	printf("\t\t║                    图书信息管理                        ║\n");
	printf("\t\t╠════════════════════════════╣\n");
    printf("\t\t║\t\t1  - 根据出版社查询                       ║\n");
	printf("\t\t║\t\t2  - 根据书名查询                         ║\n");
	printf("\t\t║\t\t3  - 返回上一级菜单                       ║\n");
	printf("\t\t╚════════════════════════════╝\n");
	printf("\t\t  请输入你的选择(1-3):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 3)
		    printf("\t\t  您的输入有误,请重新输入:");

	}while(choice < 1 || choice > 3);

	fflush(stdin);

	return choice;
}


/*五级功能按出版社查询*/

void Book_Inquiry_Bypublishinghouse()
{
	char publishinghouse[STRSIZE];
	int i , j = 0;
	int count[BOOKMAX];
	char choice;

	fflush(stdin);
	printf("\n\t\t  请输入出版社:");

	scanf("%s",publishinghouse);

	fflush(stdin);

	for(i = 0 ; i < book_count ; i++)
	{
		if((strcmp(publishinghouse,book[i].publishinghouse)) == 0)
		{
			count[j] = i ;
			j++;
		}
	}

	if( j != 0)
	{
		printf(" 查询结果如下：\n");

		printf(" ( 注 ：下面列出的依次是书名，图书编号，作者，价格，出版社，出版时间，图书总量，书架位置，图书简介)\n\n\n");

		j--;

		while(j >= 0 )
		{
			printf(" %-20s\t%-s\t%-s\t%-.2lf元\t%-s\t%-s\t%-d\t%-s\t%-s\n",book[count[j]].name,book[count[j]].book_num,book[count[j]].author,book[count[j]].price,book[count[j]].publishinghouse,book[count[j]].date,book[count[j]].number,book[count[j]].location,book[count[j]].brief);	
			j--;
		}
		
		printf("\n 以上为全部信息，是否继续查询？( y or n ): ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
						   printf(" 您的输入有误,请重新选择:");

				}while(choice != 'y' && choice != 'n');

				if(choice == 'y')
				{
					printf(" 按任意键继续.\n\n  ");
					getch();
					Book_Inquiry_Bypublishinghouse();
				}

				else
				{
					printf(" 按任意键返回上一级. ");
					getch();
					Book_Inquiry();
				}
	}

	if(j == 0)
	{
		printf("\t\t  没有找到相应书籍.是否继续查询( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  您的输入有误,请重新选择:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
		{
			printf("\t\t  按任意键继续.  ");
			getch();
			Book_Inquiry_Bypublishinghouse();
		}

		else
		{
			printf("\t\t  按任意键返回上一级.  ");
			getch();
			Book_Inquiry();
		}
	}
}


/*功能按书名查询*/

void Book_Inquiry_Byname()
{
	char bookname[STRSIZE];
	int i , j = 0;
	char choice;

	fflush(stdin);
	printf("\n\t\t  请输入书名:");

	scanf("%s",bookname);


	for(i = 0 ; i < book_count ; i++)
	{
		if((strcmp(bookname,book[i].name)) == 0)
		{
			j++;
			break;
		}
	}

	if( j == 1)
	{
		printf(" 查询结果如下：\n\n");

		printf(" （注 ：下面列出的依次是书名,图书编号,作者,价格,出版社,出版时间,图书总量,书架位置,图书简介）\n\n");
		printf(" %-20s\t%-s\t%-s\t%-.2lf元\t%-s\t%-s\t%-d\t%-s\t%-s\n",book[i].name,book[i].book_num,book[i].author,book[i].price,book[i].publishinghouse,book[i].date,book[i].number,book[i].location,book[i].brief);

		printf("\n 以上为全部结果，是否继续查询( y or n ): ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
						   printf(" 您的输入有误,请重新选择:");

				}while(choice != 'y' && choice != 'n');

				if(choice == 'y')
				{
					printf("\t\t  按任意键继续.  ");
					getch();
					Book_Inquiry_Byname();
				}

				else
				{
					printf(" 按任意键继续.  ");
					getch();
					Book_Inquiry();
				}
	}

	if(j == 0)
	{
		printf("\t\t  没有找到相应书籍.是否继续查询( y or n ): ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  您的输入有误,请重新选择:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
		{
			printf("\t\t  按任意键继续.  ");
			getch();
			Book_Inquiry_Byname();
		}

		else
		{
			printf("\t\t  按任意键返回上一级.  ");
			getch();
			Book_Inquiry();
		}
	}
}

/*********四级功能增加图书***********/

void Book_Add()
{
	int i , n = 0;
	char choice1 , choice2;  /*分别用于储存 y or n*/

	FILE *fp;
	fflush(stdin);
	printf("\n\t\t  请输入要添加的图书名： ");
	scanf("%s",book[book_count].name);

	for( i = 0 ; i < book_count ; i ++)
	{

		if((strcmp(book[book_count].name,book[i].name)) == 0 )
		{
			printf("\t\t  该书已经存在，添加将增加一本 ： ");
			printf("\t\t  是否添加？ ( y or n): ");
			do
			{
				fflush(stdin);
				scanf("%c", &choice1);

				if(choice1 != 'y' && choice1 != 'n')
					 printf("\t\t  您的输入有误,请重新选择:");

			}while(choice1 != 'y' && choice1 != 'n');

			if(choice1 == 'y')
			{
				book[i].number++;

				if((fp = fopen("book_info.txt","w")) == NULL)
					{
						printf("无法打开该文件\n");
						exit(1);
					}

				for( i = 0 ; i < book_count ; i++)
				{
					fprintf(fp,BOOK_FORMAT,book[i].number,book[i].frequency,book[i].totaltime,book[i].price,book[i].book_num,book[i].publishinghouse,book[i].name,book[i].author,book[i].date,book[i].location,book[i].brief);
					fputs("\n",fp);
				}


				printf("\t\t  存入成功！是否继续添加图书？( y or n) ");

				do
				{
					fflush(stdin);
					scanf("%c", &choice2);

					if(choice2 != 'y' && choice2 != 'n')
						printf("\t\t  您的输入有误,请重新选择:");

				}while(choice2 != 'y' && choice2 != 'n');

				if(choice2 == 'y')
					BookManagement();

				else
				{
					printf("\t\t  按任意键返回上一级菜单. ");
					getch();
					Book_Inquiry();
				}
			}

			else
			{
				printf("\t\t  是否继续添加图书？(y or n) ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice2);

					if(choice2 != 'y' && choice2 != 'n')
							printf("\t\t  您的输入有误,请重新选择:");

				}while(choice2 != 'y' && choice2 != 'n');

				if(choice2 == 'y')
					Book_Add();

				else
				{
					printf("\t\t  按任意键返回上一级菜单. ");
					getch();
					BookManagement();
				}

			}
		}

	}

			printf("\t\t  请输入该书编号(从100001开始的六位编号)：");

			scanf("%s",book[book_count].book_num);

			while(Numberformat_check(book[book_count].book_num))
			{
				fflush(stdin);
				printf("\t\t  格式错误，请重新输入 ：");
				scanf("%s",book[book_count].book_num);
			}

			while(Numberexist(book[book_count].book_num))
						{
							fflush(stdin);
							printf("\t\t  格式错误，请重新输入 ：");
							scanf("%s",book[book_count].book_num);
						}

			printf("\t\t  请输入该书要存放的书架位置（例如：a100）：");

			scanf("%s",book[book_count].location);       

			while(Locationexist(book[book_count].location))
			{
				fflush(stdin);
				printf("\t\t  该地方已有图书，请重新输入 ：");
				scanf("%s",book[book_count].location);
			}

			printf("\t\t  请输入该书的数量：");
			scanf("%d",&book[book_count].number);

			printf("\t\t  请输入该书的出版社：");
			scanf("%s",book[book_count].publishinghouse);

			printf("\t\t  请输入该书的作者：");
			scanf("%s",book[book_count].author);

			printf("\t\t  请输入该书的出版时间(格式 ****年**月**日 )：");
			scanf("%s",book[book_count].date);

			printf("\t\t  请输入该书的价格(保留两位小数 )：");
			scanf("%lf",&book[book_count].price);

			printf("\t\t  请输入该书的简介：");
			scanf("%s",book[book_count].brief);

			if((fp = fopen("book_info.txt","w")) == NULL)
				{
					printf("无法打开该文件\n");
					exit(1);
				}
			book[book_count].frequency = 0;
			book[book_count].totaltime = 0;
			
			book_count++;

			for( i = 0 ; i < book_count; i++)
			{
				fprintf(fp,BOOK_FORMAT,book[i].number,book[i].frequency,book[i].totaltime,book[i].price,book[i].book_num,book[i].publishinghouse,book[i].name,book[i].author,book[i].date,book[i].location,book[i].brief);
				fputs("\n",fp);
			}

			fclose(fp);

			printf("\t\t  存入成功!是否继续添加图书 ？( y or n ) ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice2);

				if(choice2 != 'y' && choice2 != 'n')
						printf("\t\t  您的输入有误,请重新选择:");

			}while(choice2 != 'y' && choice2 != 'n');
			fflush(stdin);

			if(choice2 == 'y')
				Book_Add();

			else
			{
				printf("\t\t  按任意键返回上一级菜单. ");
				getch();
				BookManagement();
			}
}



int Numberformat_check(char *num)     /*判断书的编号格式，如果正确返回0，不正确返回1*/
{
		int i;

		if(strlen(num) == 6)
		{
				for(i = 0 ; i < 6 ; i++)
				{
					if(isdigit(num[i]))
					{
						;
					}
					else
					{
						return EXIT_FAILURE;
					}
				}
		}

		else
		{
				return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
}

int Numberexist(char *num)
{

	int i;

	for( i = 0 ; i < book_count ; i ++)
	{
		if((strcmp(num,book[i].book_num)) == 0 )
			{
				return EXIT_FAILURE;
			}
	}
	return EXIT_SUCCESS;
}


int Locationexist(char *location)
{
	int i;

	for( i = 0 ; i < book_count ; i ++)
	{
		if((strcmp(location,book[i].location)) == 0 )
			{
				return EXIT_FAILURE;
			}
	}
	return EXIT_SUCCESS;
}
/*四级功能删除图书*/

int CheckBookborrow(char *name)
{
	int i ;

	for( i  = 0 ; i < record_count ; i++)
	{
		if(strcmp(record[i].book_name,name) == 0 )
		{
			if(record[i].back == 0 )
			{
				return 0 ;
			}
		}
	}

	return 1;
}
void Book_Delete()
{
	char name[STRSIZE];
	int i , j ;
	char choice;
	FILE *fp;
	fflush(stdin);
	printf("\n\t\t  请输入要删除的图书名： ");
	scanf("%s",name);
	
	Load_BookInfo();
	Load_RecordInfo();
	
	if(CheckBookborrow(name) == 0)
	{
		printf("\n\t\t 不能删除该书，因为已被借出...");
		printf("\t\t 是否继续删除？(y or n ) ");
			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
						printf("\t\t  您的输入有误,请重新选择:");

			}while(choice != 'y' && choice != 'n');

			if(choice == 'y')
				Book_Delete();

			else
			{
				printf("\t\t  按任意键返回上一级菜单. ");
				getch();
				BookManagement();
			}
	}

	for( i = 0 ; i < book_count ; i ++)
	{
		if(strcmp(name,book[i].name) == 0)
		{
			if((fp = fopen("book_info.txt","w")) == NULL)
				{
					printf("无法打开该文件\n");
					exit(1);
				}

			for( j = 0 ; j < book_count ; j++)
			{
				if( j != i)
				{
						fprintf(fp,BOOK_FORMAT,book[j].number,book[j].frequency,book[j].totaltime,book[j].price,book[j].book_num,book[j].publishinghouse,book[j].name,book[j].author,book[j].date,book[j].location,book[j].brief);
						fputs("\n",fp);
				}
			}
			
			fclose(fp);
			book_count--;

			printf("\t\t  删除成功!是否继续删除？(y or n ) ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
						printf("\t\t  您的输入有误,请重新选择:");

			}while(choice != 'y' && choice != 'n');

			if(choice == 'y')
				Book_Delete();

			else
			{
				printf("\t\t  按任意键返回上一级菜单. ");
				getch();
				BookManagement();
			}
		}
	}

	printf("\t\t  该书不存在，是否继续删除其他图书？ (y or n) ");
	do
	{
		fflush(stdin);
		scanf("%c", &choice);

		if(choice != 'y' && choice != 'n')
				printf("\t\t  您的输入有误,请重新选择:");

	}while(choice != 'y' && choice != 'n');

	if(choice == 'y')
		Book_Delete();

	else
	{
		printf("\t\t  按任意键返回上一级菜单. ");
		getch();
		Book_Inquiry();
	}
}

/*四级功能修改图书信息*/
void Book_Modify()
{
	int i , j ;
	char choice;
	char name[STRSIZE];
	FILE *fp;
	
	char location[STRSIZE];
	Load_BookInfo();
	fflush(stdin);
	printf("\n\t\t  请输入要修改的图书名： ");
	scanf("%s",name);

	for( i = 0 ; i < book_count ; i ++)
	{

		if((strcmp(name,book[i].name)) == 0 )
		{

			printf("\t\t  请输入该书的位置（例：a123）：");
			scanf("%s",location);

			while(Locationexist(location))
			{
				fflush(stdin);
				printf("\t\t  该地方已经有图书，请重新输入 ：");
				scanf("%s",location);
			}
			
			strncpy(book[i].location,location,STRSIZE);

			printf("\t\t  请输入该书的数量 ：");
			scanf("%lf",&book[i].number);

			printf("\t\t  请输入该书的简介 ：");
			scanf("%s",book[i].brief);

			if((fp = fopen("book_info.txt","w")) == NULL)
				{
					printf("无法打开该文件\n");
					exit(1);
				}

			for( j = 0 ; j < book_count; j++)
			{
				fprintf(fp,BOOK_FORMAT,book[j].number,book[j].frequency,book[j].totaltime,book[j].price,book[j].book_num,book[j].publishinghouse,book[j].name,book[j].author,book[j].date,book[j].location,book[j].brief);
				fputs("\n",fp);
			}

			fclose(fp);

			printf("\t\t  修改成功!是否继续修改？( y or n ) ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
						printf("\t\t  您的输入有误,请重新选择:");

			}while(choice != 'y' && choice != 'n');

			if(choice == 'y')
				Book_Modify();

			else
			{
				printf("\t\t  按任意键返回上一级菜单. ");
				getch();
				BookManagement();
			}
		}


	}
		printf("\t\t  未找到该书，是否继续修改其他书籍？( y or n ) ");

		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
					printf("\t\t  您的输入有误,请重新选择:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
			Book_Modify();

		else
		{
			printf("\t\t  按任意键返回上一级菜单. ");
			getch();
			BookManagement();
		}

}


/******************修改管理员信息***************************/
void AdminInfo_Modify()     /*选择*/
{
	switch( AdminInfo_Modify_Menu())
		{
			case 1 : 	 AdminInfo_Modify_Password();break;
			case 2 :	 AdminInfo_Modify_Email();break;
			case 3 :	 Show_Admin();break;
		}
}

int AdminInfo_Modify_Menu()
{
	int choice;

			system("cls");
		    printf("\n\n\n\n\n");
		    printf("\t╔════════════════════════════════╗\n");
		    printf("\t║                         管理员信息修改                         ║\n");
		    printf("\t╠════════════════════════════════╣\n");
		    printf("\t║\t\t1  - 修改密码                                     ║\n");
		    printf("\t║\t\t2  - 修改邮箱                                     ║\n");
		    printf("\t║\t\t3  - 返回上一级菜单                               ║\n");
		    printf("\t╚════════════════════════════════╝\n");
		    printf("\t\t  请输入你的选择(1-3):");

		    do{
		    		fflush(stdin);
		    		scanf("%d", &choice);

		    		if(choice < 1 || choice > 3)
		    		printf("\t\t  您的输入有误,请重新输入:");

		    }while(choice < 1 || choice > 3);

		    fflush(stdin);

		    return choice;
}
int Admin_IdCheck(char *id)
{
	int i;  /*循环变量*/

	for(i = 0 ; i < admin_count ; i++)
	{
		if(strcmp(id,admin[i].num) == 0)
		{
			admin_current = i ;
			return EXIT_SUCCESS ;
		}      /*表示存在该账号*/
	}

	return EXIT_FAILURE;
}

int Admin_PasswdCheck(char *passwd) /*1表示密码错误*/
{

	if(strcmp(passwd,admin[admin_current].password) != 0)
	{
		return EXIT_FAILURE ;  /*表示密码错误*/
	}
	return EXIT_SUCCESS;
}



void AdminInfo_Modify_Password()
{
	FILE *fp;
	int i;

	if((fp = fopen("admin_info.txt","w")) == NULL)
		{
			printf("无法打开该文件\n");
			exit(1);
		}

	printf("\t\t  请输入新的密码：");
	scanf("%s",admin[admin_current].password);


	for(i = 0 ; i < admin_count; i++)
	{
		fprintf(fp,ADM_FORMAT,ADM_INPUT);
		fputs("\n",fp);
	}

	printf("\t\t  保存成功，按任意键返回");
	getch();

	fclose(fp);

	AdminInfo_Modify();
}

void AdminInfo_Modify_Email()
{
	FILE *fp;
	int i;

	if((fp = fopen("admin_info.txt","w")) == NULL)
		{
			printf("无法打开该文件\n");
			exit(1);
		}

	printf("\t\t  请输入新的邮箱：");
	scanf("%s",admin[admin_current].email);

	while(EmailFormat_check(admin[admin_current].email))
	{
			fflush(stdin);
			printf("\t\t  格式错误，请输入*****@**.***格式： ");
			scanf("%s",admin[admin_current].email);
	}

	for(i = 0 ; i < admin_count; i++)
	{
		fprintf(fp,ADM_FORMAT,ADM_INPUT);
		fputs("\n",fp);
	}

	printf("\t\t  保存成功，按任意键返回");
	getch();

	fclose(fp);

	AdminInfo_Modify();
}


/******************************学生端函数***************************************/


void Show_Student()
{
	if(Check_Freeze())
	{
		Show_Freeze();
	}

	switch(Show_StudentMenu())
	{
		case 1  : Book_Borrow();break;
		case 2  : Book_Revert();break;
		case 3  : Book_Renew();break;
		case 4  : Book_StuInquiry();break;
		case 5  : Record_Check();break;
		case 6  : Record_Delete();break;
		case 7  : StudentInfo_Modify();break;
		case 8  : Logout();break;
		case 9  : Quit();break;
	}
}

int Show_StudentMenu()
{
		int choice = 0 ;

		fflush(stdin);
	 	system("cls");
	    printf("\n\n\n\n\n");
	    printf("\t╔═══════════════════════════════╗\n");
	    printf("\t║             欢迎访问图书馆借阅系统 （学生端）                ║\n");
	    printf("\t╠═══════════════════════════════╣\n");
	    printf("\t║\t\t1 -  图书借阅                                   ║\n");
	    printf("\t║\t\t2 -  图书归还                                   ║\n");
	    printf("\t║\t\t3 -  图书续借                                   ║\n");
	    printf("\t║\t\t4 -  图书查询                                   ║\n");
	    printf("\t║\t\t5 -  借阅结果查询                               ║\n");
	    printf("\t║\t\t6 -  借阅信息删除                               ║\n");
	    printf("\t║\t\t7 -  个人信息管理                               ║\n");
	    printf("\t║\t\t8 -  注销                                       ║\n");
	    printf("\t║\t\t9 -  退出                                       ║\n");
	    printf("\t╚═══════════════════════════════╝\n");
	    printf("\n\t\t  请输入你的选择(1-9):");

	    do{
	    		fflush(stdin);
	    		scanf("%d", &choice);

	    		if(choice < 1 || choice > 9)
	    		printf("\t\t  您的输入有误,请重新输入:");

	    }while(choice < 1 || choice > 9);

	    fflush(stdin);

	    return choice;
}

void Stu_Login()
{

		char id[STRSIZE] ;
		char passwd[STRSIZE];

		system("cls");
		printf("\n\n\n\n\n");
		printf("\t╔═════════════════════════════════╗\n");
		printf("\t║             欢迎访问图书馆借阅系统 （学生端）                    ║\n");
		printf("\t╠═════════════════════════════════╣\n");
		printf("\t\t  请输入您的学号（ 10 位数字）：");

		scanf("%s",id);

		while(IdformatJudge(id) || Stu_IdCheck(id))
		{
			fflush(stdin);
			printf("\t\t  学号错误，请输入正确学号：");
			scanf("%s",id);
		}

		printf("\t\t  请输入您的密码 ：");

		scanf("%s",passwd);

		while(Stu_PasswdCheck(passwd))
		{
				fflush(stdin);
				printf("\t\t  密码错误，请输入正确密码：");
				scanf("%s",passwd);
		}
		printf("\n\t\t  登陆成功，按任意键继续.");
		fflush(stdin);
		getch();

}


int IdformatJudge(char *id)
{
	int i;

	if(strlen(id) == 10)
	{
			for(i = 0 ; i < 10 ; i++)
			{
				if(isdigit(id[i]))
				{
					;
				}

				else
					{
						return EXIT_FAILURE;
					}
			}
	}

	else
	{
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int Stu_IdCheck(char *id)
{
	int i;  /*循环变量*/

	for(i = 0 ; i < student_count ; i++)
	{
		if(strcmp(id,student[i].num) == 0)
		{
			student_current = i ;
			return EXIT_SUCCESS ;
		}						/*表示存在该账号*/
	}

	return EXIT_FAILURE;
}

int Stu_PasswdCheck(char *passwd)
{

	if(strcmp(passwd,student[student_current].password) != 0)
	{
		return EXIT_FAILURE ;  /*表示密码错误*/
	}
	return EXIT_SUCCESS;
}

/***************冻结学生界面**************/

void Show_Freeze()
{
		int choice;

		fflush(stdin);
	 	system("cls");
	    printf("\n\n\n\n\n");
	    printf("\t╔═══════════════════════════════╗\n");
	    printf("\t║             欢迎访问图书馆借阅系统 （冻结学生端）            ║\n");
	    printf("\t╠═══════════════════════════════╣\n");
	    printf("\t║\t\t1 -  图书归还                                   ║\n");
	    printf("\t║\t\t2 -  借阅结果查询                               ║\n");
	    printf("\t║\t\t3 -  注销                                       ║\n");
	    printf("\t║\t\t4 -  退出                                       ║\n");
	    printf("\t╚═══════════════════════════════╝\n");
	    printf("\n\t\t  警告!你正处于冻结状态! 请及时归还图书并通知管理员解冻!!");
		printf("\n\t\t  请输入你的选择(1-4):");

	    do{
	    		fflush(stdin);
	    		scanf("%d", &choice);

	    		if(choice < 1 || choice > 4)
	    		printf("\t\t  您的输入有误,请重新输入:");

	    }while(choice < 1 || choice > 4);

	    fflush(stdin);

	switch(choice)
	{
		case 1  : Book_Revert();break;
		case 2  : Record_Check();break;
		case 3  : Logout();break;
		case 4  : Quit();break;
	}
}
/**********************二级功能图书借阅**********************/

void  Book_Borrow()
{
	int i , j = 0, k ;
	char book_name[STRSIZE];
	char choice;
	FILE *fp;

    time_t nowtime;
    struct tm *timeinfo;
	
	Load_RecordInfo();
	Load_BookInfo();

	fflush(stdin);

	for(i = 0; i < record_count; i++)/*该for循环用于判断借阅数是否达到三本*/
		{
			if(strcmp(student[student_current].num,record[i].student_num) == 0)
			{
				if(record[i].back == 0)
				{
					j++;
				}
			}
		}

	if(j>=3)
	{
		printf("\n\t\t  规定借阅数量达到三本时不能再借阅。请归还图书之后再进行借阅. ");
		printf("\n\t\t  按任意键返回上一级菜单.. ");
		getch();

		Show_Student();
	}

		printf("\n\t\t  请输入想要借阅的书名: ");

		gets(book_name);
		fflush(stdin);

		for(i = 0 ; i < book_count ; i++)		/*检查该书是否在库存中*/
		{
			if(strcmp(book_name,book[i].name) == 0)
			{
				j=0;

				for(k = 0;k < record_count ; k++)			/*检查有多少人借阅该书*/
					{
						if(book_name == record[k].book_name)
						{
							if(record[k].back == 0)
							{
									j++;
							}
						}
					}

				if( j >= book[i].number)
				{
					printf("\n\t\t  该图书已经全部被借出.  ");
					printf("\n\t\t  是否继续借阅其他图书？ ( y or n ) : ");
					do
					{
						fflush(stdin);
						scanf("%c", &choice);

						if(choice != 'y' && choice != 'n')
							   printf("\t\t  您的输入有误,请重新选择:");

					}while(choice != 'y' && choice != 'n');

					if(choice == 'y')
					{
						printf("\t\t  按任意键继续.  ");
						getch();
						Book_Borrow();
					}

					if(choice == 'n')
					{
						printf("\t\t  按任意键返回上一级菜单.  ");
						getch();
						Show_Student();
					}
				}

				else
				{
					for(i = 0 ; i < record_count ; i++ )/*检查该学生是否已经借阅这本书*/
					{
						if(strcmp(book_name,record[i].book_name) == 0)
						{
							if( strcmp(student[student_current].num,record[i].student_num) == 0)
							{
								if(record[i].back == 0)
								{
									printf("\n\t\t  你已借阅了该书，不能再借! ");
									printf("\n\t\t  是否继续借阅其他图书？ ( y or n ) : ");
									do
									{
										fflush(stdin);
										scanf("%c", &choice);

										if(choice != 'y' && choice != 'n')
											   printf("\t\t  您的输入有误,请重新选择:");

									}while(choice != 'y' && choice != 'n');


									if(choice == 'y')
									{
										printf("\t\t  按任意键继续.  ");
										getch();
										Book_Borrow();
									}

									if(choice == 'n')
									{
										printf("\t\t  按任意键返回上一级菜单.  ");
										getch();
										Show_Student();
									}
								}
							}
						}
					}

					if((fp = fopen("record_info.txt","w")) == NULL)
						{
							printf("无法打开该文件\n");
							exit(1);
						}


				    time( &nowtime );
				    timeinfo = localtime( &nowtime );

					i = SearchnumByname(book_name) - 1 ;

					record[record_count].back = 0;
				    record[record_count].b_r = 0 ;
					strncpy(record[record_count].book_num,book[i].book_num,STRSIZE);
					strncpy(record[record_count].student_num,student[student_current].num,STRSIZE);
					strncpy(record[record_count].book_name,book_name,STRSIZE);
					strncpy(record[record_count].student_name,student[student_current].name,STRSIZE);

				    record[record_count].borrowtime.year = timeinfo->tm_year + 1900;
				    record[record_count].borrowtime.month =  timeinfo->tm_mon + 1;
				    record[record_count].borrowtime.day = timeinfo->tm_mday;
					record[record_count].borrowtime.hour = timeinfo->tm_hour;
				    record[record_count].borrowtime.minute = timeinfo->tm_min;
				    record[record_count].borrowtime.second = timeinfo->tm_sec;
				    record[record_count].borrowtime.rawtime = nowtime;

					record[record_count].backtime.year = 0;
					record[record_count].backtime.month = 0;
				    record[record_count].backtime.day = 0;
					record[record_count].backtime.hour = 0;
				    record[record_count].backtime.minute = 0;
				    record[record_count].backtime.second = 0;
			        record[record_count].backtime.rawtime = 0;

					record_count++;

					for( i = 0 ; i < record_count ; i++)
					{
						fprintf(fp,RECORD_FORMAT,record[i].b_r,record[i].back,record[i].book_num,record[i].student_num,record[i].book_name,record[i].student_name,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour,record[i].borrowtime.minute,record[i].borrowtime.second,record[i].borrowtime.rawtime,record[i].backtime.year,record[i].backtime.month,record[i].backtime.day,record[i].backtime.hour,record[i].backtime.minute,record[i].backtime.second,record[i].backtime.rawtime);
						fputs("\n",fp);
					}

					fclose(fp);

					record_count++;

					printf("\n\t\t  恭喜你，借阅成功 ! ");

					printf("\n\t\t  是否继续借阅？ ( y or n ) : ");
					do
					{
						fflush(stdin);
						scanf("%c", &choice);

						if(choice != 'y' && choice != 'n')
							   printf("\t\t  您的输入有误,请重新选择:");

					}while(choice != 'y' && choice != 'n');

					fflush(stdin);

					if(choice == 'y')
					{
					
						printf("\t\t  按任意键继续.  ");
						getch();
						Book_Borrow();
					}

					if(choice == 'n')
					{
						printf("\t\t  按任意键返回上一级菜单.  ");
						getch();
						Show_Student();
					}
				}
			}
		}

		printf("\n\t\t  并没有找到该书.  ");
		printf("\n\t\t  是否继续借阅其他书籍？ ( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  您的输入有误,请重新选择:");

		}while(choice != 'y' && choice != 'n');
		fflush(stdin);

		if(choice == 'y')
		{
			printf("\t\t  按任意键继续.  ");
			getch();
			Book_Borrow();
		}

		if(choice == 'n')
		{
			printf("\t\t  按任意键返回上一级菜单.  ");
			getch();
			Show_Student();
		}
}

/***********三级功能查书序号**************/
int SearchnumByname(char *bookname)
{
	int i;

	for( i = 0 ; i < book_count ; i++ )
	{
		if(strcmp(bookname,book[i].name) == 0)
		{
			return i + 1 ;
		}
	}
	return 0 ;
}

/**************************二级功能图书归还***************************/

void Book_Revert()
{
	char choice;
	int n;
	int i , j;
	FILE *fp;

	double keephour; /****记录持有时间*****/

	char book_name[STRSIZE];

    time_t nowtime;
    struct tm *timeinfo;
	
	Load_RecordInfo();
	Load_BookInfo();
	fflush(stdin);
	printf("\n\t\t  请输入要归还的书名: ");
	gets(book_name);
	
	n = CheckIfborrow(book_name);

	if( n == 0 )
	{
		printf("\t\t  你还没有借阅该书！请先借阅！ ");

		printf("\n\t\t  是否继续还书？ ( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  您的输入有误,请重新选择:");

		}while(choice != 'y' && choice != 'n');


		if(choice == 'y')
		{
			printf("\t\t  按任意键继续.  ");
			getch();
			Book_Revert();
		}

		if(choice == 'n')
		{
			printf("\t\t  按任意键返回上一级菜单.  ");
			getch();
			Show_Student();
		}
	}

	else
	{
		printf("\t\t  归还成功！请稍等片刻，系统将记录你的归还行为. ");

		if((fp = fopen("record_info.txt","w")) == NULL)
			{
				printf("无法打开该文件\n");
				exit(1);
			}


	    time( &nowtime );
	    timeinfo = localtime( &nowtime );

	    record[n - 1].back = 1 ;
	    record[n - 1].backtime.year = timeinfo->tm_year + 1900;
	    record[n - 1].backtime.month =  timeinfo->tm_mon + 1;
	    record[n - 1].backtime.day = timeinfo->tm_mday;
	    record[n - 1].backtime.hour = timeinfo->tm_hour;
	    record[n - 1].backtime.minute = timeinfo->tm_min;
	    record[n - 1].backtime.second = timeinfo->tm_sec;
	    record[n - 1].backtime.rawtime = nowtime;

	    keephour = ((double)(record[n - 1].backtime.rawtime - record[n - 1].borrowtime.rawtime))/3600 ;


		for( i = 0 ; i < record_count ; i++)
		{
			fprintf(fp,RECORD_FORMAT,record[i].b_r,record[i].back,record[i].book_num,record[i].student_num,record[i].book_name,record[i].student_name,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour,record[i].borrowtime.minute,record[i].borrowtime.second,record[i].borrowtime.rawtime,record[i].backtime.year,record[i].backtime.month,record[i].backtime.day,record[i].backtime.hour,record[i].backtime.minute,record[i].backtime.second,record[i].backtime.rawtime);
			fputs("\n",fp);		
		}

		fclose(fp);

		n = SearchnumByname(book_name) - 1 ;

		book[n].frequency++;
		book[n].totaltime += keephour;

		if((fp = fopen("book_info.txt","w")) == NULL)
			{
				printf("无法打开该文件\n");
				exit(1);
			}

		for( j = 0 ; j < book_count ; j++)
		{
			fprintf(fp,BOOK_FORMAT,book[j].number,book[j].frequency,book[j].totaltime,book[j].price,book[j].book_num,book[j].publishinghouse,book[j].name,book[j].author,book[j].date,book[j].location,book[j].brief);
			fputs("\n",fp);
		}
		fclose(fp);

		printf("\n\t\t  记录完毕！");

		printf("\n\t\t  是否继续还书？ ( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  您的输入有误,请重新选择: ");

		}while(choice != 'y' && choice != 'n');


		if(choice == 'y')
		{
			printf("\t\t  按任意键继续.  ");
			getch();
			Book_Revert();
		}

		if(choice == 'n')
		{
			printf("\t\t  按任意键返回上一级菜单.  ");
			getch();
			Show_Student();

		}
	}
}

/*功能判断该书是否已被此人借阅,被借阅返回 1+i，未被借阅返回 0 */

int CheckIfborrow(char *book_name)
{
	int i;

	for( i = 0 ; i < record_count ; i++)
	{
		if(strcmp(book_name,record[i].book_name) == 0)
		{
			if(strcmp(student[student_current].num,record[i].student_num) == 0)

				if(record[i].back == 0)
				{
					return i + 1 ;
				}
		}
	}
	return 0;
}


/*******************二级功能图书续借****************************/

void Book_Renew()
{
	char book_name[STRSIZE];
	int n;
	int totaltime;
	char choice;
	int i;
	
	FILE *fp;

    time_t nowtime;
    struct tm *timeinfo;

	Load_RecordInfo();
	Load_BookInfo();



	fflush(stdin);

	printf("\n\t\t  请输入要续借的书名: ");
	gets(book_name);

	fflush(stdin);

	n = JudgeStuBorrow(book_name);

	if(n == 0)
	{
		printf("\t\t  你还没有借阅该书或已经归还该书 .. ");

		printf("\n\t\t  是否继续续借其他书籍？ ( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  您的输入有误,请重新选择:");

		}while(choice != 'y' && choice != 'n');


		if(choice == 'y')
		{
			printf("\t\t  按任意键继续.  ");
			getch();
			Book_Renew();
		}

		if(choice == 'n')
		{
			printf("\t\t  按任意键返回上一级菜单.  ");
			getch();
			Show_Student();
		}
	}

	else
	{
		time( &nowtime );
	    timeinfo = localtime( &nowtime );

		record[n-1].backtime.rawtime = nowtime;

		totaltime = record[n-1].backtime.rawtime - record[n-1].borrowtime.rawtime;

		if(totaltime < 2592000)   /* 30天 * 24小时/天 * 60分/小时 * 60秒/分 = 2592000秒*/
		{
			printf("\t\t  还未到归还日之后，不能续借.. ");

			printf("\n\t\t  是否继续续借其他书籍？ ( y or n ) : ");
			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
					   printf("\t\t  您的输入有误,请重新选择:");

			}while(choice != 'y' && choice != 'n');


			if(choice == 'y')
			{
				printf("\t\t  按任意键继续.  ");
				getch();
				Book_Renew();
			}

			if(choice == 'n')
			{
				printf("\t\t  按任意键继续.   ");
				getch();
				Show_Student();

			}

		}

		if(JudgeIftwice(book_name) >= 3) /*借阅+ 续借 超过三次*/
		{
			printf("\t\t  续借次数已到上限无法继续借阅.. ");

			printf("\n\t\t  是否继续续借其他书籍？ ( y or n ) : ");
			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
					   printf("\t\t  您的输入有误,请重新选择:");

			}while(choice != 'y' && choice != 'n');

			if(choice == 'y')
			{
				printf("\t\t  按任意键继续.  ");
				getch();
				Book_Renew();
			}

			if(choice == 'n')
			{
				printf("\t\t  按任意键继续.  ");
				getch();
				Show_Student();

			}

		}

		if((fp = fopen("record_info.txt","w")) == NULL)
			{
				printf("无法打开该文件\n");
				exit(1);
			}


	   

	    record[n - 1].back = 1 ;
	    record[n - 1].backtime.year = timeinfo->tm_year + 1900;
	    record[n - 1].backtime.month =  timeinfo->tm_mon + 1;
	    record[n - 1].backtime.day = timeinfo->tm_mday;
	    record[n - 1].backtime.hour = timeinfo->tm_hour;
	    record[n - 1].backtime.minute = timeinfo->tm_min;
	    record[n - 1].backtime.second = timeinfo->tm_sec;
	    record[n - 1].backtime.rawtime = nowtime;

		record[record_count].back = 0;
	    record[record_count].b_r = 1 ;
		strncpy(record[record_count].book_num,record[n - 1].book_num,STRSIZE);
		strncpy(record[record_count].student_num,record[n - 1].student_num,STRSIZE);
		strncpy(record[record_count].book_name,record[n - 1].book_name,STRSIZE);
		strncpy(record[record_count].student_name,record[n - 1].student_name,STRSIZE);

	    record[record_count].borrowtime.year = timeinfo->tm_year + 1900;
	    record[record_count].borrowtime.month =  timeinfo->tm_mon + 1;
	    record[record_count].borrowtime.day = timeinfo->tm_mday;
	    record[record_count].borrowtime.hour = timeinfo->tm_hour;
	    record[record_count].borrowtime.minute = timeinfo->tm_min;
	    record[record_count].borrowtime.second = timeinfo->tm_sec;
	    record[record_count].borrowtime.rawtime = nowtime;

	    record[record_count].backtime.year = 0;
	    record[record_count].backtime.month = 0;
	    record[record_count].backtime.day = 0;
	    record[record_count].backtime.hour = 0;
	    record[record_count].backtime.minute = 0;
	    record[record_count].backtime.second = 0;
	    record[record_count].backtime.rawtime = 0;

		record_count++;


		for( i = 0 ; i < record_count ; i++)
		{
			fprintf(fp,RECORD_FORMAT,record[i].b_r,record[i].back,record[i].book_num,record[i].student_num,record[i].book_name,record[i].student_name,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour,record[i].borrowtime.minute,record[i].borrowtime.second,record[i].borrowtime.rawtime,record[i].backtime.year,record[i].backtime.month,record[i].backtime.day,record[i].backtime.hour,record[i].backtime.minute,record[i].backtime.second,record[i].backtime.rawtime);
			fputs("\n",fp);
		}
		
		fclose(fp);
		
		n = SearchnumByname(book_name) - 1 ;

		book[n].frequency++;
		book[n].totaltime += ((double)totaltime)/3600;


		if((fp = fopen("book_info.txt","w")) == NULL)
			{
				printf("无法打开该文件\n");
				exit(1);
			}

		for( i = 0 ; i < book_count ; i++)
		{
			fprintf(fp,BOOK_FORMAT,book[i].number,book[i].frequency,book[i].totaltime,book[i].price,book[i].book_num,book[i].publishinghouse,book[i].name,book[i].author,book[i].date,book[i].location,book[i].brief);
			fputs("\n",fp);
		}
		fclose(fp);

		printf("\n\t\t  续借成功！   ");
		printf("\n\t\t  是否继续续借其他书籍？ ( y or n) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  您的输入有误,请重新选择:");

		}while(choice != 'y' && choice != 'n');


		if(choice == 'y')
		{
			printf("\t\t  按任意键继续.  ");
			getch();
			Book_Renew();
		}

		if(choice == 'n')
		{
			printf("\t\t  按任意键继续.  ");
			getch();
			Show_Student();
		}
	}
}

/***********************************************/

int JudgeStuBorrow(char *book_name)
{
	int i ;

	for( i = 0 ; i < record_count ; i++ )
	{
		if(strcmp(record[i].book_name , book_name) == 0)
		{
			if ( strcmp(student[student_current].num , record[i].student_num)== 0 )
			{
				if(record[i].back == 0)
				{
					return i+1;
				}
			}
		}
	}

	return 0;
}

/*判断是否续借超过两次*/
int JudgeIftwice(char *book_name)
{
	int i , j = 0;

	for( i = 0 ; i < record_count ; i++ )
	{
		if(strcmp(record[i].book_name,book_name) == 0)
		{
			if ( strcmp(student[student_current].num ,record[i].student_num)== 0 )
			{
				if(record[i].back == 1)
				{
					j++;
				}
			}
		}
	}

	return j ;
}

/*二级查询借阅结果*/

void Record_Check()
{
	int i;
	int n = 0 ;

	Load_RecordInfo();
	Load_BookInfo();

	printf("\n\n（注 ：下面一次输入的是书名，编号，借阅或续借(1表示续借，0表示借阅)借阅时间，归还时间 ）\n");

	for(i = 0 ; i < record_count; i++)
	{
		if( strcmp(student[student_current].num,record[i].student_num) == 0 )
		{
			if(record[i].back == 0)
			{
				printf(" %-20s\t%s\t%d\t%4d年%2d月%2d日%2d时\t无\n",record[i].book_name,record[i].book_num,record[i].b_r,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour);
				n++;
			}
			if(record[i].back == 1)
			{
				printf(" %-20s\t%s\t%d\t%4d年%2d月%2d日%2d时\t%4d年%2d月%2d日%2d时\n",record[i].book_name,record[i].book_num,record[i].b_r,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour,record[i].backtime.year,record[i].backtime.month,record[i].backtime.day,record[i].backtime.hour);
				n++;
			}
		}
	}

	if( n == 0 )
	{
		printf("\n\n 并没有您的借阅记录，赶紧借阅一本吧！ ");
		printf("\n 按任意键继续. ");
		getch();
		Show_Student();
	}

	else
	{
		printf("\n\n 以上是你曾借阅过或正在借阅的图书. ");
		printf("\n 按任意键返回上一级. ");
		getch();
		Show_Student();
	}

}


/****删除借阅信息****/

void Record_Delete()
{
	int i , j = 0;
	int n = 0;
	FILE *fp;
	char book_name[STRSIZE];
	char choice;

	Load_RecordInfo();

	printf("\n\t\t  请输入要删除记录图书的名字：  ");

	scanf("%s",book_name);

	
	for( i = 0 ; i < record_count ; i++)
	{
		if((logintime < record[i].borrowtime.rawtime)  && (record[i].back == 0))
		{
			if(strcmp(book_name,record[i].book_name) == 0)
			{
				printf("\t\t  记录已经删除..  ");
			
				if((fp = fopen("record_info.txt","w")) == NULL)
				{
					printf("无法打开该文件\n");
					exit(1);
				}

				for( j = 0 ; j < record_count ; j++)
				{
					if( j != i)
					{
					fprintf(fp,RECORD_FORMAT,record[j].b_r,record[j].back,record[j].book_num,record[j].student_num,record[j].book_name,record[j].student_name,record[j].borrowtime.year,record[j].borrowtime.month,record[j].borrowtime.day,record[j].borrowtime.hour,record[j].borrowtime.minute,record[j].borrowtime.second,record[j].borrowtime.rawtime,record[j].backtime.year,record[j].backtime.month,record[j].backtime.day,record[j].backtime.hour,record[j].backtime.minute,record[j].backtime.second,record[j].backtime.rawtime);
					fputs("\n",fp);
					}

				}
				record_count--;

				fclose(fp);

				printf("\n\t\t  是否继续删除其他书籍记录 ？ ( y or n ) : ");

				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
					   printf("\t\t  您的输入有误,请重新选择:");

				}while(choice != 'y' && choice != 'n');


				if(choice == 'y')
				{
					printf("\t\t  按任意键继续.  ");
					getch();
					Record_Delete();
				}

				if(choice == 'n')
				{
					printf("\t\t  按任意键返回上一级.  ");
					getch();
					Show_Student();
				}
			}
		}
	}

	printf("\n\t\t  未找到该记录，是否继续删除其他书籍记录 ？ ( y or n ) : ");

	do
	{
		fflush(stdin);
		scanf("%c", &choice);

		if(choice != 'y' && choice != 'n')
			   printf("\t\t  您的输入有误,请重新选择:");

	}while(choice != 'y' && choice != 'n');


	if(choice == 'y')
	{
		printf("\t\t  按任意键继续. ");
		getch();
		Record_Delete();
	}

	if(choice == 'n')
	{
		printf("\t\t  按任意键返回上一级.  ");
		getch();
		Show_Student();
	}
}

/*****************二级功能图书查询**************/
void Book_StuInquiry()
{
	switch(Book_StuInquiry_Menu())
	{
	case 1 : Book_Inquiry_Byname2();break;
	case 2 : Book_Inquiry_Byauthor();break;
	case 3 : Frequency_Inordering2();break;
	case 4 : Price_Inordering() ;break;
	case 5 : Show_Student();break;
	}
}


int Book_StuInquiry_Menu()
{
	int choice;

	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t╔════════════════════════════╗\n");
	printf("\t\t║                      图书查询                          ║\n");
	printf("\t\t╠════════════════════════════╣\n");
    printf("\t\t║\t\t1  - 根据书名查询图书                     ║\n");
	printf("\t\t║\t\t2  - 根据作者查询图书                     ║\n");
	printf("\t\t║\t\t3  - 根据借阅次数排序所有图书             ║\n");
	printf("\t\t║\t\t4  - 根据价格排序所有图书                 ║\n");
	printf("\t\t║\t\t5  - 返回上一级菜单                       ║\n");
	printf("\t\t╚════════════════════════════╝\n");
	printf("\t\t  请输入你的选择(1-5):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 5)
		    		printf("\t\t  您的输入有误,请重新输入:");

	}while(choice < 1 || choice > 5);

	fflush(stdin);

	return choice;
}

/******三级功能根据作者******/
void Book_Inquiry_Byauthor()
{
	char author[STRSIZE];
	int i , j = 0;
	int count[BOOKMAX];
	char choice;
	fflush(stdin);
	printf("\n\t\t  请输入作者:");
	scanf("%s",author);


	for(i = 0 ; i < book_count ; i++)
	{
		if((strcmp(author,book[i].author)) == 0)
		{
			count[j] = i ;
			j++;
		}
	}

	if( j != 0)
	{
		printf("\n  查询结果如下：\n");

		printf(" ( 注 ：下面列出的依次是书名，图书编号，作者，价格，出版社，出版时间，图书总量，书架位置，图书简介)\n\n\n");

		j--;

		while(j >= 0 )
		{
			printf(" %-20s\t%-s\t%-s\t%-.2lf元\t%-s\t%-s\t%-d\t%-s\t%-s\n",book[count[j]].name,book[count[j]].book_num,book[count[j]].author,book[count[j]].price,book[count[j]].publishinghouse,book[count[j]].date,book[count[j]].number,book[count[j]].location,book[count[j]].brief);	
			j--;
		}

		printf("\n 是否继续查询( y or n ): ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
						   printf(" 您的输入有误,请重新选择:");

				}while(choice != 'y' && choice != 'n');

				if(choice == 'y')
				{
					printf(" 按任意键继续.  ");
					getch();
					Book_Inquiry_Byauthor();
				}

				else
				{
					printf(" 按任意键返回上一级.  ");
					getch();
					Book_StuInquiry();
				}
	}

	if(j == 0)
	{
		printf("\t\t  没有找到相应书籍.是否继续查询( y or n ): ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  您的输入有误,请重新选择:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
		{
			printf("\t\t  按任意键继续. ");
			getch();
			Book_Inquiry_Byauthor();
		}

		else
		{
			printf("\t\t  按任意键返回上一级. ");
			getch();
			Book_StuInquiry();
		}
	}
}


/***********三级功能根据借阅次数*****************/
void Frequency_Inordering2()   	 /*冒泡算法*/
{
	int i , j ; /* 循环变量 */
	struct Book temp[BOOKMAX] , t;
	
	Load_RecordInfo();

	for( i = 0 ; i < book_count ; i++)
	{
		temp[i] = book[i];
	}

	for( j = 0 ; j < book_count - 1; j++)
	{
		for( i = 0 ; i < book_count - 1 -j ; i++)
		{
			if(temp[i].frequency < temp[i+1].frequency)
			{
				t = temp[i] ;
				temp[i]  =temp[i+1];
				temp[i+1] = t ;
			}
		}
	}
	printf("\n  借阅次数由多到少的是 :");

	printf(" （注 ：下面列出的依次是书名,图书编号,借阅次数,书架位置,图书总量）\n\n");
	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %-20s\t%s\t%d\t%s\t%d\n",temp[i].name,temp[i].book_num,temp[i].frequency,temp[i].location,temp[i].number);
	}

	printf("\n 按任意键返回上一级菜单.. ");
	getch();
	Book_StuInquiry();
}

/*********三级功能根据名字**********/
void Book_Inquiry_Byname2()
{
	char bookname[STRSIZE];
	int i , j = 0;
	char choice;


	printf("\t\t  请输入书名:");

	scanf("%s",bookname);


	for(i = 0 ; i < book_count ; i++)
	{
		if((strcmp(bookname,book[i].name)) == 0)
		{
			j++;
			break;
		}
	}

	if( j == 1)
	{
		printf("  查询结果如下：\n\n");

		printf(" （注 ：下面列出的依次是书名,图书编号,作者,价格,出版社,出版时间,图书总量,书架位置,图书简介）\n\n");
		printf("  %-20s\t%-s\t%-s\t%-.2lf元\t%-s\t%-s\t%-d\t%-s\t%-s\n",book[i].name,book[i].book_num,book[i].author,book[i].price,book[i].publishinghouse,book[i].date,book[i].number,book[i].location,book[i].brief);

		printf("\n  是否继续查询( y or n): ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
						   printf(" 您的输入有误,请重新选择:");

				}while(choice != 'y' && choice != 'n');

				if(choice == 'y')
				{
					printf("\t\t  按任意键继续.  ");
					getch();
					Book_Inquiry_Byname2();
				}

				else
				{
					printf(" 按任意键继续.  ");
					getch();
					Book_StuInquiry();
				}
	}

	if(j == 0)
	{
		printf("\t\t  没有找到相应书籍.是否继续查询( y or n): ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  您的输入有误,请重新选择:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
		{
			printf("\t\t  按任意键继续.  ");
			getch();
			Book_Inquiry_Byname2();
		}

		else
		{
			printf("\t\t  按任意键返回上一级.  ");
			getch();
			Book_StuInquiry();
		}
	}
}

/*********根据价格**********/

void Price_Inordering()   	 /*冒泡算法*/
{
	int i , j ; /* 循环变量 */

	struct Book temp[BOOKMAX] ,t ;

	Load_RecordInfo();

	for( i = 0 ; i < book_count ; i++)
	{
		temp[i] = book[i];
	}

	for( j = 0 ; j < book_count - 1; j++)
	{
		for( i = 0 ; i < book_count - 1 -j ; i++)
		{
			if(temp[i].price < temp[i+1].price)
			{
				t = temp[i] ;
				temp[i]  = temp[i+1];
				temp[i+1] = t ;
			}
		}
	}
	printf("\n 价格由多到少的是 :");

	printf(" （注 ：下面列出的依次是价格,书名,编号,借阅次数,位置,图书总量）\n\n");
	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %.2lf元\t%-20s\t%s\t%d\t%s\t%d\n",temp[i].price,temp[i].name,temp[i].book_num,temp[i].frequency,temp[i].location,temp[i].number);
	}

	printf("\n 按任意键返回上一级菜单.. ");
	getch();
	Book_StuInquiry();

}

/***********************************************************************/

void StudentInfo_Modify()     /*学生信息修改*/
{
	switch( StuInfo_Modify_Menu())
		{
			case 1 : 	 StuInfo_Modify_Tel();break;
			case 2 : 	 StuInfo_Modify_Password();break;
			case 3 :	 StuInfo_Modify_Email();break;
			case 4 :	 Show_StudentMenu();break;
		}
}

int StuInfo_Modify_Menu()
{
	int choice;

			system("cls");
		    printf("\n\n\n\n\n");
		    printf("\t╔════════════════════════════════╗\n");
		    printf("\t║                         学生用户信息修改                       ║\n");
		    printf("\t╠════════════════════════════════╣\n");
		    printf("\t║\t\t1  - 修改电话                                     ║\n");
		    printf("\t║\t\t2  - 修改密码                                     ║\n");
		    printf("\t║\t\t3  - 修改邮箱                                     ║\n");
		    printf("\t║\t\t4  - 返回上一级菜单                               ║\n");
		    printf("\t╚════════════════════════════════╝\n");
		    printf("\t\t  请输入你的选择(1-4):");

		    do{
		    		fflush(stdin);
		    		scanf("%d", &choice);

		    		if(choice < 1 || choice > 4)
		    		printf("\t\t  您的输入有误,请重新输入:");

		    }while(choice < 1 || choice > 4);

		    fflush(stdin);

		    return choice;
}

void StuInfo_Modify_Tel()
{
	FILE *fp;
	int i;

	if((fp = fopen("student_info.txt","w")) == NULL)
		{
			printf("无法打开该文件\n");
			exit(1);
		}

	printf("\t\t  请输入新的手机号码：");
	scanf("%s",student[student_current].telnum);

	while(Telformat_check(student[student_current].telnum))
	{
			fflush(stdin);
			printf("\t\t  格式错误，请输入11位数字：");
			scanf("%s",student[student_current].telnum);
	}

	for(i = 0 ; i < student_count; i++)
	{
		fprintf(fp,STU_FORMAT,STU_INPUT);
		fputs("\n",fp);
	}
	fclose(fp);
	printf("\t\t  保存成功，按任意键返回.");
	getch();

	StudentInfo_Modify();

}

void StuInfo_Modify_Password()
{
	FILE *fp;
	int i;

	if((fp = fopen("student_info.txt","w")) == NULL)
		{
			printf("无法打开该文件\n");
			exit(1);
		}

	printf("\t\t  请输入新的密码：");
	scanf("%s",student[student_current].password);


	for(i = 0 ; i < student_count; i++)
	{
		fprintf(fp,STU_FORMAT,STU_INPUT);
		fputs("\n",fp);
	}

	printf("\t\t  保存成功，按任意键返回");
	getch();

	fclose(fp);

	StudentInfo_Modify();
}

void StuInfo_Modify_Email()
{
	FILE *fp;
	int i;

	if((fp = fopen("student_info.txt","w")) == NULL)
		{
			printf("无法打开该文件\n");
			exit(1);
		}

	printf("\t\t  请输入新的邮箱：");
	scanf("%s",student[student_current].email);

	while(EmailFormat_check(student[student_current].email) == 1)
	{
			fflush(stdin);
			printf("\t\t  格式错误，请输入*****@***.***格式： ");
			scanf("%s",student[student_current].email);
	}

	for(i = 0 ; i < student_count; i++)
	{
		fprintf(fp,STU_FORMAT,STU_INPUT);
		fputs("\n",fp);
	}

	printf("\t\t  保存成功，按任意键返回");
	getch();

	fclose(fp);
	
	StudentInfo_Modify();
}

int EmailFormat_check(char *email)   /***  XXXXX@XXX.XXX 格式,如果正确返回0，不正确返回1 ***/
{
	char *p = strstr(email,"@");

	if(!p)
		return EXIT_FAILURE;

	if (!(p-email))
		return EXIT_FAILURE;

	if(!(strstr(p,".")))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int Telformat_check(char *tel)     /*判断电话格式，如果正确返回0，不正确返回1*/
{
		int i;

		if(strlen(tel) == 11)
		{
				for(i = 0 ; i < 11 ; i++)
				{
					if(isdigit(tel[i]))
					{
						;
					}
					else
					{
						return EXIT_FAILURE;
					}
				}
		}

		else
		{
				return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
}





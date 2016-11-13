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

#define ADMINMAX   10 	/*�������Ա����10��*/
#define STUDENTMAX 50	/*����ѧ������50��*/
#define RECORDMAX  1000 /*������ļ�¼����1000��*/
#define BOOKMAX    100  /*�����鱾����100��*/

#define STRSIZE 25  /*һ���ַ�������*/

struct STUDENT
{
	int flag;         	 		/*0 ��ʾ���� �� 1��ʾ������Ա����*/
	char num[STRSIZE]; 			/*ѧ��*/
	char password[STRSIZE];  	/*����*/
	char email[STRSIZE];  		/*����*/
	char telnum[STRSIZE];  		/*�绰����*/
	char major[STRSIZE]; 		/*רҵ*/
	char gender[STRSIZE]; 		/*�Ա�*/
	char name[STRSIZE];  		/*����*/
	char faculty[STRSIZE]; 		/*ѧԺ*/
}student[STUDENTMAX];			/*STUDENTMAX�����޸�*/
int student_count = 0;  		 /*��¼ѧ������*/
int student_current = 0;		 /*�����ǰΪѧ����¼�ˣ���¼��ǰѧ���ڽṹ����λ��*/
						 	 	 /*�����ǰΪ����Ա��¼�ˣ���¼�޸�ѧ��*/


struct ADMIN
{
		char num[STRSIZE];      	/*����*/
		char password[STRSIZE];		/*����*/
		char email[STRSIZE];		/*����*/
		char name[STRSIZE];			/*����*/	
}admin[ADMINMAX];
int admin_count = 0;
int admin_current = 0;

struct Book
{
	int number;						/*ͼ��������*/
	int frequency;     				/*���Ĵ���*/
	double totaltime;       		/*��λΪСʱ*/
	double price;					/*�۸�*/
	char book_num[STRSIZE];    		/*ͼ����*/
	char publishinghouse[STRSIZE];	/*������*/
	char name[STRSIZE];				/*����*/
	char author[STRSIZE];			/*����*/
	char date[STRSIZE];  			/*��������*/
	char location[STRSIZE];			/*���*/
	char brief[120];				/*���*/
}book[BOOKMAX];
int book_count = 0;

struct Time
{
    int year,month,day;
    int hour,minute,second;
    time_t rawtime;				/*��ĳһʱ�̵�����ʱ�������*/
};

struct Record
{
	int b_r;					/*���Ļ������裿0Ϊ���ģ�1Ϊ����*/
	int back;              		/*�Ƿ��ѻ���0Ϊδ����1Ϊ�ѻ�*/
	char book_num[STRSIZE];		/*��ı��*/
	char student_num[STRSIZE];	/*ѧ��ѧ��*/
	char book_name[STRSIZE];	/*����*/
	char student_name[STRSIZE];	/*ѧ������*/
	struct Time borrowtime; 	/*���Ļ�����ʱ��*/
	struct Time backtime;		/*�黹ʱ��*/
}record[RECORDMAX];
int record_count= 0;


time_t logintime ;    /*��¼��¼ʱ��*/


/**************************�ʼ���棬ѡ�����**************************/
int StartMenu();

void Stu_Login();
void Show_Student();
int Show_StudentMenu();
void Show_Freeze();

void Admin_Login();
void Show_Admin();
int Show_AdminMenu();

/*����ѧ���͹���Ա��Ϣ*/
void Load_StuInfo();
void Load_AdminInfo();
void Load_BookInfo();
void Load_RecordInfo();


/***************************�˳���ע��****************************/
void Quit();/*�˳�*/
void Logout();/*ע��*/



/****��¼��¼ʱ�䣬��Ϊ�ж��Ƿ��������(Ĭ���˳�����֮��������)****/
void LoginTime();


/************************ѧ�����ܲ˵������˵�**************************/

void Book_Borrow();    /*ͼ�����*/
void Book_Revert();    /*ͼ��黹*/
void Book_Renew();    /*ͼ������*/
void Record_Check();  /*��ѯ���Ľ��*/
void Record_Delete() ;   /*���ļ�¼ɾ��*/

void Book_StuInquiry();    /*ͼ���ѯ*/
int Book_StuInquiry_Menu(); /*ͼ���ѯ�˵�*/

void StudentInfo_Modify() ;/*ѧ����Ϣ�޸�*/
int StuInfo_Modify_Menu();/*ѧ����Ϣ�޸Ĳ˵�*/

/**********************��������************************/

void StuInfo_Modify_Password(); /*������*/
void StuInfo_Modify_Email();/*������*/
void StuInfo_Modify_Tel();/*�ĵ绰����*/

void Book_Inquiry_Byauthor(); /*�������߲�ѯͼ��*/
void Book_Inquiry_Byname2();   /*�������ֲ�ѯͼ��*/
void Frequency_Inordering2();  /*���ݽ��Ĵ�������*/
void Price_Inordering(); /*���ݼ۸�����*/


int Stu_IdCheck(char *); /*ѧ�ż��*/
int Stu_PasswdCheck(char *);/*������*/

int SearchnumByname(char *);  /*ͨ�������ҵ�ͼ����*/
int CheckIfborrow(char *);   /*�жϸ����Ƿ��ѱ����˽���*/
int JudgeStuBorrow(char *) ; /*�ж�ѧ���Ƿ����ڽ��ĸ���*/
int JudgeIftwice(char *);/*�ж��Ƿ����賬������*/

/************************************************************************/

/*����Ա���ܲ˵���������*/
/********************************/
int AdminInfo_Modify_Menu();/*����Ա��Ϣ�޸�*/
void AdminInfo_Modify();/**/
void AdminInfo_Modify_Password();/**/
void AdminInfo_Modify_Email();/**/

/********************************/

void BookManagement();/*ͼ�����*/
int BookManagement_Menu();/*ͼ�����˵�*/

void Book_Inquiry();/*ͼ���ѯ*/
int Book_Inquiry_Menu();/**/
void Book_Inquiry_Bypublishinghouse();/*ͨ���������ѯͼ��*/
void Book_Inquiry_Byname();/*ͨ�����ֲ�ѯͼ��*/

void Book_Add();	/*ͼ�����*/
void Book_Delete();	/*ͼ��ɾ��*/
void Book_Modify();	/*ͼ���޸�*/
/********************************/
int BorrowManagement_Menu();/*���Ĺ���*/
void BorrowManagement();/**/


int BorrowInfo_Show_Menu();/*��ѯ�������*/
void BorrowInfo_Show();/**/
void Borrow_AllShow();/*��ѯ����ͼ��������*/
void StudentBorrowInfo_Show();/*��ѯ����ͼ��ѧ�����*/
void OverdueStudent_Show();/*��ѯδ����ѧ��*/
void OverdueBook_Show();/*��ѯδ����ͼ��*/

void BorrowInfo_Count();/*ͳ�ƽ�����Ϣ*/
int BorrowInfo_Count_Menu();/*ͳ�ƽ�����Ϣ�˵�*/
void Major_Inordering();/*����רҵ�ڽ�����*/
void Frequency_Inordering();/*�����Ĵ�������*/
void Time_Inordering();/*������ʱ������*/

void AccountManagement();/*�˺Ź���*/
int AccountManagement_Menu();/**/
void Freeze();/*�����˺�*/
void Unfreeze();/*�ⶳ�˺�*/
/********************************/

int Check_Freeze();/*����˺��Ƿ񱻶���*/
int Admin_IdCheck(char *);/*���ż��*/
int Admin_PasswdCheck(char *);/*������*/
int Numberexist(char *);/*�����ı���Ƿ��ظ�*/
int Numberformat_check(char *) ;/*������ŵĸ�ʽ*/
int Locationexist(char *);/*������λ���Ƿ��ظ�*/

int IdformatJudge(char *);/*�˺Ÿ�ʽ���*/
int Telformat_check(char *);/*�绰�����ʽ���*/
int EmailFormat_check(char *);/*�����ʽ���*/
int CheckBookborrow(char *);

/*****************************������*******************************/

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

/***********************************��ʼ��Ϣ����******************************/

void Load_StuInfo()
{
	FILE *fp;
	int i = 0 ;   /*ѭ������*/

	if((fp = fopen("student_info.txt","r")) == NULL)
		{
			printf("�޷��򿪸��ļ�\n");
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
	int i = 0 ;   /*ѭ������*/

	if((fp = fopen("admin_info.txt","r")) == NULL)
		{
			printf("�޷��򿪸��ļ�\n");
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
	int i = 0 ;   /*ѭ������*/

	if((fp = fopen("book_info.txt","r")) == NULL)
		{
			printf("�޷��򿪸��ļ�\n");
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
	int i = 0 ;   /*ѭ������*/

	if((fp = fopen("record_info.txt","r")) == NULL)
		{
			printf("�޷��򿪸��ļ�\n");
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

void LoginTime()     /*��¼��¼ʱ�䣬��Ϊ�ж��Ƿ��������(Ĭ���˳�����֮��������)*/
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
	printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t�U                      ��ӭ����ͼ��ݽ���ϵͳ                  �U\n");
	printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
	printf("\t�U\t\t\t1 - ѧ�����                            �U\n");
	printf("\t�U\t\t\t2 - ����Ա���                          �U\n");
	printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\n\t\t  ���������ѡ��");

	do{
		fflush(stdin);
		scanf("%d",&choice);
		if(choice < 1 || choice > 2)
		printf("\t\t  ������������,����������:");

	}while(choice < 1 || choice > 2);

	fflush(stdin);

	return choice;
}


/******************************ע�����˳�******************************/
void Logout()
{
	fflush(stdin);
	main();
}

void Quit()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t�U                 ллʹ��ͼ��ݽ���ϵͳ !                       �U\n");
	printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
	printf("\t�U\t\t\t                                          �U\n");
	printf("\t�U\t\t\t��������˳�....                          �U\n");
	printf("\t�U\t\t\t                                          �U\n");
	printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	fflush(stdin);
	getch();
	exit(0);
}

/*********************************����Ա��*****************************/
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
	    printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	    printf("\t�U              ��ӭ����ͼ��ݽ���ϵͳ ������Ա�ˣ�               �U\n");
	    printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
	    printf("\t�U\t\t1  - ͼ�����                                     �U\n");
	    printf("\t�U\t\t2  - ���Ĺ���                                     �U\n");
	    printf("\t�U\t\t3  - ������Ϣͳ��                                 �U\n");
	    printf("\t�U\t\t4  - ������Ϣ�޸�                                 �U\n");
	    printf("\t�U\t\t5  - ע��                                         �U\n");
	    printf("\t�U\t\t6  - �˳�                                         �U\n");
	    printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	    printf("\t\t  ���������ѡ��(1-6):");

	    do{
	    		fflush(stdin);
	    		scanf("%d", &choice);

	    		if(choice < 1 || choice > 6)
	    		printf("\t\t  ������������,����������:");

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
		printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("\t�U            ��ӭ����ͼ��ݽ���ϵͳ ������Ա�ˣ�               �U\n");
		printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
		printf("\t\t  ���������Ĺ��ţ� 10 λ���֣���");

		scanf("%s",id);

		while(IdformatJudge(id) || Admin_IdCheck(id))
		{
			fflush(stdin);
			printf("\t\t  ���Ŵ�����������ȷ���ţ�");
			scanf("%s",id);
		}

		printf("\t\t  �������������� ��");

		scanf("%s",passwd);

		while(Admin_PasswdCheck(passwd))
		{
				fflush(stdin);
				printf("\t\t  ���������������ȷ���룺");
				scanf("%s",passwd);
		}

		printf("\t\t  ��½�ɹ��������������.");
		getch();
}


/**********ͼ����Ĺ�������˵�************/

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
	printf("\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t�U                    ͼ����Ĺ���                        �U\n");
	printf("\t\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
    printf("\t\t�U\t\t1  - ���������ѯ                         �U\n");
	printf("\t\t�U\t\t2  - �����˻�����                         �U\n");
	printf("\t\t�U\t\t3  - ������һ���˵�                       �U\n");
	printf("\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t  ���������ѡ��(1-3):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 3)
		    		printf("\t\t  ������������,����������:");

	}while(choice < 1 || choice > 3);

	fflush(stdin);

	return choice;
}

/*******�����˻����������˵�******/

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
	printf("\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t�U                    �����˺Ź���                        �U\n");
	printf("\t\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
    printf("\t\t�U\t\t1  - �˺Ŷ���                             �U\n");
	printf("\t\t�U\t\t2  - �˺Žⶳ                             �U\n");
	printf("\t\t�U\t\t3  - ������һ���˵�                       �U\n");
	printf("\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t  ���������ѡ��(1-3):");

	do
	{
		 fflush(stdin);
		 scanf("%d", &choice);

		 if(choice < 1 || choice > 3)
		     printf("\t\t  ������������,����������:");

	}while(choice < 1 || choice > 3);

	fflush(stdin);

	return choice;
}

/*�ļ�����ѧ���˻�����*/
void Freeze()
{
	int i;
	char id[STRSIZE];
	char choice1,choice2;
	FILE *fp;

	printf("\n\t\t  ������Ҫ�����ѧ�ţ�");
	scanf("%s",id);

	while(IdformatJudge(id) || Stu_IdCheck(id))
	{
		fflush(stdin);
		printf("\t\t  δ�ҵ�����ѧ�ţ����ٴ����룺");
		scanf("%s",id);
	}

	printf("\t\t  �ɹ��ҵ���ѧ�ţ��Ƿ�Ҫ���᣿(y or n) ");

	do
	{
		fflush(stdin);
		scanf("%c", &choice1);

		if(choice1 != 'y' && choice1 != 'n')
			   printf("\t\t  ������������,������ѡ��:");

	}while(choice1 != 'y' && choice1 != 'n');


	if(choice1 == 'y')
	{
		if(Check_Freeze() == 1)
		{

			printf("\t\t  ���˻��ѱ�����..");
			printf("\t\t  �Ƿ�������������˻���(y or n): ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice2);

				if(choice2 != 'y' && choice2 != 'n')
						   printf("\t\t  ������������,������ѡ��:");

			}while(choice2 != 'y' && choice2 != 'n');

			if(choice2 == 'y')
			{
				Freeze();
			}
			else
			{
				 printf("\t\t  �������������һ���˵�...");
				 getch();
				 AccountManagement();
			}
		}
		else
		{
			student[student_current].flag = 1 ;

			if((fp = fopen("student_info.txt","w")) == NULL)
				{
					printf("�޷��򿪸��ļ�\n");
					exit(1);
				}

			for(i = 0 ; i < student_count; i++)
			{
				fprintf(fp,STU_FORMAT,STU_INPUT);
				fputs("\n",fp);
			}
			fclose(fp);

			printf("\t\t  ���˻��ѳɹ�������.");
			printf("\n\t\t  �Ƿ�������������˻���(y or n): ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice2);

				if(choice2 != 'y' && choice2 != 'n')
					printf("\t\t  ������������,������ѡ��:");

			}while(choice2 != 'y' && choice2 != 'n');

			if(choice2 == 'y')
				{
					Freeze();
				}
				else
				{
					printf("\t\t  �������������һ���˵�...");
					getch();
					AccountManagement();
				}

		}
	}

	else
	{
		printf("\t\t  �������������һ���˵�...");
		getch();
		AccountManagement();
	}
}

/*�ļ�����ѧ���˻��ⶳ*/

void Unfreeze()
{
	char id[STRSIZE];
	char choice1,choice2;
	int i ;
	FILE *fp;

	printf("\n\t\t  ������Ҫ�ⶳ��ѧ�ţ�");
	scanf("%s",id);

	while(IdformatJudge(id) || Stu_IdCheck(id))
		{
			fflush(stdin);
			printf("\t\t  δ�ҵ�����ѧ�ţ����ٴ����룺");
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
					printf("\t\t  ���˻�δ������..");
					printf("\t\t  �Ƿ�����ⶳ�����˻���(y or n): ");

					do
					{
						fflush(stdin);
						scanf("%c", &choice2);

						if(choice2 != 'y' && choice2 != 'n')
								   printf("\t\t  ������������,������ѡ��:");

					}while(choice2 != 'y' && choice2 != 'n');

					if(choice2 == 'y')
					{
						Unfreeze();
					}
					else
					{
						 printf("\t\t  �������������һ���˵�...");
						 getch();
						 AccountManagement();
					}
				}

	printf("\t\t  �ɹ��ҵ���ѧ�ţ��Ƿ�Ҫ�ⶳ��(y or n) ");

		do
		{
			fflush(stdin);
			scanf("%c", &choice1);

			if(choice1 != 'y' && choice1 != 'n')
				   printf("\t\t  ������������,������ѡ��:");

		}while(choice1 != 'y' && choice1 != 'n');


		if(choice1 == 'y')
		{

				student[student_current].flag = 0 ;

				if((fp = fopen("student_info.txt","w")) == NULL)
							{
								printf("�޷��򿪸��ļ�\n");
								exit(1);
							}

						for(i = 0 ; i < student_count; i++)
						{
							fprintf(fp,STU_FORMAT,STU_INPUT);
							fputs("\n",fp);
						}
				fclose(fp);

				printf("\t\t  ���˻��ѳɹ����ⶳ.");
				printf("\n\t\t  �Ƿ�����ⶳ�����˻���(y or n): ");

				do
				{
					fflush(stdin);
					scanf("%c", &choice2);

					if(choice2 != 'y' && choice2 != 'n')
						printf("\t\t  ������������,������ѡ��:");

				}while(choice2 != 'y' && choice2 != 'n');

				if(choice2 == 'y')
					{
						Unfreeze();
					}
				else
					{
						printf("\t\t  �������������һ���˵�...");
						getch();
						AccountManagement();
					}
			
		}

		else
		{
			printf("\t\t  �������������һ���˵�...");
			getch();
			AccountManagement();
		}
}

int Check_Freeze()   /*��������᷵��1 ��δ�����᷵��0 */
{
	if(student[student_current].flag == 1 )
		return 1;

	return 0;
}

/*******������Ϣ�鿴�����˵�*********/

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
	printf("\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t�U                      ���������ѯ                      �U\n");
	printf("\t\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
    printf("\t\t�U\t\t1  - �鿴����ͼ��������                 �U\n");
	printf("\t\t�U\t\t2  - ��ѯ����ͼ��ѧ����Ϣ                 �U\n");
	printf("\t\t�U\t\t3  - ��ѯ����δ��ͼ��                     �U\n");
	printf("\t\t�U\t\t4  - ��ѯ����δ��ѧ��                     �U\n");
	printf("\t\t�U\t\t5  - ������һ���˵�                       �U\n");
	printf("\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t  ���������ѡ��(1-5):");

	do
	{
		 fflush(stdin);
		 scanf("%d", &choice);

		 if(choice < 1 || choice > 5)
		     printf("\t\t  ������������,����������:");

	}while(choice < 1 || choice > 5);

	fflush(stdin);

	return choice;
}

/*�������� �鿴����ͼ��������*/
void Borrow_AllShow()
{
	int i ;	/*ѭ������,����book*/
	int j ; /*ѭ������������record*/
	int n ;
	
	Load_RecordInfo();
	Load_BookInfo();

	printf("\n\n (ע ������������������ͼ���ţ��ڹ��������ѽ����������ߣ��۸񣬳����磬����ʱ�䣬���λ�ã�ͼ���� ) \n\n ");

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

	printf("\n\n ���Ͻ���ʾ�ѽ���ͼ����Ϣ. ");
	printf(" �������������һ���˵�. ");
	getch();

	BorrowInfo_Show();

}

/*�ļ����ܲ�ѯ����ͼ��ѧ����Ϣ*/

void StudentBorrowInfo_Show()
{
	char stu_name[STRSIZE];
	char book_name[STRSIZE];

	int i ;	
	int j ; 
	int n  = 0 ;

	printf("\t\t  ��ѯ��ĳ���ĳλͬѧ��������Ҫ��ѯ��ѧ������:");
	scanf("%s",stu_name);
	printf("\t\t  ������Ҫ��ѯ������:");
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
							printf("������%d��%d��%d��%dʱ���ĸ���.\n\n",record[j].borrowtime.year,record[j].borrowtime.month,record[j].borrowtime.day,record[j].borrowtime.hour);
							printf(" �����Ǹ�������ϸ��Ϣ: \n");
							printf("��ע������һ����ѧ��������ѧ�ţ����䣬�绰���룬רҵ���Ա�ѧԺ��\n\n");
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
		printf("\n\n �������������һ���˵�.. ");
		getch();
		BorrowInfo_Show();
	}

	if( n == 0)
	{
		printf("\t\t �޴�ѧ�������ļ�¼. ");
		printf("\n\t\t �������������һ���˵�.. ");
		getch();
		BorrowInfo_Show();
	}


}


/*�ļ����ܲ�ѯ����δ��ͼ��*/

void OverdueBook_Show()
{
	int i;
	int n = 0 ; 	/*����*/
    
	time_t nowtime;

	time( &nowtime );

	Load_RecordInfo();
	Load_BookInfo();

	printf(" ��ѯ�������: \n");
	printf("��ע������������ʾ���� ������ͼ���ţ������ߣ�������ѧ�ţ�����ʱ�䣩\n\n");

	for(i = 0 ; i < record_count ; i++)
	{
		if(record[i].back == 0 )
		{
			if(( nowtime - record[i].borrowtime.rawtime)  >= 2592000)/* 30�� * 24Сʱ/�� * 60��/Сʱ * 60��/�� = 2592000��*/
			{
				printf(" %-20s\t%s\t%s\t%s\t%4d��%2d��%2d��%2dʱ%2d��\n",record[i].book_name,record[i].book_num,record[i].student_name,record[i].student_num,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour,record[i].borrowtime.minute);
				n++;
			}
		}

	}

	if( n == 0)
	{
		printf(" û�г���δ��ͼ�飡�������������һ���˵�..");
		getch();
		BorrowInfo_Show();
	}

	if( n > 0)
	{
		printf(" ������ϣ��������������һ���˵�..");
		getch();
		BorrowInfo_Show();
	}
}

/*�ļ����ܲ�ѯ����δ��ѧ�� */

void OverdueStudent_Show()
{
	int i;
	int n = 0 ; 	/*����*/
    time_t nowtime;

	time( &nowtime );

	printf(" ��ѯ�������: \n");
	printf("��ע������������ʾ���� ������ͼ���ţ������ߣ�������ѧ�ţ�����ʱ�䣩\n\n");

	for(i = 0 ; i < record_count ; i++)
	{
		if(( nowtime - record[i].borrowtime.rawtime)  >= 2592000)/* 30�� * 24Сʱ/�� * 60��/Сʱ * 60��/�� = 2592000��*/
		{
			if(record[i].back == 0)
			{
				printf(" %-20s\t%s\t%s\t%s\t%4d��%2d��%2d��%2dʱ%2d��\n",record[i].book_name,record[i].book_num,record[i].student_name,record[i].student_num,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour,record[i].borrowtime.minute);
				n++;
			}

		}
	}

	if( n == 0)
	{
		printf(" û�г���δ��ѧ�����������������һ���˵�..");
		getch();
		BorrowInfo_Show();
	}

	if( n > 0)
	{
		printf(" ������ϣ��������������һ���˵�..");
		getch();
		BorrowInfo_Show();
	}
}


/*******�����˵�������Ϣͳ��*******/
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
	printf("\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t�U                    ͼ�������Ϣͳ��                    �U\n");
	printf("\t\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
    printf("\t\t�U\t\t1  - ������ʱ������                       �U\n");
	printf("\t\t�U\t\t2  - �����Ĵ�������                       �U\n");
	printf("\t\t�U\t\t3  - ��רҵͳ��                           �U\n");
	printf("\t\t�U\t\t4  - ������һ���˵�                       �U\n");
	printf("\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t  ���������ѡ��(1-4):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 4)
		    		printf("\t\t  ������������,����������:");

	}while(choice < 1 || choice > 4);

	fflush(stdin);

	return choice;
}

/* �������� ������ʱ������ */

void Time_Inordering()   	 /*ð���㷨*/
{
	int i , j ; /* ѭ������ */

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
	printf("\n ����ʱ���ɶൽ�ٵ��� : \n");

	printf("��ע �� ������������������ţ�����ʱ���������ܣ�ͼ��������\n\n");

	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %-20s\t%s\t%.2lf\t%s\t%d\n",temp[i].name,temp[i].book_num,temp[i].totaltime,temp[i].location,temp[i].number);
	}

	printf(" \n �������������һ���˵�.. ");
	getch();
	BorrowInfo_Count();
}

/* �������� �����Ĵ������� */
void Frequency_Inordering()   	 /*ð���㷨*/
{
	int i , j ; /* ѭ������ */

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
	printf("\n ���Ĵ����ɶൽ�ٵ��� : \n");
	printf("��ע �� ������������������ţ����Ĵ����������ܣ�ͼ��������\n\n");
	
	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %-20s\t%s\t%d\t%s\t%d\n",temp[i].name,temp[i].book_num,temp[i].frequency,temp[i].location,temp[i].number);
	}

	printf("\n ����Ϊ���������������������һ���˵�.. ");
	getch();
	BorrowInfo_Count();
}

/* �������� ��רҵͳ������ */

void Major_Inordering()
{
	struct Book book_copy[BOOKMAX],t;           /*���ø���ͼ����Ϣfrequency��ʾרҵ�Ķ���*/
	struct STUDENT student_copy[STUDENTMAX];
	int i , j = 0 , k ;
	char  major[STRSIZE];
	int count;    /*�������רҵ��ѧ������*/

	Load_RecordInfo();
	Load_BookInfo();
	
	printf("\n ��������Ҫ��ѯ��רҵ��ȫ�ƣ�: ");
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
	printf(" ��רҵ���Ĵ����ɶൽ�ٵ��� :\n");

	printf("��ע �� ������������������ţ����Ĵ����������ܣ��ڹ���Ŀ��\n\n");
	
	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %-20s\t%s\t%d\t%s\t%d\n",book_copy[i].name,book_copy[i].book_num,book_copy[i].frequency,book_copy[i].location,book_copy[i].number);
	}

	printf("\n ����Ϊ���������������������һ���˵�.. ");
	getch();
	BorrowInfo_Count();

}

/*********************************************************************/


/****************************ͼ����������˵�*****************************/

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
	printf("\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t�U                    ͼ����Ϣ����                        �U\n");
	printf("\t\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
    printf("\t\t�U\t\t1  - ��ѯͼ��                             �U\n");
	printf("\t\t�U\t\t2  - ����ͼ��                             �U\n");
	printf("\t\t�U\t\t3  - �޸�ͼ����Ϣ                         �U\n");
	printf("\t\t�U\t\t4  - ɾ��ͼ��                             �U\n");
	printf("\t\t�U\t\t5  - ������һ���˵�                       �U\n");
	printf("\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t  ���������ѡ��(1-5):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 5)
		    		printf("\t\t  ������������,����������:");

	}while(choice < 1 || choice > 5);

	fflush(stdin);

	return choice;
}

/*********�ļ�����ͼ���ѯ***********/

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
	printf("\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t�U                    ͼ����Ϣ����                        �U\n");
	printf("\t\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
    printf("\t\t�U\t\t1  - ���ݳ������ѯ                       �U\n");
	printf("\t\t�U\t\t2  - ����������ѯ                         �U\n");
	printf("\t\t�U\t\t3  - ������һ���˵�                       �U\n");
	printf("\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t  ���������ѡ��(1-3):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 3)
		    printf("\t\t  ������������,����������:");

	}while(choice < 1 || choice > 3);

	fflush(stdin);

	return choice;
}


/*�弶���ܰ��������ѯ*/

void Book_Inquiry_Bypublishinghouse()
{
	char publishinghouse[STRSIZE];
	int i , j = 0;
	int count[BOOKMAX];
	char choice;

	fflush(stdin);
	printf("\n\t\t  �����������:");

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
		printf(" ��ѯ������£�\n");

		printf(" ( ע �������г���������������ͼ���ţ����ߣ��۸񣬳����磬����ʱ�䣬ͼ�����������λ�ã�ͼ����)\n\n\n");

		j--;

		while(j >= 0 )
		{
			printf(" %-20s\t%-s\t%-s\t%-.2lfԪ\t%-s\t%-s\t%-d\t%-s\t%-s\n",book[count[j]].name,book[count[j]].book_num,book[count[j]].author,book[count[j]].price,book[count[j]].publishinghouse,book[count[j]].date,book[count[j]].number,book[count[j]].location,book[count[j]].brief);	
			j--;
		}
		
		printf("\n ����Ϊȫ����Ϣ���Ƿ������ѯ��( y or n ): ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
						   printf(" ������������,������ѡ��:");

				}while(choice != 'y' && choice != 'n');

				if(choice == 'y')
				{
					printf(" �����������.\n\n  ");
					getch();
					Book_Inquiry_Bypublishinghouse();
				}

				else
				{
					printf(" �������������һ��. ");
					getch();
					Book_Inquiry();
				}
	}

	if(j == 0)
	{
		printf("\t\t  û���ҵ���Ӧ�鼮.�Ƿ������ѯ( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  ������������,������ѡ��:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
		{
			printf("\t\t  �����������.  ");
			getch();
			Book_Inquiry_Bypublishinghouse();
		}

		else
		{
			printf("\t\t  �������������һ��.  ");
			getch();
			Book_Inquiry();
		}
	}
}


/*���ܰ�������ѯ*/

void Book_Inquiry_Byname()
{
	char bookname[STRSIZE];
	int i , j = 0;
	char choice;

	fflush(stdin);
	printf("\n\t\t  ����������:");

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
		printf(" ��ѯ������£�\n\n");

		printf(" ��ע �������г�������������,ͼ����,����,�۸�,������,����ʱ��,ͼ������,���λ��,ͼ���飩\n\n");
		printf(" %-20s\t%-s\t%-s\t%-.2lfԪ\t%-s\t%-s\t%-d\t%-s\t%-s\n",book[i].name,book[i].book_num,book[i].author,book[i].price,book[i].publishinghouse,book[i].date,book[i].number,book[i].location,book[i].brief);

		printf("\n ����Ϊȫ��������Ƿ������ѯ( y or n ): ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
						   printf(" ������������,������ѡ��:");

				}while(choice != 'y' && choice != 'n');

				if(choice == 'y')
				{
					printf("\t\t  �����������.  ");
					getch();
					Book_Inquiry_Byname();
				}

				else
				{
					printf(" �����������.  ");
					getch();
					Book_Inquiry();
				}
	}

	if(j == 0)
	{
		printf("\t\t  û���ҵ���Ӧ�鼮.�Ƿ������ѯ( y or n ): ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  ������������,������ѡ��:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
		{
			printf("\t\t  �����������.  ");
			getch();
			Book_Inquiry_Byname();
		}

		else
		{
			printf("\t\t  �������������һ��.  ");
			getch();
			Book_Inquiry();
		}
	}
}

/*********�ļ���������ͼ��***********/

void Book_Add()
{
	int i , n = 0;
	char choice1 , choice2;  /*�ֱ����ڴ��� y or n*/

	FILE *fp;
	fflush(stdin);
	printf("\n\t\t  ������Ҫ��ӵ�ͼ������ ");
	scanf("%s",book[book_count].name);

	for( i = 0 ; i < book_count ; i ++)
	{

		if((strcmp(book[book_count].name,book[i].name)) == 0 )
		{
			printf("\t\t  �����Ѿ����ڣ���ӽ�����һ�� �� ");
			printf("\t\t  �Ƿ���ӣ� ( y or n): ");
			do
			{
				fflush(stdin);
				scanf("%c", &choice1);

				if(choice1 != 'y' && choice1 != 'n')
					 printf("\t\t  ������������,������ѡ��:");

			}while(choice1 != 'y' && choice1 != 'n');

			if(choice1 == 'y')
			{
				book[i].number++;

				if((fp = fopen("book_info.txt","w")) == NULL)
					{
						printf("�޷��򿪸��ļ�\n");
						exit(1);
					}

				for( i = 0 ; i < book_count ; i++)
				{
					fprintf(fp,BOOK_FORMAT,book[i].number,book[i].frequency,book[i].totaltime,book[i].price,book[i].book_num,book[i].publishinghouse,book[i].name,book[i].author,book[i].date,book[i].location,book[i].brief);
					fputs("\n",fp);
				}


				printf("\t\t  ����ɹ����Ƿ�������ͼ�飿( y or n) ");

				do
				{
					fflush(stdin);
					scanf("%c", &choice2);

					if(choice2 != 'y' && choice2 != 'n')
						printf("\t\t  ������������,������ѡ��:");

				}while(choice2 != 'y' && choice2 != 'n');

				if(choice2 == 'y')
					BookManagement();

				else
				{
					printf("\t\t  �������������һ���˵�. ");
					getch();
					Book_Inquiry();
				}
			}

			else
			{
				printf("\t\t  �Ƿ�������ͼ�飿(y or n) ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice2);

					if(choice2 != 'y' && choice2 != 'n')
							printf("\t\t  ������������,������ѡ��:");

				}while(choice2 != 'y' && choice2 != 'n');

				if(choice2 == 'y')
					Book_Add();

				else
				{
					printf("\t\t  �������������һ���˵�. ");
					getch();
					BookManagement();
				}

			}
		}

	}

			printf("\t\t  �����������(��100001��ʼ����λ���)��");

			scanf("%s",book[book_count].book_num);

			while(Numberformat_check(book[book_count].book_num))
			{
				fflush(stdin);
				printf("\t\t  ��ʽ�������������� ��");
				scanf("%s",book[book_count].book_num);
			}

			while(Numberexist(book[book_count].book_num))
						{
							fflush(stdin);
							printf("\t\t  ��ʽ�������������� ��");
							scanf("%s",book[book_count].book_num);
						}

			printf("\t\t  ���������Ҫ��ŵ����λ�ã����磺a100����");

			scanf("%s",book[book_count].location);       

			while(Locationexist(book[book_count].location))
			{
				fflush(stdin);
				printf("\t\t  �õط�����ͼ�飬���������� ��");
				scanf("%s",book[book_count].location);
			}

			printf("\t\t  ����������������");
			scanf("%d",&book[book_count].number);

			printf("\t\t  ���������ĳ����磺");
			scanf("%s",book[book_count].publishinghouse);

			printf("\t\t  �������������ߣ�");
			scanf("%s",book[book_count].author);

			printf("\t\t  ���������ĳ���ʱ��(��ʽ ****��**��**�� )��");
			scanf("%s",book[book_count].date);

			printf("\t\t  ���������ļ۸�(������λС�� )��");
			scanf("%lf",&book[book_count].price);

			printf("\t\t  ���������ļ�飺");
			scanf("%s",book[book_count].brief);

			if((fp = fopen("book_info.txt","w")) == NULL)
				{
					printf("�޷��򿪸��ļ�\n");
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

			printf("\t\t  ����ɹ�!�Ƿ�������ͼ�� ��( y or n ) ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice2);

				if(choice2 != 'y' && choice2 != 'n')
						printf("\t\t  ������������,������ѡ��:");

			}while(choice2 != 'y' && choice2 != 'n');
			fflush(stdin);

			if(choice2 == 'y')
				Book_Add();

			else
			{
				printf("\t\t  �������������һ���˵�. ");
				getch();
				BookManagement();
			}
}



int Numberformat_check(char *num)     /*�ж���ı�Ÿ�ʽ�������ȷ����0������ȷ����1*/
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
/*�ļ�����ɾ��ͼ��*/

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
	printf("\n\t\t  ������Ҫɾ����ͼ������ ");
	scanf("%s",name);
	
	Load_BookInfo();
	Load_RecordInfo();
	
	if(CheckBookborrow(name) == 0)
	{
		printf("\n\t\t ����ɾ�����飬��Ϊ�ѱ����...");
		printf("\t\t �Ƿ����ɾ����(y or n ) ");
			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
						printf("\t\t  ������������,������ѡ��:");

			}while(choice != 'y' && choice != 'n');

			if(choice == 'y')
				Book_Delete();

			else
			{
				printf("\t\t  �������������һ���˵�. ");
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
					printf("�޷��򿪸��ļ�\n");
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

			printf("\t\t  ɾ���ɹ�!�Ƿ����ɾ����(y or n ) ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
						printf("\t\t  ������������,������ѡ��:");

			}while(choice != 'y' && choice != 'n');

			if(choice == 'y')
				Book_Delete();

			else
			{
				printf("\t\t  �������������һ���˵�. ");
				getch();
				BookManagement();
			}
		}
	}

	printf("\t\t  ���鲻���ڣ��Ƿ����ɾ������ͼ�飿 (y or n) ");
	do
	{
		fflush(stdin);
		scanf("%c", &choice);

		if(choice != 'y' && choice != 'n')
				printf("\t\t  ������������,������ѡ��:");

	}while(choice != 'y' && choice != 'n');

	if(choice == 'y')
		Book_Delete();

	else
	{
		printf("\t\t  �������������һ���˵�. ");
		getch();
		Book_Inquiry();
	}
}

/*�ļ������޸�ͼ����Ϣ*/
void Book_Modify()
{
	int i , j ;
	char choice;
	char name[STRSIZE];
	FILE *fp;
	
	char location[STRSIZE];
	Load_BookInfo();
	fflush(stdin);
	printf("\n\t\t  ������Ҫ�޸ĵ�ͼ������ ");
	scanf("%s",name);

	for( i = 0 ; i < book_count ; i ++)
	{

		if((strcmp(name,book[i].name)) == 0 )
		{

			printf("\t\t  ����������λ�ã�����a123����");
			scanf("%s",location);

			while(Locationexist(location))
			{
				fflush(stdin);
				printf("\t\t  �õط��Ѿ���ͼ�飬���������� ��");
				scanf("%s",location);
			}
			
			strncpy(book[i].location,location,STRSIZE);

			printf("\t\t  �������������� ��");
			scanf("%lf",&book[i].number);

			printf("\t\t  ���������ļ�� ��");
			scanf("%s",book[i].brief);

			if((fp = fopen("book_info.txt","w")) == NULL)
				{
					printf("�޷��򿪸��ļ�\n");
					exit(1);
				}

			for( j = 0 ; j < book_count; j++)
			{
				fprintf(fp,BOOK_FORMAT,book[j].number,book[j].frequency,book[j].totaltime,book[j].price,book[j].book_num,book[j].publishinghouse,book[j].name,book[j].author,book[j].date,book[j].location,book[j].brief);
				fputs("\n",fp);
			}

			fclose(fp);

			printf("\t\t  �޸ĳɹ�!�Ƿ�����޸ģ�( y or n ) ");

			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
						printf("\t\t  ������������,������ѡ��:");

			}while(choice != 'y' && choice != 'n');

			if(choice == 'y')
				Book_Modify();

			else
			{
				printf("\t\t  �������������һ���˵�. ");
				getch();
				BookManagement();
			}
		}


	}
		printf("\t\t  δ�ҵ����飬�Ƿ�����޸������鼮��( y or n ) ");

		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
					printf("\t\t  ������������,������ѡ��:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
			Book_Modify();

		else
		{
			printf("\t\t  �������������һ���˵�. ");
			getch();
			BookManagement();
		}

}


/******************�޸Ĺ���Ա��Ϣ***************************/
void AdminInfo_Modify()     /*ѡ��*/
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
		    printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		    printf("\t�U                         ����Ա��Ϣ�޸�                         �U\n");
		    printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
		    printf("\t�U\t\t1  - �޸�����                                     �U\n");
		    printf("\t�U\t\t2  - �޸�����                                     �U\n");
		    printf("\t�U\t\t3  - ������һ���˵�                               �U\n");
		    printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
		    printf("\t\t  ���������ѡ��(1-3):");

		    do{
		    		fflush(stdin);
		    		scanf("%d", &choice);

		    		if(choice < 1 || choice > 3)
		    		printf("\t\t  ������������,����������:");

		    }while(choice < 1 || choice > 3);

		    fflush(stdin);

		    return choice;
}
int Admin_IdCheck(char *id)
{
	int i;  /*ѭ������*/

	for(i = 0 ; i < admin_count ; i++)
	{
		if(strcmp(id,admin[i].num) == 0)
		{
			admin_current = i ;
			return EXIT_SUCCESS ;
		}      /*��ʾ���ڸ��˺�*/
	}

	return EXIT_FAILURE;
}

int Admin_PasswdCheck(char *passwd) /*1��ʾ�������*/
{

	if(strcmp(passwd,admin[admin_current].password) != 0)
	{
		return EXIT_FAILURE ;  /*��ʾ�������*/
	}
	return EXIT_SUCCESS;
}



void AdminInfo_Modify_Password()
{
	FILE *fp;
	int i;

	if((fp = fopen("admin_info.txt","w")) == NULL)
		{
			printf("�޷��򿪸��ļ�\n");
			exit(1);
		}

	printf("\t\t  �������µ����룺");
	scanf("%s",admin[admin_current].password);


	for(i = 0 ; i < admin_count; i++)
	{
		fprintf(fp,ADM_FORMAT,ADM_INPUT);
		fputs("\n",fp);
	}

	printf("\t\t  ����ɹ��������������");
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
			printf("�޷��򿪸��ļ�\n");
			exit(1);
		}

	printf("\t\t  �������µ����䣺");
	scanf("%s",admin[admin_current].email);

	while(EmailFormat_check(admin[admin_current].email))
	{
			fflush(stdin);
			printf("\t\t  ��ʽ����������*****@**.***��ʽ�� ");
			scanf("%s",admin[admin_current].email);
	}

	for(i = 0 ; i < admin_count; i++)
	{
		fprintf(fp,ADM_FORMAT,ADM_INPUT);
		fputs("\n",fp);
	}

	printf("\t\t  ����ɹ��������������");
	getch();

	fclose(fp);

	AdminInfo_Modify();
}


/******************************ѧ���˺���***************************************/


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
	    printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	    printf("\t�U             ��ӭ����ͼ��ݽ���ϵͳ ��ѧ���ˣ�                �U\n");
	    printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
	    printf("\t�U\t\t1 -  ͼ�����                                   �U\n");
	    printf("\t�U\t\t2 -  ͼ��黹                                   �U\n");
	    printf("\t�U\t\t3 -  ͼ������                                   �U\n");
	    printf("\t�U\t\t4 -  ͼ���ѯ                                   �U\n");
	    printf("\t�U\t\t5 -  ���Ľ����ѯ                               �U\n");
	    printf("\t�U\t\t6 -  ������Ϣɾ��                               �U\n");
	    printf("\t�U\t\t7 -  ������Ϣ����                               �U\n");
	    printf("\t�U\t\t8 -  ע��                                       �U\n");
	    printf("\t�U\t\t9 -  �˳�                                       �U\n");
	    printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	    printf("\n\t\t  ���������ѡ��(1-9):");

	    do{
	    		fflush(stdin);
	    		scanf("%d", &choice);

	    		if(choice < 1 || choice > 9)
	    		printf("\t\t  ������������,����������:");

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
		printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("\t�U             ��ӭ����ͼ��ݽ���ϵͳ ��ѧ���ˣ�                    �U\n");
		printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
		printf("\t\t  ����������ѧ�ţ� 10 λ���֣���");

		scanf("%s",id);

		while(IdformatJudge(id) || Stu_IdCheck(id))
		{
			fflush(stdin);
			printf("\t\t  ѧ�Ŵ�����������ȷѧ�ţ�");
			scanf("%s",id);
		}

		printf("\t\t  �������������� ��");

		scanf("%s",passwd);

		while(Stu_PasswdCheck(passwd))
		{
				fflush(stdin);
				printf("\t\t  ���������������ȷ���룺");
				scanf("%s",passwd);
		}
		printf("\n\t\t  ��½�ɹ��������������.");
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
	int i;  /*ѭ������*/

	for(i = 0 ; i < student_count ; i++)
	{
		if(strcmp(id,student[i].num) == 0)
		{
			student_current = i ;
			return EXIT_SUCCESS ;
		}						/*��ʾ���ڸ��˺�*/
	}

	return EXIT_FAILURE;
}

int Stu_PasswdCheck(char *passwd)
{

	if(strcmp(passwd,student[student_current].password) != 0)
	{
		return EXIT_FAILURE ;  /*��ʾ�������*/
	}
	return EXIT_SUCCESS;
}

/***************����ѧ������**************/

void Show_Freeze()
{
		int choice;

		fflush(stdin);
	 	system("cls");
	    printf("\n\n\n\n\n");
	    printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	    printf("\t�U             ��ӭ����ͼ��ݽ���ϵͳ ������ѧ���ˣ�            �U\n");
	    printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
	    printf("\t�U\t\t1 -  ͼ��黹                                   �U\n");
	    printf("\t�U\t\t2 -  ���Ľ����ѯ                               �U\n");
	    printf("\t�U\t\t3 -  ע��                                       �U\n");
	    printf("\t�U\t\t4 -  �˳�                                       �U\n");
	    printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	    printf("\n\t\t  ����!�������ڶ���״̬! �뼰ʱ�黹ͼ�鲢֪ͨ����Ա�ⶳ!!");
		printf("\n\t\t  ���������ѡ��(1-4):");

	    do{
	    		fflush(stdin);
	    		scanf("%d", &choice);

	    		if(choice < 1 || choice > 4)
	    		printf("\t\t  ������������,����������:");

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
/**********************��������ͼ�����**********************/

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

	for(i = 0; i < record_count; i++)/*��forѭ�������жϽ������Ƿ�ﵽ����*/
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
		printf("\n\t\t  �涨���������ﵽ����ʱ�����ٽ��ġ���黹ͼ��֮���ٽ��н���. ");
		printf("\n\t\t  �������������һ���˵�.. ");
		getch();

		Show_Student();
	}

		printf("\n\t\t  ��������Ҫ���ĵ�����: ");

		gets(book_name);
		fflush(stdin);

		for(i = 0 ; i < book_count ; i++)		/*�������Ƿ��ڿ����*/
		{
			if(strcmp(book_name,book[i].name) == 0)
			{
				j=0;

				for(k = 0;k < record_count ; k++)			/*����ж����˽��ĸ���*/
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
					printf("\n\t\t  ��ͼ���Ѿ�ȫ�������.  ");
					printf("\n\t\t  �Ƿ������������ͼ�飿 ( y or n ) : ");
					do
					{
						fflush(stdin);
						scanf("%c", &choice);

						if(choice != 'y' && choice != 'n')
							   printf("\t\t  ������������,������ѡ��:");

					}while(choice != 'y' && choice != 'n');

					if(choice == 'y')
					{
						printf("\t\t  �����������.  ");
						getch();
						Book_Borrow();
					}

					if(choice == 'n')
					{
						printf("\t\t  �������������һ���˵�.  ");
						getch();
						Show_Student();
					}
				}

				else
				{
					for(i = 0 ; i < record_count ; i++ )/*����ѧ���Ƿ��Ѿ������Ȿ��*/
					{
						if(strcmp(book_name,record[i].book_name) == 0)
						{
							if( strcmp(student[student_current].num,record[i].student_num) == 0)
							{
								if(record[i].back == 0)
								{
									printf("\n\t\t  ���ѽ����˸��飬�����ٽ�! ");
									printf("\n\t\t  �Ƿ������������ͼ�飿 ( y or n ) : ");
									do
									{
										fflush(stdin);
										scanf("%c", &choice);

										if(choice != 'y' && choice != 'n')
											   printf("\t\t  ������������,������ѡ��:");

									}while(choice != 'y' && choice != 'n');


									if(choice == 'y')
									{
										printf("\t\t  �����������.  ");
										getch();
										Book_Borrow();
									}

									if(choice == 'n')
									{
										printf("\t\t  �������������һ���˵�.  ");
										getch();
										Show_Student();
									}
								}
							}
						}
					}

					if((fp = fopen("record_info.txt","w")) == NULL)
						{
							printf("�޷��򿪸��ļ�\n");
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

					printf("\n\t\t  ��ϲ�㣬���ĳɹ� ! ");

					printf("\n\t\t  �Ƿ�������ģ� ( y or n ) : ");
					do
					{
						fflush(stdin);
						scanf("%c", &choice);

						if(choice != 'y' && choice != 'n')
							   printf("\t\t  ������������,������ѡ��:");

					}while(choice != 'y' && choice != 'n');

					fflush(stdin);

					if(choice == 'y')
					{
					
						printf("\t\t  �����������.  ");
						getch();
						Book_Borrow();
					}

					if(choice == 'n')
					{
						printf("\t\t  �������������һ���˵�.  ");
						getch();
						Show_Student();
					}
				}
			}
		}

		printf("\n\t\t  ��û���ҵ�����.  ");
		printf("\n\t\t  �Ƿ�������������鼮�� ( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  ������������,������ѡ��:");

		}while(choice != 'y' && choice != 'n');
		fflush(stdin);

		if(choice == 'y')
		{
			printf("\t\t  �����������.  ");
			getch();
			Book_Borrow();
		}

		if(choice == 'n')
		{
			printf("\t\t  �������������һ���˵�.  ");
			getch();
			Show_Student();
		}
}

/***********�������ܲ������**************/
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

/**************************��������ͼ��黹***************************/

void Book_Revert()
{
	char choice;
	int n;
	int i , j;
	FILE *fp;

	double keephour; /****��¼����ʱ��*****/

	char book_name[STRSIZE];

    time_t nowtime;
    struct tm *timeinfo;
	
	Load_RecordInfo();
	Load_BookInfo();
	fflush(stdin);
	printf("\n\t\t  ������Ҫ�黹������: ");
	gets(book_name);
	
	n = CheckIfborrow(book_name);

	if( n == 0 )
	{
		printf("\t\t  �㻹û�н��ĸ��飡���Ƚ��ģ� ");

		printf("\n\t\t  �Ƿ�������飿 ( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  ������������,������ѡ��:");

		}while(choice != 'y' && choice != 'n');


		if(choice == 'y')
		{
			printf("\t\t  �����������.  ");
			getch();
			Book_Revert();
		}

		if(choice == 'n')
		{
			printf("\t\t  �������������һ���˵�.  ");
			getch();
			Show_Student();
		}
	}

	else
	{
		printf("\t\t  �黹�ɹ������Ե�Ƭ�̣�ϵͳ����¼��Ĺ黹��Ϊ. ");

		if((fp = fopen("record_info.txt","w")) == NULL)
			{
				printf("�޷��򿪸��ļ�\n");
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
				printf("�޷��򿪸��ļ�\n");
				exit(1);
			}

		for( j = 0 ; j < book_count ; j++)
		{
			fprintf(fp,BOOK_FORMAT,book[j].number,book[j].frequency,book[j].totaltime,book[j].price,book[j].book_num,book[j].publishinghouse,book[j].name,book[j].author,book[j].date,book[j].location,book[j].brief);
			fputs("\n",fp);
		}
		fclose(fp);

		printf("\n\t\t  ��¼��ϣ�");

		printf("\n\t\t  �Ƿ�������飿 ( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  ������������,������ѡ��: ");

		}while(choice != 'y' && choice != 'n');


		if(choice == 'y')
		{
			printf("\t\t  �����������.  ");
			getch();
			Book_Revert();
		}

		if(choice == 'n')
		{
			printf("\t\t  �������������һ���˵�.  ");
			getch();
			Show_Student();

		}
	}
}

/*�����жϸ����Ƿ��ѱ����˽���,�����ķ��� 1+i��δ�����ķ��� 0 */

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


/*******************��������ͼ������****************************/

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

	printf("\n\t\t  ������Ҫ���������: ");
	gets(book_name);

	fflush(stdin);

	n = JudgeStuBorrow(book_name);

	if(n == 0)
	{
		printf("\t\t  �㻹û�н��ĸ�����Ѿ��黹���� .. ");

		printf("\n\t\t  �Ƿ�������������鼮�� ( y or n ) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  ������������,������ѡ��:");

		}while(choice != 'y' && choice != 'n');


		if(choice == 'y')
		{
			printf("\t\t  �����������.  ");
			getch();
			Book_Renew();
		}

		if(choice == 'n')
		{
			printf("\t\t  �������������һ���˵�.  ");
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

		if(totaltime < 2592000)   /* 30�� * 24Сʱ/�� * 60��/Сʱ * 60��/�� = 2592000��*/
		{
			printf("\t\t  ��δ���黹��֮�󣬲�������.. ");

			printf("\n\t\t  �Ƿ�������������鼮�� ( y or n ) : ");
			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
					   printf("\t\t  ������������,������ѡ��:");

			}while(choice != 'y' && choice != 'n');


			if(choice == 'y')
			{
				printf("\t\t  �����������.  ");
				getch();
				Book_Renew();
			}

			if(choice == 'n')
			{
				printf("\t\t  �����������.   ");
				getch();
				Show_Student();

			}

		}

		if(JudgeIftwice(book_name) >= 3) /*����+ ���� ��������*/
		{
			printf("\t\t  ��������ѵ������޷���������.. ");

			printf("\n\t\t  �Ƿ�������������鼮�� ( y or n ) : ");
			do
			{
				fflush(stdin);
				scanf("%c", &choice);

				if(choice != 'y' && choice != 'n')
					   printf("\t\t  ������������,������ѡ��:");

			}while(choice != 'y' && choice != 'n');

			if(choice == 'y')
			{
				printf("\t\t  �����������.  ");
				getch();
				Book_Renew();
			}

			if(choice == 'n')
			{
				printf("\t\t  �����������.  ");
				getch();
				Show_Student();

			}

		}

		if((fp = fopen("record_info.txt","w")) == NULL)
			{
				printf("�޷��򿪸��ļ�\n");
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
				printf("�޷��򿪸��ļ�\n");
				exit(1);
			}

		for( i = 0 ; i < book_count ; i++)
		{
			fprintf(fp,BOOK_FORMAT,book[i].number,book[i].frequency,book[i].totaltime,book[i].price,book[i].book_num,book[i].publishinghouse,book[i].name,book[i].author,book[i].date,book[i].location,book[i].brief);
			fputs("\n",fp);
		}
		fclose(fp);

		printf("\n\t\t  ����ɹ���   ");
		printf("\n\t\t  �Ƿ�������������鼮�� ( y or n) : ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  ������������,������ѡ��:");

		}while(choice != 'y' && choice != 'n');


		if(choice == 'y')
		{
			printf("\t\t  �����������.  ");
			getch();
			Book_Renew();
		}

		if(choice == 'n')
		{
			printf("\t\t  �����������.  ");
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

/*�ж��Ƿ����賬������*/
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

/*������ѯ���Ľ��*/

void Record_Check()
{
	int i;
	int n = 0 ;

	Load_RecordInfo();
	Load_BookInfo();

	printf("\n\n��ע ������һ�����������������ţ����Ļ�����(1��ʾ���裬0��ʾ����)����ʱ�䣬�黹ʱ�� ��\n");

	for(i = 0 ; i < record_count; i++)
	{
		if( strcmp(student[student_current].num,record[i].student_num) == 0 )
		{
			if(record[i].back == 0)
			{
				printf(" %-20s\t%s\t%d\t%4d��%2d��%2d��%2dʱ\t��\n",record[i].book_name,record[i].book_num,record[i].b_r,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour);
				n++;
			}
			if(record[i].back == 1)
			{
				printf(" %-20s\t%s\t%d\t%4d��%2d��%2d��%2dʱ\t%4d��%2d��%2d��%2dʱ\n",record[i].book_name,record[i].book_num,record[i].b_r,record[i].borrowtime.year,record[i].borrowtime.month,record[i].borrowtime.day,record[i].borrowtime.hour,record[i].backtime.year,record[i].backtime.month,record[i].backtime.day,record[i].backtime.hour);
				n++;
			}
		}
	}

	if( n == 0 )
	{
		printf("\n\n ��û�����Ľ��ļ�¼���Ͻ�����һ���ɣ� ");
		printf("\n �����������. ");
		getch();
		Show_Student();
	}

	else
	{
		printf("\n\n �������������Ĺ������ڽ��ĵ�ͼ��. ");
		printf("\n �������������һ��. ");
		getch();
		Show_Student();
	}

}


/****ɾ��������Ϣ****/

void Record_Delete()
{
	int i , j = 0;
	int n = 0;
	FILE *fp;
	char book_name[STRSIZE];
	char choice;

	Load_RecordInfo();

	printf("\n\t\t  ������Ҫɾ����¼ͼ������֣�  ");

	scanf("%s",book_name);

	
	for( i = 0 ; i < record_count ; i++)
	{
		if((logintime < record[i].borrowtime.rawtime)  && (record[i].back == 0))
		{
			if(strcmp(book_name,record[i].book_name) == 0)
			{
				printf("\t\t  ��¼�Ѿ�ɾ��..  ");
			
				if((fp = fopen("record_info.txt","w")) == NULL)
				{
					printf("�޷��򿪸��ļ�\n");
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

				printf("\n\t\t  �Ƿ����ɾ�������鼮��¼ �� ( y or n ) : ");

				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
					   printf("\t\t  ������������,������ѡ��:");

				}while(choice != 'y' && choice != 'n');


				if(choice == 'y')
				{
					printf("\t\t  �����������.  ");
					getch();
					Record_Delete();
				}

				if(choice == 'n')
				{
					printf("\t\t  �������������һ��.  ");
					getch();
					Show_Student();
				}
			}
		}
	}

	printf("\n\t\t  δ�ҵ��ü�¼���Ƿ����ɾ�������鼮��¼ �� ( y or n ) : ");

	do
	{
		fflush(stdin);
		scanf("%c", &choice);

		if(choice != 'y' && choice != 'n')
			   printf("\t\t  ������������,������ѡ��:");

	}while(choice != 'y' && choice != 'n');


	if(choice == 'y')
	{
		printf("\t\t  �����������. ");
		getch();
		Record_Delete();
	}

	if(choice == 'n')
	{
		printf("\t\t  �������������һ��.  ");
		getch();
		Show_Student();
	}
}

/*****************��������ͼ���ѯ**************/
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
	printf("\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t�U                      ͼ���ѯ                          �U\n");
	printf("\t\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
    printf("\t\t�U\t\t1  - ����������ѯͼ��                     �U\n");
	printf("\t\t�U\t\t2  - �������߲�ѯͼ��                     �U\n");
	printf("\t\t�U\t\t3  - ���ݽ��Ĵ�����������ͼ��             �U\n");
	printf("\t\t�U\t\t4  - ���ݼ۸���������ͼ��                 �U\n");
	printf("\t\t�U\t\t5  - ������һ���˵�                       �U\n");
	printf("\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t  ���������ѡ��(1-5):");

	do
	{
		    fflush(stdin);
		    scanf("%d", &choice);

		    if(choice < 1 || choice > 5)
		    		printf("\t\t  ������������,����������:");

	}while(choice < 1 || choice > 5);

	fflush(stdin);

	return choice;
}

/******�������ܸ�������******/
void Book_Inquiry_Byauthor()
{
	char author[STRSIZE];
	int i , j = 0;
	int count[BOOKMAX];
	char choice;
	fflush(stdin);
	printf("\n\t\t  ����������:");
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
		printf("\n  ��ѯ������£�\n");

		printf(" ( ע �������г���������������ͼ���ţ����ߣ��۸񣬳����磬����ʱ�䣬ͼ�����������λ�ã�ͼ����)\n\n\n");

		j--;

		while(j >= 0 )
		{
			printf(" %-20s\t%-s\t%-s\t%-.2lfԪ\t%-s\t%-s\t%-d\t%-s\t%-s\n",book[count[j]].name,book[count[j]].book_num,book[count[j]].author,book[count[j]].price,book[count[j]].publishinghouse,book[count[j]].date,book[count[j]].number,book[count[j]].location,book[count[j]].brief);	
			j--;
		}

		printf("\n �Ƿ������ѯ( y or n ): ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
						   printf(" ������������,������ѡ��:");

				}while(choice != 'y' && choice != 'n');

				if(choice == 'y')
				{
					printf(" �����������.  ");
					getch();
					Book_Inquiry_Byauthor();
				}

				else
				{
					printf(" �������������һ��.  ");
					getch();
					Book_StuInquiry();
				}
	}

	if(j == 0)
	{
		printf("\t\t  û���ҵ���Ӧ�鼮.�Ƿ������ѯ( y or n ): ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  ������������,������ѡ��:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
		{
			printf("\t\t  �����������. ");
			getch();
			Book_Inquiry_Byauthor();
		}

		else
		{
			printf("\t\t  �������������һ��. ");
			getch();
			Book_StuInquiry();
		}
	}
}


/***********�������ܸ��ݽ��Ĵ���*****************/
void Frequency_Inordering2()   	 /*ð���㷨*/
{
	int i , j ; /* ѭ������ */
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
	printf("\n  ���Ĵ����ɶൽ�ٵ��� :");

	printf(" ��ע �������г�������������,ͼ����,���Ĵ���,���λ��,ͼ��������\n\n");
	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %-20s\t%s\t%d\t%s\t%d\n",temp[i].name,temp[i].book_num,temp[i].frequency,temp[i].location,temp[i].number);
	}

	printf("\n �������������һ���˵�.. ");
	getch();
	Book_StuInquiry();
}

/*********�������ܸ�������**********/
void Book_Inquiry_Byname2()
{
	char bookname[STRSIZE];
	int i , j = 0;
	char choice;


	printf("\t\t  ����������:");

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
		printf("  ��ѯ������£�\n\n");

		printf(" ��ע �������г�������������,ͼ����,����,�۸�,������,����ʱ��,ͼ������,���λ��,ͼ���飩\n\n");
		printf("  %-20s\t%-s\t%-s\t%-.2lfԪ\t%-s\t%-s\t%-d\t%-s\t%-s\n",book[i].name,book[i].book_num,book[i].author,book[i].price,book[i].publishinghouse,book[i].date,book[i].number,book[i].location,book[i].brief);

		printf("\n  �Ƿ������ѯ( y or n): ");
				do
				{
					fflush(stdin);
					scanf("%c", &choice);

					if(choice != 'y' && choice != 'n')
						   printf(" ������������,������ѡ��:");

				}while(choice != 'y' && choice != 'n');

				if(choice == 'y')
				{
					printf("\t\t  �����������.  ");
					getch();
					Book_Inquiry_Byname2();
				}

				else
				{
					printf(" �����������.  ");
					getch();
					Book_StuInquiry();
				}
	}

	if(j == 0)
	{
		printf("\t\t  û���ҵ���Ӧ�鼮.�Ƿ������ѯ( y or n): ");
		do
		{
			fflush(stdin);
			scanf("%c", &choice);

			if(choice != 'y' && choice != 'n')
				   printf("\t\t  ������������,������ѡ��:");

		}while(choice != 'y' && choice != 'n');

		if(choice == 'y')
		{
			printf("\t\t  �����������.  ");
			getch();
			Book_Inquiry_Byname2();
		}

		else
		{
			printf("\t\t  �������������һ��.  ");
			getch();
			Book_StuInquiry();
		}
	}
}

/*********���ݼ۸�**********/

void Price_Inordering()   	 /*ð���㷨*/
{
	int i , j ; /* ѭ������ */

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
	printf("\n �۸��ɶൽ�ٵ��� :");

	printf(" ��ע �������г��������Ǽ۸�,����,���,���Ĵ���,λ��,ͼ��������\n\n");
	for( i = 0 ; i < book_count ; i++)
	{
		printf(" %.2lfԪ\t%-20s\t%s\t%d\t%s\t%d\n",temp[i].price,temp[i].name,temp[i].book_num,temp[i].frequency,temp[i].location,temp[i].number);
	}

	printf("\n �������������һ���˵�.. ");
	getch();
	Book_StuInquiry();

}

/***********************************************************************/

void StudentInfo_Modify()     /*ѧ����Ϣ�޸�*/
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
		    printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		    printf("\t�U                         ѧ���û���Ϣ�޸�                       �U\n");
		    printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
		    printf("\t�U\t\t1  - �޸ĵ绰                                     �U\n");
		    printf("\t�U\t\t2  - �޸�����                                     �U\n");
		    printf("\t�U\t\t3  - �޸�����                                     �U\n");
		    printf("\t�U\t\t4  - ������һ���˵�                               �U\n");
		    printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
		    printf("\t\t  ���������ѡ��(1-4):");

		    do{
		    		fflush(stdin);
		    		scanf("%d", &choice);

		    		if(choice < 1 || choice > 4)
		    		printf("\t\t  ������������,����������:");

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
			printf("�޷��򿪸��ļ�\n");
			exit(1);
		}

	printf("\t\t  �������µ��ֻ����룺");
	scanf("%s",student[student_current].telnum);

	while(Telformat_check(student[student_current].telnum))
	{
			fflush(stdin);
			printf("\t\t  ��ʽ����������11λ���֣�");
			scanf("%s",student[student_current].telnum);
	}

	for(i = 0 ; i < student_count; i++)
	{
		fprintf(fp,STU_FORMAT,STU_INPUT);
		fputs("\n",fp);
	}
	fclose(fp);
	printf("\t\t  ����ɹ��������������.");
	getch();

	StudentInfo_Modify();

}

void StuInfo_Modify_Password()
{
	FILE *fp;
	int i;

	if((fp = fopen("student_info.txt","w")) == NULL)
		{
			printf("�޷��򿪸��ļ�\n");
			exit(1);
		}

	printf("\t\t  �������µ����룺");
	scanf("%s",student[student_current].password);


	for(i = 0 ; i < student_count; i++)
	{
		fprintf(fp,STU_FORMAT,STU_INPUT);
		fputs("\n",fp);
	}

	printf("\t\t  ����ɹ��������������");
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
			printf("�޷��򿪸��ļ�\n");
			exit(1);
		}

	printf("\t\t  �������µ����䣺");
	scanf("%s",student[student_current].email);

	while(EmailFormat_check(student[student_current].email) == 1)
	{
			fflush(stdin);
			printf("\t\t  ��ʽ����������*****@***.***��ʽ�� ");
			scanf("%s",student[student_current].email);
	}

	for(i = 0 ; i < student_count; i++)
	{
		fprintf(fp,STU_FORMAT,STU_INPUT);
		fputs("\n",fp);
	}

	printf("\t\t  ����ɹ��������������");
	getch();

	fclose(fp);
	
	StudentInfo_Modify();
}

int EmailFormat_check(char *email)   /***  XXXXX@XXX.XXX ��ʽ,�����ȷ����0������ȷ����1 ***/
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

int Telformat_check(char *tel)     /*�жϵ绰��ʽ�������ȷ����0������ȷ����1*/
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





#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<time.h>
using namespace std;
#ifndef SETTING
//perf作为在perf.dat中存储的唯一结构体类型，包含了学生全部的成绩信息 
//内容为学生ID、课程编号、课程名称、课程学分、课程成绩、是否重修 
struct perf
{
	int ID;
	short int sub_id;
	char course_name[16];
	short int value;
	short int score;
	short int faial_mark;
};
//GPA包含了总学分和总gpa两个量，用于函数间的传输 
struct GPA
{
	unsigned short int total_value;
	unsigned short int total_score;
};
//stu作为student.dat中存储的唯一结构体类型，包含了一个学生的全部个人信息 
//包括学生ID、年级、姓名、课程数、挂科学分 
struct  stu
{
	int ID;
	bool sex;
	short int grade;
	char stu_name[16]; 
	short int course_num;
	short int fail_sum;
};
//man作为抽象类，提供basic information
class man
{
	public:
		man();  
		virtual ~man(); 
		virtual void setname()=0;
		virtual void setID()=0;
		virtual void setsex()=0; 
		virtual void setgrade()=0; 
		friend student;
	protected:
		int ID;
		bool sex;
		short int grade;
		char stu_name[16]; 
};
//class stuinfo is to record the academic infomations
class stuinfo
{
	public:
		stuinfo();
		virtual ~stuinfo();
		virtual void check_course()=0;
		virtual void check_fail()=0;
	protected:
		short int course_num;
		short int fail_sum;
		short int degree;
};
//student is the class to combine every student's personal information
class student:public man,public stuinfo
{
	public:
		student();
		student(stu p);
		void setname();
		void setID();
		void setsex(); 
		void setgrade(); 
		void check_course();
		void check_fail();
		friend ostream& operator <<(ostream&, student &);
		friend performance;
		friend system_SPMS;
};
class performance
{
	public:
		performance();
		performance(perf p);
		~performance();
		void setcoursename();
		void setcoursevalue();
		void setcoursescore();
		void setstuid();
		void setsubid();
		friend ostream& operator <<(ostream&, student &);
		friend system_SPMS;
		friend student;
	private:
		int ID;			//ID linked with student's ID
		short int sub_id;
		char course_name[16];
		short int value;
		short int score;
		short int faial_mark;
};
//system is the class provide commands to operate all the data. Also the object of it store all the data
class system_SPMS
{
	public:
		system_SPMS();
		system_SPMS(char*stu,char*perf);
		void init();
		void set_stu_data_add(char *);		//set the file address for student information
		void set_perf_data_add(char *);		//set for performance data address
		void add_student();
		void add_performance();
		int search_stu(int);
		int search_perf(short int);
		friend student;
		friend performance;
	private:
		char * stu_address;
		char * perf_address;
		vector<student> data_stu;
		vector<performance> data_perf;
		int id_start;
};
/*--------------Unsure settings--------------------------*/
system_SPMS * temp;
/*--------------function for class student----------------*/
void student::check_course()
{
	course_num=0;
	vector<performance>::iterator i;
	for(i=(*temp).data_perf.begin();i!=(*temp).data_perf.end();i++)
	{
		if((*i).ID==ID) course_num+=(*i).value;
	}
}
void student::check_fail()
{
	fail_sum=0;
	vector<performance>::iterator i;
	for(i=(*temp).data_perf.begin();i!=(*temp).data_perf.end();i++)
	{
		if((*i).faial_mark) fail_sum+=(*i).value;
	}
	if(fail_sum>=20) degree=-1;
}
student::student(stu p)
{
	ID=p.ID;
	grade=p.grade;
	sex=p.sex;
	strcpy(stu_name,p.stu_name);
	check_course();
	check_fail();
}
void student::setname()
{
	char t[]="Please Input Student's Name:\n";
	cout<<t;
	cin>>t;
	if(strlen(t)>15) setname();
	else strcpy(stu_name,t);
}
void student::setID()
{
	char t[]="Do you want to auto init Student ID?(y/n)\n";
	cout<<t;
	cin>>t;
	if(t[0]=='y') ID=++(*temp).id_start;
	else
	{
		cout<<"Please Input Student's ID Number:";
		cin>>ID;
	}
}	
void student::setsex()
{
	cout<<"Please Choose the Student's Sex : \n 1.Male\t2.Female";
	cin>>sex;
	if(sex!=1&&sex!=0) 
	{
		cout<<"Error. Please try again";
		getchar();
		system("clear");
		setsex();
	}
	else return;
}
void student::setgrade()
{
	cout<<"Please Input the Number of the Student's Grade:\n";
	cin>>grade;
	if(grade<1||grade>4)
	{
		cout<<"Error. Please try again";
		getchar();
		system("clear");
		setgrade();
	}
	else return;
}
/*---------function for performance-----*/
performance::performance(perf t)
{
	ID=t.ID;
	sub_id=t.ID;
	score=t.score;
	faial_mark=t.faial_mark;
	value=t.value;
	strcpy(course_name,t.course_name);
}

/*---------function for system----------*/
void system_SPMS::set_stu_data_add(char *t)
{
	strcpy(stu_address,t);
}
void system_SPMS::set_perf_data_add(char *t)
{
	strcpy(perf_address,t);
}
void system_SPMS::init()
{
	temp=this;
	time_t t;
	stu t_stu;
	performance t_perf;
	t=time(NULL);
	id_start=1000*(t/31104000+1969);
	ifstream infile(stu_address,ios::binary|ios::in);
	for(;infile.eof();)
	{
		infile.read((char *)&t_stu,sizeof(stu));
		data_stu.push_back(student(t_stu));
	}
	infile.close();
	ifstream infile(perf_address,ios::binary|ios::in);
	for(;infile.eof();)
	{
		infile.read((char *)&t_perf,sizeof(perf));
		data_perf.push_back(performance(t_perf));
	}	
}
int system_SPMS::search_stu(int t)
{
	vector<student>::iterator i;
	int j,flag=-1;
	for(i=data_stu.begin(),j=0;i!=data_stu.end();i++,j++)
	{
		if((*i).ID==t) flag=j;
	}
	return flag;
}
int system_SPMS::search_perf(short int t)
{
	vector<performance>::iterator i;
	int j,flag=-1;
	for(i=data_perf.begin(),j=0;i!=data_perf.end();i++,j++)
	{
		if ((*i).sub_id==t) flag=j;
	}
	return flag;
}
#define SETTING
#endif

 

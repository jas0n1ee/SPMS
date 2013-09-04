#include<iostream>
#include<vector>
#include<cstdlib>
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
		man(){}
		virtual ~man(){}
		virtual void setname()=0;
		virtual void setID()=0;
		virtual void setsex()=0; 
		virtual void setgrade()=0; 
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
		stuinfo(){}
		virtual ~stuinfo(){}
		virtual void check_course()=0;
		virtual void check_fail()=0;
		virtual GPA GPAcalc()=0;
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
		~student(){}
		void setname();
		void setID();
		void setID_auto();
		void setsex(); 
		void setgrade(); 
		void check_course();
		void check_fail();
		void upgrade();
		GPA GPAcalc();
		stu returnstruct();
		friend ostream& operator <<(ostream&, student &);
		friend class performance;
		friend class system_SPMS;
};
class performance
{
	public:
		performance();
		performance(perf p);
		~performance(){}
		void setcoursename();
		void setcoursevalue();
		void setcoursescore();
		void setstuid();
		void setsubid();
		perf returnstruct();
		friend ostream& operator <<(ostream&, performance&);
		friend class system_SPMS;
		friend class student;
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
		system_SPMS(){}
		system_SPMS(char*stu,char*perf);
		void init();
		void set_stu_data_add(char **);		//set the file address for student information
		void set_perf_data_add(char **);		//set for performance data address
		void add_student();
		void add_performance();
		int search_stu(int);
		int search_perf(int,short int);
		void search_print_stu(int);
		void search_print_stu(char *);
		void search_print_perf(int);
		void search_print_perf(short int);
		void search_print_perf(int,short int);
		bool delete_stu(int);
		bool delete_perf(int,short int);
		void print_menu();
		void save();
		void test();
		friend class student;
		friend class performance;
		friend ostream& operator <<(ostream&, performance&);
	private:
		char ** stu_address;
		char ** perf_address;
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
	degree=0;
	vector<performance>::iterator i;
	for(i=(*temp).data_perf.begin();i!=(*temp).data_perf.end();i++)
	{
		if((*i).ID==ID&&(*i).faial_mark) fail_sum+=(*i).value;
	}
	if(fail_sum>=20) degree=-1;
	if(course_num>170) degree=1;
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
	if(t[0]=='y') setID_auto();
	else
	{
		cout<<"Please Input Student's ID Number:\n";
		cin>>ID;
		if((*temp).search_stu(ID)!=-1)
		{
			cout<<"Error:ID already exist\n";
			getchar();
			setID();
		}
	}
}	
void student::setID_auto()
{
	if((*temp).search_stu((*temp).id_start)!=-1) 
	{
		(*temp).id_start++;
		setID_auto();
	}
	else ID=(*temp).id_start;
}
void student::setsex()
{
	cout<<"Please Choose the Student's Sex : \n0.Male\t1.Female\n";
	cin>>sex;
	if(sex!=1&&sex!=0) 
	{
		cout<<"Error. Please try again\n";
		getchar();
		system("cls");
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
		cout<<"Error. Please try again\n";
		getchar();
		system("cls");
		setgrade();
	}
	else return;
}
student::student()
{
	setname();
	setID();
	setsex();
	setgrade();
	check_course();
	check_fail();
}
ostream& operator<<(ostream&,student& t)
{
	cout<<"Name:\t"<<t.stu_name<<"\nID:\t"<<t.ID;
	switch(t.sex)
	{
	case 0:
		cout<<"\nSex:\tMale";
		break;
	default:
		cout<<"\nSex:\tFemale";
	}
	cout<<"\nGrade:\t"<<t.grade<<"\nTotal Credit:\t"<<t.course_num;
	switch (t.degree)
	{
	case 1:
		cout<<"\nStatus:\tGraduated\n\n";
		break;
	case 0:
		cout<<"\nStatus:\tUndergraduate\n\n";
		break;
	default:
		cout<<"\nStatus:\tDrop out\n\n";
		break;
	}
	return cout;
}
stu student::returnstruct()
{
	stu t;
	t.ID=ID;
	t.sex=sex;
	t.grade=grade;
	t.fail_sum=fail_sum;
	t.course_num=course_num;
	strcpy(t.stu_name,stu_name);
	return t;
}
void student::upgrade()
{
	if(degree==-1) return;
	grade++;
	if(grade>5&&course_num<170) 
	{
		grade--;
		degree=-1;
	}
}
GPA student::GPAcalc()
{
	GPA t={0,0};
	vector<performance>::iterator i;
	for(i=(*temp).data_perf.begin();i!=(*temp).data_perf.end();i++)
	{
		if((*i).ID==ID)
		{
			t.total_value+=(*i).value;
			t.total_score+=(*i).score*(*i).value;
		}
	}
	return t;
}
/*---------function for performance-----*/
performance::performance(perf t)
{
	ID=t.ID;
	sub_id=t.sub_id;
	score=t.score;
	faial_mark=t.faial_mark;
	value=t.value;
	strcpy(course_name,t.course_name);
}
void performance::setcoursename()
{
	char t[]="Please Inpute the Course Name:\n>>";
	cout<<t;
	cin>>t;
	if(strlen(t)>15) 
	{
		cout<<"Erroe. Please Try again\n";
		getchar();
		setcoursename();
	}
	else strcpy(course_name,t);
}
void performance::setcoursescore()
{
	cout<<"Please Input Course Score:\n>>";
	cin>>score;
	if(score>100||score<0)
	{
		cout<<"Error. Try again.\n>>";
		getchar();
		setcoursescore();
	}
	if(score<60) faial_mark=1;
}
void performance::setcoursevalue()
{
	cout<<"Please Input Course Credit:\n>>";
	cin>>value;
	if(value>15||value<0) 
	{
		cout<<"Error. Try again.\n>>";
		getchar();
		setcoursevalue();
	}
}
void performance::setstuid()
{
	cout<<"Please Input Student ID:\n>>";
	cin>>ID;
	if((*temp).search_stu(ID)==-1)
	{
		cout<<"Student ID incorrect. Please Try Again.\n";
		getchar();
		setstuid();
	}
}
void performance::setsubid()
{
	cout<<"Please Input Course ID:\n>>";
	cin>>sub_id;
}
performance::performance()
{
	faial_mark=0;
	setcoursename();
	setstuid();
	setsubid();
	setcoursevalue();
	setcoursescore();
	(*temp).data_stu[(*temp).search_stu(ID)].check_course();
	(*temp).data_stu[(*temp).search_stu(ID)].check_fail();
}
ostream& operator <<(ostream&,performance &t)
{
	cout<<"Course ID:\t"<<t.sub_id<<"\nCourse Credit:\t"<<t.value<<"\nScore:\t"<<t.score<<"\nFailMark:\t";
	if(t.faial_mark) cout<<"Yes\n\n";
	else cout<<"No\n\n";
	return cout;
}
perf performance::returnstruct()
{
	perf t;
	t.ID=ID;
	t.sub_id=sub_id;
	t.score=score;
	t.value=value;
	t.faial_mark=faial_mark;
	strcpy(t.course_name,course_name);
	return t;
}
/*---------function for system----------*/
void system_SPMS::set_stu_data_add(char **t)
{
	stu_address=t;
}
void system_SPMS::set_perf_data_add(char **t)
{
	perf_address=t;
}
void system_SPMS::init()
{
	temp=this;
	time_t t;
	stu t_stu;
	perf t_perf;
	int stu_sum,perf_sum;
	t=time(NULL);
	id_start=1000*(t/31104000+1969)+1;
	ifstream infile(*stu_address,ios::binary|ios::in|ios::ate);
	stu_sum=infile.tellg()/sizeof(stu);
	infile.seekg(ios::beg);
	for(int i=0;i<stu_sum;i++)
	{
		infile.read((char *)&t_stu,sizeof(stu));
		data_stu.push_back(student(t_stu));
		cout<<i+1<<"item(s) read\n";
	}
	infile.close();
	ifstream infile2(*perf_address,ios::binary|ios::in|ios::ate);
	perf_sum=infile2.tellg()/sizeof(perf);
	infile2.seekg(ios::beg);
	for(int j=0;j<perf_sum;j++)
	{
		infile2.read((char *)&t_perf,sizeof(perf));
		data_perf.push_back(performance(t_perf));
		cout<<j+1<<"item(s) read\n";
	}	
	infile2.close();
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
int system_SPMS::search_perf(int id,short int cid)
{
	int flag=-1;
	vector<performance>::iterator i;
	int j;
	for(i=data_perf.begin(),j=0;i!=data_perf.end();i++,j++)
	{
		if((*i).ID==id&&(*i).sub_id==cid) flag=j;
	}
	return flag;
}
void system_SPMS::search_print_stu(int id)
{
	vector<student>::iterator i;
	for(i=data_stu.begin();i!=data_stu.end();i++)
		if((*i).ID==id) cout<<*i;
}
void system_SPMS::search_print_stu(char *name)
{
	vector<student>::iterator i;
	for(i=data_stu.begin();i!=data_stu.end();i++)
		if(strcmp((*i).stu_name,name)==0) cout<<*i;
}
void system_SPMS::search_print_perf(int id)
{
	vector<performance>::iterator i;
	for(i=data_perf.begin();i!=data_perf.end();i++)
		if((*i).ID==id) cout<<*i;
}
void system_SPMS::search_print_perf(short int cid)
{
	vector<performance>::iterator i;
	for(i=data_perf.begin();i!=data_perf.end();i++)
		if((*i).sub_id==cid) cout<<*i;
}
void system_SPMS::search_print_perf(int id,short int cid)
{
	vector<performance>::iterator i;
	for(i=data_perf.begin();i!=data_perf.end();i++)
		if((*i).ID==id&&(*i).sub_id==cid) cout<<*i;
}
void system_SPMS::add_student()
{
	data_stu.push_back(student());
}
void system_SPMS::add_performance()
{
	data_perf.push_back(performance());
}
bool system_SPMS::delete_stu(int t)
{
	bool flag=0;
	vector<student>::iterator i;
	for(i=data_stu.begin();i!=data_stu.end();i++)
	{
		if((*i).ID==t)
		{
			flag=1;
			cout<<*i<<"\nDeleted!\n";
			data_stu.erase(i);
			break;
		}
	}
	return flag;
}
bool system_SPMS::delete_perf(int t,short int st)
{
	bool flag=0;
	vector<performance>::iterator i;
	for(i=data_perf.begin();i!=data_perf.end();i++)
	{
		if((*i).ID==t&&(*i).sub_id==st)
		{
			flag=1;
			cout<<*i<<"\nDeleted!\n";
			data_perf.erase(i);
			break;
		}
	}
	return flag;
}
void system_SPMS::save()
{
	vector<student>::iterator i;
	vector<performance>::iterator j;
	fstream outfile(*stu_address,ios::out|ios::trunc|ios::binary);
	for(i=data_stu.begin();i!=data_stu.end();i++) outfile.write((char*)&(*i).returnstruct(),sizeof(stu));
	outfile.close();
	fstream outfile2(*perf_address,ios::out|ios::trunc|ios::binary);
	for(j=data_perf.begin();j!=data_perf.end();j++) outfile2.write((char*)&(*j).returnstruct(),sizeof(perf));
	outfile2.close();
}
void system_SPMS::print_menu()
{
	int num;
	char t[]="Enter Student Name\n>>";
	char t2[]="If you dont know the student ID and the course ID, go back to menu and search it.\nContinue?(y/n)";
	GPA g;
	vector<student>::iterator i;
	system("cls");
	cout<<"              iYr        .i;:           i       ;             :LJ     \n          iMBBBB7   JBMBBBBBBBBJ       BBB     BBB        :NBBBB1     \n        NBBBB.     .BBBBr    ZBBY     BBBB:   BBBB      jBBBB:        \n       BBB5          BBM     EBBX    BBBBBB  BBBBB     BBBM           \n      iBBBi.:::     iBB7   :BBBB    uBBiNBB,BB LBB.    BBBU :::       \n       LBBBBBBBBB:  8BBU,BBBBB:     BBB :BBBBF FBBr    :MBBBBBBBBY    \n              ZBBB  BBBBBBBr       BBBM  BBBB  UBBO           7BBB    \n            :ZBBB: .BBBL          .BBB:  BBB   LBBB         .1BBB2    \n     BBBBBBBBBBY   jBBB           BBBB    r    iBBB: EBBBBBBBBBS      \n     BBBBBBEr.     JBBB           MBBN          BBBJ GBBBBBOL.        \n";
	cout<<"\t\t\t学生成绩管理系统 V1.3\n"
		<<"\t1.Add Student\n"
		<<"\t2.Add Score\n"
		<<"\t3.Search Infomation\n"
		<<"\t4.Change Detail\n"
		<<"\t5.Special function(Caution)\n"
		<<"\t6.Exit&save\n"
		<<"\t7.Exit\n"
		<<">>";
	cin>>num;
	switch(num)
	{
		case 1:
			system("cls");
			add_student();
			print_menu();
			break;
		case 2:
			system("cls");
			add_performance();
			print_menu();
			break;
		case 3:
			cout<<"Do you want to search Student(1) or Score(2) or Go back(3)\n>>";
			cin>>num;
			switch(num)
			{
				case 1:
					cout<<"By ID(1) or by NAME(2)?\n>>";
					cin>>num;
					switch(num)
					{
						case 1:
							cout<<"Enter ID\n>>";
							cin>>num;							system("cls");
							search_print_stu(num);
							getchar();getchar();getchar();
							break;
						case 2:
							cout<<t;
							cin>>t;
							system("cls");
							search_print_stu(t);
							getchar();getchar();getchar();
							break;
						default:
							break;
					}
					break;
				case 2:
					short int cid;
					cout<<"By Student ID (1) or by Course ID(2) or Both(3)\n>>";
					cin>>num;
					switch(num)
					{
						case 1:
							cout<<"Enter Student ID\n>>";
							cin>>num;
							system("cls");
							search_print_perf(num);
							getchar();getchar();getchar();
							break;
						case 2:
							cout<<"Enter Course ID\n>>";
							cin>>cid;
							system("cls");
							search_print_perf(cid);
							getchar();getchar();getchar();
							break;
						case 3:
							cout<<"Enter Student ID\n>>";
							cin>>num;
							cout<<"Enter Course ID\n>>";
							cin>>cid;
							system("cls");
							search_print_perf(num,cid);
							getchar();getchar(); getchar();
							break;
						default:
							cout<<"Error. Try again.\n";
							break;
					}
					break;
				case 3:
					break;
				default:	
					cout<<"Error. Try again.\n";
					getchar();
					break;
			}
			print_menu();
			break;
		case 4:
			int id;
			short int subid;
			cout<<t2;
			cin>>t2;
			if(t2[0]!='y') 
			{
				print_menu();
				break;
			}
			cout<<"Do you want to change Student information(1) or Course information(2)?\n>>";
			cin>>num;
			switch(num)
			{
				case 1:
					cout<<"Enter student ID\n>>";
					cin>>id;
					if(search_stu(id)==-1) 
					{
						cout<<"ID incorretc! Go to the menu and search student information!\n";
						break;
					}
					cout<<"Whitch information you want to change?\n1.Name\n2.Sex\n3.Grade\n>>";
					cin>>num;
					switch(num)
					{
						case 1:
							data_stu[search_stu(id)].setname();
							break;
						case 2:
							data_stu[search_stu(id)].setsex();
							break;
						case 3:
							data_stu[search_stu(id)].setgrade();
							break;
						default:
							cout<<"Error! ";
							getchar();
							break;
					}
					break;
				case 2:
					cout<<"Enter Student ID\n>>";
					cin>>id;
					cout<<"Enter Course ID\n>>";
					cin>>subid;
					if(search_perf(id,subid)==-1)
					{
						cout<<"Incorrect! Go to the menu and search student information!\n";
						break;
					}
					cout<<"You can only change course score but the fail lark will remain!";
					data_perf[search_perf(id,subid)].setcoursescore();
					break;
				default:
					cout<<"Error. Try again.\n";
					getchar();
					break;
			}
			print_menu();
			break;
		case 5:
			system("cls");
			short int x;
			cout<<"Special Function\n1.Upgrade All Student\n2.Delete Student\n3.Delete Course\n4.Calculate GPA \n5.Go Back\n>>";
			cin>>num;
			switch (num)
			{
			case 1:
				for(i=data_stu.begin();i!=data_stu.end();i++) (*i).upgrade();
				break;
			case 2:
				cout<<"Enter Student ID\n>>";
				cin>>num;
				delete_stu(num);
				break;
			case 3:
				cout<<"Enter Student ID\n>>";
				cin>>num;
				cout<<"Enter Course ID\n>>";
				cin>>x;
				delete_perf(num,x);
				break;
			case 4:
				cout<<"Enter Student ID\n>>";
				cin>>num;
				if(search_stu(num)==-1)
				{
					cout<<"Student Not found!\n";
					getchar();getchar();
					break;
				}
				g=data_stu[search_stu(num)].GPAcalc();
				cout<<"\nTotal Credit:\t"<<g.total_value
					<<"\nGPA:\t"<<g.total_score/(float)g.total_value<<endl;
				break;
			case 5:
				break;
			case 6:
				for(i=data_stu.begin();i!=data_stu.end();i++) (*i).sex=1-(*i).sex;
				break;
			default:
				break;
			}
			print_menu();
			break;
		case 6:
			save();
			break;
		default:
			break;
	}
}
void system_SPMS::test()
{
	vector<student>::iterator i;
	for(i=data_stu.begin();i!=data_stu.end();i++)
		cout<<*i;
	vector<performance>::iterator j;
	for(j=data_perf.begin();j!=data_perf.end();j++)
		cout<<*j;
}
#define SETTING
#endif

 

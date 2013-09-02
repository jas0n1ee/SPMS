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
	short int sex;
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
		virtual void setname(char*)=0;
		virtual void setID(int)=0;
		virtual void setsex(short int*)=0; 
		virtual void setgrade(short int)=0; 
	protected:
		int ID;
		short int sex;
		short int grade;
		char stu_name[16]; 
};
//class stuinfo is to record the academic infomations
class stuinfo
{
	public:
		stuinfo();
		virtual ~stuinfo();
		virtual void check_course(int)=0;
		virtual void check_fail(int)=0;
	protected:
		short int course_num;
		short int fail_sum;
		short int degree;
}
//student is the class to combine every student's personal information
class student:public man,public stuinfo
{
	public:
		student();
		student(stu p);
		friend ostream& operator <<(ostream&, student &);
}
class performance
{
	public:
		performance();
		performance(perf p);
		~performance();
		friend ostream& operator< <<(ostream&, student &);
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
		system_SPMS(char*);
		void set_stu_data_add(char *);		//set the file address for student information
		void set_perf_data_add(char *);		//set for performance data address
		void add_student();
		void add_performance()
		bool search_stu(int);
		bool search_perf(short int);

	private:
		char * stu_address;
		char * perf_address;
		student * data_stu;
		performance * data_perf;
}
/*--------------function for class student----------------*/


#define SETTING
#endif

 

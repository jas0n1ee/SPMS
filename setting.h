#ifndef SETTING
//perf作为在perf.dat中存储的唯一结构体类型，包含了学生全部的成绩信息 
//内容为学生ID、课程编号、课程名称、课程学分、课程成绩、是否重修 
struct perf
{
	int ID;
	unsigned int sub_id;
	char course_name[16];
	unsigned int value;
	unsigned int score;
	bool faial_mark;
};
//GPA包含了总学分和总gpa两个量，用于函数间的传输 
struct GPA
{
	unsigned int total_value;
	unsigned int total_score;
};
//stu作为student.dat中存储的唯一结构体类型，包含了一个学生的全部个人信息 
//包括学生ID、年级、姓名、课程数、挂科学分 
struct  stu
{
	int ID;
	bool sex;
	unsigned int grade;
	char stu_name[10]; 
	unsigned int course_num;
	unsigned int fail_sum;
};
//human类作为抽象类，提供 
class human
{
	public:
		human();  
		human(stu p);
		virtual ~human(); 
		virtual void setname(char*)=0;
		virtual void setsex(bool*)=0; 
		virtual void setgrade(unsigned int)=0; 
	protected:
		int ID;
		bool sex;
		unsigned int grade;
		char stu_name[10]; 
};
class performance
{
	public:
		performance();
		performance(perf p);
		~performance();
	private:
		int ID;
		unsigned int sub_id;
		char course_name[16];
		unsigned int value;
		unsigned int score;
		bool faial_mark;
};
//graduate类作为毕业生类，将根据grade、course_num和fail_sum判断是否获得学位 
class graduate :virtual public student
{
	public:
		graduate();
		graduate(stu p);
		~graduate();
	private:
		bool degree; 
};
class 

#define SETTING
#endif

 

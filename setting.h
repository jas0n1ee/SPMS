#ifndef SETTING
//perf��Ϊ��perf.dat�д洢��Ψһ�ṹ�����ͣ�������ѧ��ȫ���ĳɼ���Ϣ 
//����Ϊѧ��ID���γ̱�š��γ����ơ��γ�ѧ�֡��γ̳ɼ����Ƿ����� 
struct perf
{
	int ID;
	unsigned int sub_id;
	char course_name[16];
	unsigned int value;
	unsigned int score;
	bool faial_mark;
};
//GPA��������ѧ�ֺ���gpa�����������ں�����Ĵ��� 
struct GPA
{
	unsigned int total_value;
	unsigned int total_score;
}
//stu��Ϊstudent.dat�д洢��Ψһ�ṹ�����ͣ�������һ��ѧ����ȫ��������Ϣ 
//����ѧ��ID���꼶���������γ������ҿ�ѧ�� 
struct  stu
{
	int ID;
	unsigned int grade;
	char stu_name[10]; 
	unsigned int course_num;
	unsigned int fail_sum;
};
//student����Ϊ�����࣬�ṩ�����ɼ���Ϣ������gpa������������ 
class student
{
	public:
		student();  
		student(stu p);
		virtual ~student(); 
		virtual void search(perf *temp)=0;
		virtual GPA cal_gpa(perf *temp)=0; 
	protected:
		int ID;
		unsigned int grade;
		char stu_name[10]; 
		unsigned int course_num;
		unsigned int fail_sum; 
}
//graduate����Ϊ��ҵ���࣬������grade��course_num��fail_sum�ж��Ƿ���ѧλ 
class graduate :virtual public student
{
	public:
		graduate();
		graduate(stu p);
		~graduate();
	private:
		bool degree; 
}

#define SETTING
#endif

 

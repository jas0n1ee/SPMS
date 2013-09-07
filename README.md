Student Performance Manage System(SPMS)
-----
#####本程序为某校OOP程设大作业。  
####版权归[jas0n1ee](mailto:i@jas0n1ee.me)所有  

-----
##程序要求
1. 类的数目不少于4个  
2. 每个类中要有各自的属性多于3个和方法多于3个  
3. 需要定义一个抽像类，采用继承方式派生这些类
4. 设计一个多重继承的派生类
5. 在程序设计中，引入多函数的多态性、运算符重载等机制。  

-----
##程序实现  
为了方便二进制文件的读写，统一用结构体进行存储于读写。    

		struct perf
		{
			int ID;
			short int sub_id;
			char course_name[16];
			short int value;
			short int score;
			short int faial_mark;
		};

与   

		struct  stu
		{
			int ID;
			bool sex;
			short int grade;
			char stu_name[16]; 
			short int course_num;
			short int fail_sum;
		};

-----

##类的设计   
抽象类 man，提供人员信息  

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

抽象类 stuinfo，提供学籍信息  

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
		
派生类 student，包含学生的全部功能  

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
				void GPAexport();
				stu returnstruct();
				friend ostream& operator <<(ostream&, student &);
				friend ofstream& operator<<(ofstream& ,student& );
				friend class performance;
				friend class system_SPMS;
		};

类performance，包含成绩的全部信息  

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
				friend ofstream& operator <<(ofstream&,performance &);
				friend class system_SPMS;
				friend class student;
			private:
				int ID;	
				short int sub_id;
				char course_name[16];
				short int value;
				short int score;
				short int faial_mark;
		};
		
类system_SPMS，封装程序所有的功能

		class system_SPMS
		{
			public:
				system_SPMS(){}
				system_SPMS(char*stu,char*perf);
				void init();
				void set_stu_data_add(char **);		
				void set_perf_data_add(char **);	
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

		
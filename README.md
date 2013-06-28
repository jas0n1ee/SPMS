Student Performance Manage System(SPMS)
-----
#####本程序为某校OOP程设大作业。  
####版权归[jas0n1ee](mailto:i@jas0n1ee.me)所有  

-----
##程序要求
1. 类的数目*不少于4个*  
2. 每个类中要有各自的属性**多于3个**和方法**多于3个**  
3. 需要定义一个*抽像类*，采用继承方式派生这些类
4. 设计一个**多重继承**的派生类
5. 在程序设计中，引入多函数的**多态性**、**运算符重载**等机制。  

-----
##程序实现
	为了方便二进制文件的读写，统一用结构体进行存储于读写。
>		struct perf
		{
			int ID;
			unsigned int sub_id;
			char course_name[16];
			unsigned int value;
			unsigned int score;
			bool faial_mark;
		}; 

与
>		struct  stu
		{
			int ID;
			unsigned int grade;
			char stu_name[10]; 
			unsigned int course_num;
			unsigned int fail_sum;
		};

-----
####未完待续...

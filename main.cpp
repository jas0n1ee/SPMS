#include"setting.h"
using namespace std;
char *stu_rout="student.dat";
char *perf_rout="perf.dat";
int main()
{
	system_SPMS system;
	system.set_stu_data_add(&stu_rout);
	system.set_perf_data_add(&perf_rout);
	system.init();
	system.print_menu();
	system.test();
	system.save();
	return 0;
}



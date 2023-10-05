#include "programa-testes.h" 

 
//dataset large

/*
input

1 AfoCastro81
2 100
3 100
4 Braga
5 19/03/2015 16/01/2016
6 Faro 14/01/2012 12/11/2013
7 100 Porto
8 F 12
9 13/10/2021 13/10/2021

*/

//void query_1(char* ID, int command, GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides){ 

int compareFile(FILE *f1, FILE *f2){ //Devolve 0 se os ficheiros forem iguais
   char c1 = getc(f1);
   char c2 = getc(f2);
   int error = 0;
   while (c1 != EOF && c2 != EOF){
      if (c1 != c2){
         return 1;
      }
      c1 = getc(f1);
      c2 = getc(f2);
   }
   return 0;
}

void test_q1(GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides){

	clock_t t1 = clock();
	query_1("AfoCastro81", 100001, t_users, t_drivers, t_rides);
	clock_t t2 = clock();
	double time = ((double) (t2-t1) / CLOCKS_PER_SEC);

	FILE* file_res_obtained = fopen("./Resultados/command100001_output.txt", "r+");
	FILE* file_res_expected = fopen("./expected_files/testRes1.txt", "r+");
	if (file_res_obtained != NULL || file_res_expected != NULL){
		int r = compareFile(file_res_obtained, file_res_expected);
		if (r==0 && time<10) printf("A query 1 produz um resultado correto em tempo útil (%f s)\n", time);
		else if (r==0 && time>=10) printf("A query 1 produz um resultado correto, porém, não o faz em tempo útil (%f s)\n", time);
		else printf("A query 1 não produz um resultado correto\n");
	}
	printf("-----------------------------------------------\n");
}

void test_q2(GHashTable* t_drivers, GHashTable* t_rides){

	clock_t t1 = clock();
	query_2("100", 100002, t_drivers, t_rides);
	clock_t t2 = clock();
	double time = ((double) (t2-t1) / CLOCKS_PER_SEC);

	FILE* file_res_obtained = fopen("./Resultados/command100002_output.txt", "r+");
	FILE* file_res_expected = fopen("./expected_files/testRes2.txt", "r+");
	if (file_res_obtained != NULL || file_res_expected != NULL){
		int r = compareFile(file_res_obtained, file_res_expected);
		if (r==0 && time<10) printf("A query 2 produz um resultado correto em tempo útil (%f s)\n", time);
		else if (r==0 && time>=10) printf("A query 2 produz um resultado correto, porém, não o faz em tempo útil (%f s)\n", time);
		else printf("A query 2 não produz um resultado correto\n");
	}
	printf("-----------------------------------------------\n");
}

void test_q3(GHashTable* t_users, GHashTable* t_rides){

	clock_t t1 = clock();
	query_3("100", 100003, t_users, t_rides);
	clock_t t2 = clock();
	double time = ((double) (t2-t1) / CLOCKS_PER_SEC);

	FILE* file_res_obtained = fopen("./Resultados/command100003_output.txt", "r+");
	FILE* file_res_expected = fopen("./expected_files/testRes3.txt", "r+");
	if (file_res_obtained != NULL || file_res_expected != NULL){
		int r = compareFile(file_res_obtained, file_res_expected);
		if (r==0 && time<10) printf("A query 3 produz um resultado correto em tempo útil (%f s)\n", time);
		else if (r==0 && time>=10) printf("A query 3 produz um resultado correto, porém, não o faz em tempo útil (%f s)\n", time);
		else printf("A query 3 não produz um resultado correto\n");
	}
	printf("-----------------------------------------------\n");
}

void test_q4(GHashTable* t_rides, GHashTable* t_drivers){

	clock_t t1 = clock();
	query_4("Braga", 100004, t_rides, t_drivers);
	clock_t t2 = clock();
	double time = ((double) (t2-t1) / CLOCKS_PER_SEC);

	FILE* file_res_obtained = fopen("./Resultados/command100004_output.txt", "r+");
	FILE* file_res_expected = fopen("./expected_files/testRes4.txt", "r+");
	if (file_res_obtained != NULL || file_res_expected != NULL){
		int r = compareFile(file_res_obtained, file_res_expected);
		if (r==0 && time<10) printf("A query 4 produz um resultado correto em tempo útil (%f s)\n", time);
		else if (r==0 && time>=10) printf("A query 4 produz um resultado correto, porém, não o faz em tempo útil (%f s)\n", time);
		else printf("A query 4 não produz um resultado correto\n");
	}
	printf("-----------------------------------------------\n");
}

void test_q5(GHashTable* t_rides, GHashTable* t_drivers){

	clock_t t1 = clock();
	query_5("19/03/2015", "16/01/2016", 100005, t_rides, t_drivers); //tenho q alterar isto
	clock_t t2 = clock();
	double time = ((double) (t2-t1) / CLOCKS_PER_SEC);

	FILE* file_res_obtained = fopen("./Resultados/command100005_output.txt", "r+");
	FILE* file_res_expected = fopen("./expected_files/testRes5.txt", "r+");
	if (file_res_obtained != NULL || file_res_expected != NULL){
		int r = compareFile(file_res_obtained, file_res_expected);
		if (r==0 && time<10) printf("A query 5 produz um resultado correto em tempo útil (%f s)\n", time);
		else if (r==0 && time>=10) printf("A query 5 produz um resultado correto, porém, não o faz em tempo útil (%f s)\n", time);
		else printf("A query 5 não produz um resultado correto\n");
	}
	printf("-----------------------------------------------\n");
}

void test_q6(GHashTable* t_rides){

	clock_t t1 = clock();
	query_6("Faro", "14/01/2012", "12/11/2013", 100006, t_rides); //tenho q alterar isto
	clock_t t2 = clock();
	double time = ((double) (t2-t1) / CLOCKS_PER_SEC);

	FILE* file_res_obtained = fopen("./Resultados/command100006_output.txt", "r+");
	FILE* file_res_expected = fopen("./expected_files/testRes6.txt", "r+");
	if (file_res_obtained != NULL || file_res_expected != NULL){
		int r = compareFile(file_res_obtained, file_res_expected);
		if (r==0 && time<10) printf("A query 6 produz um resultado correto em tempo útil (%f s)\n", time);
		else if (r==0 && time>=10) printf("A query 6 produz um resultado correto, porém, não o faz em tempo útil (%f s)\n", time);
		else printf("A query 6 não produz um resultado correto\n");
	}
	printf("-----------------------------------------------\n");
}

void test_q7(GHashTable* t_rides, GHashTable* t_drivers){

	clock_t t1 = clock();
	query_7("100", "Porto", 100007, t_rides, t_drivers); //tenho q alterar isto
	clock_t t2 = clock();
	double time = ((double) (t2-t1) / CLOCKS_PER_SEC);

	FILE* file_res_obtained = fopen("./Resultados/command100007_output.txt", "r+");
	FILE* file_res_expected = fopen("./expected_files/testRes7.txt", "r+");
	if (file_res_obtained != NULL || file_res_expected != NULL){
		int r = compareFile(file_res_obtained, file_res_expected);
		if (r==0 && time<10) printf("A query 7 produz um resultado correto em tempo útil (%f s)\n", time);
		else if (r==0 && time>=10) printf("A query 7 produz um resultado correto, porém, não o faz em tempo útil (%f s)\n", time);
		else printf("A query 7 não produz um resultado correto\n");
	}
	printf("-----------------------------------------------\n");
}

void test_q8(GHashTable* t_rides, GHashTable* t_drivers, GHashTable* t_users){

	clock_t t1 = clock();
	query_8("F", "12", 100008, t_rides, t_drivers, t_users); //tenho q alterar isto
	clock_t t2 = clock();
	double time = ((double) (t2-t1) / CLOCKS_PER_SEC);

	FILE* file_res_obtained = fopen("./Resultados/command100008_output.txt", "r+");
	FILE* file_res_expected = fopen("./expected_files/testRes8.txt", "r+");
	if (file_res_obtained != NULL || file_res_expected != NULL){
		int r = compareFile(file_res_obtained, file_res_expected);
		if (r==0 && time<10) printf("A query 8 produz um resultado correto em tempo útil (%f s)\n", time);
		else if (r==0 && time>=10) printf("A query 8 produz um resultado correto, porém, não o faz em tempo útil (%f s)\n", time);
		else printf("A query 8 não produz um resultado correto\n");
	}
	printf("-----------------------------------------------\n");
}

void test_q9(GHashTable* t_rides){

	clock_t t1 = clock();
	query_9("13/10/2015", "17/10/2015", 100009, t_rides); 
	clock_t t2 = clock();
	double time = ((double) (t2-t1) / CLOCKS_PER_SEC);

	FILE* file_res_obtained = fopen("./Resultados/command100009_output.txt", "r+");
	FILE* file_res_expected = fopen("./expected_files/testRes9.txt", "r+");
	if (file_res_obtained != NULL || file_res_expected != NULL){
		int r = compareFile(file_res_obtained, file_res_expected);
		if (r==0 && time<10) printf("A query 9 produz um resultado correto em tempo útil (%f s)\n", time);
		else if (r==0 && time>=10) printf("A query 9 produz um resultado correto, porém, não o faz em tempo útil (%f s)\n", time);
		else printf("A query 9 não produz um resultado correto\n");
	}
	printf("-----------------------------------------------\n");
}


void teste_queries(GHashTable* t_users, GHashTable* t_drivers, GHashTable* t_rides){
	printf("------------------------ TESTES -----------------------\n");
	test_q1(t_users, t_drivers, t_rides);
	test_q2(t_drivers, t_rides);
	test_q3(t_users, t_rides);
	test_q4(t_rides, t_drivers);
	test_q5(t_rides, t_drivers);
	test_q6(t_rides);
	test_q7(t_rides, t_drivers);
	test_q8(t_rides, t_drivers, t_users);
	test_q9(t_rides);
}

int main(int argc, char **argv){

	struct rusage r_usage1;
	getrusage(RUSAGE_SELF,&r_usage1);

	char* path_csv = argv[1];
	char* path_file_input = argv[2];

	char* open_input = (argv[2]);
	FILE* file_input = fopen(open_input, "r");

	GHashTable* t_users = g_hash_table_new_full(g_str_hash, g_str_equal, free_key,free_user);
   t_users = catalogoUsers(argv, t_users);
	GHashTable* t_drivers = g_hash_table_new_full(g_str_hash, g_str_equal, free_key,free_driver);
   t_drivers = catalogoDrivers(argv, t_drivers);
   GHashTable* t_rides = g_hash_table_new_full(g_str_hash, g_str_equal, free_key,free_ride);
   t_rides = catalogoRides(argv, t_rides);

	teste_queries(t_users, t_drivers, t_rides);

	fclose(file_input);

   g_hash_table_destroy(t_users);
   g_hash_table_destroy(t_drivers);
   g_hash_table_destroy(t_rides);

   struct rusage r_usage2;
  	getrusage(RUSAGE_SELF,&r_usage2);
  	printf("Memória usada: %ld megabytes\n",(r_usage2.ru_maxrss - r_usage1.ru_maxrss)/1000);
  	printf("-----------------------------------------------\n");
	
	return 0;
}

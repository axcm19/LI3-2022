#include "programa-principal.h" 
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <glib.h>
#include <sys/stat.h>
#include <sys/types.h>


typedef void* gpointer;
typedef const void* gconstpointer;

/*
----------------------------------------------------------------------------------------------------------
"print_MENU" ---> função sem argumentos que imprime um menu para interação com o utilizador
----------------------------------------------------------------------------------------------------------
*/

void print_MENU(){
    printf("-------------------------------------------------------------------------\n");
    printf("CSV MANAGER - V.1\n");
    printf("\n");
    printf("Premir 1 - Imprimir hashtable de users (APENAS PARA TESTES!)\n");
    printf("Premir 2 - Imprimir hashtable de drivers (APENAS PARA TESTES!)\n");
    printf("Premir 3 - Imprimir hashtable de rides (APENAS PARA TESTES!)\n");
    printf("Premir 4 - Modo interativo\n");
    printf("\n");
    printf("Premir 0 - Fechar programa\n");
    printf("-------------------------------------------------------------------------\n");
}

/*
----------------------------------------------------------------------------------------------------------
"print_MENU_INTERATIVO" ---> função sem argumentos que imprime um menu para interação com o utilizador
----------------------------------------------------------------------------------------------------------
*/

void print_MENU_INTERATIVO(){
    printf("-------------------------------------------------------------------------\n");
    printf("MODO INTERATIVO\n");
    printf("\n");
    printf("Premir 1 - Executar query 1\n");
    printf("Premir 2 - Executar query 2\n");
    printf("Premir 3 - Executar query 3\n");
    printf("Premir 4 - Executar query 4\n");
    printf("Premir 5 - Executar query 5\n");
    printf("Premir 6 - Executar query 6\n");
    printf("Premir 7 - Executar query 7\n");
    printf("Premir 8 - Executar query 8\n");
    printf("Premir 9 - Executar query 9\n");
    printf("\n");
    printf("Premir 0 - Regressar\n");
    printf("-------------------------------------------------------------------------\n");
}

/*
----------------------------------------------------------------------------------------------------------
"print_MENU_BATCH" ---> função sem argumentos que imprime um menu para o modo batch da aplicação
----------------------------------------------------------------------------------------------------------
*/

void print_MENU_BATCH(){
    printf("MODO BATCH\n");
    printf("\n");
    printf("...Lendo ficheiro com os inputs\n");
    printf("\n");
    printf("Criados ficheiros 'command#_OUTPUT.txt' na pasta Resultados\n");
    printf("-------------------------------------------------------------------------\n");
}

/*
----------------------------------------------------------------------------------------------------------
"main" ---> função main, não precisa de explicações
----------------------------------------------------------------------------------------------------------
*/

int main(int argc, char **argv) {

	int result = mkdir("./Resultados", 0777);

	

	//------- ESTA SECÇÃO A COMENTÁRIO CORRESPONDE AO MODO DE INTERAÇÃO COM O UTILIZADOR A IMPLEMENTAR NO FUTURO -------

    if(argc == 1){
    
        system("clear");
        // passar a informação ao programa sobre a pasta onde estão os fixheiros .CSV
        //char ficheiros_entrada[1000] = "";
        
        printf("-------------------------------------------------------------------------\n");
        printf("CSV MANAGER - V.1\n");
        printf("\n");
        printf("Insira o caminho da pasta com os ficheiros de entrada (.csv)\n");
        printf("-------------------------------------------------------------------------\n");

        char** argumentos = malloc(1000);
        char* ficheiros_entrada = malloc(100);
        scanf("%s", ficheiros_entrada);
        argumentos[1] = ficheiros_entrada;

        if(ficheiros_entrada != " "){
            system("clear"); 
        
            GHashTable* t_users = g_hash_table_new_full(g_str_hash, g_str_equal, free_key,free_user);
            t_users = catalogoUsers(argumentos, t_users);
            GHashTable* t_drivers = g_hash_table_new_full(g_str_hash, g_str_equal, free_key,free_driver);
            t_drivers = catalogoDrivers(argumentos, t_drivers);
            GHashTable* t_rides = g_hash_table_new_full(g_str_hash, g_str_equal, free_key,free_ride);
            t_rides = catalogoRides(argumentos, t_rides);

            print_MENU();

            int input; 
            scanf("%d", &input);
            switch (input){
                while(input != 0){

                    case 1:
                        if(input==1){
                            system("clear"); 
                            
                            GHashTable* table = g_hash_table_new(g_str_hash, g_str_equal);

                            char* open_users = malloc(sizeof(strlen(ficheiros_entrada) + strlen("users.csv") +1));
                            sprintf(open_users, "%s/users.csv", ficheiros_entrada);

                            FILE * f;
                            FILE* f_OUTPUT;

                            f = fopen(open_users, "r");
                            f_OUTPUT = fopen("./Resultados/users_OUTPUT.txt", "w");

                            table = parse_file_users(f,t_users);
                            printf("-------------------------------------------------------------------------\n");

                            g_hash_table_foreach(table, printFuncHash_User, f_OUTPUT);
                            printf("Criado ficheiro 'users_OUTPUT.txt' na pasta Resultados\n");
                            printf("Tamanho hashtable users = %d\n", g_hash_table_size(table));
                            printf("\n");
                            printf("\n");
                            printf("Premir 0 - Voltar ao menu inicial\n");

                            printf("-------------------------------------------------------------------------\n");

                            g_hash_table_destroy(table);

                            fclose(f);
                            fclose(f_OUTPUT);
                            
                            int i; 
                            scanf("%d", &i);
                            while(i == 0){
                                system("clear"); 
                                print_MENU();
                                break;
                            }

                        }

                    case 2:
                        if(input==2){
                            system("clear"); 
                            
                            GHashTable* table = g_hash_table_new(g_str_hash, g_str_equal);

                            char* open_users = malloc(sizeof(strlen(ficheiros_entrada) + strlen("drivers.csv") +1));
                            sprintf(open_users, "%s/drivers.csv", ficheiros_entrada);

                            FILE * f;
                            FILE* f_OUTPUT;

                            f = fopen(open_users, "r");
                            f_OUTPUT = fopen("./Resultados/drivers_OUTPUT.txt", "w");

                            table = parse_file_drivers(f,t_drivers);
                            printf("-------------------------------------------------------------------------\n");

                            g_hash_table_foreach(table, printFuncHash_Driver, f_OUTPUT);
                            printf("Criado ficheiro 'drivers_OUTPUT.txt' na pasta Resultados\n");
                            printf("Tamanho hashtable drivers = %d\n", g_hash_table_size(table));
                            printf("\n");
                            printf("\n");
                            printf("Premir 0 - Voltar ao menu inicial\n");

                            printf("-------------------------------------------------------------------------\n");

                            g_hash_table_destroy(table);

                            fclose(f);
                            fclose(f_OUTPUT);
                            
                            int i; 
                            scanf("%d", &i);
                            while(i == 0){
                                system("clear"); 
                                print_MENU();
                                break;
                            }

                        }

                    case 3:
                        if(input==3){
                            system("clear"); 
                            
                            GHashTable* table = g_hash_table_new(g_str_hash, g_str_equal);

                            char* open_users = malloc(sizeof(strlen(ficheiros_entrada) + strlen("rides.csv") +1));
                            sprintf(open_users, "%s/rides.csv", ficheiros_entrada);

                            FILE * f;
                            FILE* f_OUTPUT;

                            f = fopen(open_users, "r");
                            f_OUTPUT = fopen("./Resultados/rides_OUTPUT.txt", "w");

                            table = parse_file_rides(f,t_rides);
                            printf("-------------------------------------------------------------------------\n");

                            g_hash_table_foreach(table, printFuncHash_Ride, f_OUTPUT);
                            printf("Criado ficheiro 'rides_OUTPUT.txt' na pasta Resultados\n");
                            printf("Tamanho hashtable rides = %d\n", g_hash_table_size(table));
                            printf("\n");
                            printf("\n");
                            printf("Premir 0 - Voltar ao menu inicial\n");

                            printf("-------------------------------------------------------------------------\n");

                            g_hash_table_destroy(table);

                            fclose(f);
                            fclose(f_OUTPUT);
                                
                            int i; 
                            scanf("%d", &i);
                            while(i == 0){
                                system("clear"); 
                                print_MENU();
                                break;
                            }

                        }
                        
                    case 4:
                    
                        if(input==4){ 
                            system("clear"); 

                            print_MENU_INTERATIVO();

                            int query_escolhida; 
                            scanf("%d", &query_escolhida);

                            
                            while(query_escolhida != 0){

                                    if(query_escolhida == 1){
                                        system("clear"); 

                                        char* parametro_id = malloc(100);

                                        printf("-------------------------------------------------------------------------\n");
                                        printf("QUERY 1\n");
                                        printf("Listar o resumo de um perfil registado no serviço através do seu identificador\n");
                                        printf("\n");
                                        printf("Insira o parametro: <ID>\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("\n");

                                        scanf("%s", parametro_id);

                                        system("clear"); 

                                        query_1_INTERATIVA(parametro_id, t_users, t_drivers, t_rides);

                                        printf("\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("Premir 0 - Voltar ao menu anterior\n");
                                        printf("-------------------------------------------------------------------------\n");

                                        free(parametro_id);
                                    }


                                    if(query_escolhida == 2){
                                        system("clear"); 

                                        char* parametro_N = malloc(100);

                                        printf("-------------------------------------------------------------------------\n");
                                        printf("QUERY 2\n");
                                        printf("Listar os N condutores com maior avaliação média\n");
                                        printf("\n");
                                        printf("Insira o parametro: <N>\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("\n");

                                        scanf("%s", parametro_N);

                                        system("clear"); 

                                        query_2_INTERATIVA(parametro_N, t_drivers, t_rides);

                                        printf("\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("Premir 0 - Voltar ao menu anterior\n");
                                        printf("-------------------------------------------------------------------------\n");

                                        free(parametro_N);
                                    }

                                    if(query_escolhida == 3){
                                        system("clear"); 

                                        char* parametro_N = malloc(100);

                                        printf("-------------------------------------------------------------------------\n");
                                        printf("QUERY 3\n");
                                        printf("Listar os N utilizadores com maior distância viajada\n");
                                        printf("\n");
                                        printf("Insira o parametro: <N>\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("\n");

                                        scanf("%s", parametro_N);

                                        system("clear"); 

                                        query_3_INTERATIVA(parametro_N, t_users, t_rides);

                                        printf("\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("Premir 0 - Voltar ao menu anterior\n");
                                        printf("-------------------------------------------------------------------------\n");

                                        free(parametro_N);
                                    }

                                    if(query_escolhida == 4){
                                        system("clear"); 

                                        char* parametro_city = malloc(100);

                                        printf("-------------------------------------------------------------------------\n");
                                        printf("QUERY 4\n");
                                        printf("Preço médio das viagens (sem considerar gorjetas) numa determinada cidade\n");
                                        printf("\n");
                                        printf("Insira o parametro: <city>\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("\n");

                                        scanf("%s", parametro_city);

                                        system("clear"); 

                                        query_4_INTERATIVA(parametro_city, t_rides, t_drivers);

                                        printf("\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("Premir 0 - Voltar ao menu anterior\n");
                                        printf("-------------------------------------------------------------------------\n");

                                        free(parametro_city);
                                    }

                                    if(query_escolhida == 5){
                                        system("clear"); 

                                        char* parametro_data_A = malloc(100);
                                        char* parametro_data_B = malloc(100);

                                        printf("-------------------------------------------------------------------------\n");
                                        printf("QUERY 5\n");
                                        printf("Preço médio das viagens (sem considerar gorjetas) num dado intervalo de tempo\n");
                                        printf("\n");
                                        printf("Insira os parametros: <data A> <data B>\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("\n");

                                        scanf("%s", parametro_data_A);
                                        scanf("%s", parametro_data_B);

                                        system("clear"); 

                                        query_5_INTERATIVA(parametro_data_A, parametro_data_B, t_rides, t_drivers);

                                        printf("\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("Premir 0 - Voltar ao menu anterior\n");
                                        printf("-------------------------------------------------------------------------\n");

                                        free(parametro_data_A);
                                        free(parametro_data_B);
                                    }

                                    if(query_escolhida == 6){
                                        system("clear"); 

                                        char* parametro_city = malloc(100);
                                        char* parametro_data_A = malloc(100);
                                        char* parametro_data_B = malloc(100);

                                        printf("-------------------------------------------------------------------------\n");
                                        printf("QUERY 6\n");
                                        printf("Distância média percorrida, numa determinada cidade, num dado intervalo de tempo\n");
                                        printf("\n");
                                        printf("Insira os parametros: <city> <data A> <data B>\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("\n");

                                        scanf("%s", parametro_city);
                                        scanf("%s", parametro_data_A);
                                        scanf("%s", parametro_data_B);

                                        system("clear"); 

                                        query_6_INTERATIVA(parametro_city, parametro_data_A, parametro_data_B, t_rides);

                                        printf("\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("Premir 0 - Voltar ao menu anterior\n");
                                        printf("-------------------------------------------------------------------------\n");

                                        free(parametro_city);
                                        free(parametro_data_A);
                                        free(parametro_data_B);
                                    }

                                    if(query_escolhida == 7){
                                        system("clear"); 
                                        
                                        char* parametro_N = malloc(100);
                                        char* parametro_city = malloc(100);

                                        printf("-------------------------------------------------------------------------\n");
                                        printf("QUERY 7\n");
                                        printf("Top N condutores numa determinada cidade, ordenado pela avaliação média do condutor\n");
                                        printf("\n");
                                        printf("Insira os parametros: <N> <city>\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("\n");

                                        scanf("%s", parametro_N);
                                        scanf("%s", parametro_city);

                                        system("clear"); 

                                        query_7_INTERATIVA(parametro_N, parametro_city, t_rides, t_drivers);

                                        printf("\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("Premir 0 - Voltar ao menu anterior\n");
                                        printf("-------------------------------------------------------------------------\n");

                                        free(parametro_N);
                                        free(parametro_city);
                                    }

                                    if(query_escolhida == 8){
                                        system("clear"); 
                                        
                                        char* parametro_gender = malloc(100);
                                        char* parametro_X = malloc(100);

                                        printf("-------------------------------------------------------------------------\n");
                                        printf("QUERY 8\n");
                                        printf("Listar todas as viagens nas quais o utilizador e o condutor são do género passado como parâmetro, e têm perfis com X ou mais anos\n");
                                        printf("\n");
                                        printf("Insira os parametros: <gender> <X>\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("\n");

                                        scanf("%s", parametro_gender);
                                        scanf("%s", parametro_X);

                                        system("clear"); 

                                        query_8_INTERATIVA(parametro_gender, parametro_X, t_rides, t_drivers, t_users);

                                        printf("\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("Premir 0 - Voltar ao menu anterior\n");
                                        printf("-------------------------------------------------------------------------\n");

                                        free(parametro_gender);
                                        free(parametro_X);
                                    }

                                    if(query_escolhida == 9){
                                        system("clear"); 
                                        
                                        char* parametro_data_A = malloc(100);
                                        char* parametro_data_B = malloc(100);

                                        printf("-------------------------------------------------------------------------\n");
                                        printf("QUERY 9\n");
                                        printf("Listar as viagens nas quais o passageiro deu gorjeta, no intervalo de tempo (data A, data B), ordenadas por ordem de distância percorrida (em ordem decrescente)\n");
                                        printf("\n");
                                        printf("Insira os parametros: <data A> <data B>\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("\n");

                                        scanf("%s", parametro_data_A);
                                        scanf("%s", parametro_data_B);

                                        system("clear"); 

                                        query_9_INTERATIVA(parametro_data_A, parametro_data_B, t_rides);

                                        printf("\n");
                                        printf("-------------------------------------------------------------------------\n");
                                        printf("Premir 0 - Voltar ao menu anterior\n");
                                        printf("-------------------------------------------------------------------------\n");

                                        free(parametro_data_A);
                                        free(parametro_data_B);
                                    }


                                    scanf("%d", &query_escolhida);
                                }
                            

                            int i;
                            scanf("%d", &i); 
                            while(i == 0){
                                system("clear"); 
                                print_MENU();
                                break;
                            }
                        }
                    
                    default:
                        system("clear"); 
                        print_MENU();
                        scanf("%d", &input);
                }
            }
            
            g_hash_table_destroy(t_users);
            g_hash_table_destroy(t_drivers);
            g_hash_table_destroy(t_rides);
        }

        else{
            printf("ERRO - Diretoria não encontrada\n");
        }

        free(argumentos);
        free(ficheiros_entrada);
        
        system("clear"); 
        return 0;

	}

    else if (argc >= 2){


		//------- MODO BATCH -------

        clock_t t1 = clock();

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
		
		parse_BATCH(file_input, t_users, t_drivers, t_rides);
		print_MENU_BATCH();
		printf("\n");
        
        g_hash_table_destroy(t_users);
        g_hash_table_destroy(t_drivers);
        g_hash_table_destroy(t_rides);

        fclose(file_input);

        clock_t t2 = clock();
        double time = ((double) (t2-t1) / CLOCKS_PER_SEC);
        printf("Queries completadas em %f segundos\n", time);

		return 0;

    } 
}   


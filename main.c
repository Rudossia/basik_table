#include "table.h"

int main() {

  Table* t = createTable();

  while(1){
  
    printf("Меню опций работы с таблицей:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1.Вставка элеметна\n2.Удаление из таблицы элемента\n3.Поиск в таблице элемента\n4.Вывод содержимого таблицы\n5.Импорт данных из текстового файла\n6.Индивидуальное задание\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  
    int choice = 0;
    printf("\nВаш выбор:");

    while(scanf("%d", &choice) != 1) {

      if (scanf("%d", &choice) == EOF) {
        if (t->ks){
          freeTable(t);
        }
        else {
          free(t);
        }
        return -1;
      }

      printf("Попробуйте еще раз\n");
      scanf("%*[^\n]");
          
    }
    
            

    switch(choice) {

      case 1:
        

        char* key = readline("Your form key:");
        char* info = readline("Your form info:");

        insert(t, key, info);

        printTable(t);
        
        free(key);
        free(info);
        break;
        

      case 2:
      
        char* del_key = readline("Your key for deleted:");
        
        delete(t, del_key);
        

        printTable(t);
        free(del_key);
        break;

      case 3:
        char* search_k = readline("Your key for search: ");

        search_info(t, search_k);

        //printTable(t);
        free(search_k);
        break;
      case 4:

        printf("\n\n");
        printTable(t);
        printf("\n\n");

      
        break;
      case 5:
        FILE* my_file = fopen("text.txt", "r");

        if (my_file == NULL){
          free(t);
          printf("free file\n");
        }
        char* keys = malloc(sizeof(char) * MAX_READ_SIZE);
        char* infos = malloc(sizeof(char) * MAX_READ_SIZE);
        
        while (fscanf(my_file, "%s %s", keys, infos) == 2) {

          insert(t, keys, infos);
          
        }

        fclose(my_file);
        free(keys);
        free(infos);

        printTable(t);      
        break;
        
       case 6:
        Table* ind_z = NULL;
         
         char* start = readline("Введите начало диапазона: ");

         char* end = readline("Введите конец диапазона: ");
         
        ind_z = my_task(t, start, end);
        printTable(ind_z);

        freeTable(ind_z);

        free(start);
        free(end);
        
         break;  
    }
    
  }
  
  


    return 0;
}

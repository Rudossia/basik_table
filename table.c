#include "table.h"

KeyType createKey(KeyType k) {
    KeyType key = strdup(k);
    if (!key) {
        fprintf(stderr, "Can\'t allocate memory!\n");
        return NULL;
    }
    return key;
}

InfoType createInfo(InfoType k) {
    InfoType key = strdup(k);
    if (!key) {
        fprintf(stderr, "Can\'t allocate memory!\n");
        return NULL;
    }
    return key;
}

KeySpace* createKeySpace(KeyType k, InfoType i) {
    KeySpace* ks = malloc(sizeof(KeySpace));
    if (!ks) {
        fprintf(stderr, "Can\'t create keyspace!\n");
        return NULL;
    }
    ks->key = createKey(k);
    if (!ks->key) {
        free(ks);
        return NULL;
    }
    ks->info = createInfo(i);
    if (!ks->info) {
        free(ks->key);
        free(ks);
        return NULL;
    }
    ks->next = NULL;
    return ks;
}

void freeKeySpace(KeySpace* ks) {
    if (ks) {
        if (ks->key) {
            free(ks->key);
        }
        if (ks->info) {
            free(ks->info);
        }
        free(ks);
    }
}

Table* createTable() {
    Table* t = malloc(sizeof(Table));
    if (!t) {
        fprintf(stderr, "\n\nCan\'t create table!\n\n");
        return NULL;
    }
    t->ks = NULL;
    return t;
}

void freeTable(Table* t) {
    if (t) {
        if (!t->ks) {
            return;
        }
        KeySpace* ptr = t->ks;
        while (ptr->next) {
            KeySpace* x = ptr;
            ptr = ptr->next;
            freeKeySpace(x);
        }
        freeKeySpace(ptr);
        free(t);
    }
}

KeySpace* insert(Table* t, KeyType k, InfoType i) {

  KeySpace* ptr = t->ks;
  KeySpace* check = t->ks;

    if (t) {
        if (!t->ks) {
            t->ks = createKeySpace(k, i);
            return t->ks;
        }
        
        while (check) {
          if (strcmp(check->key, k)== 0){
            fprintf(stderr, "\n\nFailed with key\n");
            return NULL;
          }
          check = check->next;
        }
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = createKeySpace(k, i);
        
    }
    return ptr->next;
}

void printTable(Table* t) {
  
  
    if (t) {
        if (!t->ks) {
          fprintf(stderr, "NO TABLE\n");
            return;
        }
        KeySpace* ptr = t->ks;
        printf("\n\n");
        while (ptr->next) {
            fprintf(stdout, "{%s, %s}\n", ptr->key, ptr->info);
            ptr = ptr->next;
        }
        fprintf(stdout, "{%s, %s}\n", ptr->key, ptr->info);
        printf("\n\n");
    }
    
}

void delete(Table* t, KeyType k) {
    if (t) {
        if (!t->ks) {
          fprintf(stderr, "\n\nNO table!\n\n");
            return;
        }
        if (!t->ks->next) {
            if (strcmp(t->ks->key, k) == 0) {
                freeKeySpace(t->ks);
                t->ks = NULL;
                return;
            }
        }

        KeySpace* pp = NULL;
        KeySpace* p = t->ks;
        while (p->next) {
            if (strcmp(p->key, k) == 0) {
                if (pp == NULL) {
                    t->ks = p->next;
                    freeKeySpace(p);
                    return;
                }
                else {
                    pp->next = p->next;
                    freeKeySpace(p);
                    return;
                }
            }
            pp = p;
            p = p->next;
        }
        if (strcmp(p->key, k) == 0) {
            if (pp == NULL) {
                t->ks = p->next;
                freeKeySpace(p);
                return;
            }
            else {
                pp->next = p->next;
                freeKeySpace(p);
            return;
            }
        }

      
    }
    
    printf("\n\nКлюча с такими данными не существует\n");
    
}



void search_info(Table* t, KeyType k) {
    if (t) {
        if (!t->ks) {
          fprintf(stderr, "\n\nTable not exist\n\n");    
            return;
        }
        if (!t->ks->next) {
            if (strcmp(t->ks->key, k) == 0) {
                
                printf("\ninfo: %s\n", t->ks->info);
                return;
            }
        }
        
        KeySpace* p = t->ks;
        while (p->next) {
            if (strcmp(p->key, k) == 0) {
                
                   
                 printf("\ninfo: %s\n", p->info);
                 return;
                
            }
            
            p = p->next;
        }
        if (strcmp(p->key, k) == 0) {
            
            printf("\ninfo: %s\n", p->info);
            return;
            
        }
    }

    printf("\n\nКлюча с такими данными не существует\n");
}





Table* my_task(Table* t, KeyType start, KeyType end) {
  
  Table* res = createTable();

    if (t) {
        if (!t->ks) {
          fprintf(stderr, "Table not exist\n");
          free(res);    
            return NULL;
        }
        if (!t->ks->next) {
            if (strcmp(t->ks->key, start) >= 0 && strcmp(t->ks->key, end) <= 0) {
                
                insert(res, t->ks->key, t->ks->info);
            }
        }
        
    
        KeySpace* p = t->ks;
        
        while (p->next) {
            if ((strcmp(p->key, start) >= 0 )&& (strcmp(p->key, end) <= 0))  {
                                                
                insert(res, p->key, p->info);    
                
            }            
            p = p->next;
        }

        
        if (strcmp(p->key, start) >= 0 && strcmp(p->key, end) <= 0)  {
                               
            insert(res, p->key, p->info);
           
        }
    }
  if (!res->ks) {
      printf("\n\nКлючей в таком диапазоне не существует\n");
    }

    return res;
}

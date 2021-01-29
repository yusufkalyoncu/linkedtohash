#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct cell {
    char *anahtar;//KEY
    struct cell *next;
};

struct table_node{
    int count;
    struct cell *header;
};

struct hash_tablosu{
    struct table_node *tablo_basi;//TABLE'S HEAD
    int tablo_uzunlugu;//TABLE LENGTH
    int multiplier;
};

unsigned int hash(char *s, int multiplier, int table_size){
    int i=0;
    unsigned int value =0;
    while(s[i] != '\0'){
        value=(s[i]+multiplier*value) % table_size;
        i++;
    }
    return value;
}
void print_list(struct cell *l){
    if(l!=NULL){
        printf("%s ", l->anahtar);
        print_list(l->next);
    }
    
}
void print_hash_table(struct hash_tablosu *hash_table){
    if(hash_table){
        int index;
        printf("----- HASH TABLE -----\n");
        for(index=0; index<hash_table->tablo_uzunlugu; index++){
            printf("%5d : (%2d) ",index,(hash_table->tablo_basi +index)->count);
          //  printf("%5d : (%2d) ",index,hash_table->tablo_basi[index].counter);
            print_list((hash_table->tablo_basi+index)->header);
            printf("\n");
        }
    }
    else printf("Hash Table is Empty ...\n"); 
    
}
void initialize_hash_table(struct hash_tablosu **hash_table, int multiplier, int table_size){
    int i;
    *hash_table=(struct hash_tablosu*)malloc(sizeof(struct hash_tablosu));
   if(*hash_table==NULL){
       printf(" ERROR !!!");
       exit(1);
   }    
    (*hash_table)->tablo_basi=
       (struct table_node *)malloc(table_size*sizeof(struct table_node));
    if((*hash_table)->tablo_basi==NULL){
       printf(" ERROR !!!");
       exit(1);
    }
    (*hash_table)->tablo_uzunlugu= table_size;
    (*hash_table)->multiplier= multiplier;
    
    for(i=0; i<table_size; i++){
        ((*hash_table)->tablo_basi+i)->count = 0;
        ((*hash_table)->tablo_basi+i)->header = NULL;
    }
}
struct cell* hucre_olustur(char *icerik){
    struct cell *a;
    a=(struct cell*)malloc(sizeof(struct cell));
    if(a==NULL){
        printf("ERROR !!! \n");
        exit(1);
    }
    a->anahtar=icerik;
    a->next=NULL;
    return a;
}
// ADD KEY TO LINKED LIST
void liste_sonuna_ekle(char *icerik,struct cell **liste_basi){
    struct cell* a=hucre_olustur(icerik);
    if(*liste_basi==NULL){
        a->next=*liste_basi;
        *liste_basi=a;
    }
    else {
        struct cell *x=*liste_basi;
        while(x->next!=NULL){
            x=x->next;
        }
        x->next=a;
    }
}
void liste_yaz(struct cell *liste_basi){
    while(liste_basi!=NULL){
        printf(liste_basi->anahtar);
        liste_basi=liste_basi->next;
    }
    printf("\n");
}
// LINKED LIST TO HASH TABLE WITHOUT MALLOC OPERATORS
void listeyi_hash_tablosuna_donusturme(struct hash_tablosu *htable, struct cell **liste_basi){
	if(*liste_basi==NULL){return;}
	struct cell *temp;
	while(*liste_basi!=NULL){
		int samekey = 0;
		int hash_index = hash((*liste_basi)->anahtar,htable->multiplier,htable->tablo_uzunlugu);
		struct cell *hashtravel = ((htable->tablo_basi)+hash_index)->header;
		struct cell *keytravel = ((htable->tablo_basi)+hash_index)->header;
		
		while(keytravel!=NULL){
			if(keytravel->anahtar==(*liste_basi)->anahtar){
				samekey=1;
			}keytravel=keytravel->next;	
		}
	if(samekey==0){
		if(((htable->tablo_basi)+hash_index)->header==NULL){
			temp = *liste_basi;
			*liste_basi=(*liste_basi)->next;
			temp->next=NULL;
			((htable->tablo_basi)+hash_index)->header = temp;
			((htable->tablo_basi)+hash_index)->count+=1;		
		}
		else{
		while(hashtravel->next!=NULL){
			hashtravel=hashtravel->next;	
		    }
		    temp=*liste_basi;
		    *liste_basi=(*liste_basi)->next;
		    temp->next=NULL;
		    hashtravel->next=temp;
		    ((htable->tablo_basi)+hash_index)->count+=1;
		}
	}else{
		struct cell *deleter=*liste_basi;
		*liste_basi=(*liste_basi)->next;
		free(deleter);
		samekey=0;
	}
  }
}
// END
	


int main(){
	struct hash_tablosu *hashtable=NULL;
	initialize_hash_table(&hashtable, 2, 5);
	print_hash_table(hashtable);
	struct cell *liste=NULL;
	liste_sonuna_ekle("Erzincan", &liste);
	liste_sonuna_ekle("Erzincan", &liste);
	liste_sonuna_ekle("Erzincan", &liste);
	liste_sonuna_ekle("Erzincan", &liste);
	liste_sonuna_ekle("Istanbul", &liste);
	liste_sonuna_ekle("Adana", &liste);
	liste_sonuna_ekle("Antalya", &liste);
	liste_sonuna_ekle("Yalova", &liste);
	
	listeyi_hash_tablosuna_donusturme(hashtable, &liste);
	print_hash_table(hashtable);
	

    return 0; 
} 

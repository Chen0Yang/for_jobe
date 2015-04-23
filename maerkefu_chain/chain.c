#define num_word 2
#define table_size 450
#define factor 37
#define NOWORD " "
#define true 1
#define false 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <mcheck.h>
struct elem{
    char * word;
    struct elem *next;
};
struct state{
    char *prefix[num_word];
    struct state *next;
    struct elem *pelem;
};
struct state*hash_tbl[table_size];
void build_statetbl(char *prefex[num_word],FILE* fp);
void distory();
void free_list(struct elem *pelem);
void add(char *prefex[num_word],char*buf);
struct state * in_table(char *prefex[num_word],int creat);
unsigned int hash_fun(char *prefex[num_word]);
void generate_words(int n_word){
    char *prefex[num_word];
    int i=0;
    int num_hashed;
    struct state *pstate;
    char *word="jj";
    struct elem *pelem;
    FILE * p=fopen("hehe.txt","r");
    FILE * p_result=fopen("c_result.txt","w");
    for(i=0;i<num_word;i++){
        prefex[i] = NOWORD;
    }
    build_statetbl(prefex,p);
    for(i=0;i<num_word;i++){
        prefex[i] = NOWORD;
    }
    for(i=0;i<n_word;i++){
        pstate = in_table(prefex,false);
        if(pstate){
            num_hashed=0;
            pelem=pstate->pelem;
            for(;pelem!=NULL;pelem=pelem->next){
                if(rand()%++num_hashed==0)
                    word = pelem->word;
            }
            memmove(prefex,prefex+1,sizeof(char*)*(num_word-1));
            prefex[num_word-1] = word;
        }else{
            printf("error,no state mached\n");
            break;
        }
        fprintf(p_result,"%s ",word);
        printf("i=%d",i);
    }
    fclose(p);
    fclose(p_result);
    distory();
}
void build_statetbl(char *prefex[num_word],FILE* fp){
    char buf[100];
    char fmt[10];
    int j=0;
    sprintf(fmt,"%%%ds",sizeof(buf)-1);
    while(fscanf(fp,fmt,buf)>0){
        add(prefex,strdup(buf));
        printf("j=%d",j++);
    }
}
void distory(){
    int i;
    int j;
    struct state *pstate;
    struct state *to_free;
    for(i=0;i<table_size;i++){
        if(hash_tbl[i]){
            for(pstate=hash_tbl[i],to_free=hash_tbl[i];pstate!=NULL;){
                free_list(pstate->pelem);
                pstate=pstate->next;
                for(j=0;j<num_word;j++){
                    free(to_free->prefix[j]);
                }
                free(to_free);
                to_free=pstate;
            }
        }
    }
}
void free_list(struct elem *pelem){
    struct elem *to_free=pelem;
    for(;pelem!=NULL;){
        pelem=pelem->next;
        free(to_free->word);
        free(to_free);
        to_free=pelem;
    }
}
void add(char *prefex[num_word],char*buf)
{
    if(buf==NULL){
        printf("buf is NULL\n");
        exit(0);
    }
    struct elem *pelem;
    struct state *to_add=in_table(prefex,true);

    pelem =(struct elem *)malloc(sizeof(struct elem));
    pelem->word=buf;
    pelem->next=to_add->pelem;
    to_add->pelem=pelem;
    memmove(prefex,prefex+1,sizeof(char*)*(num_word-1));
    prefex[num_word-1] = buf;
}
struct state * in_table(char *prefex[num_word],int creat){
    unsigned int hash_num=hash_fun(prefex);
    struct state *is_in=hash_tbl[hash_num];
    int i;
    for(;is_in!=NULL;is_in=is_in->next){
        for(i=0;i<num_word;i++){
            if(is_in->prefix[i]&&strcmp(is_in->prefix[i],prefex[i])==0){
            }else{
                break;
            }
        }
        if(i==num_word){
            return is_in;
        }
    }
    if(creat){
        is_in = (struct state *)malloc(sizeof(struct state));
        is_in->next = hash_tbl[hash_num];
        hash_tbl[hash_num] = is_in;
        for(i=0;i<num_word;i++){
            is_in->prefix[i]=strdup(prefex[i]);
        }
        is_in->pelem = NULL;
        return is_in;
    }
    return NULL;
}
unsigned int hash_fun(char *prefex[num_word]){
    int i ;
    char *p;
    unsigned int hash=0;
    for(i=0;i<num_word;i++){
        for(p=prefex[i];p && *p!='\0';p++){
            hash=hash*factor+*p;
        }
    }
    return hash%table_size;

}
int main(){ 
    setenv("MALLOC_TRACE", "output_file_name", 1);
    mtrace();
    generate_words(100000);
    /*FILE * p=fopen("hehe.txt","r");
    char buf[100];
    while(fscanf)*/

}

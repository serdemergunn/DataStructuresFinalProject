/*
In this project, I used circular linked list and stack structure.
I used circular linked list to keep the actual playlist.
Using the linked list in a circular structure was especially useful for the "PlaySong" command.
Thus, for example, when the "PlaySong   N" command was given while playing the song at the end of the list,
it was possible to switch from the last song to the top song. I used the stack structure to execute the
"PrintPlaylist  R" command. For this, I created a different linked list that will be used only when this command is given. */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char * val[50];
    struct node * next;
} n;
typedef struct stacknode {
    char * val[50];
    struct node * next;
} sn;
sn *top= NULL;
void ekle(n*r, char* val);
n * ekleBastan (n*r, char* val);
n * InsertSong(n*r, char* val, char secim);
n* sil(n*r, char* tasinacak);
void bastir(n*r);
n* MoveSong(n*r, char secim, char*hedef, char* tasinacak);
n* PlaySong (n*playingsong,n*root, char secim, FILE* outputfile);
n* RemoveSong (n*r, n*playingsong , char* silinecek, FILE* outputfile);
void PrintPlaylist(n*r, char secim, FILE* outputfile);
void BastanBasla(n*r, FILE* outputfile);
void push(char* song);
void pop(FILE* outputfile);
n* ReverseList(n*r);
int main()
{
    FILE *inputfile, *outputfile;
inputfile=fopen("input.txt","r");
outputfile=fopen("output.txt","w");
char *command[50];
char choice;
char *song[50];
char *songtomove [50];
char *targetsong[50];
int secim;
if(inputfile==NULL || outputfile==NULL){
    printf("Acilamadi");
}


    n * root;
    root=NULL;
    n* playingsong;
    playingsong=NULL;
while (!feof(inputfile)){
fscanf(inputfile, "%s\t", command);
if(strcmp(command,"InsertSong") == 0)
    {
    fscanf(inputfile, "%c\t%s\n", &choice, song);
    root=InsertSong(root, song, choice);
    }
else if(strcmp(command,"MoveSong") == 0)
    {
    fscanf(inputfile, "%c\t%s\t%s\n", &choice, songtomove, targetsong);
    root=MoveSong(root,choice, targetsong,songtomove);

    }
else if(strcmp(command,"RemoveSong") == 0)
    {
    fscanf(inputfile, "%s\n", song);
    root=RemoveSong(root, playingsong, song, outputfile);
    }
else if(strcmp(command,"PlaySong") == 0)
    {
    fscanf(inputfile, "%c\n",&choice);
    playingsong=PlaySong(playingsong, root, choice, outputfile);
    }
else if(strcmp(command,"PrintPlaylist") == 0){

    fscanf(inputfile, "%c\n", &choice);
    PrintPlaylist(root,choice,outputfile);
}
else if(strcmp(command,"ReversePlaylist") == 0)
    {
    root=ReverseList(root);
    }


}
fclose(inputfile);
fclose(outputfile);
    return 0;
}

void ekle(n*r, char* val){
n*sabitroot=r;
        while(r->next != sabitroot){
            r= r->next;
        }
        r->next= (n*)malloc(sizeof(n));
        r->next->next=sabitroot;
        strcpy(r->next->val, val);


}
n * ekleBastan (n*r, char* val){
n* sabitroot=r;
n* sabitroot2=r;
        n * temp= (n*)malloc(sizeof(n));
        strcpy(temp->val, val);
        temp->next=r;
        r=temp;
            while(sabitroot->next != sabitroot2){
            sabitroot= sabitroot->next;
        }
        sabitroot->next=r;
        return r;

}
n * InsertSong(n*r, char* val, char secim){
    n* temp= r;
        if(r==NULL){
        r= (n*)malloc(sizeof(n));
        r->next=r;
        strcpy(r->val, val);

        return r;
        }
        else{
                switch(secim){
                case 'H':
                    ekleBastan(r, val);
                    break;
                case 'T':
                    ekle(r,val);
                    return temp;
                    break;
                }

        }
}
n* sil(n*r, char* tasinacak){

    n*temp=r;
    n*temproot=r;

    if(strcmp(r->val,tasinacak) != 0){

        while (strcmp(r->next->val,tasinacak) != 0){
            r=r->next;

        }
        temp=r->next;
        r->next=r->next->next;
        free(temp);
        return temproot; //root degismedigi icin
    }
    else {
        if(r->next==r){
            r=NULL;
            free(temp);
            return NULL;
        }
        else{
        r=r->next;
        n*helper=r;
        while(helper->next !=temp){
           helper=helper->next;
        }
        helper->next=r;
        free(temp);

        return r;
        }
    }
}
void bastir(n*r){
      n*iter;
    iter=r;
int i=1;
    while(iter->next != r){
        printf("%d. sarki -> %s \n",i, iter->val);
        i++;
        iter=iter->next;
    }
    printf("%d. sarki -> %s \n",i, iter->val);
printf("\n Son olarak rootumuz = %s  \n\n", r->val);
}
n* MoveSong(n*r, char secim, char*hedef, char* tasinacak){
    int kontrol1=0;
    int kontrol2=0;
    n* forcontrol=r;
    while(forcontrol->next!=r){
        if(strcmp(forcontrol->val,hedef) == 0)
            kontrol1=1;
        else if (strcmp(forcontrol->val,tasinacak) == 0)
            kontrol2=1;
        forcontrol=forcontrol->next;
    }
            if(strcmp(forcontrol->val,hedef) == 0)
            kontrol1=1;
            else if (strcmp(forcontrol->val,tasinacak) == 0)
            kontrol2=1;
    if(kontrol1==1 && kontrol2&&1){
    r=sil(r, tasinacak);
    n*sabit=r;
    n* newone;
    switch (secim){
case 'A':
    while(strcmp(r->val,hedef) != 0){
        r=r->next;
    }
    newone=(n*)malloc(sizeof(n));
    strcpy(newone->val,tasinacak);
    newone->next=r->next;
    r->next=newone;
    return sabit;

    break;

case 'B':
    if (strcmp(r->val,hedef) != 0){

    while(strcmp(r->next->val,hedef) != 0){
        r=r->next;
    }
    newone=(n*)malloc(sizeof(n));
    strcpy(newone->val,tasinacak);
    newone->next=r->next;
    r->next=newone;
    return sabit;
    }
    else{
    newone=(n*)malloc(sizeof(n));
    strcpy(newone->val,tasinacak);
    newone->next=r;
    r=newone;
    while (sabit->next!=r->next){
        sabit=sabit->next;
    }
    sabit->next=r;
    return r;
    }
    break;

    }
    }
    else{
        return r;
    }
}
n* PlaySong (n*playingsong,n*root, char secim, FILE* outputfile){
    n*sabitroot=root;

    if(root== NULL){
        fprintf(outputfile,"No Songs to Play\n");
        fprintf(outputfile,"*****\n");

    }
    else{
    if (playingsong==NULL){
            switch(secim){
        case 'N':
            playingsong=root;
            break;

        case 'P':
            while (root->next!= sabitroot){
                root=root->next;
            }
            playingsong=root;
            break;
            }

    }
    else{
            n*temp=playingsong;
                    switch(secim){
        case 'N':
            playingsong=playingsong->next;
            break;
        case 'P':

            while (temp->next!= playingsong){
                temp= temp->next;
            }
            playingsong=temp;
            break;
            }

    }
    fprintf(outputfile, "Playing %s \n", playingsong);
    fprintf(outputfile,"*****\n");
    }
    return playingsong;

}
n* RemoveSong (n*r, n*playingsong , char* silinecek, FILE* outputfile){
if (playingsong==NULL){
    r= sil(r, silinecek);
}
else{
    if(strcmp(playingsong,silinecek) != 0){

        r= sil(r, silinecek);
    }

    else{
        fprintf(outputfile, "Cannot Remove The Playing Song \n");
        fprintf(outputfile,"*****\n");
    }
    }
    return r;

}
void PrintPlaylist(n*r, char secim, FILE* outputfile){
    n*temp=r;
    if(r==NULL){
        fprintf(outputfile,"No Songs To Print\n");
    }
    else {
switch(secim){
case 'F':
    BastanBasla(r, outputfile);
    break;
case 'R':
    while (temp->next != r){
        push(temp->val);
        temp=temp->next;
    }
    push(temp->val);
    temp=r;
        while (temp->next != r){
        pop(outputfile);
        temp=temp->next;
    }
    pop(outputfile);
    break;
}
    }
    fprintf(outputfile,"*****\n");
}
void BastanBasla(n*r, FILE* outputfile){

n*temp=r;
while(temp->next!= r){
    fprintf(outputfile, "%s \n", temp->val);
    temp=temp->next;
}
fprintf(outputfile, "%s \n", temp->val);
}
void push(char* song){
sn * eklenecek= (sn*)malloc(sizeof(sn));
strcpy(eklenecek->val, song);
eklenecek->next=NULL;
if(top!= NULL){
    eklenecek->next=top;
}
top=eklenecek;
}
void pop(FILE*outputfile){
if(top->val != NULL){
    sn*temp;
    temp=top;
    top=top->next;
    fprintf(outputfile," %s \n", temp->val);
    free(temp);
}
}
n* ReverseList(n*r){
    n* sabitroot=r;
if(r==NULL){
    return r;
}
else{
            while(r->next != sabitroot){
            r= r->next;
        }
n*prev=r;
n*current=sabitroot;
n*next;
while (current->next!=sabitroot){
    next=current->next;
    current->next=prev;
    prev=current;
    current=next;

}
    next=current->next;
    current->next=prev;
    prev=current;
    current=next;
return prev;
}
}

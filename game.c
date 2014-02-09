#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <termios.h>

void vivod (int a []);
int maxofsteps=50;

struct stack * top [9]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
int winner [9]={1,2,3,4,5,6,7,8,0};


void zapolnenie (int a [])
{int j,i,ran,f;
srand((unsigned)time(NULL));
f=0;
int k;
i=0;
while (i<9)
        {f=0;
        ran=rand();
        for (j=0;j<i;j++)
                if ((ran%9)==a[j])
                        f=1;
        if (f==0)
                {a[i]=ran%9;
                i++;}

}
int count=0;
int curr;
for (i=0;i<9;i++)
{   curr=a[i];
    for (j=i+1;j<9;j++)
        if ((a[j]<a[i]) && (a[j]!=0))
            count++;
}
for (i=0;i<9;i++)
    if (a[i]==0)
        k=i;
int levzero=(int)k/3+1;
if ((count%2!=0) || (levzero!=3))
    zapolnenie (a);
}


typedef struct tnode tnode;
struct tnode  {
        struct tnode * left;
        struct tnode * right;
        int * matrix ;};

typedef struct stack stack;
struct stack {
        int * A;
        struct stack * next;
        };
void push  (int * matr,int num){
stack * node=(stack *) malloc (sizeof (stack));
node->A=matr;
node->next=top[num];
top[num]=node;
}
int * pop (int numb){
if (top[numb]==NULL)
    return NULL;
struct stack *z = top[numb];
top[numb] = top[numb]->next;
return z->A;
}



tnode* nalloc (int * a) {
        tnode * node=(tnode*) malloc (sizeof (tnode));
        if (!node) return NULL;
        node->left=NULL;
        node->right=NULL;
        int i;
        node->matrix=a;
        return node;
        }
int compare (int * m1, int * m2,int noce){
    int i=0;
    while ((m1[i]==m2[i]) && (i<noce))
        i++;
    if (m1[i]<m2[i])
        return -1;
    if (i==noce)
        return 0;
    return 1;
}


int addnode (tnode ** root, int * a ) {
    if (*root==NULL) {
        tnode * node=nalloc (a);
        *root= node;
        return 1;
        }
    int res=compare (a,(*root)->matrix,9);
    if (res==0){
        return 0;
    }
    if (res<0) {
        tnode ** z = &((*root)->left);
        return addnode ( z,a);
    }
    else {
        tnode ** z = &((*root)->right);
        //puts("pass it");
        return addnode ( z,a);
    }
}


int function (tnode ** root,int * mas,int step,int stepsin){
       int t;int z;int z2;int flag;
    int z3=0;int i;int k,j;
        if ((stepsin>maxofsteps) )
            return 0;
        if (compare (mas,winner,(step+1)*1)==0){
               push (mas,step);
                return 1;
    }else {
        int * a=(int *) malloc (16*sizeof (int));
        for(j = 0; j < 9; j++){
 a[j]=mas[j];
        }
       for (i=0; i<9;i++)
            if (a[i]==0)
                        k=i;
                i=k;
        //printf("%i = i\n",i);
       // puts("1");
        if (((i)%3)!=0){
            t=a[i-1];
            a[i-1]=a[i];
            a[i]=t;
            //vivod(a);
            z=addnode (root,a);
          //  puts("add done");
            if (z==1) {
                z2=function(root,a,step,stepsin+1);
                if (z2==1) {
                    push (mas,step);
                    z3=1;
                    //vivod(a);
 return z3;
                }else{free(a);}
            }else{free(a);}
        }else{free(a);}
        a=(int *) malloc (16*sizeof (int));
        for(j = 0; j < 9; j++){
            a[j]=mas[j];
        }
       // puts("2");
        if ((i+3)<9){
            t=a[i+3];
            a[i+3]=a[i];
            a[i]=t;
            //vivod(a);
            z=addnode (root,a);
            //puts("add done");
            if (z==1) {
                z2=function(root,a,step,stepsin+1);
                if (z2==1) {
                        push (mas,step);
                        z3=1;
                    return z3;
                }else{free(a);}
            }else{free(a);}
        }else{free(a);}
//        puts("3");
        a=(int *) malloc (16*sizeof (int));
        for(j = 0; j < 9; j++){
            a[j]=mas[j];
        }
        if (((i)%3)!=2){
            t=a[i+1];
            a[i+1]=a[i];
            a[i]=t;
            //vivod(a);
            z=addnode (root,a);
         //   puts("add done");
            if (z==1) {
                //puts("accepted");
                z2=function(root,a,step,stepsin+1);
                if (z2==1) {
                    //puts("go to next");
                    push (mas,step);
                    z3=1;
return z3;
                }else{free(a);}
            }else{free(a);}
        }else{free(a);}
        a=(int *) malloc (16*sizeof (int));
        for(j = 0; j < 9; j++){
            a[j]=mas[j];
        }
        //puts("4");
        if ((i-3)>=0){
            t=a[i-3];
            a[i-3]=a[i];
            a[i]=t;
            z=addnode (root,a);
          //  puts("add done");
            if (z==1) {
                z2=function(root,a,step,stepsin+1);
                if (z2==1) {
                    push (mas,step);
                    z3=1;
 return z3;
                }else{free(a);}
            }else{free(a);}
        }else{free(a);}
    }
    return z3;
}


void vivod (int a [])
{int i=0;
int j=0;
for (i=0; i<9; i++)
        {if ((j%3)==0) printf ("\n");
        if (a[i]<10 )
                {printf ("[ %d]",a[i]);
                j++;}
        else
                {printf ("[%d]",a[i]);
                j++;}
        }
printf("\n");
}



int main ()
{//printf ("To move the empty cell called [ 0 ] use 'u' to move up;'d' to move down;'l' to move left;'r' to move right; press 'q' to leave the game \n ");
//FILE * myoutput=fopen ("myoutput.txt","w");
    struct termios savetty, tty;
   char ch;
   /*if( !isatty( 0 ) ) { 
      fprintf( stderr, "stdin not terminal\n" ); 
      exit( EXIT_FAILURE ); 
   }; 
   tcgetattr( 0, &tty );             // получили состояние терминала 
   savetty = tty; 
   tty.c_lflag &= ~( ICANON | ECHO | ISIG ); 
   tty.c_cc[ VMIN ] = 1; 
   tcsetattr( 0, TCSAFLUSH, &tty ); */// изменили состояние терминала 
int k,i;
struct tnode* root = NULL;
//zapolnenie(mas);
//vivod(mas);
int mas [9] ={1,2,3,4,5,6,7,0,8};/*5,6,1,4,0,8,7,3,2};{1,2,3,4,5,0,8,7,6};*/
int p;
function(&root, mas,0,1);
while (top[0]->next!=NULL){
    vivod (pop(0));}
    vivod (top[0]->A);
for (p=1;p<9;p++){
    if (compare(top[p-1]->A,winner,9)==0)
        break;
function(&root, top[p-1]->A,p,1);
while (top[p]->next!=NULL){
    vivod (pop(p));}
    vivod (top[p]->A);
}/*while (top[1]!=NULL){
    free(top[1]);
    top[1]=top[1]->next;
}
function(&root, mas,2,1);
while (top[2]!=NULL){
//      sleep (2);
    vivod (pop(2));
  }
while (top[2]!=NULL){
    free(top[2]);
    top[2]=top[2]->next;
}
function(&root, mas,3,1);
while (top[3]!=NULL){
//      sleep (2);
    vivod (pop(3));
  }
while (top[3]!=NULL){
    free(top[3]);
    top[3]=top[3]->next;
}

//move(mas,k);
 tcsetattr( 0, TCSAFLUSH, &savetty ); // восстановили состояние терминала 
   printf( "\n" ); 
   exit( EXIT_SUCCESS ); */
//fclose (myoutput);
return 0;
}



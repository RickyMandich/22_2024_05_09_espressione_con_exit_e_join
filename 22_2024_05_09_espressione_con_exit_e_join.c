#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int box1;
int semaforo1 = 0;

int box2;
int semaforo2 = 0;

void* somma(void* arg){
    while (semaforo1 == 1 && semaforo2 == 1){}
    semaforo1 = 1;
    semaforo2 = 1;
    int risultato = box1 + box2;
    printf("faccio %d + %d = %d\n", box1, box2, risultato);
    semaforo1 = 0;
    semaforo2 = 0;
    pthread_exit((void*)risultato);
}

void* differenza(void* arg){
    while (semaforo1 == 1 && semaforo2 == 1){}
    semaforo1 = 1;
    semaforo2 = 1;
    int risultato = box1 - box2;
    printf("faccio %d - %d = %d\n", box1, box2, risultato);
    semaforo1 = 0;
    semaforo2 = 0;
    pthread_exit((void*)risultato);
}

void setBox1(int box){
    while (semaforo1 == 1){}
    semaforo1 = 1;
    box1 = box;
    semaforo1 = 0;    
}

void setBox2(int box){
    while (semaforo2 == 1){}
    semaforo2 = 1;
    box2 = box;
    semaforo2 = 0;    
}
/*
(3+2)*(6-2)
*/
int main(){
    int a = 3, b = 2, c = 6, d = 2;
    setBox1(a);
    setBox2(b);
    pthread_t tid;
    void* ret;
    pthread_create(&tid, NULL, somma, NULL);
    pthread_join(tid, &ret);
    int ris1 = ret;
    setBox1(c);
    setBox2(d);
    pthread_create(&tid, NULL, differenza, NULL);
    pthread_join(tid, &ret);
    int ris2 = ret;

    int ris = ris1 * ris2;
    printf("il risultato delle prime parentesi (%d+%d) è %d quello delle seconde (%d-%d) è %d\nil risultato di tutto è %d\n", a, b, ris1, c, d, ris2, ris);

}
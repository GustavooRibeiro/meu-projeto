#include<stdio.h>
#include<stdlib.h>
float calcMedia(int x, float* nota){
float soma = 0.0;
for(int i = 0; i < x; i++){
    soma += nota[i];
}
return soma / x;
}
void ler(int x, float* nota, char* nome){
    for(int i = 0; i < x; i++ ){
        printf("nome do aluno %d: \n", i + 1);
    scanf("%s", &nome[i * 50]);
    printf("nota do aluno %s: \n", nome + i * 50);
    scanf("%f", &nota[i]);
    }
}
void maiorMenor(float *nota, int x, float *maior, float *menor, int *iMa, int *iMe) {
    for(int i = 0; i < x; i++){
        if(nota[i] > *maior){
            *maior = nota[i];
            *iMa = i;
        }
        if(*menor > nota[i]){
            *menor = nota[i];
            *iMe = i;
        }
    }
}
int main(){
int x;
printf("quantos alunos? \n");
scanf("%d", &x );
while(x == 0){
    scanf("%d", &x);
}
char *nome = malloc(x * 50 * sizeof(char));
float *nota = malloc(x * sizeof(float));
float maior = 0.0;
float menor = 9999999.9;
int iMa = 0;
int iMe = 0;
ler(x, nota, nome);
maiorMenor(nota, x, &maior, &menor, &iMa, &iMe);
float media = calcMedia(x, nota);
printf("\nAprovados:\n");
for(int i = 0; i < x; i++){
    if(nota[i] >= 6.0){
        printf(" %s\n", nome + i * 50);
    }
}
printf("\nReprovados:\n");
for(int i = 0; i < x; i++){
    if(nota[i] < 6.0){
        printf(" %s\n", nome + i * 50);
    }
}
printf("A media da turma: %.2f\n", media);
printf("A maior nota foi do aluno %s : %.2f\n", nome + iMa * 50, maior);
printf("A menor nota foi do aluno %s : %.2f\n", nome + iMe * 50, menor);
free(nota);
free(nome);
    return 0;
}
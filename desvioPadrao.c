#include<stdio.h>
#include<math.h>
float dPadrao(float valores[], int tam){
    float media = 0;
    float dPadrao = 0;
    for(int i = 0; i < tam; i++){
        media += valores[i];
    }
    media = media/tam;
    for(int i = 0; i < tam; i++){
        dPadrao = dPadrao + (valores[i]-media)*(valores[i]-media);
    }
    dPadrao = sqrt(dPadrao/tam);
    return dPadrao;
}

int main(){
    int n;
    scanf("%d", &n);
    float valores[n];
    for(int i = 0; i < n; i++){
        scanf("%f", &valores[i]);
    }
    float d;
    d = dPadrao(valores, n);
    printf("%.2f\n", d);
 
    return 0;
}
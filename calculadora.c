#include<stdio.h>
#include<math.h>
double calcular(double a, double b, char op, double *pr){
switch(op){
    case'+':
    *pr = a + b;
    break;
    case'-':
    *pr = a - b;
    break;
    case'*':
    *pr = a * b;
    break;
    case'/':
    *pr = a / b;
    break;
    case'p':
    *pr = pow(a, b);
    break;
    case'r':
    *pr = sqrt(a);
    break;
    case'f': {
    double fat = 1.0;
    int n = (int)a;
    for(int i = 1; i <= n; i++){
        fat *= i;
    }
    *pr = fat;
    break;
}
    default:
    return 0;
}
return 1;
}

int main(){
    printf("Calculadora do Batman!\n");
    printf("\nOperadores: \n '+' = adicao\n '-' = subtracao\n '*' = multiplicacao\n '/' = divisao\n 'p' = potencia\n 'r' = raiz\n 'f' = fatorial\n");
double a, b;
char op;
printf("\nDigite o numero: ");
scanf("%lf", &a);
printf("\nDigite o operador: ");
scanf(" %c", &op);
if(op != 'r' && op != 'f'){
printf("\nDigite o outro numero: ");
scanf("%lf", &b);
}
double resultado;
double *pr = &resultado;
if(op == '/' && b == 0){
    printf("\nimpossivel divisao por zero!\n");
}
else if(calcular(a, b, op, pr) == 0){
    printf("\n Operacao invalida!\n");
}
else{
calcular(a, b, op, pr);
printf("\nResultado: %.2lf\n", resultado);
printf("\nVolte sempre!\n");
}
    return 0;
}
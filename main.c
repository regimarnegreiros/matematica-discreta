#include <stdio.h>

void checarMostrar(int n) {
    if (n != 0 && n != 1) {
        printf("Erro: o último parâmetro deve ser 0 ou 1.\n");
        printf("0: Não mostrar resultado\n");
        printf("1: Mostrar resultado\n");
    }
}

int divEuclidiano(int a, int b, int mostrar) {
    checarMostrar(mostrar);

    int q = a / b;

    if (a - b * q == 0 || a > 0);
    else if (a < 0 && b < 0) q++;
    else q--;

    if (mostrar  == 1) printf("Quociente = %d\n", q);
    return q;
}

int modEuclidiano(int a, int b, int mostrar) {
    checarMostrar(mostrar);

    if (b == 0) {
        if (mostrar  == 1) printf("Erro: Divisão por 0 não suportada\n");
        return -1;
    }

    int r = a - (b * divEuclidiano(a, b, 0));
    if (mostrar  == 1) printf("Resto = %d\n", r);

    return r;
}

int mdc(int a, int b, int mostrar) {
    checarMostrar(mostrar);

    int anterior = a;
    int atual = b;
    int resto = modEuclidiano(anterior, atual, 0);

    while (resto != 0) {
        if (mostrar  == 1) printf("MDC(%d, %d) | %d = %d . %d + %d | c ≠ 0\n", 
                            anterior, atual, 
                            anterior, atual, 
                            divEuclidiano(anterior, atual, 0), 
                            resto);
        anterior = atual;
        atual = resto;
        resto = modEuclidiano(anterior, atual, 0);
    }

    if (mostrar  == 1) {
        printf("MDC(%d, %d) | %d = %d . %d + %d | c = 0\n", 
                anterior, atual, anterior, atual, 
                divEuclidiano(anterior, atual, 0), resto);
        printf("MDC(%d, %d) = %d\n", a, b, atual);
    }

    return atual;
}

int adicaoModular(int a, int b, int z, int mostrar) {
    checarMostrar(mostrar);

    int adicao = modEuclidiano(a + b, z, 0);
    if (mostrar  == 1) printf("%d + %d em z%d = %d\n", a, b, z, adicao);

    return adicao;
}

int subtracaoModular(int a, int b, int z, int mostrar) {
    checarMostrar(mostrar);

    int subtracao = modEuclidiano(a - b, z, 0);
    if (mostrar  == 1) printf("%d - %d em z%d = %d\n", a, b, z, subtracao);
    return subtracao;
}

int multiplicacaoModular(int a, int b, int z, int mostrar) {
    checarMostrar(mostrar);

    int multiplicacao = modEuclidiano(a * b, z, 0);
    if (mostrar  == 1) printf("%d x %d em z%d = %d\n", a, b, z, multiplicacao);

    return multiplicacao;
}

int inversoMultiplicativo(int a, int z, int mostrar) {
    checarMostrar(mostrar);

    for(int b = 0; b < z; b++) {
        if(modEuclidiano(a*b, z, 0) == 1) {
            if (mostrar  == 1) printf("Inverso de %d em z%d é %d\n", a, z, b);
            return b;
        }
    }
    if (mostrar  == 1) printf("%d ∄ inverso em z%d\n", a, z);

    return -1;
}

int divisaoModular(int a, int b, int z, int mostrar) {
    checarMostrar(mostrar  == 1);

    int inverso = inversoMultiplicativo(b, z, 0);
    if (inverso == -1) {
        printf("%d ∄ inverso\n", b);
        return -1;
    }

    int divisao = multiplicacaoModular(a, inverso, z, 0);
    if (mostrar  == 1) printf("%d / %d em z%d = %d\n", a, b, z, divisao);

    return divisao;
}

int congruencia(int a, int b, int mod_n, int mostrar) {
    checarMostrar(mostrar);

    int r = modEuclidiano(a-b, mod_n, 0);

    if (r == 0) {
        if (mostrar  == 1) printf("%d ≡ %d (mod %d) pois %d-(%d) = %d e %d | %d\n",
                                    a, b, mod_n, a, b, a-b, mod_n, a-b);
    } else {
        if (mostrar  == 1) printf("%d ≢  %d (mod %d) pois %d-(%d) = %d e %d ∤ %d\n", 
                                    a, b, mod_n, a, b, a-b, mod_n, a-b);
    }

    return r;
}

int congruenciaLinear(int a, int b, int mod_n, int mostrar) {
    checarMostrar(mostrar);

    int aInicial = a;
    int bInicial = b;
    int modInicial = mod_n;

    int m = mdc(a, mod_n, 0);
    
    if (modEuclidiano(b, m, 0) == 0) {
        if(mostrar  == 1) {
            printf("%dx ≡ %d mod(%d)\n", a, b, mod_n);
            printf("mdc(%d, %d) = %d e %d | %d portanto ∃ solução\n", a, mod_n, m, m, b);
            printf("(%d/%d)x ≡ (%d/%d) (mod %d/%d)\n", a, m, b, m, mod_n, m);
        }

        a = a / m;
        b = b / m;
        mod_n = mod_n / m;

        if (mostrar  == 1) printf("%dx ≡ %d (mod %d)\n", a, b, mod_n);

        int inverso = inversoMultiplicativo(a, mod_n, 0);

        if (mostrar  == 1) {
            printf("O inverso de %d (mod %d) é %d\n", a, mod_n, inverso);
            printf("%d . %dx ≡ %d . %d mod(%d)\n", inverso, a, inverso, b, mod_n);
        }

        b = b * inverso;

        if (mostrar  == 1) printf("x ≡ %d (mod %d)\n", b, mod_n);

        int q = b / mod_n;
        
        if (mostrar  == 1) printf("x ≡ %d - %d . %d (mod %d)\n", b, mod_n, q, mod_n);

        b = b - q * mod_n;

        if (mostrar  == 1) {
            printf("x ≡ %d (mod %d)\n", b, mod_n);
            printf("x = %d + %dk\n", b, mod_n);
            printf("x = {..., ");
            int k;
            for (k = -3; k < 3; k++) {
                printf("%d, ", b + mod_n * k);
            }
            printf("%d, ...}\n", b + mod_n * ++k);
            printf("%d . %d ≡ %d (mod %d)\n", aInicial, b, bInicial, modInicial);
        }

        congruencia(aInicial * b, bInicial, modInicial, mostrar  == 1);

        return b;
    } else {
        if (mostrar == 1) {
            printf("%dx ≡ %d mod(%d)\n", a, b, mod_n);
            printf("mdc(%d, %d) = %d e %d ∤ %d portanto ∄ solução\n", a, mod_n, m, m, b);
        }
        
        return -1;
    }
}

int main() {

    printf("\n");

    adicaoModular(5, 5, 5, 1);
    subtracaoModular(7, 5, 4, 1);
    multiplicacaoModular(7, 5, 4, 1);
    divisaoModular(2, 7, 10, 1);
    inversoMultiplicativo(3, 12, 1); printf("\n");

    int a = 18;
    int b = 8;
    int mod = 20;

    divEuclidiano(a, b, 1); 
    modEuclidiano(a, b, 1); printf("\n");

    mdc(a, b, 1); printf("\n");

    congruencia(a, b, mod, 1); printf("\n");
    
    congruenciaLinear(a, b, mod, 1); printf("\n");
    
    return 0;
}

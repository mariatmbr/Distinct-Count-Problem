// Copyright 2020 Timbur Maria
#include <stdio.h>
#include <stdlib.h>

int main() {
    int x, j;
    int k = -100, a = 0;
    // aloc vectorul de frecventa
    int *freq = calloc(2000100, sizeof(int));
    int b;
    // citesc numerele pana cand nu dau de sfarsitul fisierului
     while  (!feof(stdin)){
            fscanf(stdin, "%d", &x);
            b = x;
            if (x < 2000000){
                freq[x] = freq[x] + 1;
                if (x > k){
                    k = x;
               }
            } else {
                a++;
            }
        }
        freq[b]--;
        for (j = 0; j <= k; j++){
            // afisez frecventa
            if (freq[j] > 0){
                printf("%d %d\n", j, freq[j]);
            }
        }
        if (a > 0){
            printf("2000000 %d\n", a);
        }
    // eliberez memoria
    free(freq);
    return 0;
}
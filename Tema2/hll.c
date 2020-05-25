// Copyright 2020 Timbur Maria
#include <stdio.h>
#define MPOW 11
#define alpha 2*0.72092017926
// functie de hash pentru numere intregi
unsigned int hash(unsigned int uint_a) {
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = (uint_a >> 16u) ^ uint_a;
    return uint_a;
}
// functie car intoarce numerul de zerouri consecutive
unsigned int getZerCnt(unsigned int x){
    int cnt = 0;
    for (int i = 32 - MPOW - 1; i >= 0; i--){
        if (((1 << i) & x) == 0){
            cnt++;
        } else {
            return cnt;
        }
    }
    return cnt;
}
// functie care intoarce numarul bucketului
unsigned int getBuck(unsigned int x){
    return (x >> (32 - MPOW));
}

int main(int argc, char *argv[]) {
    // verific daca fisierul este dat ca parametru
    if (argc !=2){
        printf("nr gresit de parametri");
    }

    FILE *f = fopen(argv[1], "r");
    // initializez vectorul de zerouri
    int M[(1 << MPOW)] = {0};
    int x;
    while (!feof(f)){
        // citesc cate un numar
        fscanf(f, "%d", &x);
        // il trec prin functia de hash
        int h = hash(x);
        // gasesc bucketul corespunzator
        int buck = getBuck(h);
        // gasesc numarul de zerouri consecutive
        int zer = getZerCnt(h);
        // nr de zerouri il pun in caseta bucketului respectiv
        if (M[buck] < zer) M[buck] = zer;
    }
    // formula pentru Z
    double Z = 0;
    for (int i = 0; i < (1 << MPOW); i++){
        Z += 1.0 / (1 << M[i]);
    }
    Z = 1 / Z;
    // formula pentru E
    // (MPOW << 1) = 22;
    // (1 << (MPOW << 1)) = m^2
    int E = alpha * (1 << (MPOW << 1)) * Z;
    // afisez rezultatul
    printf("%d", E);
    // inchid fisierul
    fclose(f);
    return 0;
}


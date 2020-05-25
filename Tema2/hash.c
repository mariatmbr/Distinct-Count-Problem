// Copyright 2020 Timbur Maria
#include <ctype.h>
#include <stdio.h>
#include <string.h>
// size ul unui cuvant
#define SIZE_WORD 101
// nuamarul maxim de cuvinte
#define NR_WORDS 200
// am definit fisierul standard input
#define stdin stdin


typedef struct {
	char word[SIZE_WORD + 1];
	int freq, next;
} Hashtable;

int get_word(FILE *stdin, char str[]) {
	// am transformat cuvintele din litere mari in litere mici
	// stochez urmatorul cuvant
	// daca am gasit cuvantul intoarcem 1, in caz contrar 0
	char c;
	int n = 0;
	// skip altor elemente care nu sunt litere
	while (!isalpha(c = getc(stdin)) && c != EOF){
		c = getc(stdin);
	}
	if (c == EOF){
		return 0;
	}
	str[n++] = tolower(c);
	while (isalpha(c = getc(stdin)) && c != EOF){
		if (n < SIZE_WORD) str[n++] = tolower(c);
	}
	str[n] = '\0';
	return 1;
}
// functia de hashing care imi intoarce un int
int hash_function(char a[]) {
    int h = 0, keyNum = 0, w = 27;
	while (a[h] != '\0') {
		keyNum += w * a[h++];
		w = w + 8;
	}
	return keyNum;
}
// functie care cauta cuvantul in hastable
int search_word_in_hashtable(Hashtable table[], char key[]) {
	// caut cheia in hashtable, daca am gasit-o, intorc locatia
	// daca nu e gasita, returnez -place
	int keyNum = hash_function(key);
	int place = keyNum % 30 + 1;
	int k = keyNum % (30 - 2) + 1;

	while ((strcmp(table[place].word, "" ) != 0) &&
					(strcmp(table[place].word, key) != 0)) {
		place = place + k;
		if (place > 30) place = place - 30;
	}
	if (strcmp(table[place].word, "") == 0) return -place;
	return place;
}
// functie care adauga un cuvant in hashtable
int add_to_hashtable(Hashtable table[], char key[], int place, int head) {
	// pastrez cheia in hashtable[place] in ordine alfabetica
	strncpy(table[place].word, key, strlen(key)+1);
	table[place].freq = 1;
	int curr = head;
	int prev = -1;
	while (curr != -1 && (strcmp(key, table[curr].word) > 0)) {
		prev = curr;
		curr = table[curr].next;
	}
	table[place].next = curr;
	// noul prim element
	if (prev == -1) return place;
	// liniar probing
	table[prev].next = place;
	// primul element neschimbat
	return head;
}
// functie care afiseaza cuvintele si frecventele corespunzatoare
void print_hashtable(Hashtable table[], int head) {
	while (head != -1) {
		printf("%s %d\n", table[head].word, table[head].freq);
		head = table[head].next;
	}
}
int main() {
	char word[SIZE_WORD+1];
	Hashtable hashtable[30+1];
	for (int i = 1; i <= 30; i++){
		strncpy(hashtable[i].word, "", 1);
	}
	// chestia asta am gasit- o pe net, am vrut sa folosesc stdin ul
	// properly ca pe un fisier
	FILE *stdin = (FILE *) &_IO_2_1_stdin_;
	// se duce la primul cuvant in ordine alfabetica
	int fst = -1;
	// citesc cuvintele pana se termina fisierul
	while (get_word(stdin, word) != 0) {
		// verific daca cuvantul este deja in hashtable
		int place = search_word_in_hashtable(hashtable, word);
		// cresc frecventa
		if (place > 0) hashtable[place].freq++;
		else
			// daca e un nou cuvant il adaug in hashtable
			fst = add_to_hashtable(hashtable, word, -place, fst);
	}
	// afisez rezultatele
	print_hashtable(hashtable, fst);
	// inchid fisierul
	fclose(stdin);
}


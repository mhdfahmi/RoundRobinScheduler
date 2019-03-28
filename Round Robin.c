#include <stdio.h>
#include <stdlib.h>

// Deklarasi Tipe Data Boolean //
#ifndef _BOOLEAN_h
#define _BOOLEAN_h
#define boolean char
#define true 1
#define false 0
#endif
#define Nil NULL

// Struktur Data Linked List //
typedef int infotype;
typedef struct tElmtList *address;
typedef struct tElmtList {
	infotype info;		// Deklarasi tipe data untuk Info(P)
	address next;
	char infoname;		// Deklarasi tipe data untuk Name(P)
} ElmtList;

typedef struct {
	address first;
} List;

// Selektor //
#define Info(P) (P)->info
#define Name(P) (P)->infoname
#define Next(P) (P)->next
#define First(L) (L).first

/*---PROTOTYPE---*/
// Cek list kosong //
boolean IsEmpty (List L) {
	return (First(L) == Nil);
}

// Membuat List kosong //
void CreateEmpty (List *L) {
	First(*L) = Nil;
}

/*-------------MANAJEMEN MEMORI-------------*/
// Alokasi elemen baru //
address Allocation (infotype X, char Y) {
	// Kamus //
	address P;
	P = (address) malloc (sizeof(ElmtList));
	// Algoritma //
	if (P != Nil) {
		Info(P) = X;
		Name(P) = Y;
		Next(P) = Nil;
		return P;
	}
}

// Dealokasi elemen beralamat P ke sistem //
void Deallocation (address *P) {
	free(*P);
}

/*---PENAMBAHAN ELEMEN---*/
void InsertFirst (List *L, infotype X, char Y) {
	address P, Prec;
	P = Allocation(X,Y);
	Prec = First(*L);
	if (P != Nil) {
		Next(P) = First(*L);
		if (IsEmpty(*L)) {
			Next(P)   = P;
			First(*L) = P;
		} else {
			while (Next(Prec) != First(*L)) {
				Prec = Next(Prec);
			}
			Next(Prec) = P;
		}
		First(*L) = P;
	}
}

/*---PENCARIAN ADDRESS YANG BERISI QUANTA <= 0---*/
address SearchQuanta (List L) {
	// Kamus //
	address P, Pt;
	Pt = P = First(L);
	// Algoritma //
	while (Next(P) != First(L)) {
		P = Next(P);
	}
	while (Next(Pt) != First(L)) {
		if (Info(Pt) <= 0) {
			return P;
		}
		P  = Pt;
		Pt = Next(Pt);
	}
	return P;
}

/*---PENGHAPUSAN ELEMEN---*/
void DeleteFirst (List *L, infotype *X) {
	// Kamus //
	address Pt, Q; 
	Pt = Q = First(*L);
	*X = Info(Pt);
	// Algoritma //
	if (Next(Pt) == Pt) { // penghapusan satu elemen
		First(*L) = Nil;
	} else {
		while (Next(Pt) != First(*L))
			Pt = Next(Pt);
		First(*L) = Next(Pt) = Next(First(*L));
	}
	Deallocation(&Q);
}

void DeleteInfo (List *L, address *P){
	// Kamus //
	address Q;
	Q = SearchQuanta(*L);
	infotype X;
	// Algoritma //
	if ((Next(*P) == *P) && (Info(*P) <= 0)) {
		*P = First(*L);
		X = Info(*P);
		First(*L) = Nil;
		Deallocation(P);
	} else if (Info(First(*L)) <= 0) {
		DeleteFirst(L,&X);
	} else {
		*P = Next(Q);
		X = Info(*P);
		Next(Q) = Next(Next(Q));
		Next(*P) = Nil;
	}
}

/*---PRINT DATA DALAM BENTUK TABEL---*/
void PrintInfo (List L) {
	// Kamus //
	address P;
	P = First(L);
	// ALgoritma //
	printf("\n");
	printf("Data   >> \n");
	printf("+---------------+---------------+\n");
	printf("|     Data      |    Quanta     |\n");
	printf("+---------------+---------------+\n");
	if (IsEmpty(L)) {
		/*Do Nothing*/
	} else {
		while (Next(P) != First(L)) {
		printf("|      %c        |      %d       |\n", Name(P), Info(P));
			P = Next(P);
		}
		printf("|      %c        |      %d       |\n", Name(P), Info(P));
	}
	printf("+---------------+---------------+\n");
	printf("\n\n");
}

/*--------------PROSES UTAMA ROUND ROBIN---------------*/
void Utama (List *L, address *P, infotype Quantum) {
	// Kamus //
	address Q;
	*P = First(*L);
	int Switch = 1;
	int QntmTotal = 0;
	// Algoritma //
	printf("Proses >> \n");
	printf("+---------------+---------------+\n");
	printf("|     Data\t|    Quantum    |\n");
	printf("+---------------+---------------+\n");
	while (!IsEmpty(*L)) {
		if (Next(*P) == *P) {
			if (Info(*P) > 0) {
				printf("|      %c\t", Name(*P));
				printf("|  \t%d\t| >>", Quantum);
				printf(" %c ", Name(*P));
				Info(*P) -= Quantum;
				printf(" =  %d", Info(*P));
			} else if (Info(*P) > 0) {
				QntmTotal += Quantum + Switch;
				printf("\n");
				printf("| Switch \t|      \t   %d \t|\n", Switch);
			} else {
				printf(". Dispose %c\n", Name(*P));
				QntmTotal += Quantum;
				Q = *P;
				DeleteInfo(L,&Q);
			}
		} else if (P != Nil){
			printf("|      %c\t", Name(*P));
			printf("|  \t%d\t| >>", Quantum);
			printf(" %c ", Name(*P));
			Info(*P) -= Quantum;
			printf(" =  %d", Info(*P));
			if (Info(*P) > 0) {
				printf("\n");
				printf("|    Switch \t| \t%d \t|\n", Switch);
				*P = Next(*P);
			} else {
				printf(". Dispose %c", Name(*P));
				printf("\n");
				printf("|    Switch \t| \t%d \t|\n", Switch);
				Q = *P;
				*P = Next(*P);
				DeleteInfo(L,&Q);
			}
		QntmTotal += Quantum + Switch;
		}
	}
	printf("+---------------+---------------+\n");
	printf("| Total Quantum : \t%d\t|\n", QntmTotal);
	printf("+---------------+---------------+\n");

}

int main () {
	// Kamus //
	address P;
	int n, i;
	infotype qntm;
	List L;
	// Algoritma //
	CreateEmpty(&L);
	
	printf ("\t\t\t*========================*\n");
	printf ("\t\t\t||ROUND ROBIN SCHEDULING||\n");
	printf ("\t\t\t*========================*\n\n");

	printf("Jumlah Data\t\t: ");  //Input Jumlah Data
	scanf("%d", &n);
		if (n<5) {
		printf ("\t---------------------\n");
		printf ("\tJumlah Data Minimal 5\n");
		printf ("\t---------------------\n");
	} else {
		printf("Quantum Per Proses\t: ");  //Input Quantum
		scanf("%d", &qntm);

	infotype a[n];
	char b[n];

	for(i=1; i<=n; i++){
		printf("\n");
		printf("\n");
            fflush(stdin);
            printf("Simpul	#%d \n", i);
			printf("Data	#%d\t\t : ", i);
			scanf("%c",&b[i]);
			printf("Quanta	#%d\t\t : ", i);
			scanf("%d",&a[i]);
			printf("\n");
			InsertFirst(&L, a[i], b[i]);
		}
	
	PrintInfo(L);
	Utama(&L, &P, qntm);
	}
	return 0;
}

#include <stdio.h>
#include <string.h>


//Control panel
const char Kalem[] = "Kalem"; //hedef gen
#define B_S 20 //number of humans in a generation
#define G_S 5 //number of genes - must be the same as strlen(Kalem)
#define SBS 6 //how many of the healthiest people will have children.

char baba[] = "KtueV"; //Father starting gene
char anne[] = "palYj"; //Mother starting gene

//Global variables
const char HAVUZ[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //gene pool
char Kabile[B_S][G_S+1]; //peoples here
char KabileYedek[SBS][G_S+1]; //backup
int KabileSaglik[B_S]; //people's health


int x,y,a,b; //variables for loops

/* mating function:
It takes in information about how many offspring have been produced in the tribe.
It takes genes from identified parents and the possibility of mutations and produces the new offspring.
It also calculates health as an additional feature.
*/
void ciftlesme(int a){
	int saglik = 0,rastgele;
	for (b = 0;b < G_S;b++){
		rastgele = rand() % 100 + 1;
		if (rastgele <= 45){
			Kabile[a][b] = baba[b];
		}
		else if (rastgele > 45 && rastgele <= 90){
			Kabile[a][b] = anne[b];
		}
		else if (rastgele > 90 ){
			Kabile[a][b] = HAVUZ[rand() % 52];
		}
		//check health
		if(Kabile[a][b] == Kalem[b]){
			saglik++;
		}
	}
	KabileSaglik[a] = saglik;
}

/*
Sort function:
Ranks individuals in the tribe from oldest to youngest according to their health information in TribeHealth
*/
void sirala(){
	int itemp;
	char ctemp[G_S+1];
	for (x = 0; x < B_S;x++){
		for (y = 0; y < B_S;y++){
			if (KabileSaglik[y] < KabileSaglik[x] ){
				itemp = KabileSaglik[x];
				KabileSaglik[x] = KabileSaglik[y];
				KabileSaglik[y] = itemp;

				strcpy(ctemp,Kabile[x]);
				strcpy(Kabile[x],Kabile[y]);
				strcpy(Kabile[y],ctemp);
			}
		}
	}
}

/*
Control function :
Keeps the While loop spinning until the Pen gene is found.
Checks health information in TribeHealth
*/
int kontrol(){
	for (x = 0;x<B_S;x++){
		if (KabileSaglik[x] == G_S){
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));

	for (a = 0;a < B_S;a++){
		ciftlesme(a);
	}
	sirala();

	int rast1,rast2,Nesil = 1;
	while (kontrol()){
		for (x = 0;x<SBS;x++){
			strcpy(KabileYedek[x],Kabile[x]);
		}

		for (x = 0;x < B_S;x++){
			rast1 = 0;
			rast2 = 0;
			while (rast1 == rast2){
				rast1 = rand() %SBS;
				rast2 = rand() %SBS;
			}
			strcpy(baba,KabileYedek[rast1]);
			strcpy(anne,KabileYedek[rast2]);
			ciftlesme(x);
		}
		Nesil += 1;
		sirala();

		//console output
		printf("Nesil %i:\n",Nesil);
		for (x = 0;x < B_S;x++){
			printf("%s ",Kabile[x]);
		}
		printf("\n---\n");

	}

	printf("\n  ___\n (._.)\n  <|> After %d generations, %s gene found \n _/\\_",Nesil,Kalem);

	return 0;
}

extern int min;
extern int max;
extern int dft(int *, int );
extern int TabSig[];

//Pour chaque valeur de k (de fréquence, plus ou moins) on va stocker la dft correspondante
//Chaque résultat sera la dft complète M2 = 
int dft_res[64];
int main(void)
{
	for (int i=0; i<64 ; i++) {
			//On effectue la dft du signal pour chaque valeur de fréquence
			dft_res[i] = dft(TabSig,i);
	}

while	(1) {}
}

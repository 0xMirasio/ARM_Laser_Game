extern int min;
extern int max;
extern int dft(int *, int );
extern int TabSig[];

//Pour chaque valeur de k (de fr�quence, plus ou moins) on va stocker la dft correspondante
//Chaque r�sultat sera la dft compl�te M2 = 
int dft_res[64];
int main(void)
{
	for (int i=0; i<64 ; i++) {
			//On effectue la dft du signal pour chaque valeur de fr�quence
			dft_res[i] = dft(TabSig,i);
	}

while	(1) {}
}

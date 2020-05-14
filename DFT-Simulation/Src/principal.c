

extern int min;
extern int max;
extern int dft(int *, int );
extern int TabSig[];

int dft_res[64];
int main(void)
{
	for (int i=0; i<64 ; i++) {
			dft_res[i] = dft(TabSig,i);
	}

while	(1)
	{
	}
}

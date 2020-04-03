
extern int min;
extern int max;
extern int dft(int, int *);
extern int TabSig[];

int dft_res = 0;
int re[64];
int main(void)
{

	int k = 1;
	for (int i=0; i < 64 ; i++) {
			re[i] = dft(i, TabSig);
	}
	dft_res = dft(k, TabSig);
while	(1)
	{
	}
}

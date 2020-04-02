//Signal carré


//Calcul trigo
extern void test_trigo(int, int *);

int main() {
	int S;
	for (int i=0; i< 64; i++) {
		test_trigo(i, &S);
	}
}
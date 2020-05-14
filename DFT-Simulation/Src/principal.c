//Signal carré


//Calcul trigo
extern void test_trigo(int, int *);
int S;
int main() {

	for (int i=0; i< 64; i++) {
		test_trigo(i, &S);
	}
}

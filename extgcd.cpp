int extgcd(int a, int b) {
	int aa = 1, ab = 0, ba = 0, bb = 1;
	while (b != 0) {
		int d = a / b;
		a %= b;
		aa -= ba * d;
		ab -= bb * d;
		swap(aa, ba);
		swap(ab, bb);
		swap(a, b);
	}
 
	return aa;
}

char* tostr(int A) {
	if (A != 0)
		return "TRUE";
	return "FALSE";
}

void print(int I) {
	WriteLine(tostr(I));
}

void Main() {
	for (int i = 0; i < 3; i++)
		print(i);

	WriteLine("Hello World!");
}
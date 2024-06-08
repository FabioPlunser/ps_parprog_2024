#include <stdio.h>
#include <stdlib.h>

#define N 10

void a(unsigned c1) {
	unsigned c2 = 32 * c1;
	printf("a): %u\n", c2);
}

void a_solution(unsigned c1) {
	unsigned c2 = c1 << 5;
	printf("as): %u\n", c2);
}

void b(unsigned c1) {
	unsigned c2 = 15 * c1;
	printf("b): %u\n", c2);
}

void b_solution(unsigned c1) {
	unsigned c2 = (c1 << 4) - c1;
	printf("bs): %u\n", c2);
}

void c(unsigned c1) {
	unsigned c2 = 96 * c1;
	printf("c): %u\n", c2);
}

void c_solution(unsigned c1) {
	// unsigned c2 = (c1 << 5) + (c1 << 6); // c1 * 32 + c1 * 64 my solution
	unsigned c2 = (c1 * 3) << 5; // c1 * 3 * 32 the solution the compiler uses
	printf("cs): %u\n", c2);
}

void d(unsigned c1) {
	unsigned c2 = 0.125 * c1;
	printf("d): %u\n", c2);
}

void d_solution(unsigned c1) {
	unsigned c2 = c1 >> 3;
	printf("ds): %u\n", c2);
}

void e(unsigned* a) {
	unsigned sum_fifth = 0;
	for(int i = 0; i < N / 5; ++i) {
		sum_fifth += a[5 * i];
	}
	printf("e): %u\n", sum_fifth);
}

void e_solution(unsigned* a) {
	unsigned sum_fifth = 0;

	for(int i = 0; i < N; i += 5) {
		sum_fifth += a[i];
	}
	printf("es): %u\n", sum_fifth);
}

void f(double* a) {
	for(int i = 0; i < N; ++i) {
		a[i] += i / 5.3;
	}
	printf("f):");
	for(int i = 0; i < N; ++i) {
		printf("%lf, ", a[i]);
	}
	printf("\n");
}

void f_solution(double* a) {
	double factor = 1 / 5.3;
	for(int i = 0; i < N; ++i) {
		a[i] += i * factor;
	}
	printf("fs):");
	for(int i = 0; i < N; ++i) {
		printf("%lf, ", a[i]);
	}
	printf("\n");
}

void g(float c1) {
	float c2 = -1 * c1;
	printf("g): %f\n", c2);
}

void g_solution(float c1) {
	//*(int*)&c1 ^= (1 << 31); // Flip the sign bit not save
	// float c2 = c1;
	float c2 = -c1; // save way to flip the sign bit, let the compiler do the work
	printf("gs): %f\n", c2);
}

int main(void) {
	unsigned c1 = 100;
	a(c1);
	a_solution(c1);
	b(c1);
	b_solution(c1);
	c(c1);
	c_solution(c1);
	d(c1);
	d_solution(c1);

	unsigned a[N];
	for(int i = 0; i < N; ++i) {
		a[i] = i;
	}
	e(a);
	for(int i = 0; i < N; i++) {
		a[i] = i;
	}
	e_solution(a);

	double b[N];
	for(int i = 0; i < N; ++i) {
		b[i] = i;
	}
	f(b);
	for(int i = 0; i < N; i++) {
		b[i] = i;
	}
	f_solution(b);

	float cf1 = 5;
	g(cf1);
	g_solution(cf1);

	return 0;
}

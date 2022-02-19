#include<stdio.h>
#include <iostream>
#include<stdlib.h>
#include<math.h>
#include <chrono>
#include <thread>
#include <ctime>

# define M_PI 3.14159265358979323846 /* pi, #include <math.h> */

using namespace std;

//подынтегральная функция
double my_fun(double x)
{
	return 4 / ((1 + x * x) * (1 + x * x));
}

//метод Симпсона с отключением векторизации
double pragma_no_vector_simpson(int n)
{
	double left = -1;
	double right = 1;
	double sum = 0;

	double step = (right - left) / n;
	//отключение векторизации
#pragma loop(no_vector)
	for (int i = 0; i < n; i++) {
		const double x1 = left + i * step;
		const double x2 = left + (i + 1)*step;
		sum += (x2 - x1) / 6.0*(my_fun(x1) + 4.0*my_fun(0.5*(x1 + x2)) + my_fun(x2));
	}
	printf("Значение методом Симпсона : %.15f | Разбиение n = : %d\n", sum, n);
	return sum;
}

int main()
{
	using namespace std::chrono;
	using namespace std;
	setlocale(LC_ALL, "Russian");

	for (int i = 100; i <= 1000000; i = i * 10)
	{
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		double trap = pragma_no_vector_simpson(i);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> duration = (t2 - t1);
		cout << "Время работы : " << duration.count() << " seconds\n" << endl;
	}
	return 0;
}

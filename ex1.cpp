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

double reshenie_analitic()
{	
	double a = 0;
	double b = 1;
	double area = 2 * ((2 * atan(b)) + (2 * b) / (1 + b * b)) - ((2 * atan(a)) + (2 * a) / (1 + a * a));
	printf("Аналитическое значение интеграла : %.15f\n", area);
	return area;
}

//метод Симпсона
double simpson(int n)
{	
	double left		= -1; 
	double right	= 1;  
	double sum		= 0;

	double step = (right - left) / n;
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
		double trap = simpson(i);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> duration = (t2 - t1);
		cout <<  "Время работы : " << duration.count() << " seconds\n" << endl;
	}	

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	reshenie_analitic();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> duration = (t2 - t1);
	cout << "Время работы : " << duration.count() << " seconds\n" << endl;

	return 0;
}
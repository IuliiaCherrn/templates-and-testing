#include <iostream>
#include <cassert>
#include "Treasure.hpp"

using namespace std;

using yc::Mat22d;
using yc::Vec2d;

int main()
{
	setlocale(LC_ALL, "Rus");

	cout << "=== Test 1 ===" << endl;
	{
		Mat22d A({ {
			 {1,2},
			 {3,4}
		} });

		Vec2d X({ {
			{1},
			{1}
		} });

		auto B = A * X;
		cout << B;
	}
	cout << "Умножение матриц выполнено!" << endl;

	

	cout << "=== Test 2 ===" << endl;
	{
		Mat22d A({ {
			 {1,1},
		 {4,3}
		} });


		auto B = A.inverse();
		cout << B;
	}
	cout << "Обратная матрица найдена!" << endl;


	cout << "=== Test 3 ===" << endl;
	{

		yc::Matrix<double, 3, 3> A({ {
				 {1, 0, 1},
			 {8, 1, 5},
			{0, 0, 1}
			} });


		auto B = A.MatrixTransposition();
		cout << B;
	}
	cout << "Транспонированная матрица найдена!" << endl;


	cout << "=== Test 4 ===" << endl;
	{
		Mat22d A({ {
			 {1,1},
			 {1,1}
		} });

		Mat22d B({ {
			 {1,1},
			 {1,1}
		} });


		auto Z = A + B;
		cout << Z;
	}
	cout << "Сложение выполнено!" << endl;


	cout << "=== Test 5 ===" << endl;
	{
		Mat22d A({ {
			 {1,1},
			 {1,1}
		} });

		Mat22d B({ {
			 {1,1},
			 {1,1}
		} });


		auto Z = A - B;
		cout << Z;
	}
	cout << "Вычитание выполнено!" << endl;


	cout << "=== Test 6 ===" << endl;
	{
		Mat22d A({ {
			 {1,7},
			 {6,-2}
		} });

		auto Z = A.determinant();
		cout << Z << endl;
	}
	cout << "Определитель найден!" << endl;


	return 0;
}

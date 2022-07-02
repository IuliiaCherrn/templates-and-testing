#pragma once
#include <iostream>

using namespace std;

namespace yc
{
	// MY_DEBUG 
	//#define MY_DEBUG 

	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	template<typename T, int N, int M>
	class Matrix
	{
	public:
		Matrix()
		{
#ifdef MY_DEBUG
			cout << "Constructor" << endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = 0;
		}

		Matrix(const T mas[N][M])
		{
#ifdef MY_DEBUG
			cout << "Constructor" << endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas[i][j];
		}

		Matrix(const MasWrapper<T, N, M>& mas)
		{
#ifdef MY_DEBUG
			cout << "Constructor" << endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas.mas[i][j];
		}

		Matrix(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "Copy constructor" << endl;
#endif

			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];
		}

		int getN() const { return m_n; }
		int getM() const { return m_m; }
		T get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }

		template<typename T, int N, int M>
		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "Operator =" << endl;
#endif

			m_n = mat.getN();
			m_m = mat.getM();

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.get(i, j);

			return *this;
		}
		template<typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "operator+" << endl;
#endif
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
			return tmp;
		}


		template<typename T, int N, int M>
		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "operator-" << endl;
#endif
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
			return tmp;
		}
  
		template<typename T, int N, int M>
		Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "operator*" << endl;
#endif
			Matrix<T, N, M> tmp;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < mat.getM(); j++)
				{
					int sum = 0;
					for (int k = 0; k < m_m; k++)
						sum += m_mat[i][k] * mat.get(i, j);
					tmp.set(i, j, sum);
				}

			return tmp;
		}

		Matrix<T, N, M> inverse() 
		{
#ifdef MY_DEBUG
			cout << "Inverse matrix" << endl;
#endif
			if ((m_n == 2 and m_m == 2) or (m_n == 3 and m_m == 3)) 
			{
				if (m_n == 2 and m_m == 2) 
				{
					Matrix<T, N, M> tmp;

					T det;
					det = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];

					tmp.m_mat[0][0] = m_mat[1][1] / det;
					tmp.m_mat[0][1] = (-m_mat[0][1]) / det;
					tmp.m_mat[1][0] = (-m_mat[1][0]) / det;
					tmp.m_mat[1][1] = m_mat[0][0] / det;
					return tmp;
				}
				else 
				{
					Matrix<T, N, M> tmp;
					T det;
					det = m_mat[0][0] * m_mat[1][1] * m_mat[2][2] + 
						m_mat[1][0] * m_mat[2][1] * m_mat[0][2] + 
						m_mat[0][1] * m_mat[1][2] * m_mat[2][0] -
						m_mat[0][2] * m_mat[1][1] * m_mat[2][0] - 
						m_mat[0][0] * m_mat[1][2] * m_mat[2][1] - 
						m_mat[0][1] * m_mat[1][0] * m_mat[2][2];


					tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / det;
					tmp.m_mat[1][0] = (-m_mat[1][0] * m_mat[2][2] + m_mat[2][0] * m_mat[1][2]) / det;
					tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / det;
					tmp.m_mat[0][1] = (-m_mat[0][1] * m_mat[2][2] + m_mat[2][1] * m_mat[0][2]) / det;
					tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / det;
					tmp.m_mat[2][1] = (-m_mat[0][0] * m_mat[2][1] + m_mat[2][0] * m_mat[0][1]) / det;
					tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / det;
					tmp.m_mat[1][2] = (-m_mat[0][0] * m_mat[1][2] + m_mat[1][0] * m_mat[0][2]) / det;
					tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / det;

					return tmp;
				}
			}
			else {
				Err();
			}
		}

		Matrix<T, N, M> MatrixTransposition()
		{
#ifdef MY_DEBUG
			cout << Ttransposed matrix" << endl;
#endif
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[j][i] = m_mat[i][j];
			return tmp;
		}

		void Err() {
			cout << "Error" << endl;
		}

		T determinant() 
		{
#ifdef MY_DEBUG
			cout << "determinant" << endl;
#endif
			if ((m_n == 2 and m_m == 2) or (m_n == 3 and m_m == 3))
			{
				if (m_n == 2 and m_m == 2) 
				{
					T tmp;
					tmp = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
					return tmp;
				}
				else 
				{
					T tmp;
					tmp = m_mat[0][0] * m_mat[1][1] * m_mat[2][2]
						+ m_mat[1][0] * m_mat[2][1] * m_mat[0][2]
						+ m_mat[0][1] * m_mat[1][2] * m_mat[2][0]
						- m_mat[0][2] * m_mat[1][1] * m_mat[2][0]
						- m_mat[0][0] * m_mat[1][2] * m_mat[2][1] 
						- m_mat[0][1] * m_mat[1][0] * m_mat[2][2];
					return tmp;
				}
			}
			else 
			{
				Err();
			}
		}

		~Matrix()
		{
#ifdef MY_DEBUG
			scout << "Destructor" << endl;
#endif
		}

		template<typename T, int N, int M>
		friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);

		template<typename T, int N, int M>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);

	private:
		int m_n, m_m;
		T m_mat[N][M];
	};

  
	template<typename T, int N, int M>
	istream& operator>>(istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;
	}

	template<typename T, int N, int M>
	ostream& operator<<(ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat.m_n << "x" << mat.m_m << endl;
		for (int i = 0; i < mat.m_n; i++) 
		{
			for (int j = 0; j < mat.m_m; j++)
				out << mat.m_mat[i][j] << " ";
			out << endl;
		}
		return out;
	}

	using Vec2i = Matrix<int, 2, 1>;	 
	using Vec2d = Matrix<double, 2, 1>;
	using Mat22i = Matrix<int, 2, 2>;
	using Mat22d = Matrix<double, 2, 2>;
}

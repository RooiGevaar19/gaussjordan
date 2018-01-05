#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

int tries = 10;
int max_grade = 1000;

template <typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b)
{
    assert(a.size() == b.size());

    vector<T> result;
    result.reserve(a.size());

    transform(a.begin(), a.end(), b.begin(),
                   back_inserter(result), plus<T>());
    return result;
}

template <typename T> class MyMatrix {
private:
    vector<vector<T> > matrix;
    unsigned rows;
    unsigned cols;

    int abs(int x) {
        return (x >= 0) ? x : -x;
    }

    long int abs(long int x) {
        return (x >= 0) ? x : -x;
    }

    long long int abs(long long int x) {
        return (x >= 0) ? x : -x;
    }

    float abs(float x) {
        return (x >= 0) ? x : -x;
    }

    double abs(double x) {
        return (x >= 0) ? x : -x;
    }

    public:
        // konstruktory
        MyMatrix(unsigned wiersz, unsigned kolumna, const T& x) {
            matrix.resize(wiersz);
            for (unsigned i=0; i<matrix.size(); i++) {
                matrix[i].resize(kolumna, x);
            }
            rows = wiersz;
            cols = kolumna;
        }
        MyMatrix(const MyMatrix<T>& pom) {
            matrix = pom.matrix;
            rows = pom.getRowCount();
            cols = pom.getColCount();
        }

        // destruktory
        virtual ~MyMatrix() {
            // nic XD
        }

        // przypisanie
        MyMatrix<T>& operator=(const MyMatrix<T>& pom) {
            if (&pom == this) return *this;
            unsigned new_rows = pom.getRowCount();
            unsigned new_cols = pom.getColCount();

            matrix.resize(new_rows);
            for (unsigned i=0; i<matrix.size(); i++) {
                matrix[i].resize(new_cols);
            }

            for (unsigned i=0; i<new_rows; i++) {
                for (unsigned j=0; j<new_cols; j++) {
                    matrix[i][j] = pom(i, j);
                }
            }
            rows = new_rows;
            cols = new_cols;
            return *this;
        }

        // dodawanie macierzy
        MyMatrix<T> operator+(const MyMatrix<T>& pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    result(i,j) = this->matrix[i][j] + pom(i,j);
                }
            }
            return result;
        }
        MyMatrix<T>& operator+=(const MyMatrix<T>& pom) {
            unsigned rows = pom.getRowCount();
            unsigned cols = pom.getColCount();
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    this->matrix[i][j] += pom(i,j);
                }
            }
            return *this;
        }
        MyMatrix<T> operator-(const MyMatrix<T>& pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    result(i,j) = this->matrix[i][j] - pom(i,j);
                }
            }
            return result;
        }
        MyMatrix<T>& operator-=(const MyMatrix<T>& pom) {
            unsigned rows = pom.getRowCount();
            unsigned cols = pom.getColCount();
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    this->matrix[i][j] -= pom(i,j);
                }
            }
            return *this;
        }
        MyMatrix<T> operator*(const MyMatrix<T>& pom) {
            unsigned rows = pom.getRowCount();
            unsigned cols = pom.getColCount();
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    for (unsigned k=0; k<rows; k++) {
                        result(i,j) += this->matrix[i][k] * pom(k,j);
                    }
                }
            }
            return result;
        }
        MyMatrix<T>& operator*=(const MyMatrix<T>& pom) {
            MyMatrix result = (*this) * pom;
            (*this) = result;
            return *this;
        }
        MyMatrix<T> transpose() {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    result(i,j) = this->matrix[j][i];
                }
            }
            return result;
        }

        // skalary
        MyMatrix<T> operator+(const T& pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i = 0; i < rows; i++) {
                for (unsigned j = 0; j < cols; j++) {
                    result(i,j) = this->matrix[i][j] + pom;
                }
            }
            return result;
        }
        MyMatrix<T> operator-(const T& pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i = 0; i < rows; i++) {
                for (unsigned j = 0; j < cols; j++) {
                    result(i,j) = this->matrix[i][j] - pom;
                }
            }
            return result;
        }
        MyMatrix<T> operator*(const T& pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i = 0; i < rows; i++) {
                for (unsigned j = 0; j < cols; j++) {
                    result(i,j) = this->matrix[i][j] * pom;
                }
            }
            return result;
        }
        MyMatrix<T> operator/(const T& pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i = 0; i < rows; i++) {
                for (unsigned j = 0; j < cols; j++) {
                    result(i,j) = this->matrix[i][j] / pom;
                }
            }
            return result;
        }

        // mnożenie macierzy przez wektor
        vector<T> operator*(const vector<T> pom) {
            vector<T> result(pom.size(), 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    result[i] += this->matrix[i][j] * pom[j];
                }
            }
            return result;
        }
        vector<T> diagonalVector() {
            vector<T> result(rows, 0.0);
            for (unsigned i=0; i<rows; i++) {
                result[i] = this->matrix[i][i];
            }
            return result;
        }

        // dostań się do poszczególnych elementóœ
        T& operator()(const unsigned& row, const unsigned& col) {
            return this->matrix[row][col];
        }
        const T& operator()(const unsigned& row, const unsigned& col) const {
            return this->matrix[row][col];
        }

        // gettery i settery do kolumn
        void setAt(unsigned row, unsigned col, const T& x) {
            this->matrix[row][col] = x;
        }

        T& getAt(unsigned row, unsigned col) {
            return this->matrix[row][col];
        }

        // zwróć liczbę wierszy/kolumn
        unsigned getRowCount() const {
            return this->rows;
        }
        unsigned getColCount() const {
            return this->cols;
        }

        // wyświetl
        void display() {
            for (int i = 0; i < getRowCount(); i++) {
                cout << "[ ";
                for (int j=0; j < getColCount(); j++) {
                    //cout << " " << getAt(i,j);
                    cout << setw(12) << getAt(i,j);
                }
                cout << " ]" << endl;
            }
        }

        // metoda eliminacji Gaussa bez wyboru elementu podstawowego
        vector<T> solveGauss() {
            int n = getRowCount();
            for (int i = 0; i < n; i++) {
                // wyprowadź zera przed obecnym wierszem
                for (int k = i+1; k < n; k++) {
                    T c = -matrix[k][i] / matrix[i][i];
                    for (int j = i; j < n+1; j++) {
                        if (i == j) {
                            matrix[k][j] = 0;
                        } else {
                            matrix[k][j] += c * matrix[i][j];
                        }
                    }
                }
            }
            // rozwiąż Ax = B za pomocą powstałej macierzy trójkątnej
            vector<T> x(n);
            for (int i=n-1; i>=0; i--) {
                x[i] = matrix[i][n] / matrix[i][i];
                for (int k=i-1;k>=0; k--) {
                    matrix[k][n] -= matrix[k][i] * x[i];
                }
            }
            return x;
        }

        // metoda eliminacji Gaussa z częściowym wyborem
        vector<T> solveGaussPartial() {
            int n = getRowCount();
            for (int i = 0; i < n; i++) {
                // znajdź wiersz z maksymalnym elementem
                T maxEl = abs(matrix[i][i]);
                int maxRow = i;
                for (int k = i+1; k < n; k++) {
                    if (abs(matrix[k][i]) > maxEl) {
                        maxEl = abs(matrix[k][i]);
                        maxRow = k;
                    }
                }
                // zamień maksymalny wiersz z obecnym
                for (int k = i; k < n+1; k++) {
                    T pom = matrix[maxRow][k];
                    matrix[maxRow][k] = matrix[i][k];
                    matrix[i][k] = pom;
                }
                // wyprowadź zera przed obecnym wierszem
                for (int k = i+1; k < n; k++) {
                    T c = -matrix[k][i] / matrix[i][i];
                    for (int j = i; j < n+1; j++) {
                        if (i == j) {
                            matrix[k][j] = 0;
                        } else {
                            matrix[k][j] += c * matrix[i][j];
                        }
                    }
                }
            }
            // rozwiąż Ax = B za pomocą powstałej macierzy trójkątnej
            vector<T> x(n);
            for (int i=n-1; i>=0; i--) {
                x[i] = matrix[i][n] / matrix[i][i];
                for (int k=i-1;k>=0; k--) {
                    matrix[k][n] -= matrix[k][i] * x[i];
                }
            }
            return x;
        }

        // metoda eliminacji Gaussa z pełnym wyborem elementu
        vector<T> solveGaussFull() {
            int n = getRowCount();
            for (int i = 0; i < n; i++) {
                // znajdź wiersz z maksymalnym elementem
                T maxEl = abs(matrix[i][i]);
                int maxRow = i;
                int maxCol = i;
                for (int k = i+1; k < n; k++) {
                    if (abs(matrix[k][i]) > maxEl) {
                        maxEl = abs(matrix[k][i]);
                        maxRow = k;
                        maxCol = i;
                    }
                }
                // zamień maksymalny wiersz z obecnym
                for (int k = i; k < n+1; k++) {
                    T pom = matrix[maxRow][k];
                    matrix[maxRow][k] = matrix[i][k];
                    matrix[i][k] = pom;
                }
                // zamień maksymalną kolumnę z obecną
                for (int k = i; k < n+1; k++) {
                  T pom = matrix[k][maxCol];
                  matrix[k][maxCol] = matrix[k][i];
                  matrix[k][i] = pom;
                }
                // wyprowadź zera przed obecnym wierszem
                for (int k = i+1; k < n; k++) {
                    T c = -matrix[k][i] / matrix[i][i];
                    for (int j = i; j < n+1; j++) {
                        if (i == j) {
                            matrix[k][j] = 0;
                        } else {
                            matrix[k][j] += c * matrix[i][j];
                        }
                    }
                }
            }
            // rozwiąż Ax = B za pomocą powstałej macierzy trójkątnej
            vector<T> x(n);
            for (int i=n-1; i>=0; i--) {
                x[i] = matrix[i][n] / matrix[i][i];
                for (int k=i-1;k>=0; k--) {
                    matrix[k][n] -= matrix[k][i] * x[i];
                }
            }
            return x;
        }

        // odwrocenie macierzy
        //MyMatrix<T>& invert() {
        //    MyMatrix<T> inverse_matrix (getRowCount(), getColCount(), 0.0);
        //    MyMatrix<T> shit (getRowCount(), getColCount(), 0.0);
        //    T det = determinant();
        //    if (det == 0) {
        //        return shit;
        //    } else {
        //        T num= 1 / det;
        //        MyMatrix<T> m_Transpose (getRowCount(), getColCount(), 0.0);
        //        m_Transpose = transpose();
        //        for (int i = 1; i <= getRowCount(); i++) {
        //            for (int j = 1; j <= getColCount(); j++) {
        //                inverse_matrix.setAt(i,j, num*m_Transpose.getAt(i,j));
        //            }
        //        }
        //    }
        //    return inverse_matrix;
        //}

        MyMatrix<T> invert_triangular() {
            MyMatrix<T> inverse_matrix (getRowCount(), getColCount(), 0.0);
            MyMatrix<T> shit (getRowCount(), getColCount(), 0.0);
            T det = det_triangular();
            if (det == 0.0) {
                return shit;
            } else {

                T num= 1 / det;

                MyMatrix<T> m_Transpose (getColCount(), getRowCount(), 0.0);

                m_Transpose = transpose();

                for (int i = 0; i < getRowCount(); i++) {
                    for (int j = 0; j < getColCount(); j++) {

                        inverse_matrix.setAt(i,j, num*m_Transpose.getAt(i,j));
                    }
                }
            }
            return inverse_matrix;
        }

        //MyMatrix<T> minor(int m) {
        //    MyMatrix<T> szlug (getRowCount()-1, getColCount()-1, 0.0);
        //    int row = 0, col = 0;
        //    for (int j = 1; j < getRowCount(); j++) {
		//		for (int k = 0; k < getColCount(); k++) {
		//			if (k < m) {
		//				szlug.setAt(j - 1, k, matrix[j][k]);
		//			} else if (k > m) {
		//				szlug.setAt(j - 1, k - 1, matrix[j][k]);
		//			}
		//		}
        //    }
        //    return szlug;
        //}
        //
        //T determinant() {
        //  T det = 0;
        //  int n = getRowCount();
        //  if (getColCount() == getRowCount()){
        //    if (getRowCount() == 1)
        //      return getAt(0,0);
        //    else if (getRowCount() == 2)
        //      return (getAt(0,0) * getAt(1,1) - getAt(0,1) * getAt(1,0));
        //    else {
        //      for (int k = 0; k < getRowCount(); k++){
        //          //MyMatrix<T> xd (getRowCount, getColCount, 0.0);
        //          //xd = minor(k);
        //        det += ((-1)^(k)) * getAt(0, k) * minor(k).determinant();
        //        //n = size;
        //      }
        //      return det;
        //    }
        //  } else {
        //    return 0.0;
        //  }
        //}
        //
        //T determinant() {
        //    int s;
        //    if (getRowCount() != getColCount()) {
        //        return 0.0;
        //    } else {
        //        switch (getRowCount()) {
        //            case 0 : return 0.0;
        //            case 1 : return getAt(0,0);
        //            case 2 : return getAt(0,0)*getAt(1,1)-getAt(1,0)*getAt(0,1);
        //            case 3 : return ((getAt(0,0)*getAt(1,1)*getAt(2,2) + getAt(0,1)*getAt(1,2)*getAt(2,0) + getAt(0,2)*getAt(1,0)*getAt(2,1))
        //                           -(getAt(2,0)*getAt(1,1)*getAt(0,2) + getAt(0,0)*getAt(2,1)*getAt(1,2) + getAt(2,2)*getAt(1,0)*getAt(0,1)));
        //            default : {
        //                s = 0;
        //                for (int col = 0; col < getColCount(); col++)
        //                {
        //                    printf("OK %i\n", col);
        //                    s += pow(-1.0, col+1.0) * getAt(0, col) * minor(col).determinant();
        //                    minor(col).display();
        //                }
        //            }
        //        }
        //    }
        //    return s;
        //}

        T det_triangular() {
            vector<T> S;
            S = diagonalVector();
            T s = 1.0;
            for (int i = 0; i < S.size(); i++) {
                s *= S[i];
            }
            return s;
        }

        vector<T> solveJacobi(int littleTim) {
            int n = getRowCount();
            // inicjalizacja macierzy z elementami przeciwnymi do macierzy A
            MyMatrix<T> L (n, n, 0.0);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i > j) {
                        L.setAt(i, j, (this->getAt(i, j))*(-1));
                    }
                }
            }
            MyMatrix<T> U (n, n, 0.0);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i < j) {
                        U.setAt(i, j, (this->getAt(i, j))*(-1));
                    }
                }
            }
            // wynieś macierz diagonalną
            MyMatrix<T> D (n, n, 0.0);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j) {
                        D.setAt(i, j, 1.0/(this->getAt(i, j)));
                    }
                }
            }
            // wynieś macierz elementów wolnych
            vector<T> B (n, 0.0);
            for (int i = 0; i < n; i++) {
                B[i] = this->matrix[i][n];
            }
            // wynieś macierz Tj
            MyMatrix<T> Tj (n, n, 0.0);
            Tj = D * (L + U);

            // wynieś wektor Fj
            vector<T> Fj (n, 0.0);
            for (int i = 0; i < n; i++){
              Fj[i] = (D.getAt(i,i)) * B[i];
            }

            // utwórz wektor rozwiązania
            vector<T> X (n, 0.0);

            // iteruj
            for (int Timmy = 0; Timmy < littleTim; Timmy++) {
                X = Tj*X + Fj;
            }
            return X;
        }

        vector<T> solveGaussSeidel(int littleTim){
          int n = getRowCount();
          // inicjalizacja macierzy z elementami przeciwnymi do macierzy A
          MyMatrix<T> L (n, n, 0.0);
          for (int i = 0; i < n; i++) {
              for (int j = 0; j < n; j++) {
                  if (i > j) {
                      L.setAt(i, j, (this->getAt(i, j))*(-1));
                  }
              }
          }
          MyMatrix<T> U (n, n, 0.0);
          for (int i = 0; i < n; i++) {
              for (int j = 0; j < n; j++) {
                  if (i < j) {
                      U.setAt(i, j, (this->getAt(i, j))*(-1));
                  }
              }
          }
          // wynieś macierz diagonalną
          MyMatrix<T> D (n, n, 0.0);
          for (int i = 0; i < n; i++) {
              for (int j = 0; j < n; j++) {
                  if (i == j) {
                      D.setAt(i, j, 1.0/(this->getAt(i, j)));
                  }
              }
          }
          // wynieś macierz elementów wolnych
          vector<T> B (n, 0.0);
          for (int i = 0; i < n; i++) {
              B[i] = this->matrix[i][n];
          }
          // wynieś macierz Tj
          MyMatrix<T> Tj (n, n, 0.0);
          Tj = D * (L + U);

          // wynieś wektor Fj
          vector<T> Fj (n, 0.0);
          for (int i = 0; i < n; i++){
            Fj[i] = (D.getAt(i,i)) * B[i];
          }

          // utwórz wektor rozwiązania
          vector<T> X (n, 0.0);
          vector<T> Y (n, 0.0);

          // iteruj
          for (int Timmy = 0; Timmy < littleTim; Timmy++) {
              for (int i = 0; i < n; i++){
                Y[i] = Fj[i];
                for (int j = 0; j < n; j++){
                  if (j == i)
                    continue;
                  Y[i] = Y[i] + ((Tj.getAt(i,j)) * X[j]);
                  X[i] = Y[i];
                }
                //printf("x%d = %f\t", i+1, Y[i]);
              }
              //cout << "\n";
          }
          return X;
        }

        // ładowanie z pliku
        void loadFromFile(string fileName) {
            int x, y;
            ifstream in(fileName);
            if (!in) {
                cout << "Cannot open file.\n";
                return;
            } else {
                int new_rows, new_cols;
                in >> new_rows;
                in >> new_cols;
                matrix.resize(new_rows);
                for (unsigned i=0; i<matrix.size(); i++) {
                    matrix[i].resize(new_cols);
                }
                for (unsigned i=0; i<new_rows; i++) {
                    for (unsigned j=0; j<new_cols; j++) {
                        in >> matrix[i][j];
                    }
                }
                rows = new_rows;
                cols = new_cols;
                in.close();
            }
        }
};

int main(int argc, char** argv) {
    MyMatrix<double> M (1, 2, 0.0);
    M.loadFromFile(argv[1]);
    vector<double> res;
    res = M.solveGaussPartial();
    printf("%.12lf\n", res[0]);
    return 0;
}

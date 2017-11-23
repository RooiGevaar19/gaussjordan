//------------------------------------------------------------------------------
// Projekt:   MyMatrix vs. Eigen - test operacji na macierzach
// Autorzy:   Paweł Lipkowski
// Data:      11/20/2017
//------------------------------------------------------------------------------
// Nagłówki i stałe
// 
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <eigen3/Eigen/Dense>
using namespace std;
using namespace Eigen;
//------------------------------------------------------------------------------
// Klasy i struktury
// 
// klasa Timer

class Timer
{
public:
    Timer() { clock_gettime(CLOCK_REALTIME, &beg_); }

    double elapsed() {
        clock_gettime(CLOCK_REALTIME, &end_);
        return end_.tv_sec - beg_.tv_sec +
            (end_.tv_nsec - beg_.tv_nsec) / 1000000000.;
    }

    void reset() { clock_gettime(CLOCK_REALTIME, &beg_); }

private:
    timespec beg_, end_;
};

double avg(double t[], int n)			// pomocniczo do uśredniania wyników
{
	double sum = 0.0;
	int i;
	for (i = 0; i < n; i++) sum += t[i];
	return sum/n;
}
// klasa MyMatrix

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

    //Fraction abs(Fraction x) {
    //    Fraction result((x.getNumerator() >= 0) ? x.getNumerator() : -(x.getNumerator()), (x.getDenominator() >= 0) ? x.getDenominator() : -(x.getDenominator()));
    //    return result;
    //}

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
        vector<T> operator*(const vector<T>& pom) {
            vector<T> result(pom.size(), 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    result[i] = this->matrix[i][j] * pom[j];
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
                    cout << setw(8) << getAt(i,j);
                }
                cout << " ]" << endl;
            }
        }

        // metoda eliminacji Gaussa
        vector<T> solveGauss() {
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
};
//------------------------------------------------------------------------------
// Funkcje pomocnicze do testów
// 
// wypełnianie tabel

void fill_random(MyMatrix<float> A, int wie, int kol) {
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            srand(time(NULL));
            float x = ((float)rand()/RAND_MAX*200.0)-100.0;
            A.setAt(i, j, x);
        }
    }
}

void fill_random(MyMatrix<double> A, int wie, int kol) {
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            srand(time(NULL));
            float x = ((double)rand()/RAND_MAX*200.0)-100.0;
            A.setAt(i, j, x);
        }
    }
}
//------------------------------------------------------------------------------
// Moduł testowy
// 
// Porównanie 1
// wynik A*X

void test1(int grade, int tries) {
    printf("%i\t", grade);
    double times[tries];
    // MyMatrix-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<float> A(grade, grade, 0.0);
        MyMatrix<float> B(grade, 1, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, 1);
        Timer t;
        MyMatrix<float> x (grade, 1, 0.0);
        t.reset();
        x = A * B;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // MyMatrix-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<double> A(grade, grade, 0.0);
        MyMatrix<double> B(grade, 1, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, 1);
        Timer t;
        MyMatrix<double> x (grade, 1, 0.0);
        t.reset();
        x = A * B;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // MyMatrix-Frac
    //Fraction zero (0.0);
    //for (int attempt = 0; attempt < tries; attempt++) {
    //    MyMatrix<Fraction> A(grade, grade, zero);
    //    MyMatrix<Fraction> B(grade, 1, zero);
    //    fill_random(A, grade, grade);
    //    fill_random(B, grade, 1);
    //    Timer t;
    //    MyMatrix<Fraction> x (grade, 1, zero);
    //    t.reset();
    //    x = A * B;
    //    times[attempt] = t.elapsed();
    //}
    //printf("%.10lf\t", avg(times, tries));
    // Eigen-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXf A(grade, grade);
        A = MatrixXf::Random(grade, grade) * 100.0;
        MatrixXf B(grade, 1);
        B = MatrixXf::Random(grade, 1) * 100.0;
        Timer t;
        MatrixXf x(grade, 1);
        t.reset();
        x = A * B;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // Eigen-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXd A(grade, grade);
        A = MatrixXd::Random(grade, grade) * 100.0;
        MatrixXd B(grade, 1);
        B = MatrixXd::Random(grade, 1) * 100.0;
        Timer t;
        MatrixXd x(grade, 1);
        t.reset();
        x = A * B;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf", avg(times, tries));
    printf("\n");
}
// Porównanie 2
// wynik (A+B+C)*X

void test2(int grade, int tries) {
    printf("%i\t", grade);
    double times[tries];
    // MyMatrix-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<float> A(grade, grade, 0.0);
        MyMatrix<float> B(grade, grade, 0.0);
        MyMatrix<float> C(grade, grade, 0.0);
        MyMatrix<float> X(grade, 1, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, grade);
        fill_random(C, grade, grade);
        fill_random(X, grade, 1);
        Timer t;
        MyMatrix<float> x (grade, 1, 0.0);
        t.reset();
        x = (A + B + C) * X;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // MyMatrix-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<double> A(grade, grade, 0.0);
        MyMatrix<double> B(grade, grade, 0.0);
        MyMatrix<double> C(grade, grade, 0.0);
        MyMatrix<double> X(grade, 1, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, grade);
        fill_random(C, grade, grade);
        fill_random(X, grade, 1);
        Timer t;
        MyMatrix<double> x (grade, 1, 0.0);
        t.reset();
        x = (A + B + C) * X;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // Eigen-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXf A(grade, grade);
        A = MatrixXf::Random(grade, grade) * 100.0;
        MatrixXf B(grade, grade);
        B = MatrixXf::Random(grade, grade) * 100.0;
        MatrixXf C(grade, grade);
        C = MatrixXf::Random(grade, grade) * 100.0;
        MatrixXf X(grade, 1);
        X = MatrixXf::Random(grade, 1) * 100.0;
        Timer t;
        MatrixXf x(grade, 1);
        t.reset();
        x = (A + B + C) * X;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // Eigen-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXd A(grade, grade);
        A = MatrixXd::Random(grade, grade) * 100.0;
        MatrixXd B(grade, grade);
        B = MatrixXd::Random(grade, grade) * 100.0;
        MatrixXd C(grade, grade);
        C = MatrixXd::Random(grade, grade) * 100.0;
        MatrixXd X(grade, 1);
        X = MatrixXd::Random(grade, 1) * 100.0;
        Timer t;
        MatrixXd x(grade, 1);
        t.reset();
        x = (A + B + C) * X;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf", avg(times, tries));
    printf("\n");
}
// Porównanie 3
// wynik A*(B*C)


void test3(int grade, int tries) {
    printf("%i\t", grade);
    double times[tries];
    // MyMatrix-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<float> A(grade, grade, 0.0);
        MyMatrix<float> B(grade, grade, 0.0);
        MyMatrix<float> C(grade, grade, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, grade);
        fill_random(C, grade, grade);
        Timer t;
        MyMatrix<float> x (grade, grade, 0.0);
        t.reset();
        x = A * (B * C);
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // MyMatrix-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<double> A(grade, grade, 0.0);
        MyMatrix<double> B(grade, grade, 0.0);
        MyMatrix<double> C(grade, grade, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, grade);
        fill_random(C, grade, grade);
        Timer t;
        MyMatrix<double> x (grade, grade, 0.0);
        t.reset();
        x = A * (B * C);
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // Eigen-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXf A(grade, grade);
        A = MatrixXf::Random(grade, grade) * 100.0;
        MatrixXf B(grade, grade);
        B = MatrixXf::Random(grade, grade) * 100.0;
        MatrixXf C(grade, grade);
        C = MatrixXf::Random(grade, grade) * 100.0;
        Timer t;
        MatrixXf x(grade, grade);
        t.reset();
        x = A * (B * C);
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // Eigen-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXd A(grade, grade);
        A = MatrixXd::Random(grade, grade) * 100.0;
        MatrixXd B(grade, grade);
        B = MatrixXd::Random(grade, grade) * 100.0;
        MatrixXd C(grade, grade);
        C = MatrixXd::Random(grade, grade) * 100.0;
        Timer t;
        MatrixXd x(grade, grade);
        t.reset();
        x = A * (B * C);
        times[attempt] = t.elapsed();
    }
    printf("%.10lf", avg(times, tries));
    printf("\n");
}
//------------------------------------------------------------------------------
// Main
// 
int main() {
    int tries = 10;
    int max_grade = 1000;
    int k = 1;
    printf("Rozmiar\tMyMatrix-Float\tMyMatrix-Double\tEigen-Float\tEigen-Double\n");
    for (int grade = 2; grade <= max_grade; grade+=k) {
        test1(grade, tries);
        if (grade % (10*k) == 0) k = 10*k;
    }
    return 0;
}
//------------------------------------------------------------------------------

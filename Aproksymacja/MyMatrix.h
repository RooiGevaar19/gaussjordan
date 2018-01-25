#ifndef MYMATRIX_H
#define MYMATRIX_H
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

vector<double> operator+(const vector<double>& a, const vector<double>& b)
{
    assert(a.size() == b.size());

    vector<double> result;
    result.reserve(a.size());

    transform(a.begin(), a.end(), b.begin(),
                   back_inserter(result), plus<double>());
    return result;
}

class MyMatrix {
private:
    vector<vector<double> > matrix;
    unsigned rows;
    unsigned cols;

    double abs(double x) {
        return (x >= 0) ? x : -x;
    }

    public:
        // konstruktory
        MyMatrix(unsigned wiersz, unsigned kolumna, const double &x) {
            matrix.resize(wiersz);
            for (unsigned i=0; i<matrix.size(); i++) {
                matrix[i].resize(kolumna, x);
            }
            rows = wiersz;
            cols = kolumna;
        }
        MyMatrix(const MyMatrix& pom) {
            matrix = pom.matrix;
            rows = pom.getRowCount();
            cols = pom.getColCount();
        }

        // destruktory
        virtual ~MyMatrix() {
            // nic XD
        }

        // przypisanie
        MyMatrix& operator=(const MyMatrix& pom) {
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
        MyMatrix operator+(const MyMatrix& pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    result(i,j) = this->matrix[i][j] + pom(i,j);
                }
            }
            return result;
        }
        MyMatrix& operator+=(const MyMatrix& pom) {
            unsigned rows = pom.getRowCount();
            unsigned cols = pom.getColCount();
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    this->matrix[i][j] += pom(i,j);
                }
            }
            return *this;
        }
        MyMatrix operator-(const MyMatrix& pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    result(i,j) = this->matrix[i][j] - pom(i,j);
                }
            }
            return result;
        }
        MyMatrix& operator-=(const MyMatrix& pom) {
            unsigned rows = pom.getRowCount();
            unsigned cols = pom.getColCount();
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    this->matrix[i][j] -= pom(i,j);
                }
            }
            return *this;
        }
        MyMatrix operator*(const MyMatrix& pom) {
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
        MyMatrix& operator*=(const MyMatrix& pom) {
            MyMatrix result = (*this) * pom;
            (*this) = result;
            return *this;
        }
        MyMatrix transpose() {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    result(i,j) = this->matrix[j][i];
                }
            }
            return result;
        }

        // skalary
        MyMatrix operator+(const double &pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i = 0; i < rows; i++) {
                for (unsigned j = 0; j < cols; j++) {
                    result(i,j) = this->matrix[i][j] + pom;
                }
            }
            return result;
        }
        MyMatrix operator-(const double &pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i = 0; i < rows; i++) {
                for (unsigned j = 0; j < cols; j++) {
                    result(i,j) = this->matrix[i][j] - pom;
                }
            }
            return result;
        }
        MyMatrix operator*(const double &pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i = 0; i < rows; i++) {
                for (unsigned j = 0; j < cols; j++) {
                    result(i,j) = this->matrix[i][j] * pom;
                }
            }
            return result;
        }
        MyMatrix operator/(const double &pom) {
            MyMatrix result(rows, cols, 0.0);
            for (unsigned i = 0; i < rows; i++) {
                for (unsigned j = 0; j < cols; j++) {
                    result(i,j) = this->matrix[i][j] / pom;
                }
            }
            return result;
        }

        // mnożenie macierzy przez wektor
        vector<double> operator*(const vector<double> pom) {
            vector<double> result(pom.size(), 0.0);
            for (unsigned i=0; i<rows; i++) {
                for (unsigned j=0; j<cols; j++) {
                    result[i] += this->matrix[i][j] * pom[j];
                }
            }
            return result;
        }
        vector<double> diagonalVector() {
            vector<double> result(rows, 0.0);
            for (unsigned i=0; i<rows; i++) {
                result[i] = this->matrix[i][i];
            }
            return result;
        }

        // dostań się do poszczególnych elementóœ
        double& operator()(const unsigned& row, const unsigned& col) {
            return this->matrix[row][col];
        }
        const double& operator()(const unsigned& row, const unsigned& col) const {
            return this->matrix[row][col];
        }

        // gettery i settery do kolumn
        void setAt(unsigned row, unsigned col, const double& x) {
            this->matrix[row][col] = x;
        }

        double& getAt(unsigned row, unsigned col) {
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

        //================== metody eliminacji
        vector<double> solveGaussPartial() {
            int n = getRowCount();
            for (int i = 0; i < n; i++) {
                // znajdź wiersz z maksymalnym elementem
                double maxEl = abs(matrix[i][i]);
                int maxRow = i;
                for (int k = i+1; k < n; k++) {
                    if (abs(matrix[k][i]) > maxEl) {
                        maxEl = abs(matrix[k][i]);
                        maxRow = k;
                    }
                }
                // zamień maksymalny wiersz z obecnym
                for (int k = i; k < n+1; k++) {
                    double pom = matrix[maxRow][k];
                    matrix[maxRow][k] = matrix[i][k];
                    matrix[i][k] = pom;
                }
                // wyprowadź zera przed obecnym wierszem
                for (int k = i+1; k < n; k++) {
                    double c = -matrix[k][i] / matrix[i][i];
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
            vector<double> x(n);
            for (int i=n-1; i>=0; i--) {
                x[i] = matrix[i][n] / matrix[i][i];
                for (int k=i-1;k>=0; k--) {
                    matrix[k][n] -= matrix[k][i] * x[i];
                }
            }
            return x;
        }


        //================== aproksymacja
        vector<double> CountEquation(int power){
          int dataLength = matrix.size();
          int sCount = (2 * power) + 1;
          int tCount = power + 1;
          int size = power + 1;
          double sTab [dataLength][sCount];
          double tTab [dataLength][tCount];
          double sResults [sCount];
          double tResults [tCount];

          for (int i = 0; i < dataLength; i++){
            for (int j = 0; j < sCount; j++){
              sTab[i][j] = pow(matrix[i][0], j);
              sResults[j] += sTab[i][j];
            }
            for(int j = 0; j < tCount; j++){
              tTab[i][j] = matrix[i][1] * sTab[i][j];
              tResults[j] += tTab[i][j];
            }
          }

          MyMatrix mat(size, size, 0.0);
          vector<double> vec(size, 0.0);
          int helper = 0;
          for (int i = 0; i < size; i++) {
            vec[i] = tResults[i];
            for (int j = 0; j < size; j++) {
              mat.setAt(i, j, sResults[j + helper]);
            }
            helper++;
          }
          MyMatrix M (size, size + 1, 0.0);
          for (int i = 0; i < size; i++){
            for (int j = 0; j < size + 1; j++){
              if(j == size){
                M.setAt(i, j, vec[i]);
              }
              else{
                M.setAt(i, j, mat.getAt(i, j));
              }
            }
          }
          vector<double> result = M.solveGaussPartial();
          return result;
        }

        double CountVariable(double variable) {
          string tmp = "";
          double result = 0;
          for (int i = 0; i < getRowCount(); i++) {
            result += matrix[i][0] * pow(variable, i);
            // 2 * x^0 + 5 * x^1 + 1 * x^2
            //tmp = tmp + " + " + getAt(i, 0) + " * x ^ " + i + ""; // i++
            tmp.append(to_string(getAt(i,0)));
            tmp.append(" * x ^ ");
            tmp.append(to_string(i));
            tmp.append(" + ");
            //if (i != matrix.getRowCount() - 1){
              //tmp += " + ";
            //}
          }
          cout<<tmp;
          return result;
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

#endif

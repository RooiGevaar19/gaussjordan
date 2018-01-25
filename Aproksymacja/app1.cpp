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
#include "MyMatrix.h"
#include "Entry.h"

using namespace std;
using namespace Eigen;

int new_rows, new_cols;
double times[100][100];
string names[100];

void loadFile(string fileName) {
  ifstream in(fileName);
  if (!in) {
    cout << "Cannot open file.\n";
    return;
  } else {
    in >> new_cols;
    in >> new_rows;
    for (int i = 0; i < new_cols; i++) {
      in >> names[i];
    }
    for (int i = 0; i < new_rows; i++) {
      for (int j = 0; j < new_cols; j++) {
        in >> times[i][j];
      }
    }
    in.close();
  }
}

//================== aproksymacja
vector<double> CountEquation(int power, int k){
  int dataLength = new_rows;
  int sCount = (2 * power) + 1;
  int tCount = power + 1;
  int size = power + 1;
  double sTab [dataLength][sCount];
  double tTab [dataLength][tCount];
  double sResults [sCount];
  double tResults [tCount];

  for (int i = 0; i < dataLength; i++){
    for (int j = 0; j < sCount; j++){
      sTab[i][j] = pow(times[i][0], j);
      sResults[j] += sTab[i][j];
    }
    for(int j = 0; j < tCount; j++){
      tTab[i][j] = times[i][k] * pow(times[i][0], j);
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

//double CountVariable() {
//  string tmp = "";
//  double result = 0;
//  for (int i = 0; i < getRowCount(); i++) {
//    result += matrix[i][0] * pow(variable, i);
//    // 2 * x^0 + 5 * x^1 + 1 * x^2
//    //tmp = tmp + " + " + getAt(i, 0) + " * x ^ " + i + ""; // i++
//    tmp.append(to_string(getAt(i,0)));
//    tmp.append(" * x ^ ");
//    tmp.append(to_string(i));
//
//    if (i != getRowCount() - 1){
//      tmp.append(" + ");
//    }
//  }
//  cout<<tmp;
//  return result;
//}
//

int main(int argc, char** argv) {
    loadFile(argv[1]);
    vector<double> res;
    for (int col = 1; col < new_cols; col++) {
      //Timer t;
      //t.reset();
      res = CountEquation(2, col);
      //double tim = t.elapsed();
      //printf("%2.6lf\n", times[14][2]);
      printf("%s : \t%.12lf ", names[col].c_str(), res[0]);
      for(int i = 1; i < 3; i++) {
        if (res[i] == 0) {
          continue;
        } else if (res[i] < 0) {
          printf("- %.12lf * x^%i ", res[i]*(-1), i);
        } else {
          printf("+ %.12lf * x^%i ", res[i], i);
        }
      }
      printf("\n");
    }

    //fprintf(stderr, "%.12lf", tim);
    return 0;
}

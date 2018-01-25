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

double times[100][100];
string names[100];

void loadFile(string fileName) {
  ifstream in(fileName);
  if (!in) {
    cout << "Cannot open file.\n";
    return;
  } else {
    int new_rows, new_cols;
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

int main(int argc, char** argv) {
    MyMatrix M (1, 2, 0.0);
    M.loadFromFile(argv[1]);
    vector<double> res;
    Timer t;
    t.reset();
    res = M.solveGaussPartial();
    double tim = t.elapsed();
    printf("%.12lf\n", res[0]);
    fprintf(stderr, "%.12lf", tim);
    return 0;
}

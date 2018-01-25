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

int main(int argc, char** argv) {
    MyMatrix<double> M (1, 2, 0.0);
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

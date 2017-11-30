// Test dokładności Gaussa bez wyboru elementu podstawowego

double testMyMatrixFloat(MyMatrix<float> A, vector<float> B, int grade, int tries) {
    MyMatrix<float> M (grade, grade+1, 0.0);
    for (int i = 0; i < grade; i++) {
        for (int j = 0; j < grade; j++) {
            M.setAt(i, j, A.getAt(i,j));
        }
    }
    for (int i = 0; i < grade; i++) {
        M.setAt(i, grade, B[i]);
    }
    vector<float> res;
    res = M.solveGauss();
    vector<float> acc;
    acc = A*res;
    for (int i = 0; i < grade; i++){
         acc[i] -= B[i];
         acc[i] = abs(acc[i]);
    }
    double errors = max(acc);
    return errors;
}

double testMyMatrixDouble(MyMatrix<double> A, vector<double> B, int grade, int tries) {
    MyMatrix<double> M (grade, grade+1, 0.0);
    for (int i = 0; i < grade; i++) {
        for (int j = 0; j < grade; j++) {
            M.setAt(i, j, A.getAt(i,j));
        }
    }
    for (int i = 0; i < grade; i++) {
        M.setAt(i, grade, B[i]);
    }
    vector<double> res;
    res = M.solveGauss();
    vector<double> acc;
    acc = A*res;
    for (int i = 0; i < grade; i++){
         acc[i] -= B[i];
         acc[i] = abs(acc[i]);
    }
    double errors = max(acc);
    return errors;
}

double testEigenFloat(MatrixXf A, VectorXf B, int grade, int tries) {
    HouseholderQR<MatrixXf> dec(A);
    VectorXf x = dec.solve(B);
    VectorXf acc;
    acc = A*x;
    acc -= B;
    double errors = max(acc);
    return errors;
}

double testEigenDouble(MatrixXd A, VectorXd B, int grade, int tries) {
    HouseholderQR<MatrixXd> dec(A);
    VectorXd x = dec.solve(B);
    VectorXd acc;
    acc = A*x;
    acc -= B;
    double errors = max(acc);
    return errors;
}

int main() {
    srand(time(NULL));
    printf("Rozmiar\tMyMatrix-Float\tMyMatrix-Double\tMyMatrix-Fraction\tEigen-Float\tEigen-Double\n");
    int k = 1;
    int grade = 8;
    for (int grade = 2; grade <= max_grade; grade+=k) {
        MyMatrix<float> matrix1a(grade, grade, 0.0);
        vector<float> matrix1b(grade);
        MyMatrix<double> matrix2a(grade, grade, 0.0);
        vector<double> matrix2b(grade);
        fill_random(matrix1a, grade, grade);
        fill_random(matrix1b, grade);
        fill_random(matrix2a, grade, grade);
        fill_random(matrix2b, grade);
        printf("%i\t", grade);
        double ta = testMyMatrixFloat(matrix1a, matrix1b, grade, 1);
        printf("%.16lf\t", abs(ta));
        double tb = testMyMatrixDouble(matrix2a, matrix2b, grade, 1);
        printf("%.16lf\t", abs(tb));
        VectorXf a1 = Map<VectorXf, Unaligned>(matrix1b.data(), matrix1b.size());
        double tc = testEigenFloat(MyMatrixToEigen(matrix1a), a1, grade, tries);
        printf("%.16lf\t", abs(tc));
        VectorXd a2 = Map<VectorXd, Unaligned>(matrix2b.data(), matrix2b.size());
        double td = testEigenDouble(MyMatrixToEigen(matrix2a), a2, grade, tries);
        printf("%.16lf\t", abs(td));
        printf("\n");
        if (grade % (10*k) == 0) k = 10*k;
    }
    return 0;
}

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
    M.display();
    vector<float> res;
    res = M.solveGauss();
    printf("\n");
    M.display();
    vector<float> acc;
    acc = A*res;
    for (int i = 0; i < grade; i++) printf("%f\t", res[i]); printf("\n");
    for (int i = 0; i < grade; i++) printf("%f\t", acc[i]); printf("\n");
    for (int i = 0; i < grade; i++) printf("%f\t", B[i]); printf("\n");
    for (int i = 0; i < grade; i++) acc[i] -= B[i];
    double errors = avg(acc);
    printf("%f\n", errors);
    return errors;
}

int main() {
    srand(time(NULL));
    printf("Rozmiar\tMyMatrix-Float\tMyMatrix-Double\tEigen-Float\tEigen-Double\n");
    int k = 1;
    int grade = 8;
    //for (int grade = 2; grade <= max_grade; grade+=k) {
        MyMatrix<float> matrix1a(grade, grade, 0.0);
        vector<float> matrix1b(grade);
        MyMatrix<double> matrix2a(grade, grade, 0.0);
        vector<double> matrix2b(grade);
        fill_random(matrix1a, grade, grade);
        fill_random(matrix1b, grade);
        fill_random(matrix2a, grade, grade);
        fill_random(matrix2b, grade);
        matrix1a.display();
        for (int i = 0; i < grade; i++) printf("%f\t", matrix1b[i]); printf("\n");
        matrix2a.display();
        for (int i = 0; i < grade; i++) printf("%f\t", matrix2b[i]); printf("\n");
        //printf("%i\t", grade);
        double ta = testMyMatrixFloat(matrix1a, matrix1b, grade, 1);
        printf("%.10lf\t", ta);
        //double tb = testMyMatrixDouble(matrix2a, matrix2b, grade, 1);
        //printf("%.10lf\t", tb);
        //double tc = testEigenFloat(matrix1, grade, tries);
        //printf("%.10lf\t", tc);
        //double td = testEigenDouble(matrix2, grade, tries);
        //printf("%.10lf\t", td);
        printf("\n");
        if (grade % (10*k) == 0) k = 10*k;
    //}
    return 0;
}

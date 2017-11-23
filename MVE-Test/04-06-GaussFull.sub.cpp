// MyMatrix z Float

double testMyMatrixFloat(int grade, int tries) {
    double times[tries];
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<float> A(grade, grade+1, 0.0);
        fill_random(A, grade, grade+1);
        vector<float> res(grade, 0.0);
        Timer t;
        t.reset();
        res = A.solveGaussFull();
        times[attempt] = t.elapsed();
    }
    return avg(times, tries);
}


// MyMatrix z double

double testMyMatrixDouble(int grade, int tries) {
    double times[tries];
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<double> A(grade, grade+1, 0.0);
        fill_random(A, grade, grade+1);
        vector<double> res(grade, 0.0);
        Timer t;
        t.reset();
        res = A.solveGaussFull();
        times[attempt] = t.elapsed();
    }
    return avg(times, tries);
}

// Eigen + Float

double testEigenFloat(int grade, int tries) {
    double times[tries];
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXf A(grade, grade);
        A = MatrixXf::Random(grade, grade) * 100.0;
        VectorXf b(grade);
        b = VectorXf::Random(grade) * 100.0;
        Timer t;
        HouseholderQR<MatrixXf> dec(A);
        t.reset();
        VectorXf x = dec.solve(b);
        times[attempt] = t.elapsed();
    }
    return avg(times, tries);
}

// Eigen + Double

double testEigenDouble(int grade, int tries) {
    double times[tries];
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXd A(grade, grade);
        A = MatrixXd::Random(grade, grade) * 100.0;
        VectorXd b(grade);
        b = VectorXd::Random(grade) * 100.0;
        Timer t;
        HouseholderQR<MatrixXd> dec(A);
        t.reset();
        VectorXd x = dec.solve(b);
        times[attempt] = t.elapsed();
    }
    return avg(times, tries);
}

int main() {
    srand(time(NULL));
    printf("Rozmiar\tMyMatrix-Float\tMyMatrix-Double\tEigen-Float\tEigen-Double\n");
    int tries = 10;
    int max_grade = 1000;
    int k = 1;
    for (int grade = 2; grade <= max_grade; grade+=k) {
        printf("%i\t", grade);
        double ta = testMyMatrixFloat(grade, tries);
        printf("%.10lf\t", ta);
        double tb = testMyMatrixDouble(grade, tries);
        printf("%.10lf\t", tb);
        //double te = testMyMatrixFraction(grade, tries);
        //printf("%.10lf\t", te);
        double tc = testEigenFloat(grade, tries);
        printf("%.10lf\t", tc);
        double td = testEigenDouble(grade, tries);
        printf("%.10lf\t", td);
        printf("\n");
        if (grade % (10*k) == 0) k = 10*k;
    }
    return 0;
}

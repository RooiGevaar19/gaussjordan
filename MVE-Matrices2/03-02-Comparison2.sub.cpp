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

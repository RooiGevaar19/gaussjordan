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

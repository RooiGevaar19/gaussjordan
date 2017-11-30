// Porównanie 1
// wynik A*X

void test1(int grade, int tries) {
    printf("%i\t", grade);
    double times[tries];
    // MyMatrix-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<float> A(grade, grade, 0.0);
        vector<float> B(grade);
        fill_random(A, grade, grade);
        fill_random(B, grade);
        Timer t;
        vector<float> x (grade);
        t.reset();
        x = A * B;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // MyMatrix-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<double> A(grade, grade, 0.0);
        vector<double> B(grade);
        fill_random(A, grade, grade);
        fill_random(B, grade);
        Timer t;
        vector<double> x (grade);
        t.reset();
        x = A * B;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // MyMatrix-Fraction
    for (int attempt = 0; attempt < tries; attempt++) {
        Fraction zero (21.37);
        MyMatrix<Fraction> A(grade, grade, zero);
        vector<Fraction> B(grade);
        fill_random(A, grade, grade);
        fill_random(B, grade);
        Timer t;
        vector<Fraction> x (grade);
        t.reset();
        x = A * B;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // Eigen-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXf A(grade, grade);
        A = MatrixXf::Random(grade, grade) * 100.0;
        MatrixXf B(grade, 1);
        B = VectorXf::Random(grade) * 100.0;
        Timer t;
        VectorXf x(grade, 1);
        t.reset();
        x = A * B;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // Eigen-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXd A(grade, grade);
        A = MatrixXd::Random(grade, grade) * 100.0;
        VectorXd B(grade);
        B = VectorXd::Random(grade) * 100.0;
        Timer t;
        VectorXd x(grade, 1);
        t.reset();
        x = A * B;
        times[attempt] = t.elapsed();
    }
    printf("%.10lf", avg(times, tries));
    printf("\n");
}

int main() {
    srand(time(NULL));
    int tries = 10;
    int max_grade = 1000;
    int k = 1;
    printf("Rozmiar\tMyMatrix-Float\tMyMatrix-Double\tMyMatrix-Fraction\tEigen-Float\tEigen-Double\n");
    for (int grade = 2; grade <= max_grade; grade+=k) {
        test1(grade, tries);
        if (grade % (10*k) == 0) k = 10*k;
    }
    return 0;
}

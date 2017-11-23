// Funkcje pomocnicze do testów
// 
// wypełnianie tabel

void fill_random(MyMatrix<float> A, int wie, int kol) {
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            srand(time(NULL));
            float x = ((float)rand()/RAND_MAX*200.0)-100.0;
            A.setAt(i, j, x);
        }
    }
}

void fill_random(MyMatrix<double> A, int wie, int kol) {
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            srand(time(NULL));
            float x = ((double)rand()/RAND_MAX*200.0)-100.0;
            A.setAt(i, j, x);
        }
    }
}
// Moduł testowy
// 
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
// Porównanie 3
// wynik A*(B*C)


void test3(int grade, int tries) {
    printf("%i\t", grade);
    double times[tries];
    // MyMatrix-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<float> A(grade, grade, 0.0);
        MyMatrix<float> B(grade, grade, 0.0);
        MyMatrix<float> C(grade, grade, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, grade);
        fill_random(C, grade, grade);
        Timer t;
        MyMatrix<float> x (grade, grade, 0.0);
        t.reset();
        x = A * (B * C);
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // MyMatrix-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<double> A(grade, grade, 0.0);
        MyMatrix<double> B(grade, grade, 0.0);
        MyMatrix<double> C(grade, grade, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, grade);
        fill_random(C, grade, grade);
        Timer t;
        MyMatrix<double> x (grade, grade, 0.0);
        t.reset();
        x = A * (B * C);
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
        Timer t;
        MatrixXf x(grade, grade);
        t.reset();
        x = A * (B * C);
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
        Timer t;
        MatrixXd x(grade, grade);
        t.reset();
        x = A * (B * C);
        times[attempt] = t.elapsed();
    }
    printf("%.10lf", avg(times, tries));
    printf("\n");
}
// Funkcje pomocnicze do testów
// 
// wypełnianie tabel

void fill_random(MyMatrix<float> A, int wie, int kol) {
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            srand(time(NULL));
            float x = ((float)rand()/RAND_MAX*200.0)-100.0;
            A.setAt(i, j, x);
        }
    }
}

void fill_random(MyMatrix<double> A, int wie, int kol) {
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            srand(time(NULL));
            float x = ((double)rand()/RAND_MAX*200.0)-100.0;
            A.setAt(i, j, x);
        }
    }
}
// Moduł testowy
// 
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
// Porównanie 3
// wynik A*(B*C)


void test3(int grade, int tries) {
    printf("%i\t", grade);
    double times[tries];
    // MyMatrix-Float
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<float> A(grade, grade, 0.0);
        MyMatrix<float> B(grade, grade, 0.0);
        MyMatrix<float> C(grade, grade, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, grade);
        fill_random(C, grade, grade);
        Timer t;
        MyMatrix<float> x (grade, grade, 0.0);
        t.reset();
        x = A * (B * C);
        times[attempt] = t.elapsed();
    }
    printf("%.10lf\t", avg(times, tries));
    // MyMatrix-Double
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<double> A(grade, grade, 0.0);
        MyMatrix<double> B(grade, grade, 0.0);
        MyMatrix<double> C(grade, grade, 0.0);
        fill_random(A, grade, grade);
        fill_random(B, grade, grade);
        fill_random(C, grade, grade);
        Timer t;
        MyMatrix<double> x (grade, grade, 0.0);
        t.reset();
        x = A * (B * C);
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
        Timer t;
        MatrixXf x(grade, grade);
        t.reset();
        x = A * (B * C);
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
        Timer t;
        MatrixXd x(grade, grade);
        t.reset();
        x = A * (B * C);
        times[attempt] = t.elapsed();
    }
    printf("%.10lf", avg(times, tries));
    printf("\n");
}

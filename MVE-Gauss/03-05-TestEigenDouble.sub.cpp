// Eigen + Double

double testEigenDouble(int grade, int tries) {
    double times[tries];
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXd A(grade, grade);
        A = MatrixXd::Random(grade, grade) * 100.0;
        VectorXd b(grade);
        b = VectorXd::Random(grade) * 100.0;
        Timer t;
        PartialPivLU<MatrixXd> dec(A);
        t.reset();
        VectorXd x = dec.solve(b);
        times[attempt] = t.elapsed();
    }
    return avg(times, tries);
}

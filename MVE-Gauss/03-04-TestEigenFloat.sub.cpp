// Eigen + Float

double testEigenFloat(int grade, int tries) {
    double times[tries];
    for (int attempt = 0; attempt < tries; attempt++) {
        MatrixXf A(grade, grade);
        A = MatrixXf::Random(grade, grade) * 100.0;
        VectorXf b(grade);
        b = VectorXf::Random(grade) * 100.0;
        Timer t;
        PartialPivLU<MatrixXf> dec(A);
        t.reset();
        VectorXf x = dec.solve(b);
        times[attempt] = t.elapsed();
    }
    return avg(times, tries);
}

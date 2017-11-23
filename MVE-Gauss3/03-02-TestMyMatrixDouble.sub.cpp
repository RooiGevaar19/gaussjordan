// MyMatrix z double

MyMatrix<double> fill_random(MyMatrix<double> A, int wie, int kol) {
    MyMatrix<double> result (wie, kol, 0.0);
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            srand(time(NULL));
            double x = ((double)rand()/RAND_MAX*200.0)-100.0;
            result.setAt(i, j, x);
        }
    }
    return result;
}

double testMyMatrixDouble(int grade, int tries) {
    double times[tries];
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<double> A(grade, grade+1, 0.0);
        fill_random(A, grade, grade+1);
        vector<double> res(grade, 0.0);
        Timer t;
        t.reset();
        res = A.solveGauss();
        times[attempt] = t.elapsed();
    }
    return avg(times, tries);
}

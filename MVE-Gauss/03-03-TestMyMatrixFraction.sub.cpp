// MyMatrix z Fraction

MyMatrix<Fraction> fill_random(MyMatrix<Fraction> A, int wie, int kol) {
    MyMatrix<Fraction> result (wie, kol, 0.0);
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            srand(time(NULL));
            Fraction x ((rand()%(200))-100, (rand()%(100))+1);
            result.setAt(i, j, x);
        }
    }
    return result;
}

double testMyMatrixFraction(int grade, int tries) {
    double times[tries];
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<Fraction> A(grade, grade+1, 0.0);
        fill_random(A, grade, grade+1);
        vector<Fraction> res(grade, 0.0);
        Timer t;
        t.reset();
        res = A.solveGauss();
        times[attempt] = t.elapsed();
    }
    return avg(times, tries);
}

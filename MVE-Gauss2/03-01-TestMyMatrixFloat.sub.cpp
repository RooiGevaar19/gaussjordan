// MyMatrix z Float

MyMatrix<float> fill_random(MyMatrix<float> A, int wie, int kol) {
    MyMatrix<float> result (wie, kol, 0.0);
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            srand(time(NULL));
            float x = ((float)rand()/RAND_MAX*200.0)-100.0;
            result.setAt(i, j, x);
        }
    }
    return result;
}

double testMyMatrixFloat(int grade, int tries) {
    double times[tries];
    for (int attempt = 0; attempt < tries; attempt++) {
        MyMatrix<float> A(grade, grade+1, 0.0);
        fill_random(A, grade, grade+1);
        vector<float> res(grade, 0.0);
        Timer t;
        t.reset();
        res = A.solveGauss();
        times[attempt] = t.elapsed();
    }
    return avg(times, tries);
}

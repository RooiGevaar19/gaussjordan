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

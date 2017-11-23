// suma

float sum(float t[], int n) {
    float s = 0.0;
	for (int i = 0; i < n; i++) s += t[i];
    return s;
}

double sum(double t[], int n) {
    double s = 0.0;
	for (int i = 0; i < n; i++) s += t[i];
    return s;
}

float sum(vector<float>& t) {
    float s = 0.0;
	for (int i = 0; i < t.size(); i++) s += t[i];
    return s;
}

double sum(vector<double>& t) {
    double s = 0.0;
	for (int i = 0; i < t.size(); i++) s += t[i];
    return s;
}

// średnia

float avg(float t[], int n) {
	return sum(t,n)/n;
}

double avg(double t[], int n) {
	return sum(t,n)/n;
}

float avg(vector<float> t) {
    return sum(t)/t.size();
}

double avg(vector<double> t) {
    return sum(t)/t.size();
}

float avg(VectorXf t) {
    float s = 0.0;
	for (int i = 0; i < t.size(); i++) s += t(i);
    return s/t.size();
}

double avg(VectorXd t) {
    double s = 0.0;
	for (int i = 0; i < t.size(); i++) s += t(i);
    return s/t.size();
}

// odchylenie standardowe

float stddev(float t[], int n) {
    float av = sum(t,n)/n;
    float s = 0;
    for (int i = 0; i < n; i++) s += ((t[i] - av) * (t[i] - av));
    float dev = sqrt(s/n);
    return dev;
}

double stddev(double t[], int n) {
    double av = sum(t,n)/n;
    double s = 0;
    for (int i = 0; i < n; i++) s += ((t[i] - av) * (t[i] - av));
    double dev = sqrt(s/n);
    return dev;
}

float stddev(vector<float> t) {
    float av = sum(t)/t.size();
    float s = 0;
    for (int i = 0; i < t.size(); i++) s += ((t[i] - av) * (t[i] - av));
    float dev = sqrt(s/t.size());
    return dev;
}

double stddev(vector<double> t) {
    double av = sum(t)/t.size();
    double s = 0;
    for (int i = 0; i < t.size(); i++) s += ((t[i] - av) * (t[i] - av));
    double dev = sqrt(s/t.size());
    return dev;
}

// wypełnianie tabel

void fill_random(MyMatrix<float>& A, int wie, int kol) {
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            //srand(time(NULL));
            //float x = ((float)rand()/RAND_MAX*200.0)-100.0;
            float x = (float)(rand()%(200))-100;
            A.setAt(i, j, x);
        }
    }
}

void fill_random(MyMatrix<double>& A, int wie, int kol) {
    for (unsigned i=0; i<wie; i++) {
        for (unsigned j=0; j<kol; j++) {
            //srand(time(NULL));
            //double x = ((double)rand()/RAND_MAX*200.0)-100.0;
            double x = (double)(rand()%(200))-100;
            A.setAt(i, j, x);
        }
    }
}

void fill_random(vector<float>& A, int n) {
    for (unsigned i=0; i<n; i++) {
        //srand(time(NULL));
        //A[i] = ((float)rand()/RAND_MAX*200.0)-100.0;
        A[i] = (float)(rand()%(200))-100;
    }
}

void fill_random(vector<double>& A, int n) {
    for (unsigned i=0; i<n; i++) {
        //srand(time(NULL));
        //A[i] = ((double)rand()/RAND_MAX*200.0)-100.0;
        A[i] = (double)(rand()%(200))-100;
    }
}

MatrixXf MyMatrixToEigen(MyMatrix<float> input) {
    MatrixXf a(input.getRowCount(), input.getColCount());
    for (int i = 0; i < input.getRowCount(); i++) {
        for (int j = 0; j < input.getColCount(); j++) {
            a(i, j) = input.getAt(i,j);
        }
    }
    return a;
}

MatrixXd MyMatrixToEigen(MyMatrix<double> input) {
    MatrixXd a(input.getRowCount(), input.getColCount());
    for (int i = 0; i < input.getRowCount(); i++) {
        for (int j = 0; j < input.getColCount(); j++) {
            a(i, j) = input.getAt(i,j);
        }
    }
    return a;
}

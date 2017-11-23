int main() {
    //printf("Rozmiar\tMyMatrix-Float\tMyMatrix-Double\tMyMatrix-Frac\tEigen-Float\tEigen-Double\n");
    printf("Rozmiar\tMyMatrix-Float\tMyMatrix-Double\tEigen-Float\tEigen-Double\n");
    int tries = 10;
    int max_grade = 1000;
    int k = 1;
    for (int grade = 2; grade <= max_grade; grade+=k) {
        printf("%i\t", grade);
        double ta = testMyMatrixFloat(grade, tries);
        printf("%.10lf\t", ta);
        double tb = testMyMatrixDouble(grade, tries);
        printf("%.10lf\t", tb);
        //double te = testMyMatrixFraction(grade, tries);
        //printf("%.10lf\t", te);
        double tc = testEigenFloat(grade, tries);
        printf("%.10lf\t", tc);
        double td = testEigenDouble(grade, tries);
        printf("%.10lf\t", td);
        printf("\n");
        if (grade % (10*k) == 0) k = 10*k;
    }
    return 0;
}

int main() {
    int tries = 10;
    int max_grade = 1000;
    int k = 1;
    printf("Rozmiar\tMyMatrix-Float\tMyMatrix-Double\tEigen-Float\tEigen-Double\n");
    for (int grade = 2; grade <= max_grade; grade+=k) {
        test1(grade, tries);
        if (grade % (10*k) == 0) k = 10*k;
    }
    return 0;
}

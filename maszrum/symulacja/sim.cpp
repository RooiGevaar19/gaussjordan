#include <cstdio>
#include <cstring>

class Params {
    private:
        int fieldsN;
        int mushCount;
        int* mush;
        int p1start;
        int p2start;
        int wallCount;              // ilosć ścian kostki XDD
        int* wall;
        int* prop;
    public:
        Params (string input) {
            fp = fopen(input.c_str(), "r");
            fscanf(fp, "%i\n", fieldsN);
            fscanf(fp, "%i", mushCount);
            *mush = new int [mushCount];
            for (int i = 0; i < mushcount; i++) {
                fscanf(fp, "\t%i", mush[i]);
            }
            fscanf(fp, "\n%i\t%i\n", p1start, p2start);
            fscanf(fp, "%i\n", wallCount);
            *wall = new int [wallCount];
            fscanf(fp, "%i", wall[0]);
            for (int i = 1; i < wallCount; i++) {
                fscanf(fp, "\t%i", wall[i]);
            }
            fscanf(fp, "\n");
            *prop = new int [wallCount];
            fscanf(fp, "%i", prop[0]);
            for (int i = 1; i < wallCount; i++) {
                fscanf(fp, "\t%i", prop[i]);
            }
            fscanf(fp, "\n");
            fclose(fp);
        }

        ~Params () {
            delete mush;
            delete wall;
            delete prop;
        }
}

double doSimulation(int tries) {
    Params params = new Params("input");

}

int main() {
    return 0;
}

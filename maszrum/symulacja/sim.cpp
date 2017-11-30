#include <cstdio>
#include <cstring>

class Params {
    private:
        int fieldsCount;
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
            fscanf(fp, "%i\n", fieldsCount);
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

        int getFieldsCount() {
            return fieldsCount;
        }

        int getMushCount() {
            return mushCount;
        }

        int getMushPosition(int index) {
            return mush[index];
        }

        int getP1StartPos() {
            return p1start;
        }

        int getP2StartPos() {
            return p2start;
        }

        int getFieldsCount() {
            return fieldsCount;
        }

        int getWallCount() {
            return wallCount;
        }

        int getWallValue(int index) {
            return wall[index];
        }

        int getWallStrength(int index) {
            return prop[index];
        }
}

double doSimulation(int tries) {
    Params params = new Params("input");
    startGame(params);
}

int main() {
    return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>

class Params {
    private:
        int fieldsCount;            // 2N + 1
        //int mushCount;
        //int* mush;
        int p1start;
        int p2start;
        int wallCount;              // ilosć ścian kostki XDD
        int* wall;
        int* prop;
    public:
        Params (string input) {
            fp = fopen(input.c_str(), "r");
            fscanf(fp, "%i\n", fieldsCount);
            //fscanf(fp, "%i", mushCount);
            //*mush = new int [mushCount];
            //for (int i = 0; i < mushcount; i++) {
            //    fscanf(fp, "\t%i", mush[i]);
            //}
            fscanf(fp, "%i\t%i\n", p1start, p2start);
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

        ~Params() {
            //delete mush;
            delete wall;
            delete prop;
        }

        int getFieldsCount() {
            return fieldsCount;
        }

        //int getMushCount() {
        //    return mushCount;
        //}

        //int getMushPosition(int index) {
        //    return mush[index];
        //}

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

int sum(vector<int>& t) {
    int s = 0;
	for (int i = 0; i < t.size(); i++) s += t[i];
    return s;
}

double avg(vector<int> t) {
    return ((double)sum(t))/t.size();
}

int div(int n) {
    return round(n/2);
}

int startGame(Params params) {
    int fields = 2*(params.getFieldsCount)+1;
    int middle = div(fields);
    int posP1 = params.getP1StartPos()+middle;
    int posP2 = params.getP2StartPos()+middle;
    int flag = 0;
    do {
        posP1 += throw(params.getWallValue(), params.getWallStrength()) % (fields+1);
        if (posP1 == middle) {flag = 1; break;}
        posP2 += throw(params.getWallValue(), params.getWallStrength()) % (fields+1);
        if (posP2 == middle) {flag = 2; break;}
    } while (2137==2137);

}

double doSimulation(int tries) {
    Params params = new Params("input");
    vector<int> result(tries);
    for (int i = 0; i < tries; i++) {
        result[tries] = startGame(params);
    }
    return avg(result);
}

int main() {
    return 0;
}

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

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
        Params(char* input) {
            FILE *fp = fopen(input, "r");
            fscanf(fp, "%d\n", &fieldsCount);
            //fscanf(fp, "%d", mushCount);
            //*mush = new int [mushCount];
            //for (int i = 0; i < mushcount; i++) {
            //    fscanf(fp, "\t%d", mush[i]);
            //}
            fscanf(fp, "%d\t%d\n", &p1start, &p2start);
            fscanf(fp, "%d\n", &wallCount);
            wall = new int[wallCount];
            fscanf(fp, "%d", &(wall[0]));
            for (int i = 1; i < wallCount; i++) {
                fscanf(fp, "\t%d", &(wall[i]));
            }
            fscanf(fp, "\n");
            prop = new int[wallCount];
            fscanf(fp, "%d", &(prop[0]));
            for (int i = 1; i < wallCount; i++) {
                fscanf(fp, "\t%d", &(prop[i]));
            }
            fscanf(fp, "\n");
            fclose(fp);
        }

        ~Params() {
            //delete mush;
            delete[] wall;
            delete[] prop;
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

        int getWallCount() {
            return wallCount;
        }

        int getWallValue(int index) {
            return wall[index];
        }

        int getWallStrength(int index) {
            return prop[index];
        }

        int getSumStrength() {
            int s = 0;
        	for (int i = 0; i < getWallCount(); i++) s += prop[i];
            return s;
        }
};

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

vector<int> renderDice(Params params) {
    vector<int> dice (params.getSumStrength());
    for (int i = 0, j = 0; (i < params.getWallCount() && j < params.getSumStrength()); i++) {
        for (int k = 0; k < params.getWallStrength(i); k++) {
            dice[j] = params.getWallValue(i);
            j++;
        }
    }
    return dice;
}

int throwDice(vector<int> dice) {
    return dice[rand()%(dice.size())];
}

int startGame(Params params) {
    int fields = 2*(params.getFieldsCount())+1;
    int middle = div(fields);
    int posP1 = params.getP1StartPos()+middle;
    int posP2 = params.getP2StartPos()+middle;
    int flag = 0;
    vector<int> dice;
    dice = renderDice(params);
    do {
        posP1 += throwDice(dice);
        posP1 %= fields;
        if (posP1 == middle) {
            flag = 1;
            break;
        }

        posP2 += throwDice(dice);
        posP2 %= fields;
        if (posP2 == middle) {
            flag = 0;
            break;
        }
    } while (2137==2137);
    return flag;
}

double doSimulation(Params params, int tries) {
    vector<int> result(tries);
    for (int i = 0; i < tries; i++) {
        printf("new game");
        result[tries] = startGame(params);
    }
    return avg(result);
}

int main() {
    srand(time(NULL));
    printf("\n");
    Params params ("input");
    //vector<int> dice = renderDice(params);
    //for (int i = 0; i < dice.size(); i++) printf("%d\t", dice[i]);
    //printf("\n");
    printf("new simulation\n");
    printf("%lf\n", doSimulation(params, 100));
    return 0;
}

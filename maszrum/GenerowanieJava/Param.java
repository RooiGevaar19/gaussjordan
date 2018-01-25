import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;

import java.util.*;

public class Param {
    private int fieldsCount = 0;
    private int p1start = 0;
    private int p2start = 0;
    private int wallCount = 0;
    private int[] wall;
    private int[] prop;
    private int mushCount;
    private boolean[] mush;

    Param (String inp) {
        FileReader fr = null;
        try {
            fr = new FileReader(inp);
            Scanner plik = new Scanner(fr);
            while (plik.hasNext()) {
                this.wallCount = plik.nextInt();
                wall = new int[wallCount];
                prop = new int[wallCount];
                for (int i = 0; i < wallCount; i++) this.wall[i] = plik.nextInt();
                for (int i = 0; i < wallCount; i++) this.prop[i] = plik.nextInt();
                try {
                    fr.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            plik.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }


    int getFieldsCount() {
        return this.fieldsCount;
    }

    int getP1StartPos() {
        return this.p1start;
    }

    int getP2StartPos() {
        return this.p2start;
    }

    int getWallCount() {
        return this.wallCount;
    }

    int getWallValue(int index) {
        return this.wall[index];
    }

    int getWallStrength(int index) {
        return this.prop[index];
    }

    int getSumStrength() {
        int s = 0;
        for (int i = 0; i < this.wallCount; i++) s += prop[i];
        return s;
    }

    void setFieldsCount(int x) {
        this.fieldsCount = x;
    }

    void setP1StartPos(int x) {
        this.p1start = x;
    }

    void setP2StartPos(int x) {
        this.p2start = x;
    }

    void setWallCount(int x) {
        this.wallCount = x;
    }

    void setWallValue(int index, int x) {
        this.wall[index] = x;
    }

    void setWallStrength(int index, int x) {
        this.prop[index] = x;
    }

    int getMushCount() {
        return this.mushCount;
    }

    void setMushCount(int x) {
        this.mushCount = x;
    }

    boolean[] getMushTable() {
        return mush;
    }

    void setMushTable(boolean[] t) {
        this.mush = t;
    }

    boolean isMushThere(int index) {
        return this.mush[index];
    }

    void setMushThere(int index, boolean val) {
        this.mush[index] = val;
    }
}

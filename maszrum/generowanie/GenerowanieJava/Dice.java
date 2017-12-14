import java.util.Random;

public class Dice {
    private int[] values;

    public Dice(Param params) {
        values = new int[params.getSumStrength()];
        int j = 0;
        for (int i = 0; i < params.getWallCount(); i++) {
            for (int k = 0; i < params.getWallStrength(i); k++) {
                 values[j] = params.getWallValue(i);
                 j++;
            }
        }
    }

    public int Throw() {
        Random rand = new Random();
        return values[rand.nextInt(values.length)];
    }

    public int[] GetFields() {
        return values;
    }
}

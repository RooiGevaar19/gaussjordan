public class Game {
    private int fields;
    private int middle;
    private int posP1, posP2;

    public Game(Param params) {
        fields = 2*params.getFieldsCount()+1;
        middle = fields / 2;
        posP1 = params.getP1StartPos()+middle;
        posP2 = params.getP2StartPos()+middle;
    }

    public int play(Dice dic, Param params, boolean[] mushs) {
        int flag;
        int mushP1 = 0;
        int mushP2 = 0;
        flag = 0;
        do {
            posP1 += dic.Throw();
            posP1 = Math.floorMod(posP1, fields);
            //System.out.println(posP1);
            if (mushs[posP1]) {
                mushP1++;
                mushs[posP1] = false;
            }
            if (posP1 == middle) {
                if (mushP1 >= mushP2) {
                    flag = 1;
                    break;
                } else {
                    flag = 0;
                    break;
                }
            }

            posP2 += dic.Throw();
            posP2 = Math.floorMod(posP2, fields);
            //System.out.println(posP2);
            if (mushs[posP2]) {
                mushP2++;
                mushs[posP2] = false;
            }
            if (posP2 == middle) {
                if (mushP1 > mushP2) {
                    flag = 1;
                    break;
                } else {
                    flag = 0;
                    break;
                }
            }
        } while (2137==2137);
        return flag;
    }
}

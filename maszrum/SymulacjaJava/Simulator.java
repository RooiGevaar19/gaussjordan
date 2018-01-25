import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;

public class Simulator {

    public static void main(String[] args) {
        Param par;
        Dice dic;
        Game game;
        double result;
        double count;

        par = new Param(args[0]);
        par.setFieldsCount(Integer.parseInt(args[1]));
        par.setP1StartPos(Integer.parseInt(args[1]));
        par.setP2StartPos(Integer.parseInt(args[1])*(-1));
        dic = new Dice(par);
        game = new Game(par);

        int fields = 2*(par.getFieldsCount())+1;

        boolean[] mushs = new boolean[fields];
        for (int i = 0; i < fields; i++) mushs[i] = false;
        par.setMushTable(mushs);

        FileReader fr = null;
        try {
   		 fr = new FileReader(args[3]);
   		 Scanner plik = new Scanner(fr);
   		 while (plik.hasNext()) {
   			 par.setMushCount(plik.nextInt());
             if (par.getMushCount() > 0)
   			 for (int i = 0; i < par.getMushCount(); i++) par.setMushThere(plik.nextInt()+fields/2, true);
   			 try {
   				 fr.close();
   			 } catch (IOException e) {
   				 e.printStackTrace();
   			 }
   		 }
   		 mushs = par.getMushTable();
   		 plik.close();
   	    } catch (FileNotFoundException e) {
   	        e.printStackTrace();
   	    }

        result = 0.0;
        count = 0.0;
        for (int i = 1; i <= Integer.parseInt(args[2]); i++) {
             if (game.play(dic, par, par.getMushTable()) == 1) {
                  result += 1.0;
                  count += 1.0;
             } else {
                 count += 1.0;
             }
        }
        System.out.println(result/count);
    }
}

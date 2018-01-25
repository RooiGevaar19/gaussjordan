import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;

public class MatrixGenerator {

	public static void main(String[] args) {

	 // init
     Param par = new Param(args[0]);
	 par.setFieldsCount(Integer.parseInt(args[1]));
	 par.setP1StartPos(Integer.parseInt(args[1]));
	 par.setP2StartPos(Integer.parseInt(args[1])*(-1));
	 //System.out.println(args[2]);

     Dice dic = new Dice(par);

	 int fields = 2*(par.getFieldsCount())+1;

	 // wygeneruj grzyby
	 boolean[] mushs = new boolean[fields];
	 for (int i = 0; i < fields; i++) mushs[i] = false;
	 par.setMushTable(mushs);
	 FileReader fr = null;
	 try {
		 fr = new FileReader(args[2]);
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


     EntryManager xs = new EntryManager();
     int step = 0;
     int i = 0;

     xs.add(new Entry(i+1, 0, par.getP1StartPos(), par.getP2StartPos(), 0, 0));
     boolean anythingleft;
     try {
    	 do {
    		 anythingleft = false;
    		 for (int k : dic.GetFields()) {
				 int curplay = ((xs.get(step).getPlayer()+1)%2);
				 int curpos1 = Math.floorMod(((xs.get(step).getPosP1())+(k*((xs.get(step).getPlayer()+1)%2))+par.getFieldsCount()), fields)-par.getFieldsCount();
				 int curpos2 = Math.floorMod(((xs.get(step).getPosP2())+(k*((xs.get(step).getPlayer())%2))+par.getFieldsCount()), fields)-par.getFieldsCount();
				 int curmush1 = ((par.isMushThere(curpos1+fields/2)) && (curplay == 1)) ? xs.get(step).getMushP1()+1 : xs.get(step).getMushP1();
				 int curmush2 = ((par.isMushThere(curpos2+fields/2)) && (curplay == 0)) ? xs.get(step).getMushP2()+1 : xs.get(step).getMushP2();
    			 if ((!xs.exists(curplay, curpos1, curpos2, curmush1, curmush2))&&(curpos1 != 0)&&(curpos2 != 0)) {
    				 anythingleft = true;
					 par.setMushThere(((curpos1+fields/2)*((curplay+1)%2)) + ((curpos2+fields/2)*(curplay)), false);
    				 xs.add(new Entry(i+2, curplay, curpos1, curpos2, curmush1, curmush2));
    				 i++;
    			 }
    		 }
    		 step++;
    	 //} while (anythingleft);	// (i <= 96) dziala bez wyjatku, no i ofc (anythingleft)
	 	 } while (2137==2137);
     } catch (Exception e) {
    	 //System.out.println(i+1);
     }

	 par.setMushTable(mushs);
     // utwórz macierz z prawdopodobieństw
     double[][] output = new double[xs.getCount()][xs.getCount()+2];
     for (int x = 0; x < xs.getCount(); x++) {
    	 for (int y = 0; y < xs.getCount()+2; y++) {
    		 output[x][y] = 0.0;
    	 }
     }
     for (Entry v : xs.getAll()) {
    	 output[v.getID()-1][0] = v.getID();
    	 output[v.getID()-1][v.getID()] = 1;
    	 for (int k : dic.GetFields()) {
			 int curplay = ((v.getPlayer()+1)%2);
			 int curpos1 = Math.floorMod(((v.getPosP1())+(k*((v.getPlayer()+1)%2))+par.getFieldsCount()), fields)-par.getFieldsCount();
			 int curpos2 = Math.floorMod(((v.getPosP2())+(k*((v.getPlayer())%2))+par.getFieldsCount()), fields)-par.getFieldsCount();
			 int curmush1 = ((par.isMushThere(curpos1+fields/2)) && (curplay == 1)) ? v.getMushP1()+1 : v.getMushP1();
			 int curmush2 = ((par.isMushThere(curpos2+fields/2)) && (curplay == 0)) ? v.getMushP2()+1 : v.getMushP2();
			 if ((curpos1 == 0 && curmush1 >= curmush2)||(curpos2 == 0 && curmush1 > curmush2)) {
				 output[v.getID()-1][xs.getCount()+1] += 1.0/par.getSumStrength();
			 } else if (xs.exists(curplay, curpos1, curpos2, curmush1, curmush2)) {
				Entry insert = xs.findEntryByParams(curplay, curpos1, curpos2, curmush1, curmush2);
				output[v.getID()-1][insert.getID()] -= 1.0/par.getSumStrength();
			 }
		 }
     }

	 System.out.println(xs.getCount());
	 System.out.println(xs.getCount()+1);
     // wypisanie macierzy
     for (int x = 0; x < xs.getCount(); x++) {
    	 System.out.print(""+output[x][1]+"");
    	 for (int y = 2; y < xs.getCount()+2; y++) {
    		 System.out.print("\t"+output[x][y]+"");
    	 }
    	 System.out.println();
     }


     // czyszczenie zasobów
     xs.clear();
	}
}

import java.util.ArrayList;
import java.util.List;

public class MatrixGenerator {

	public static void main(String[] args) {

     Param par = new Param("./input");
     Dice dic = new Dice(par);
     EntryManager xs = new EntryManager();
     int step = 0;
     int i = 0;
     int fields = 2*(par.getFieldsCount())+1;
     xs.add(new Entry(i+1, 0, par.getP1StartPos(), par.getP2StartPos()));
     boolean anythingleft;
     try {
    	 do {
    		 anythingleft = false;
    		 for (int k : dic.GetFields()) {
				 int curplay = ((xs.get(step).getPlayer()+1)%2);
				 int curpos1 = Math.floorMod(((xs.get(step).getPosP1())+(k*((xs.get(step).getPlayer()+1)%2))+par.getFieldsCount()), fields)-par.getFieldsCount();
				 int curpos2 = Math.floorMod(((xs.get(step).getPosP2())+(k*((xs.get(step).getPlayer())%2))+par.getFieldsCount()), fields)-par.getFieldsCount();
    			 if ((!xs.exists(curplay, curpos1, curpos2))&&(curpos1 != 0)&&(curpos2 != 0)) {
    				 anythingleft = true;
    				 xs.add(new Entry(i+2, curplay, curpos1, curpos2));
    				 i++;
    			 }
    		 }
    		 step++;
    	 //} while (anythingleft);	// (i <= 96) dziala bez wyjatku, no i ofc (anythingleft)
	 	 } while (2137==2137);
     } catch (Exception e) {
    	 //System.out.println(i+1);
     }


   // wypisz prawdopodobieństwa
   for (Entry v : xs.getAll()) {
  	 System.err.println("Var "+(v.getID())+" - P"+(v.getPlayer()+1)
  			 +" ("+(v.getPosP1())
  			 +", "+(v.getPosP2())
  			 +") ");
   }

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
			 if (curpos1 == 0) {
				 output[v.getID()-1][xs.getCount()+1] += 1.0/par.getWallCount();
			 } else if (xs.exists(curplay, curpos1, curpos2)) {
				Entry insert = xs.findEntryByParams(curplay, curpos1, curpos2);
				output[v.getID()-1][insert.getID()] -= 1.0/par.getWallCount();
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

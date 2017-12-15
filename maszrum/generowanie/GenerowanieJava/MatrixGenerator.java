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
    			 if (!xs.exists( 
            		 		((xs.get(step).getPlayer()+1)%2), 
            		 		Math.floorMod(((xs.get(step).getPosP1())+(k*((xs.get(step).getPlayer()+1)%2))+par.getFieldsCount()), fields)-par.getFieldsCount(), 
            		 		Math.floorMod(((xs.get(step).getPosP2())+(k*((xs.get(step).getPlayer())%2))+par.getFieldsCount()), fields)-par.getFieldsCount()
            		 		)) {
    				 anythingleft = true;
    				 xs.add(new Entry(
                		 i+2, 
                		 ((xs.get(step).getPlayer()+1)%2), 
                		 Math.floorMod(((xs.get(step).getPosP1())+(k*((xs.get(step).getPlayer()+1)%2))+par.getFieldsCount()), fields)-par.getFieldsCount(), 
                		 Math.floorMod(((xs.get(step).getPosP2())+(k*((xs.get(step).getPlayer())%2))+par.getFieldsCount()), fields)-par.getFieldsCount()
                		 ));
    				 i++;
    			 }
    		 }
    		 step++;
    	 } while (anythingleft);	// (i <= 96) dzia³a bez wyj¹tku, no i ofc (anythingleft)
     } catch (Exception e) {
    	 //System.out.println(i+1);
     }
     

//   // wypisz prawdopodobieñstwa
//   for (Entry v : xs) {
//  	 System.out.println("Var "+(v.getID())+" - P"+(v.getPlayer()+1)
//  			 +" ("+(v.getPosP1())
//  			 +", "+(v.getPosP2())
//  			 +") ");
//   }

     // utwórz macierz z prawdopodobieñstw
     int[][] output = new int[xs.getCount()][xs.getCount()+2];
     for (int x = 0; x < xs.getCount(); x++) {
    	 for (int y = 0; y < xs.getCount()+2; y++) {
    		 output[x][y] = 0;
    	 }
     }
     for (Entry v : xs.getAll()) {
    	 output[v.getID()-1][0] = v.getID();
    	 output[v.getID()-1][v.getID()] = 1;
    	 for (int k : dic.GetFields()) {
			 if (!xs.exists(
        		 		((v.getPlayer()+1)%2), 
        		 		Math.floorMod(((v.getPosP1())+(k*((v.getPlayer()+1)%2))+par.getFieldsCount()), fields)-par.getFieldsCount(), 
        		 		Math.floorMod(((v.getPosP2())+(k*((v.getPlayer())%2))+par.getFieldsCount()), fields)-par.getFieldsCount()
        		 		)) {
				 int as = xs.findIDByParams(
						 ((v.getPlayer()+1)%2), 
						 Math.floorMod(((v.getPosP1())+(k*((v.getPlayer()+1)%2))+par.getFieldsCount()), fields)-par.getFieldsCount(), 
						 Math.floorMod(((v.getPosP2())+(k*((v.getPlayer())%2))+par.getFieldsCount()), fields)-par.getFieldsCount()
						 );
				 
				 Entry insert = xs.findEntryByID(as);
				 
//				 System.out.println("Param "+
//						 String.valueOf(((v.getPlayer()+1)%2))+"\t"+
//						 String.valueOf(Math.floorMod(((v.getPosP1())+(k*((v.getPlayer()+1)%2))+par.getFieldsCount()), fields)-par.getFieldsCount())+"\t"+
//						 String.valueOf(Math.floorMod(((v.getPosP2())+(k*((v.getPlayer())%2))+par.getFieldsCount()), fields)-par.getFieldsCount())+""
//						 );
				 
				 
				 System.out.println("Var "+(insert.getID())+" - P"+(insert.getPlayer()+1)
		  			 +" ("+(insert.getPosP1())
		  			 +", "+(insert.getPosP2())
		  			 +") ");
				 
				 if ((insert.getPosP1() == 0)) {
					 output[v.getID()-1][xs.getCount()+1] += 1/par.getWallCount();
				 } else {
					 output[v.getID()-1][insert.getID()] -= 1/par.getWallCount(); 
				 }
			 }
		 }
     }
     
     // wypisanie macierzy
     for (int x = 0; x < xs.getCount(); x++) {
    	 for (int y = 0; y < xs.getCount()+2; y++) {
    		 System.out.print(""+output[x][y]+"\t");
    	 }
    	 System.out.println();
     }
     
     
     // czyszczenie zasobów
     xs.clear();
	}
}

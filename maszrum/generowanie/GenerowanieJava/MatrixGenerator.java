import java.util.ArrayList;
import java.util.List;

public class MatrixGenerator {

	static boolean exists(List<Entry> xs, int player, int posP1, int posP2) {
		boolean flag = false;
		for (Entry i : xs) {
			if ((player == i.getPlayer())
				&&(posP1 == i.getPosP1())
				&&(posP2 == i.getPosP2())
				) {
				flag = true;
				break;
			}
		}
		return flag;
	}
	
	public static void main(String[] args) {

     Param par = new Param("./input");
     Dice dic = new Dice(par);
     List<Entry> xs = new ArrayList<Entry>();
     int step = 0;
     int i = 0;
     int fields = 2*(par.getFieldsCount())+1;
     xs.add(new Entry(i+1, 0, par.getP1StartPos(), par.getP2StartPos()));
     boolean anythingleft;
     do {
         anythingleft = false;
    	 for (int k : dic.GetFields()) {
             if (!exists(xs, 
            		 		((xs.get(step).getPlayer()+1)%2), 
            		 		Math.floorMod(((xs.get(step).getPosP1())+(k*((xs.get(step).getPlayer()+1)%2))), fields)-3, 
            		 		Math.floorMod(((xs.get(step).getPosP2())+(k*((xs.get(step).getPlayer())%2))), fields)-3
            		 		)) {
            	 anythingleft = true;
                 xs.add(new Entry(
                		 i+2, 
                		 ((xs.get(step).getPlayer()+1)%2), 
                		 Math.floorMod(((xs.get(step).getPosP1())+(k*((xs.get(step).getPlayer()+1)%2))), fields)-3, 
                		 Math.floorMod(((xs.get(step).getPosP2())+(k*((xs.get(step).getPlayer())%2))), fields)-3
                		 ));
                 i++;
             }
         }
         step++;
     } while (anythingleft);

     for (Entry v : xs) {
    	 System.out.println("Var "+(v.getID())+" - P"+(v.getPlayer()+1)
    			 +" ("+(v.getPosP1())
    			 +", "+(v.getPosP2())
    			 +") ");
     }
     xs.clear();
	}
}

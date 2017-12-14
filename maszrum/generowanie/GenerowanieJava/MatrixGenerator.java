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
     int i = 0;
     xs.add(new Entry(i+1, 0, par.getP1StartPos(), par.getP2StartPos()));
     for (Entry j : xs) {
         for (int k : dic.GetFields()) {
             if (!exists(xs, 
            		 		((j.getPlayer()+1)%2), 
            		 		(j.getPosP1())+(k+((j.getPlayer()+1)%2)), 
            		 		(j.getPosP2())+(k+((j.getPlayer())%2))
            		 		)) {
                 xs.add(new Entry(
                		 i+2, 
                		 ((j.getPlayer()+1)%2), 
                		 (j.getPosP1())+(k+((j.getPlayer()+1)%2)), 
                		 (j.getPosP2())+(k+((j.getPlayer())%2))
                		 ));
                 i++;
             }
         }
     }

     for (Entry v : xs) {
    	 System.out.println("Var "+(v.getID()+1)+" - P"+(v.getPlayer()+1)
    			 +" ("+(v.getPosP1())
    			 +", "+(v.getPosP2())
    			 +") ");
     }
     xs.clear();
	}
}

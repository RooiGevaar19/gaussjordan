import java.util.ArrayList;
import java.util.List;

public class EntryManager {
	private List<Entry> db = new ArrayList<Entry>();

	public List<Entry> getDb() {
		return db;
	}

	public void setDb(List<Entry> db) {
		this.db = db;
	}

	public List<Entry> getAll() {
		return db;
	}

	public int getCount() {
		return db.size();
	}

	public void add(Entry e) {
		db.add(e);
	}

	public void clear() {
		db.clear();
	}

	boolean exists(int player, int posP1, int posP2, int mushP1, int mushP2) {
		boolean flag = false;
		for (Entry i : db) {
			if ((player == i.getPlayer())
				&&(posP1 == i.getPosP1())
				&&(posP2 == i.getPosP2())
				&&(mushP1 == i.getMushP1())
				&&(mushP2 == i.getMushP2())
				) {
				flag = true;
				break;
			}
		}
		return flag;
	}

	public Entry findEntryByParams(int player, int posP1, int posP2, int mushP1, int mushP2) {
		for (Entry i : getAll()) {
			if ((player == i.getPlayer())
				&&(posP1 == i.getPosP1())
				&&(posP2 == i.getPosP2())
				&&(mushP1 == i.getMushP1())
				&&(mushP2 == i.getMushP2())
				) {
				return i;
			}
		}
		return new Entry(0, player, posP1, posP2, mushP1, mushP2);
	}

	public Entry findEntryByID(int id) {
		for (Entry i : db) {
			if (id == i.getID()) {
				return i;
			}
		}
		return null;
	}

	public int findIDByParams(int player, int posP1, int posP2,  int mushP1, int mushP2) {
		for (Entry i : db) {
			if ((player == i.getPlayer())
				&&(posP1 == i.getPosP1())
				&&(posP2 == i.getPosP2())
				&&(mushP1 == i.getMushP1())
				&&(mushP2 == i.getMushP2())
				) {
				return i.getID();
			}
		}
		return 0;
	}

	public Entry get(int step) {
		return db.get(step);
	}

}


public class Entry {
	private int id;
	private int player;
	private int posP1;
	private int posP2;
	private int mushP1;
	private int mushP2;

	public Entry(int id, int player, int posP1, int posP2, int mushP1, int mushP2) {
		super();
		this.setID(id);
		this.player = player;
		this.posP1 = posP1;
		this.posP2 = posP2;
		this.mushP1 = mushP1;
		this.mushP2 = mushP2;
	}

	public int getID() {
		return id;
	}

	public void setID(int id) {
		this.id = id;
	}

	public int getPlayer() {
		return player;
	}

	public void setPlayer(int player) {
		this.player = player;
	}

	public int getPosP1() {
		return posP1;
	}

	public void setPosP1(int posP1) {
		this.posP1 = posP1;
	}

	public int getPosP2() {
		return posP2;
	}

	public void setPosP2(int posP2) {
		this.posP2 = posP2;
	}

	public int getMushP1() {
		return mushP1;
	}

	public void setMushP1(int mushP1) {
		this.mushP1 = mushP1;
	}

	public int getMushP2() {
		return mushP2;
	}

	public void setMushP2(int mushP2) {
		this.mushP2 = mushP2;
	}
}

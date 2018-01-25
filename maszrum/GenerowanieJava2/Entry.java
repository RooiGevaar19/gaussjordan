
public class Entry {
	private int id;
	private int player;
	private int posP1;
	private int posP2;
	
	public Entry(int id, int player, int posP1, int posP2) {
		super();
		this.setID(id);
		this.player = player;
		this.posP1 = posP1;
		this.posP2 = posP2;
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
}

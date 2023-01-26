import java.awt.Graphics2D;

public class Game {
	public Game(GameBoard board) {

	}

	public Boll boll = new Boll(150, 350, 40, 5);
	public Slagtra slagtra = new Slagtra(150, 100, 20, 8);
	public Boxar boxar = new Boxar(80, 400);
	public int tt = 0;

	public void update(Keyboard keyboard) {
		boll.update(keyboard);
		slagtra.update(keyboard);

		boll.collision_sprite(slagtra);
		for (Box box : boxar.get_levande_boxar()) {
			if (boll.collision_sprite(box)) {
				box.hit();
			}

		}

	}

	public void draw(Graphics2D graphics) {
		slagtra.draw(graphics);
		boxar.draw(graphics);
		boll.draw(graphics);
	}
}

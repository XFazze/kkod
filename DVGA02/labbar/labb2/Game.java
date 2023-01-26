import java.awt.Graphics2D;
import java.util.*;

public class Game {
	private int tickcount = 0;

	public Game(GameBoard board) {
	}

	private RedBox redbox = new RedBox(20, 20, 20, 20);
	private List<GreenBox> greenboxes = new ArrayList<GreenBox>();
	private SquareCollection squareCollection = new SquareCollection();

	private Ball ball = new Ball(50, 50, 20, 20);

	public void update(Keyboard keyboard) {
		tickcount += 1;
		this.redbox.setX(this.redbox.getX() + 1);
		this.squareCollection.setY(this.squareCollection.getY() + 1);
		if (this.squareCollection.getY() == 580) {
			System.exit(0);
		}
		this.ball.move(keyboard);

		if (tickcount % 40 == 0) {
			System.out.println("SECONDDDD");
			this.greenboxes.add(new GreenBox(40 * tickcount / 40, 20, 20, 20));

		}
		// for (int i = 0; i < this.greenboxes.size(); i++) {
		// GreenBox greenbox = this.greenboxes.get(i);
		// greenbox.setX(greenbox.getX() + 1);
		// greenbox.setY(greenbox.getY() + 1);
		// }

	}

	public void draw(Graphics2D graphics) {
		this.squareCollection.draw(graphics);
		this.redbox.draw(graphics);
		this.ball.draw(graphics);
		for (GreenBox greenBox : greenboxes) {
			greenBox.draw(graphics);

		}
	}
}

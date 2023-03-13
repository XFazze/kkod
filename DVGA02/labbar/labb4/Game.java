import java.awt.Graphics2D;
import java.awt.Font;

public class Game {
	private LatestRun latestRun;
	private Highscore highscore;

	public Boll boll;
	public Slagtra slagtra;
	public Boxar boxar;

	private int points, bollar;
	boolean paused, started;
	private final int orginal_speed = 15,
			start_x = 150,
			start_y = 350,
			ball_size = 80,
			box_size = 200,
			box_air = 400;

	public Game(GameBoard board, Program program) {
		this.latestRun = program.latestRun;
		this.highscore = program.highscore;

		this.setupBoard();
	}

	public void setupBoard() {
		boll = new Boll(start_x, start_y, ball_size, orginal_speed);
		slagtra = new Slagtra(150, 100, 20, 8);
		boxar = new Boxar(box_size, box_air);
		points = 0;
		bollar = 1;
		paused = false;
		started = false;
	}

	public void update(Keyboard keyboard) {
		if ((bollar < 1 || boxar.get_levande_boxar().size() == 0) && !paused) {
			paused = true;
			latestRun.AddLatestRun(points);
			highscore.AddHighscore(points);

		}
		if (paused) {
			return;
		}
		if (!started) {
			if (keyboard.isKeyDown(Key.Right) || keyboard.isKeyDown(Key.Left)) {
				started = true;
			} else {
				return;
			}
		}
		if (boll.is_lost_ball()) {
			bollar -= 1;
			if (bollar > 0) {
				boll.setX(start_x);
				boll.setY(start_y);
				boll.setSpeedX(orginal_speed);
				boll.setSpeedY(-orginal_speed);
			}
		}
		slagtra.update(keyboard);

		boll.collision_sprite(slagtra);
		for (Box box : boxar.get_levande_boxar()) {
			if (boll.collision_sprite(box)) {
				points += box.hit();
			}
		}
	}

	public void draw(Graphics2D graphics) {
		slagtra.draw(graphics);
		boxar.draw(graphics);
		boll.draw(graphics);
		// System.out.println("draw:"+points);
		graphics.setFont(new Font("TimesRoman", Font.PLAIN, 20));
		graphics.drawString("Points:" + points, 10, 550);
		if (bollar < 0) {
			bollar = 0;
		}
		graphics.drawString("Bollar:" + bollar, 10, 570);

		if (paused) {
			graphics.setFont(new Font("TimesRoman", Font.PLAIN, 30));
			graphics.drawString("Game over. Points:" + points, 50, 250);
			graphics.drawString("Enter initials in the box to the right", 50, 300);

		}
	}
}

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
	public static final int game_window_height = 600,
			game_window_width = 800;
	private static final int orginal_speed = 5,
			boll_start_x = 150,
			boll_start_y = 350,
			ball_size = 80,
			box_size = 200,
			box_air = 400,
			slagtra_start_x = 150,
			slagtra_start_y = game_window_height - 100,
			slagtra_width = 200,
			slagtra_height = 16,
			slagtra_speed = 5;

	public Game(GameBoard board, Program program) {
		this.latestRun = program.latestRun;
		this.highscore = program.highscore;

		this.setupBoard();
	}

	public void setupBoard() {
		boll = new Boll(boll_start_x, boll_start_y, ball_size, orginal_speed);
		slagtra = new Slagtra(slagtra_start_x, slagtra_start_y, slagtra_width, slagtra_height, slagtra_speed);
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
			if (keyboard.isKeyDown(Key.Space)) {
				setupBoard();
			}
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
				boll.setX(boll_start_x);
				boll.setY(boll_start_y);
				boll.setSpeedX(orginal_speed);
				boll.setSpeedY(-orginal_speed);
			}
		}
		slagtra.update(keyboard);
		boll.update(keyboard);

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
		graphics.setFont(new Font("TimesRoman", Font.PLAIN, 20));
		graphics.drawString("Points:" + points, 10, 550);

		graphics.drawString("Bollar:" + bollar, 10, 570);

		if (paused) {
			graphics.setFont(new Font("TimesRoman", Font.PLAIN, 30));
			graphics.drawString("Game over. Points:" + points, 50, 250);
			graphics.drawString("Enter initials to the right if highscore", 50, 300);
			graphics.drawString("Space to restart", 50, 350);

		}
	}
}

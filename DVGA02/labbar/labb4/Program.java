
import java.awt.Dimension;
import java.awt.event.KeyEvent;
import java.awt.Color;

import javax.swing.*;

public class Program extends JFrame {
	private JSplitPane splitPane;
	private JSplitPane rightComponents;
	public GameBoard board;
	public LatestRun latestRun;
	public Highscore highscore;

	private Integer latestRunsSaved = 3;
	private Integer highscoresSaved = 10;

	public Program() {
		latestRun = new LatestRun(latestRunsSaved);
		latestRun.setBackground(Color.BLACK);
		highscore = new Highscore(highscoresSaved, this);
		highscore.setBackground(Color.BLACK);

		board = new GameBoard(this);

		rightComponents = new JSplitPane(JSplitPane.VERTICAL_SPLIT, latestRun, highscore);
		rightComponents.setResizeWeight(0.5);
		rightComponents.setPreferredSize(new Dimension(150, 100));
		splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, board, rightComponents);
		add(splitPane);
		setResizable(true);
		pack();
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
		board.requestFocusInWindow();
		board.start();
	}

	@Override
	protected void processKeyEvent(KeyEvent e) {
		super.processKeyEvent(e);
		board.processKeyEvent(e);
	}

	public static void main(String[] args) {
		new Program();
	}

}

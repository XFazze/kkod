
import java.awt.event.KeyEvent;

import javax.swing.*;

public class Program extends JFrame {
	JSplitPane splitPane;
	GameBoard board;
	RecentScore recentScore;

	public Program() {
		splitPane = new JSplitPane();
		board = new GameBoard();
		recentScore = new RecentScore();
		splitPane.setRightComponent(new JScrollPane(recentScore));
		splitPane.setLeftComponent(board);
		add(splitPane);
		setResizable(true);
		pack();
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
		board.start();
	}

	@Override
	protected void processKeyEvent(KeyEvent e) {
		super.processKeyEvent(e);
		board.processKeyEvent(e);
	}

	public static void main(String[] args) {
		Program program = new Program();
	}

}

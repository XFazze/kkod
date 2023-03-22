import java.util.ArrayList;

import javax.swing.*;

import java.awt.Color;
import java.awt.event.*;

public class Highscore extends JPanel {
    private ArrayList<HighscoreModel> scores;
    private Integer numberOfHighscores;

    private JList<String> list;
    private DefaultListModel<String> model;
    private JLabel label, textInputLabel;

    private JTextField textInput;
    private Integer score;

    public Program program;

    public Highscore(Integer numberOfHighscores, Program program) {
        this.program = program;
        this.numberOfHighscores = numberOfHighscores;
        scores = new ArrayList<HighscoreModel>();
        label = new JLabel("Highscores");
        label.setForeground(Color.YELLOW);
        add(label);

        model = new DefaultListModel<>();

        list = new JList<String>(model);
        list.setFocusable(false);
        list.setForeground(Color.YELLOW);
        list.setBackground(Color.BLACK);
        add(list);

        textInputLabel = new JLabel("<html>Enter your initials!<br/>(Confirm with enter)<html/>");
        textInputLabel.setVisible(false);
        textInputLabel.setFocusable(false);
        textInputLabel.setForeground(Color.YELLOW);
        add(textInputLabel);
        textInput = new JTextField(3);
        // textInput.setBounds(textInput.getX(), textInput.getY(), 10, 10);
        // textInput.setPreferredSize(new Dimension(10, 20));
        // textInput.setSize(new Dimension(100, 20));
        textInput.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String text = textInput.getText();
                textInput.setText("");
                addHighscore(text, score);
                textInput.setVisible(false);
                textInputLabel.setVisible(false);
                textInput.setFocusable(false);
                program.board.requestFocusInWindow();
            }
        });
        textInput.setVisible(false);
        add(textInput);

        this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

    }

    public boolean AddHighscore(Integer score) {
        if (this.scores.size() < numberOfHighscores || score > this.scores.get(this.scores.size() - 1).score) {
            this.textInput.setVisible(true);
            this.textInputLabel.setVisible(true);
            this.textInput.setFocusable(true);
            this.textInput.requestFocusInWindow();
            this.score = score;
            return true;
        } else {
            return false;
        }
    }

    private void addHighscore(String name, Integer score) {
        if (name.length() == 0) {
            name = "?";
        }
        name = String.format("%.3s", name);

        HighscoreModel newHighscore = new HighscoreModel(name, score);
        HighscoreModel tempHighscore;
        Integer originalScoreSize = this.scores.size();
        if (originalScoreSize == 0) {
            scores.add(newHighscore);
        }
        for (int i = 0; i < originalScoreSize; i++) {
            if (this.scores.get(i).score < newHighscore.score) {
                tempHighscore = this.scores.get(i);
                scores.set(i, newHighscore);
                newHighscore = tempHighscore;
            }
            if (i + 1 == originalScoreSize && i + 1 < this.numberOfHighscores) {
                scores.add(newHighscore);
            }
        }

        model.removeAllElements();
        for (int i = 0; i < scores.size(); i++) {
            HighscoreModel highscore = this.scores.get(i);
            model.add(i, String.format("%d. %3s %d", i + 1, highscore.name, highscore.score));
        }

    }

}

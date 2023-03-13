import javax.swing.DefaultListModel;
import javax.swing.*;
import java.awt.Color;
import java.util.ArrayList;

public class LatestRun extends JPanel {
    private ArrayList<Integer> scores;
    private Integer numberOfSavedScores;

    private JList<String> list;
    private DefaultListModel<String> model;
    private JLabel label;

    public LatestRun(Integer numberOfSavedScores) {
        this.numberOfSavedScores = numberOfSavedScores;
        this.scores = new ArrayList<Integer>();
        label = new JLabel("Latest runs");
        label.setFocusable(false);
        label.setForeground(Color.YELLOW);
        add(label);

        model = new DefaultListModel<>();

        list = new JList<String>(model);
        list.setFocusable(false);
        list.setForeground(Color.YELLOW);
        list.setBackground(Color.BLACK);
        add(list);

        this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
    }

    public void AddLatestRun(Integer score) {
        if (this.scores.size() >= numberOfSavedScores) {
            this.scores.remove(0);
        }
        this.scores.add(score);

        model.removeAllElements();
        for (int i = 0; i < scores.size(); i++) {
            Integer reverse = (scores.size() - 1) - i;
            model.add(i, Integer.toString(i + 1) + ". " + Integer.toString(this.scores.get(reverse)));
        }

    }

}

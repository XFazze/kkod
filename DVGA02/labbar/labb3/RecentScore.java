import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

public class RecentScore extends JPanel {

    private JList<Integer> recentScores = new JList<>();
    private DefaultListModel<Integer> model = new DefaultListModel<>();

    public RecentScore() {
        recentScores.setModel(model);
        model.addElement(100);
        model.addElement(200);

    }

}

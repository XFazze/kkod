import java.awt.Graphics2D;
import java.util.*;

public class SquareCollection {
    private List<RedBox> redboxes = new ArrayList<RedBox>();

    public int getX() {
        return this.redboxes.get(0).getX();

    }

    public int getY() {
        return this.redboxes.get(0).getY();
    }

    public void setX(int x) {
        for (int i = 0; i < this.redboxes.size(); i++) {
            RedBox redBox = this.redboxes.get(i);
            redBox.setX(x + i * 20);
        }
    };

    public void setY(int y) {
        for (RedBox redBox : this.redboxes) {
            redBox.setY(y);
        }
    };

    public SquareCollection() {
        for (int i = 0; i < 10; i++) {
            this.redboxes.add(new RedBox(i * 20, 20, 20, 20));
        }
    }

    public void draw(Graphics2D graphics) {
        for (RedBox redBox : this.redboxes) {
            redBox.draw(graphics);
        }
    }
}

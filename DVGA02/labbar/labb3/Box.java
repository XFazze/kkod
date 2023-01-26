import java.awt.Graphics2D;
import java.util.Map;
import java.awt.Color;
import static java.util.Map.entry;

public class Box extends Sprite {
    private int hp;
    private boolean active = false;
    Map<Integer, Color> hps = Map.ofEntries(entry(1,
            Color.blue), entry(2, Color.yellow),
            entry(3, Color.red));

    Box(
            int x,
            int y,
            int size,
            int hp,
            boolean active) {
        super(x, y, size, size);
        this.hp = hp;
        this.active = active;
    }

    public void update(Keyboard keyboard) {
    };

    public void draw(Graphics2D graphics) {
        graphics.setColor(hps.get(this.hp));
        graphics.fillRect(getX(), getY(), getWidth(), getHeight());
        graphics.setColor(Color.white);
        graphics.drawRect(getX(), getY(), getWidth(), getHeight());

    }

    public boolean isAlive() {
        return this.hp != 0;
    }

    public boolean isActive() {
        return this.active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }

    public boolean getActive() {
        return this.active;
    }

    public void hit() {
        if (hp == 0) {
            return;
        }
        this.hp -= 1;
    }

}

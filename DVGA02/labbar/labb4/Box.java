import java.awt.Graphics2D;
import java.util.Map;
import java.awt.Color;
import static java.util.Map.entry;
import java.util.Random;

public class Box extends Sprite {
    private int hp, points;
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

        Random rand = new Random();
        this.hp = rand.nextInt(3)+1;
        this.active = active;
        
        this.points = rand.nextInt(2)+1;
    }

    public void update(Keyboard keyboard) {
    };

    public void draw(Graphics2D graphics) {
        graphics.setColor(hps.get(this.hp));
        graphics.fillRect(getX(), getY(), getWidth(), getHeight());
        graphics.setColor(Color.white);
        graphics.drawRect(getX(), getY(), getWidth(), getHeight());
        if(points>1){
        graphics.setColor(Color.white);
            graphics.fillOval(getX()+getWidth()/4,getY()+getWidth()/4, getWidth()/2, getWidth()/2 );
        }

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

    public int hit() {
        this.hp -= 1;
        if (hp == 0) {
            return points;
        }
        return 0;
    }

}

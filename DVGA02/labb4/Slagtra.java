import java.awt.Graphics2D;
import java.awt.Color;

public class Slagtra extends Sprite {
    private int speed;

    Slagtra(int x, int width, int height, int speed) {
        super(x, 600 - height, width, height);
        this.speed = speed;
    }

    public void update(Keyboard keyboard) {
        if (keyboard.isKeyDown(Key.Right) && getX() + getWidth() < 800) {
            setX(getX() + speed);
        }
        if (keyboard.isKeyDown(Key.Left) && getX() > 0) {
            setX(getX() - speed);
        }

    };

    public void draw(Graphics2D graphics) {
        graphics.setColor(Color.white);
        graphics.fillRect(getX(), getY(), getWidth(), getHeight());

    }

}

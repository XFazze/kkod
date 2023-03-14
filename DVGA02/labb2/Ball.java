import java.awt.Color;
import java.awt.Graphics2D;

public class Ball extends Sprite {

    Ball(int x, int y, int width, int height) {
        super(x, y, width, height);

    }

    public void update(Keyboard keyboard) {

    }

    @Override
    public void draw(Graphics2D graphics) {
        graphics.setColor(Color.white);
        graphics.fillOval(getX(), getY(), getWidth(), getHeight());

    }

    public void move(Keyboard keyboard) {
        int speed = 2;
        if (keyboard.isKeyDown(Key.Up)) {
            setY(getY() - speed);
        }
        if (keyboard.isKeyDown(Key.Down)) {
            setY(getY() + speed);
        }
        if (keyboard.isKeyDown(Key.Right)) {
            setX(getX() + speed);
        }
        if (keyboard.isKeyDown(Key.Left)) {
            setX(getX() - speed);
        }
    }
}

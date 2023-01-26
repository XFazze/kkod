import java.awt.Graphics2D;
import java.awt.Color;
import java.lang.Thread;

public class Boll extends Sprite {
    private int speed_x, speed_y;

    Boll(int x, int y, int size, int speed) {
        super(x, y, size, size);
        this.speed_x = speed;
        this.speed_y = speed;
    }

    public void update(Keyboard keyboard) {
        if (getX() < 0) {
            speed_x = Math.abs(speed_x);
        } else if (getX() + getWidth() > 800) {
            speed_x = -Math.abs(speed_x);
        }
        if (getY() < 0) {
            speed_y = Math.abs(speed_y);
        }
        setX(getX() + speed_x);
        setY(getY() + speed_y);

        // Add function for collision change movment
    };

    public void draw(Graphics2D graphics) {
        graphics.setColor(Color.white);
        graphics.fillOval(getX(), getY(), getWidth(), getHeight());

    }

    public boolean collision_sprite(Sprite box) {
        int square_center_x = box.getX() + box.getWidth() / 2;
        int square_center_y = box.getY() + box.getHeight() / 2;
        int square_right = box.getX() + box.getWidth();
        int square_left = box.getX();
        int square_top = box.getY();
        int square_bottom = box.getY() + box.getHeight();

        int sphere_center_x = getX() + getWidth() / 2;
        int sphere_center_y = getY() + getHeight() / 2;
        int sphere_left = getX();
        int sphere_top = getY();
        int sphere_right = getX() + getWidth();
        int sphere_bottom = getY() + getHeight();
        int sphere_width = getWidth();
        // int sphere_height = getHeight();

        if ((sphere_left > square_right || sphere_right < square_left)
                || (sphere_top > square_bottom || sphere_bottom < square_top)) {
            // System.out.println("NO kollision");
            return false;
        }

        // checks for corner case
        int x_delta = 0, y_delta = 0, sensitivity = 0;
        // top

        // System.out.println("CORNER TOP RIGHT" + sphere_center_y + "<=" + square_top);
        if (sphere_center_y <= square_top - sensitivity) {
            y_delta = square_top - sphere_center_y;
            // System.out.println("YDET" + y_delta);
            // left
            if (sphere_center_x <= square_left - sensitivity) {
                System.out.println("CORNER TOP LEFT"
                        + Math.sqrt(Math.pow((double) y_delta, 2) + Math.pow((double) x_delta, 2)));
                x_delta = square_left - sphere_center_x;
                if (Math.sqrt(Math.pow((double) y_delta, 2) + Math.pow((double) x_delta, 2)) <= sphere_width / 2) {
                    System.out.println("CORNER TOP LEFT succes");
                    speed_x = -Math.abs(speed_x);
                    speed_y = -Math.abs(speed_y);
                    setX(getX() - 5);
                    setY(getY() - 5);
                }
                System.out.println(Math.sqrt(Math.pow((double) y_delta, 2) + Math.pow((double) x_delta, 2))
                        + "CORNER TOP LEFT failed" + sphere_width / 2 + "xx:" + x_delta + "yy" + y_delta);
            }
            // right
            else if (sphere_center_x >= square_right + sensitivity) {
                System.out.println("CORNER TOP RIGHT");
                x_delta = sphere_center_x - square_right;
                if (Math.sqrt(Math.pow((double) y_delta, 2) + Math.pow((double) x_delta, 2)) <= sphere_width / 2) {
                    speed_x = Math.abs(speed_x);
                    speed_y = -Math.abs(speed_y);
                    setX(getX() + 5);
                    setY(getY() - 5);
                }
            }
        }
        // bottom
        else if (sphere_center_y >= square_bottom + sensitivity) {
            y_delta = square_bottom - sphere_center_y;
            // left
            if (sphere_center_x <= square_left - sensitivity) {
                System.out.println("CORNER BOTTOM LEFT");
                x_delta = square_left - sphere_center_x;
                if (Math.sqrt(Math.pow((double) y_delta, 2) + Math.pow((double) x_delta, 2)) <= sphere_width / 2) {
                    speed_x = -Math.abs(speed_x);
                    speed_y = Math.abs(speed_y);
                    setX(getX() - 5);
                    setY(getY() + 5);
                }
            }
            // right
            else if (sphere_center_x >= square_right + sensitivity) {
                System.out.println("CORNER BOTTOM RIGHT");
                x_delta = sphere_center_x - (square_right);
                if (Math.sqrt(Math.pow((double) y_delta, 2) + Math.pow((double) x_delta, 2)) <= sphere_width / 2) {
                    speed_x = Math.abs(speed_x);
                    speed_y = -Math.abs(speed_y);
                    setX(getX() + 5);
                    setY(getY() - 5);
                }
            }
        }
        // System.out.println("CORNER deltas x:" + x_delta + " y:" + y_delta);
        if (x_delta != 0 && y_delta != 0) {
            int c = (int) Math.sqrt(Math.pow((double) y_delta, 2) + Math.pow((double) x_delta, 2));
            System.out.println("BALL len" + c + "spe wid:" + sphere_width / 2);

            if (c > sphere_width / 2) {
                return false;
            }
            // speed_x = -speed_x;
            // speed_y = -speed_y;

            // Not enough sensitivity to work
            // b*fake_n/|fake_n|^2*n
            // b*fake_n skalärprodukt
            // double circle_hypo_squared = Math.sqrt(Math.pow(y_delta, 2) +
            // Math.pow(x_delta, 2));
            // double thing1 = (speed_x * x_delta + speed_y * y_delta) /
            // Math.pow(circle_hypo_squared, 2);
            // double normV_x = thing1 * x_delta;
            // double normV_y = thing1 * y_delta;
            // speed_x += normV_x * 2;
            // speed_y += normV_y * 2;

            // System.out.println("CORNER IN BOUNDS normx" + normV_x + " normy" + normV_y +
            // " xdelta" + x_delta + " ydelta"
            // + y_delta);
            // try {
            // Thread.sleep(5000);
            // } catch (InterruptedException e) {
            // System.out.println("got interrupted!");
            // }
            return true;

        } else {
            // Not a corner
            // System.out.println("WHAT SIDE x:" + Math.abs(sphere_center_x -
            // square_center_x) + "y:" + Math
            // .abs(sphere_center_y - square_center_y));
            if (Math.abs(sphere_top - square_bottom) < 5) {
                System.out.println("SIDE BOTTOM");
                setY(getY() + 5);
                speed_y = Math.abs(speed_y);

            } else if (Math.abs(sphere_bottom - square_top) < 5) {
                System.out.println("SIDE TOP");
                setY(getY() - 5);
                speed_y = -Math.abs(speed_y);

            } else if (Math.abs(sphere_right - square_left) < 5) {
                System.out.println("SIDE LEFT");
                setX(getX() - 5);
                speed_x = -Math.abs(speed_x);

            } else if (Math.abs(sphere_left - square_right) < 5) {
                System.out.println("SIDE LEFT");
                setX(getX() + 5);
                speed_x = Math.abs(speed_x);

            }
            return true;

        }
    }

}

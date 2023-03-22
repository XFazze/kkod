import java.awt.Graphics2D;
import java.awt.Color;

public class Boll extends Sprite {
    private int speed_x, speed_y;

    public Boll(int x, int y, int size, int speed) {
        super(x, y, size, size);
        this.speed_x = speed;
        this.speed_y = -speed;
    }

    public void setSpeedX(int speed_x) {
        this.speed_x = speed_x;
    };

    public void setSpeedY(int speed_y) {
        this.speed_y = speed_y;
    };

    public void update(Keyboard keyboard) {
        setX(getX() + speed_x);
        setY(getY() + speed_y);
    }

    public boolean is_lost_ball() {
        if (getX() < 0) {
            speed_x = Math.abs(speed_x);
        } else if (getX() + getWidth() > 800) {
            speed_x = -Math.abs(speed_x);
        }
        if (getY() < 0) {
            speed_y = Math.abs(speed_y);
        } else if (getY() + getHeight() > 650) {
            return true;
        }
        return false;

    }

    public void draw(Graphics2D graphics) {
        graphics.setColor(Color.white);
        graphics.fillOval(getX(), getY(), getWidth(), getHeight());

    }

    public boolean collision_sprite(Sprite box) {
        int square_right = box.getX() + box.getWidth();
        int square_left = box.getX();
        int square_top = box.getY();
        int square_bottom = box.getY() + box.getHeight();

        int sphere_center_x = getX() + getWidth() / 2;
        int sphere_center_y = getY() + getHeight() / 2;
        int sphere_width = getWidth();

        int aim_x = sphere_center_x;
        int aim_y = sphere_center_y;
        if (sphere_center_x > square_right) {
            aim_x = square_right;
        } else if (sphere_center_x < square_left) {
            aim_x = square_left;
        }
        if (sphere_center_y > square_bottom) {
            aim_y = square_bottom;
        } else if (sphere_center_y < square_top) {
            aim_y = square_top;
        }
        boolean corner_hit = false;
        if (Math.sqrt(Math.pow((double) (aim_x - sphere_center_x), 2)
                + Math.pow((double) (aim_y - sphere_center_y), 2)) < sphere_width * 2 / 3) {

            // checks corners
            if (sphere_center_x > square_right) {
                // right side
                if (sphere_center_y > square_bottom) {
                    // boottom
                    speed_x = Math.abs(speed_x);
                    speed_y = Math.abs(speed_y);
                    System.out.println("BOTTOM RIGHT");
                    corner_hit = true;
                } else if (sphere_center_y < square_top) {
                    speed_x = Math.abs(speed_x);
                    speed_y = -Math.abs(speed_y);
                    System.out.println("TOP RIGHT");
                    corner_hit = true;
                    // top
                }
            } else if (sphere_center_x < square_left) {
                // left side
                if (sphere_center_y > square_bottom) {
                    // boottom
                    speed_x = -Math.abs(speed_x);
                    speed_y = Math.abs(speed_y);
                    System.out.println("BOTTOM LEFT");
                    corner_hit = true;
                } else if (sphere_center_y < square_top) {
                    // top
                    speed_x = -Math.abs(speed_x);
                    speed_y = -Math.abs(speed_y);
                    System.out.println("TOP LEFT");
                    corner_hit = true;
                }
            }
            if (!corner_hit) {
                if (sphere_center_x > square_right) {
                    speed_x = Math.abs(speed_x);
                } else if (sphere_center_x < square_left) {
                    speed_x = -Math.abs(speed_x);
                } else if (sphere_center_y > square_bottom) {
                    speed_y = Math.abs(speed_y);
                } else if (sphere_center_y < square_top) {
                    speed_y = -Math.abs(speed_y);
                }
            }
            setX(getX() + speed_x);
            setY(getY() + speed_y);
            return true;
        }

        return false;

    }

}

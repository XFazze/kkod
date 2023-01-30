import java.awt.Graphics2D;
import java.awt.Color;
import java.lang.Thread;

public class Boll extends Sprite {
    private int speed_x, speed_y;
    

    Boll(int x, int y, int size, int speed) {
        super(x, y, size, size);
        this.speed_x = speed;
        this.speed_y = -speed;
    }
    
	public void setSpeedX(int speed_x) { this.speed_x = speed_x; };
	public void setSpeedY(int speed_y) { this.speed_y = speed_y; };

    public void update(Keyboard keyboard) {

        // Add function for collision change movment
    };
    public boolean is_lost_ball(){
        if (getX() < 0) {
            speed_x = Math.abs(speed_x);
        } else if (getX() + getWidth() > 800) {
            speed_x = -Math.abs(speed_x);
        }
        if (getY() < 0) {
            speed_y = Math.abs(speed_y);
        }else if(getY()+getHeight()>600){
            return true;          
        }
        setX(getX() + speed_x);
        setY(getY() + speed_y);
        return false;          


    }

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
        if (Math.sqrt(Math.pow((double) (aim_x - sphere_center_x), 2)
                + Math.pow((double) (aim_y - sphere_center_y), 2)) < sphere_width) {
                
            // checks corners
            boolean corner_hit = false;
            if(sphere_center_x > square_right){
                // right side
                if(sphere_center_y > square_bottom){
                    // boottom
                    speed_x = Math.abs(speed_x);
                    speed_y = Math.abs(speed_y);
                    System.out.println("BOTTOM RIGHT");
                    corner_hit = true;
                }else if(sphere_center_y < square_top){
                    speed_x = Math.abs(speed_x);
                    speed_y = -Math.abs(speed_y);
                    System.out.println("TOP RIGHT");
                    corner_hit = true;
                    //top
                }
            }else if(sphere_center_x<square_left){
                // left side
                if(sphere_center_y > square_bottom){
                    // boottom
                    speed_x = -Math.abs(speed_x);
                    speed_y = Math.abs(speed_y);
                    System.out.println("BOTTOM LEFT");
                    corner_hit = true;
                }else if(sphere_center_y < square_top){
                    //top
                    speed_x = -Math.abs(speed_x);
                    speed_y = -Math.abs(speed_y);
                    System.out.println("TOP LEFT");
                    corner_hit = true;
                }
            }

            if(!corner_hit){
               
            int x_diff = Math.abs(sphere_center_x-square_center_x);
            int y_diff = Math.abs(sphere_center_y-square_center_y);
            // rectangle made square
            int y_diff_equal = Math.abs(sphere_center_y-square_center_y)*getWidth()/getHeight();
            
            System.out.println("REGULAR SIDE "+y_diff+";"+x_diff+";"+y_diff_equal);
            if(y_diff_equal>x_diff){

                if(sphere_center_x>square_center_x){
                    speed_x = Math.abs(speed_x);
                    System.out.println("REGULAR SIDE RIGHT");
                }else if(sphere_center_x<square_center_x){
                    System.out.println("REGULAR SIDE LEFT");
                    speed_x = -Math.abs(speed_x);
                }
            }else{
                if(sphere_center_y>square_center_y){
                    System.out.println("REGULAR SIDE BOTTOM");
                    speed_y = Math.abs(speed_y);
                }else if(sphere_center_y<square_center_y){
                    System.out.println("REGULAR SIDE TOP");
                    speed_y = -Math.abs(speed_y);
                }
            } 
            }
            
            setX(getX()+speed_x);
            setY(getY()+speed_y);
            return true;
        } else {
            // System.out.println("no collisoin");
            return false;
        }

        // System.out.println("CORNER deltas x:" + x_delta + " y:" + y_delta);

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

    }

}

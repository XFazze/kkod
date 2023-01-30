import java.awt.Graphics2D;
import java.awt.Font;

public class Game {
	private int points=0, bollar=2;
	private final int orginal_speed =5, start_x=150, start_y=350;
	public Game(GameBoard board) {

	}

	public Boll boll = new Boll(start_x, start_y, 40, orginal_speed);

	public Slagtra slagtra = new Slagtra(150, 100, 20, 8);
	public Boxar boxar = new Boxar(80, 400);
	public int tt = 0;

	public void update(Keyboard keyboard) {
		if(boll.is_lost_ball()){
			bollar-=1;
			if(bollar >0){
				boll.setX(start_x);
				boll.setY(start_y);
				boll.setSpeedX(orginal_speed);
				boll.setSpeedY(-orginal_speed);
			}
			
		}
		slagtra.update(keyboard);

		boll.collision_sprite(slagtra);
		for (Box box : boxar.get_levande_boxar()) {
			if (boll.collision_sprite(box)) {
				points += box.hit();
			}

		}

	}

	public void draw(Graphics2D graphics) {
		slagtra.draw(graphics);
		boxar.draw(graphics);
		boll.draw(graphics);
		// System.out.println("draw:"+points);
				graphics.setFont(new Font("TimesRoman", Font.PLAIN, 20)); 
		graphics.drawString("Points:"+points, 10, 550);
		graphics.drawString("Bollar:"+bollar, 10, 570);
		if(bollar<1){
		
				graphics.setFont(new Font("TimesRoman", Font.PLAIN, 30)); 
				graphics.drawString("You lost. Points:"+points, 50, 250);
				try {
					Thread.sleep(2000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
		}
	}
}

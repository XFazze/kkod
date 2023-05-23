import java.awt.Graphics2D;
import java.util.*;

public class Boxar {
    private int boxsize, air;
    private List<List<Box>> alla_boxar;

    public Boxar(int size, int air) {
        alla_boxar = new ArrayList<>();
        this.boxsize = size;
        this.air = air;
        for (int o = 0; o < (Game.game_window_height - air) / size; o++) {
            List<Box> rad = new ArrayList<>();
            for (int i = 0; i < Game.game_window_width / size; i++) {
                if (size * (i + 1) >= Game.game_window_width / size) {
                    rad.add(new Box(size * i, o * size, size, true));
                } else {

                    rad.add(new Box(size * i, o * size, size, false));
                }
            }
            alla_boxar.add(rad);
        }
    }

    public void draw(Graphics2D graphics) {
        for (List<Box> boxar : this.alla_boxar) {
            for (Box box : boxar) {
                if (box.isAlive())
                    box.draw(graphics);
            }
        }

    }

    public List<Box> get_levande_boxar() {
        List<Box> levande_boxar = new ArrayList<>();
        for (List<Box> boxar : this.alla_boxar) {
            for (Box box : boxar) {
                if (box.isAlive() && box.isActive()) {
                    levande_boxar.add(box);
                }

            }
        }
        return levande_boxar;

    }

    public void aktivera_grannar(Box deadbox) {
        int row = deadbox.getY() / boxsize;
        int col = deadbox.getX() / boxsize;
        if (row > 0) {
            if (col > 0) {
                alla_boxar.get(row - 1).get(col - 1).setActive(true);

            } else if (col * boxsize < Game.game_window_width) {
                alla_boxar.get(row - 1).get(col + 1).setActive(true);

            }

        } else if (row * boxsize < (Game.game_window_height - air)) {
            if (col > 0) {
                alla_boxar.get(row + 1).get(col - 1).setActive(true);

            } else if (col * boxsize < Game.game_window_width) {
                alla_boxar.get(row + 1).get(col + 1).setActive(true);

            }
        }
    }

}

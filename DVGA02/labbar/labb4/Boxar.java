import java.awt.Graphics2D;
import java.util.*;

public class Boxar {
    private int boxsize;
    private int air;
    private List<List<Box>> alla_boxar = new ArrayList<>();

    Boxar(int size, int air) {
        this.boxsize = size;
        this.air = air;
        for (int o = 0; o < (600 - air) / size; o++) {
            List<Box> rad = new ArrayList<>();
            for (int i = 0; i < 800 / size; i++) {
                if (size * (i + 1) >= 800 / size) {
                    rad.add(new Box(size * i, o * size, size, 3, true));
                } else {

                    rad.add(new Box(size * i, o * size, size, 3, false));
                }
            }
            alla_boxar.add(rad);
        }
    }

    public void update(Keyboard keyboard) {

    }

    public void draw(Graphics2D graphics) {
        for (List<Box> boxar : this.alla_boxar) {
            // System.out.println(boxar.get(0).getY());
            for (Box box : boxar) {
                if (box.isAlive())
                    box.draw(graphics);
            }
        }

    }

    public List<Box> get_levande_boxar() {
        List<Box> levande_boxar = new ArrayList<>();
        for (List<Box> boxar : this.alla_boxar) {
            // System.out.println(boxar.get(0).getY());
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

            } else if (col * boxsize < 800) {
                alla_boxar.get(row - 1).get(col + 1).setActive(true);

            }

        } else if (row * boxsize < (600 - air)) {
            if (col > 0) {
                alla_boxar.get(row + 1).get(col - 1).setActive(true);

            } else if (col * boxsize < 800) {
                alla_boxar.get(row + 1).get(col + 1).setActive(true);

            }
        }
    }

}

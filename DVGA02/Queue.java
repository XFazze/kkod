import java.util.ArrayList;

public class Queue {
    public ArrayList<Integer> q;

    Queue() {
        this.q = new ArrayList<Integer>();
    }

    public void enqueue(int el) {
        q.add(el);
    }

    public int dequeue() {
        return q.remove(0);
    }

    public boolean isEmpty() {
        return q.isEmpty();
    }

    public void remove(Queue qq, int el) {
        if (qq.isEmpty()) {
            System.out.println("in exist case" + qq.q);
            return;
        } else {
            System.out.println("NOT in exist case" + qq.q);
            Queue q2 = new Queue();
            int tmp = qq.dequeue();
            q2.enqueue(tmp);
            remove(qq, el);
            System.out.println("Returned array:" + qq.q);
            System.out.println("New ret q2" + q2.q);
            System.out.println("Empty?:" + qq.isEmpty());
            while (!qq.isEmpty()) {

                System.out.println("CREATING NEW:" + q2.q + qq.q);
                q2.enqueue(qq.dequeue());
                System.out.println("AFTER NEW:" + q2.q + qq.q);
            }
            qq = q2;
            System.out.println("being returned:" + qq.q);

        }

    }

    public static void main(String[] args) {
        Queue o = new Queue();
        o.enqueue(3);
        o.enqueue(5);
        o.enqueue(3);
        o.enqueue(6);
        o.enqueue(7);

        System.out.println("FINAL" + o.q);
        o.remove(o, 3);
        System.out.println("FINAL" + o.q);

    }

}

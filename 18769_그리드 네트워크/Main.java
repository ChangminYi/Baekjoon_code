import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collections;

public class Main {
    private static class Node {
        public int row, col;
        Node(int r, int c) {
            this.row = r;
            this.col = c;
        }
    }

    private static class Edge implements Comparable<Edge> {
        public Node node1, node2;
        public int cost;

        Edge(Node n1, Node n2, int cost) {
            this.node1 = n1;
            this.node2 = n2;
            this.cost = cost;
        }

        @Override
        public int compareTo(Main.Edge o) {
            return this.cost - o.cost;
        }
    };

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static String[] tmp;

    private static Node[][] parent = new Node[501][501];

    /**
     * 최소 스패닝 트리 문제. 입력으로 들어오는 가중치를
     * 간선으로 변환하여, 크루스칼 알고리즘을 통해 해결.
     */
    public static void main(String args[]) throws IOException {
        for(int t = Integer.parseInt(reader.readLine()); t > 0; t--)
            writer.write(Integer.toString(doMST()) + "\n");
        
        writer.flush();
        reader.close();
        writer.close();
    }

    private static int doMST() throws IOException {
        tmp = reader.readLine().split(" ");
        int r = Integer.parseInt(tmp[0]), c = Integer.parseInt(tmp[1]);
        
        ArrayList<Edge> arg = new ArrayList<>();
        for(int i = 0; i < r; i++) {
            tmp = reader.readLine().split(" ");
            for(int j = 0; j < c - 1; j++) {
                arg.add(new Edge(new Node(i, j), new Node(i, j + 1), Integer.parseInt(tmp[j])));
            }
        }
        for(int i = 0; i < r - 1; i++) {
            tmp = reader.readLine().split(" ");
            for(int j = 0; j < c; j++) {
                arg.add(new Edge(new Node(i, j), new Node(i + 1, j), Integer.parseInt(tmp[j])));
            }
        }

        Collections.sort(arg);
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                parent[i][j] = new Node(i, j);
            }
        }

        int sum = 0;
        for(int i = 0, cnt = 0; i < (r - 1) * c + r * (c - 1) && cnt < r * c - 1; i++) {
            Node p1 = findParent(arg.get(i).node1);
            Node p2 = findParent(arg.get(i).node2);
            if(p1.row == p2.row && p1.col == p2.col)
                continue;
            sum += arg.get(i).cost;
            parent[p2.row][p2.col] = p1;
            cnt++;
        }

        return sum;
    }

    private static Node findParent(Node cur) {
        if(parent[cur.row][cur.col].row == cur.row && parent[cur.row][cur.col].col == cur.col)
            return cur;
        else
            return parent[cur.row][cur.col] = findParent(parent[cur.row][cur.col]);
    }
}

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

class Dir {
    final public int row, col;

    Dir(final int row, final int col) {
        this.row = row;
        this.col = col;
    }

    public Dir Add(final Dir other) {
        return new Dir(this.row + other.row, this.col + other.col);
    }
}

class Node implements Comparable<Node> {
    final public Dir pos;
    final public int dirIdx;
    final public int dist;
    
    Node(final Dir pos, final int dirIdx, final int dist) {
        this.pos = pos;
        this.dirIdx = dirIdx;
        this.dist = dist;
    }

    public int compareTo(final Node other) {
        if(this.dist > other.dist) return 1;
        else if(this.dist < other.dist) return -1;
        else return 0;
    }
}

public class Main {
    final private static int INF = 1000000000;
    final private static char WALL = '*';
    final private static Dir[] possDir = {
        new Dir(0, 1), new Dir(0, -1), new Dir(1, 0), new Dir(-1, 0)
    };
    final private static int[][] dirIdx = {
        {0, 2, 3},
        {1, 2, 3},
        {0, 1, 2},
        {0, 1, 3}
    };

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer parser;

    private static int w, h;
    private static String tmp;
    private static int[][][] dist = new int[100][100][4];
    private static char[][] board = new char[100][100];
    private static Dir[] point = { new Dir(-1, -1), new Dir(-1, -1) };


    /**
     * 최단거리를 찾아야 하기 때문에 다익스트라 알고리즘 사용.
     * 목적지까지 도착해야 할 때 사용해야 하는 거울의 수를 거리로 정의.
     * 목적지에 도달할 수 있는 방향이 4가지이므로, 거리 배열을
     * 3차원으로 정의하여 각각의 방향 중 가장 짧은 거리가 최소 거리.
     */ 
    public static void main(String[] args) throws Exception {
        parser = new StringTokenizer(reader.readLine());
        w = Integer.parseInt(parser.nextToken());
        h = Integer.parseInt(parser.nextToken());

        for(int i = 0; i < h; i++) {
            tmp = reader.readLine();
            for(int j = 0; j < w; j++) {
                board[i][j] = tmp.charAt(j);
                if(board[i][j] == 'C') {
                    if(point[0].row == -1) point[0] = new Dir(i, j);
                    else point[1] = new Dir(i, j);
                }
                for(int k = 0; k < 4; k++) {
                    dist[i][j][k] = INF;
                }
            }
        }
        reader.close();

        dijk(point[0]);

        int ans = INF;
        for(final int d : dist[point[1].row][point[1].col]) {
            ans = Math.min(ans, d);
        }

        writer.write(Integer.toString(ans));
        writer.flush();
        writer.close();
    }
    
    private static void dijk(final Dir start) {
        PriorityQueue<Node> pq = new PriorityQueue<>();

        for(int i = 0; i < 4; i++) {
            dist[start.row][start.col][i] = 0;
            Dir nxt = start.Add(possDir[i]);
            if(inRange(nxt) && board[nxt.row][nxt.col] != WALL) {
                dist[nxt.row][nxt.col][i] = 0;
                pq.add(new Node(nxt, i, 0));
            }
        }

        while(!pq.isEmpty()) {
            Node node = pq.poll();

            for(final int nxtIdx: dirIdx[node.dirIdx]) {
                Dir nxt = node.pos.Add(possDir[nxtIdx]);
                int newDist = (nxtIdx == node.dirIdx ? node.dist : node.dist + 1);
                if(inRange(nxt) && board[nxt.row][nxt.col] != WALL && newDist < dist[nxt.row][nxt.col][nxtIdx]) { 
                    dist[nxt.row][nxt.col][nxtIdx] = newDist;
                    pq.add(new Node(nxt, nxtIdx, newDist));
                }
            }
        }
    }

    private static boolean inRange(final Dir d) {
        return 0 <= d.row && d.row < h && 0 <= d.col && d.col < w;
    }
}

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
    static class Dir {
        int row, col;
        
        Dir() {
            this(0, 0);
        }
        Dir(int row, int col) {
            this.row = row;
            this.col = col;
        }

        @Override
        public boolean equals(Object obj) {
            return this.row == ((Dir)obj).row && this.col == ((Dir)obj).col;
        }
    }

    static class Pqn implements Comparable<Pqn> {
        Dir pos;
        int curDist, minDist;

        Pqn(Dir pos, int curDist, int minDist) {
            this.pos = pos;
            this.curDist = curDist;
            this.minDist = minDist;
        }

        @Override
        public int compareTo(Main.Pqn o) {
            if(this.curDist != o.curDist)
                return this.curDist - o.curDist;
            else
                return this.minDist - o.minDist;
        }
    }

    final static int NOT_VISIT = -1;
    final static Dir possDir[] = {
        new Dir(1, 0), new Dir(-1, 0),
        new Dir(0, 1), new Dir(0, -1)
    };

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    static int n, m;
    static char board[][];
    static int dist[][];
    static Dir sp, ep;
    static Queue<Dir> treeQ = new LinkedList<>();
    static PriorityQueue<Pqn> pq = new PriorityQueue<>(Collections.reverseOrder());

    /**
     * 우선순위 큐를 이용하여 bfs를 실행한다.
     * 우선 bfs를 통해 각 칸에서의 나무와의 거리의 최솟값을 구한다.
     * 그 후, 우선순위 큐를 통해 현재까지 진행한 경로 중
     * 나무와의 최소 거리가 가장 큰 경로부터 탐색하여 정답을 구한다.
     */
    public static void main(String[] args) throws Exception {
        tokenizer = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());

        board = new char[n][m];
        dist = new int[n][m];
        for(int i = 0; i < n; i++) {
            Arrays.fill(dist[i], NOT_VISIT);

            String tmp = reader.readLine();
            for(int j = 0; j < m; j++) {
                board[i][j] = tmp.charAt(j);
                if(board[i][j] == '+') {
                    treeQ.add(new Dir(i, j));
                    dist[i][j] = 0;
                } else if(board[i][j] == 'V') {
                    sp = new Dir(i, j);
                } else if(board[i][j] == 'J') {
                    ep = new Dir(i, j);
                }
            }
        }

        while(!treeQ.isEmpty()) {
            Dir cur = treeQ.poll();
            for(Dir pd: possDir) {
                Dir nxt = new Dir(cur.row + pd.row, cur.col + pd.col);
                if(inRange(nxt) && dist[nxt.row][nxt.col] == NOT_VISIT) {
                    dist[nxt.row][nxt.col] = dist[cur.row][cur.col] + 1;
                    treeQ.add(nxt);
                }
            }
        }

        int ans = 0;
        pq.add(new Pqn(sp, dist[sp.row][sp.col], dist[sp.row][sp.col]));
        while(!pq.isEmpty()) {
            Dir cur = pq.peek().pos;
            int minDist = pq.poll().minDist;

            if(cur.equals(ep)) {
                ans = minDist;
                break;
            } else if(dist[cur.row][cur.col] == NOT_VISIT) {
                continue;
            }

            dist[cur.row][cur.col] = NOT_VISIT;
            for(Dir pd: possDir) {
                Dir nxt = new Dir(cur.row + pd.row, cur.col + pd.col);
                if(inRange(nxt) && dist[nxt.row][nxt.col] != NOT_VISIT) {
                    pq.add(new Pqn(nxt, dist[nxt.row][nxt.col], Math.min(dist[nxt.row][nxt.col], minDist)));
                }
            }
        }

        writer.write(Integer.toString(ans));

        writer.flush();
        writer.close();
    }

    static boolean inRange(Dir d) {
        return 0 <= d.row && d.row < n && 0 <= d.col && d.col < m;
    }
}

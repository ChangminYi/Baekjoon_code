import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Main {
    private static class Dir {
        int row, col;
        Dir(int r, int c) {
            this.row = r;
            this.col = c;
        }
    };
    private static class Qnode {
        Dir dir;
        int time;

        Qnode(Dir d, int t) {
            this.dir = d;
            this.time = t;
        }
    }

    final private static int INF = Integer.MAX_VALUE / 2;
    final private static Dir[] possDir = {
        new Dir(0, 1), new Dir(0, -1), new Dir(-1, 0), new Dir(1, 0)
    };

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static String[] tmp;

    private static int n, m;
    private static int[][] board;
    private static ArrayList<Qnode> virus = new ArrayList<>();
    private static Qnode[] dfsVisit;
    private static int res = INF;
    private static int initEmptyCnt = 0;

    /**
     * dfs로 모든 조합을 구하고, bfs를 통해 바이러스 전파.
     * 시간을 줄이기 위해 빈 칸이 사라지면 즉시 bfs 중지.
     */
    public static void main(String[] args) throws Exception {
        tmp = reader.readLine().split(" ");
        n = Integer.parseInt(tmp[0]);
        m = Integer.parseInt(tmp[1]);
        
        board = new int[n][n];
        for (int i = 0; i < n; i++) {
            tmp = reader.readLine().split(" ");
            for (int j = 0; j < n; j++) {
                board[i][j] = Integer.parseInt(tmp[j]);
                if (board[i][j] == 0)
                    initEmptyCnt++;
                else if (board[i][j] == 2)
                    virus.add(new Qnode(new Dir(i, j), 0));
            }
        }

        if (initEmptyCnt == 0)
            writer.write("0");
        else {
            dfsVisit = new Qnode[m];
            dfs(0, 0);
            writer.write((res == INF ? "-1" : Integer.toString(res)));
        }

        writer.flush();
        writer.close();
        reader.close();
    }

    private static void dfs(int idx, int cnt) {
        if (cnt == m)
            bfs();
        else {
            for (int i = idx; i < virus.size(); i++) {
                dfsVisit[cnt] = virus.get(i);
                dfs(i + 1, cnt + 1);
            }
        }
    }

    private static boolean inRange(Dir d) {
        return 0 <= d.row && d.row < n && 0 <= d.col && d.col < n;
    }

    private static void bfs() {
        int emptyCnt = initEmptyCnt;
        Queue<Qnode> q = new LinkedList<>();
        boolean[][] visit = new boolean[n][n];

        for(Qnode sp: dfsVisit) {
            visit[sp.dir.row][sp.dir.col] = true;
            q.add(sp);
        }
        while (!q.isEmpty()) {
            Qnode cur = q.poll();

            for(final Dir pd: possDir) {
                Dir nxt = new Dir(cur.dir.row + pd.row, cur.dir.col + pd.col);
                if(!inRange(nxt) || board[nxt.row][nxt.col] == 1 || visit[nxt.row][nxt.col])
                    continue;
                
                if(board[nxt.row][nxt.col] == 0 && --emptyCnt == 0) {
                    res = Math.min(res, cur.time + 1);
                    return;
                }
                visit[nxt.row][nxt.col] = true;
                q.add(new Qnode(nxt, cur.time + 1));
            }
        }
    }
}
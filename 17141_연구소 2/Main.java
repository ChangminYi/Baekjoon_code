import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
    static class Dir {
        int row, col;
        
        Dir() {
            this(0, 0);
        }

        Dir(int r, int c) {
            this.row = r;
            this.col = c;
        }
    }

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    final static Dir possDir[] = {
        new Dir(1, 0), new Dir(-1, 0), new Dir(0, 1), new Dir(0, -1)
    };

    static int n, m;
    static int emptyCount = 0;
    static int board[][];
    static ArrayList<Dir> virusPoss = new ArrayList<>();
    static boolean virusUsed[];

    /**
     * 바이러스를 놓을 수 있는 칸이 m의 값보다 클 수 있다.
     * 따라서 dfs를 통해 m개의 바이러스를 놓는 모든 경우의 수를
     * 탐색한 후, 바이러스를 전파하며 걸린 시간의 최솟값을
     * 구하면 된다. 모든 경우에서 모든 칸에 바이러스를 놓을 수
     * 없는 경우 -1을 출력하면 된다.
     */
    public static void main(String[] args) throws Exception {
        tokenizer = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());

        board = new int[n][n];
        for(int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(reader.readLine());
            for(int j = 0; j < n; j++) {
                board[i][j] = Integer.parseInt(tokenizer.nextToken());
                if(board[i][j] == 2)
                    virusPoss.add(new Dir(i, j));
                else if(board[i][j] == 0)
                    emptyCount++;
            }
        }
        virusUsed = new boolean[virusPoss.size()];
        reader.close();

        int res = dfs(0, 0);
        if(res == Integer.MAX_VALUE)
            writer.write("-1");
        else
            writer.write(Integer.toString(res));

        writer.flush();
        writer.close();
    }

    static int dfs(int depth, int select) {
        int ret = Integer.MAX_VALUE;
        if(select == m) {
            ret = Math.min(ret, bfs());
        } else if (depth < virusPoss.size()){
            virusUsed[depth] = true;
            ret = Math.min(ret, dfs(depth + 1, select + 1));
            virusUsed[depth] = false;
            ret = Math.min(ret, dfs(depth + 1, select));
        }
        return ret;
    }

    static boolean inRange(Dir d) {
        return 0 <= d.row && d.row < n && 0 <= d.col && d.col < n;
    }

    static int bfs() {
        int tmpBoard[][] = new int[n][n];
        boolean visit[][] = new boolean[n][n];
        Queue<Dir> q = new LinkedList<>();

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                tmpBoard[i][j] = board[i][j];
            }
        }
        for(int i = 0; i < virusPoss.size(); i++) {
            if(virusUsed[i]) {
                Dir init = virusPoss.get(i);
                q.add(init);
                visit[init.row][init.col] = true;
            }
        }

        int iter = 0;
        int remain = emptyCount + (virusPoss.size() - m);
        while(!q.isEmpty() && remain > 0) {
            int qSize = q.size();
            do {
                Dir cur = q.poll();

                for(Dir pd: possDir) {
                    Dir nxt = new Dir(cur.row + pd.row, cur.col + pd.col);
                    if(inRange(nxt) && tmpBoard[nxt.row][nxt.col] != 1 && !visit[nxt.row][nxt.col]) {
                        visit[nxt.row][nxt.col] = true;
                        remain--;
                        q.add(nxt);
                    }
                }
            } while(--qSize > 0);

            iter++;
        }

        return (remain == 0 ? iter : Integer.MAX_VALUE);
    }
}

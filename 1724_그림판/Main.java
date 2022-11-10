import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
    static class Dir {
        int row, col;

        Dir(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    final static Dir moveDir[] = {
        new Dir(-1, 0),
        new Dir(0, -1),
        new Dir(0, 1),
        new Dir(1, 0)
    };
    final static Dir possDir[][] = {
        {new Dir(0, 0), new Dir(0, 1)},
        {new Dir(0, 0), new Dir(1, 0)},
        {new Dir(0, 1), new Dir(1, 1)},
        {new Dir(1, 0), new Dir(1, 1)}
    };
    final static int VERT = 0;
    final static int HORI = 1;

    static int n, m;
    static boolean dotUsed[][][], visit[][];
    static Queue<Dir> q = new LinkedList<>();

    /**
     * 선분을 가로 선분과 세로 선분을 구분해야 제대로 탐색할 수 있다.
     * 선분이 지나가는 점을 방향을 구분하여 모두 저장한 후, bfs를 통해 탐색한다.
     * 다음 칸으로 넘어가는 방향에 대해서 지나가게 되는 경계선의
     * 양쪽 점이 모두 같은 방향에 대해 사용되었다면 넘어갈 수 없다.
     * 각 영역에 대해서 탐색 시 영역의 크기를 계산하여 조건에 맞게 출력한다.
     */
    public static void main(String[] args) throws Exception {
        tokenizer = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());
        visit = new boolean[n][m];
        dotUsed = new boolean[2][n + 1][m + 1];
        for(int t = Integer.parseInt(reader.readLine()), r1, r2, c1, c2; t > 0; t--) {
            tokenizer = new StringTokenizer(reader.readLine());
            r1 = Integer.parseInt(tokenizer.nextToken());
            c1 = Integer.parseInt(tokenizer.nextToken());
            r2 = Integer.parseInt(tokenizer.nextToken());
            c2 = Integer.parseInt(tokenizer.nextToken());

            if(c1 == c2) {
                if(r1 > r2)
                    for(int i = r2; i <= r1; i++) dotUsed[VERT][i][c1] = true;
                else
                    for(int i = r1; i <= r2; i++) dotUsed[VERT][i][c1] = true;
            } else {
                if(c1 > c2)
                    for(int i = c2; i <= c1; i++) dotUsed[HORI][r1][i] = true;
                else
                    for(int i = c1; i <= c2; i++) dotUsed[HORI][r1][i] = true;
            }
        }

        int maxAns = 0, minAns = Integer.MAX_VALUE;
        for(int i = 0, tmp; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(visit[i][j]) continue;
                tmp = bfs(i, j);
                maxAns = Math.max(maxAns, tmp);
                minAns = Math.min(minAns, tmp);
            }
        }

        writer.write(Integer.toString(maxAns) + "\n" + Integer.toString(minAns));

        writer.flush();
        writer.close();
    }

    static int bfs(int r, int c) {
        int ret = 1;

        visit[r][c] = true;
        q.add(new Dir(r, c));
        while(!q.isEmpty()) {
            Dir cur = q.poll();

            for(int i = 0; i < moveDir.length; i++) {
                Dir nxt = new Dir(cur.row + moveDir[i].row, cur.col + moveDir[i].col);
                Dir border[] = {
                    new Dir(cur.row + possDir[i][0].row, cur.col + possDir[i][0].col),
                    new Dir(cur.row + possDir[i][1].row, cur.col + possDir[i][1].col)
                };

                if(inRange(nxt) && canMove(border) && !visit[nxt.row][nxt.col]) {
                    visit[nxt.row][nxt.col] = true;
                    ret++;
                    q.add(nxt);
                }
            }
        }

        return ret;
    }

    static boolean canMove(Dir dot[]) {
        int cnt = 0;
        if(dot[0].row == dot[1].row) {
            for(Dir d: dot)
                if(dotUsed[HORI][d.row][d.col]) cnt++;
        } else {
            for(Dir d: dot)
                if(dotUsed[VERT][d.row][d.col]) cnt++;
        }
        return cnt != 2;
    }

    static boolean inRange(Dir d) {
        return 0 <= d.row && d.row < n && 0 <= d.col && d.col < m;
    }
}

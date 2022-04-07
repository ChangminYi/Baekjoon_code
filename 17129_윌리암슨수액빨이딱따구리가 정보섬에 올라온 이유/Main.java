import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

class Dir {
    public int row = 0, col = 0;
    Dir(final int _r, final int _c) {
        this.row = _r;
        this.col = _c;
    }
}

/**
 * BFS 문제이다. 음식은 3에서 5의 값을 가지므로, 현재 칸이 이에 해당하면
 * 출력 문자를 TAK+현재 거리로 설정하고 반복문을 탈출한다. 만약 현재 칸이
 * 아직 음식이 아니라면, 모든 인접한 주변 칸에 대하여 갈 수 있는지를 검사하고,
 * 갈 수 있다면 거리와 방문 여부를 최신화하고 큐에 삽입한다.
**/
public class Main {
    final public static char START = '2';
    final public static char WALL = '1';
    final public static char EMPTY = '0';
    final public static Dir[] possDir = {
        new Dir(1, 0), new Dir(-1, 0), new Dir(0, 1), new Dir(0, -1)
    };

    public static BufferedReader scanner = new BufferedReader(new InputStreamReader(System.in));
    public static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    public static StringTokenizer parser;

    public static int n, m;
    public static String tmp;
    public static String ans = "NIE";
    
    public static char[][] board = new char[3000][3000];
    public static int[][] dist = new int[3000][3000];
    public static boolean[][] visit = new boolean[3000][3000];
    public static Queue<Dir> que = new LinkedList<>();

    public static void main(String args[]) throws Exception {
        parser = new StringTokenizer(scanner.readLine());
        n = Integer.parseInt(parser.nextToken());
        m = Integer.parseInt(parser.nextToken());

        for(int i = 0; i < n; i++) {
            tmp = scanner.readLine();
            for(int j = 0; j < m; j++) {
                board[i][j] = tmp.charAt(j);
                visit[i][j] = false;
                if(board[i][j] == START) {
                    visit[i][j] = true;
                    board[i][j] = EMPTY;
                    dist[i][j] = 0;
                    que.add(new Dir(i, j));
                }
            }
        }

        while(!que.isEmpty()) {
            Dir cur = que.poll();

            if(canFinishBFS(cur)) {
                ans = "TAK\n" + Integer.toString(dist[cur.row][cur.col]);
                break;
            }
            else {
                for(Dir pd: possDir) {
                    Dir nxt = new Dir(cur.row + pd.row, cur.col + pd.col);
                    if(inRange(nxt) && board[nxt.row][nxt.col] != WALL && !visit[nxt.row][nxt.col]) {
                        visit[nxt.row][nxt.col] = true;
                        dist[nxt.row][nxt.col] = dist[cur.row][cur.col] + 1;
                        que.add(nxt);
                    }
                }
            }
        }

        writer.write(ans);

        scanner.close();
        writer.close();        
    }

    public static boolean canFinishBFS(final Dir cur){
        return '3' <= board[cur.row][cur.col] && board[cur.row][cur.col] <= '5';
    }

    public static boolean inRange(final Dir cur) {
        return 0 <= cur.row && cur.row < n && 0 <= cur.col && cur.col < m;
    }
}
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
    static class Dir {
        int row, col;

        Dir(){
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

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    static int n, m;
    static int setCnt;
    static Queue<Dir> q = new LinkedList<>();
    static char[][] board;
    static Dir[][] parent;
    static HashMap<Character, Dir> possDir = new HashMap<>(){{
        put('S', new Dir(1, 0));
        put('N', new Dir(-1, 0));
        put('W', new Dir(0, -1));
        put('E', new Dir(0, 1));
    }};

    /**
     * 구사과가 이동할 수 있는 영역의 수가 최소 선물의 수이다.
     * 특정 영역 안에서는 구사과의 이동에 맞춰 반드시 선물을 하나 줄 수 있다.
     * 따라서, 영역을 분리집합으로 관리하여 전체 영역의 수를 구하면 된다.
     */
    public static void main(String[] args) throws Exception {
        tokenizer = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());

        board = new char[n][m];
        parent = new Dir[n][m];
        for(int i = 0; i < n; i++) {
            String tmp = reader.readLine();
            for(int j = 0; j < m; j++) {
                board[i][j] = tmp.charAt(j);
                parent[i][j] = new Dir(i, j);
            }
        }
        reader.close();

        setCnt = n * m;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(parent[i][j].row == i && parent[i][j].col == j) {
                    dfs(parent[i][j]);
                }
            }
        }

        writer.write(Integer.toString(setCnt));

        writer.flush();
        writer.close();
    }

    static void dfs(Dir cur) {
        Dir nxtDir = possDir.get(board[cur.row][cur.col]);
        Dir nxt = new Dir(cur.row + nxtDir.row, cur.col + nxtDir.col);
        if(inBoard(nxt)) {
            Dir curPar = findParent(cur);
            Dir nxtPar = findParent(nxt);
            if(!curPar.equals(nxtPar)) {
                parent[nxtPar.row][nxtPar.col] = curPar;
                setCnt--;
                dfs(nxt);
            }
        }
    }

    static boolean inBoard(Dir d) {
        return 0 <= d.row && d.row < n && 0 <= d.col && d.col < m;
    }

    static Dir findParent(Dir cur) {
        if(parent[cur.row][cur.col].equals(cur))
            return cur;
        else
            return parent[cur.row][cur.col] = findParent(parent[cur.row][cur.col]);
    }
}

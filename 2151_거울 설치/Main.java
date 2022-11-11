import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;
import java.util.Collections;
import java.util.PriorityQueue;


public class Main {
    static class Dir {
        int row, col;

        Dir(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }
    
    static class Pqn implements Comparable<Pqn> {
        Dir pos;
        int dist, dirIdx;

        Pqn(Dir pos, int dist, int dirIdx) {
            this.pos = pos;
            this.dist = dist;
            this.dirIdx = dirIdx;
        }

        @Override
        public int compareTo(Pqn other) {
            return this.dist - other.dist;
        }
    }

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));

    final static Dir possDir[] = {
        new Dir(1, 0),
        new Dir(-1, 0),
        new Dir(0, 1),
        new Dir(0, -1)
    };
    final static char DOOR = '#';
    final static char EMPTY = '.';
    final static char MIRROR_AVAIL = '!';
    final static char WALL = '*';
    final static int INF = Integer.MAX_VALUE / 2;

    static int n;
    static char board[][];
    static int dist[][][];
    static Dir startDir = null, endDir = null;
    static PriorityQueue<Pqn> pq = new PriorityQueue<>(Collections.reverseOrder());

    /**
     * 빛의 방향이 꺾이는 횟수를 거리로 설정한다.
     * 상하 방향에서 도착했을 때와 좌우 방향에서 도착했을 때의 거리를 따로 구한다.
     * 다익스트라 알고리즘을 통해 최단거리를 구하고,
     * 두 방향의 최단거리 중 더 작은 값을 출력하면 된다.
     */
    public static void main(String[] args) throws Exception {
        n = Integer.parseInt(reader.readLine());
        board = new char[n + 2][n + 2];
        Arrays.fill(board[0], WALL);
        Arrays.fill(board[n + 1], WALL);
        for(int i = 1; i <= n; i++) {
            board[i][0] = WALL;
            board[i][n + 1] = WALL;
            String tmp = reader.readLine();
            for(int j = 1; j <= n; j++) {
                board[i][j] = tmp.charAt(j - 1);
                if(board[i][j] == DOOR) {
                    if(startDir == null) startDir = new Dir(i, j);
                    else endDir = new Dir(i, j);
                }
            }
        }
        reader.close();

        dist = new int[2][n + 2][n + 2];
        for(int[][] plane: dist) {
            for(int[] d: plane) Arrays.fill(d, INF);
        }
        dist[0][startDir.row][startDir.col] = 0;
        dist[1][startDir.row][startDir.col] = 0;
        for(int i = 0; i < possDir.length; i++) {
            Dir adj = new Dir(startDir.row + possDir[i].row, startDir.col + possDir[i].col);
            if(board[adj.row][adj.col] != WALL) {
                dist[i / 2][adj.row][adj.col] = 0;
                pq.add(new Pqn(adj, 0, i));
            }
        }
        while(!pq.isEmpty()) {
            Pqn cur = pq.poll();

            if(cur.dist > dist[cur.dirIdx / 2][cur.pos.row][cur.pos.col])
                continue;
            
            if(board[cur.pos.row][cur.pos.col] == EMPTY) {
                Dir nxt = new Dir(cur.pos.row + possDir[cur.dirIdx].row, cur.pos.col + possDir[cur.dirIdx].col);
                if(board[nxt.row][nxt.col] != WALL && cur.dist < dist[cur.dirIdx / 2][nxt.row][nxt.col]) {
                    dist[cur.dirIdx / 2][nxt.row][nxt.col] = cur.dist;
                    pq.add(new Pqn(nxt, cur.dist, cur.dirIdx));
                }
            } else {
                for(int i = 0; i < possDir.length; i++) {
                    Dir nxt = new Dir(cur.pos.row + possDir[i].row, cur.pos.col + possDir[i].col);
                    int newDist = (cur.dirIdx == i ? cur.dist : cur.dist + 1);
                    if(board[nxt.row][nxt.col] != WALL && newDist < dist[i / 2][nxt.row][nxt.col]) {
                        dist[i / 2][nxt.row][nxt.col] = newDist;
                        pq.add(new Pqn(nxt, newDist, i));
                    }
                }
            }
        }

        writer.write(Integer.toString(Math.min(dist[0][endDir.row][endDir.col], dist[1][endDir.row][endDir.col])));

        writer.flush();
        writer.close();
    }
}

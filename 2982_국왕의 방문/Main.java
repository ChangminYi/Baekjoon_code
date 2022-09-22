import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {
    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer parser;

    private static class Pqn implements Comparable<Pqn> {
        private int node, dist;

        private Pqn(int node, int dist) {
            this.node = node;
            this.dist = dist;
        }

        @Override
        public int compareTo(Pqn other) {
            return this.dist - other.dist;
        }
    };

    final private static int INF = Integer.MAX_VALUE / 2;

    private static int n, m, a, b, k, g;
    private static int[] arg = new int[1001];
    private static int[][][] blockTime = new int[1001][1001][2];
    private static int[] dist = new int[1001];
    private static int[][] weight = new int[1001][1001];
    private static ArrayList<Integer>[] adj = new ArrayList[1001];

    /**
     * 다익스트라 알고리즘을 사용하여 최단시간을 구할 수 있다.
     * 특정 노드에 도착했고, 다음 노드를 연결하는 간선을 살필 때
     * 만약 해당 간선이 국왕에 의해 사용 중이라면 국왕이 지나간 후,
     * 즉 다음 노드나 현재 노드에 국왕이 도착한 후에 사용할 수 있다.
     * 이 점을 newDist에 반영하여 다음 노드까지의 시간을 구하면 된다.
     */
    public static void main(String args[]) throws IOException {
        parser = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(parser.nextToken());
        m = Integer.parseInt(parser.nextToken());
        for(int i = 1; i <= n; i++)
            adj[i] = new ArrayList<>();
        parser = new StringTokenizer(reader.readLine());
        a = Integer.parseInt(parser.nextToken());
        b = Integer.parseInt(parser.nextToken());
        k = Integer.parseInt(parser.nextToken());
        g = Integer.parseInt(parser.nextToken());
        parser = new StringTokenizer(reader.readLine());
        for(int i = 0; i < g; i++)
            arg[i] = Integer.parseInt(parser.nextToken());
        for(int u, v; m > 0; m--) {
            parser = new StringTokenizer(reader.readLine());
            u = Integer.parseInt(parser.nextToken());
            v = Integer.parseInt(parser.nextToken());
            adj[u].add(v); adj[v].add(u);
            weight[u][v] = Integer.parseInt(parser.nextToken());
            weight[v][u] = weight[u][v];
        }
        for(int i = 0, base = 0; i < g - 1; i++) {
            blockTime[arg[i]][arg[i + 1]][0] = base;
            blockTime[arg[i + 1]][arg[i]][0] = base;
            blockTime[arg[i]][arg[i + 1]][1] = base + weight[arg[i]][arg[i + 1]];
            blockTime[arg[i + 1]][arg[i]][1] = base + weight[arg[i]][arg[i + 1]];
            base += weight[arg[i]][arg[i + 1]];
        }
        
        dijk();

        writer.write(Integer.toString(dist[b] - dist[a]));
        writer.flush();
        reader.close();
        writer.close();
    }

    private static void dijk() {
        PriorityQueue<Pqn> pq = new PriorityQueue<>();

        Arrays.fill(dist, INF);
        dist[a] = k;
        pq.add(new Pqn(a, dist[a]));
        while(!pq.isEmpty()) {
            int cur = pq.peek().node;
            int curDist = pq.peek().dist;
            pq.remove();

            if(curDist > dist[cur])
                continue;
            for(final int nxt: adj[cur]) {
                int newDist = curDist + weight[cur][nxt];
                if(blockTime[cur][nxt][0] <= curDist && curDist < blockTime[cur][nxt][1])
                    newDist = blockTime[cur][nxt][1] + weight[cur][nxt];

                if(newDist < dist[nxt]) {
                    dist[nxt] = newDist;
                    pq.add(new Pqn(nxt, newDist));
                }
            }
        }
    }
}

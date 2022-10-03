import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {
    private static class Edge {
        int node = 0, cost = 0;
        Edge(int n, int c) {
            this.node = n;
            this.cost = c;
        }
    };

    private static class Node implements Comparable<Node> {
        int node;
        long dist;
        long wSum;

        Node(int n, long d, long w) {
            this.node = n;
            this.dist = d;
            this.wSum = w;
        }

        @Override
        public int compareTo(Main.Node o) {
            if(this.dist != o.dist) return (this.dist < o.dist ? -1 : 1);
            else if(this.wSum == o.wSum) return 0;
            else return (this.wSum < o.wSum ? 1 : -1);
        }

    }

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer tokenizer;

    private static long INF = Long.MAX_VALUE / 2;

    private static int n, m, s, t;
    private static ArrayList<Edge>[] graph;
    private static int[] water;
    private static long[] dist, maxWater;

    /**
     * 다익스트라 알고리즘을 사용하여 최단거리를 구할 수 있다.
     * 최단거리 다음으로 최대수량을 다시 비교하여 우선순위를 정한다.
     * 이를 통해 최단거리-최대수량 쌍을 구할 수 있다.
     * 거리와 수량이 int의 범위를 넘을 수 있음에 주의한다.
     */
    public static void main(String[] args) throws Exception {
        n = Integer.parseInt(reader.readLine());
        water = new int[n + 1];
        graph = new ArrayList[n + 1];
        tokenizer = new StringTokenizer(reader.readLine());
        for(int i = 1; i <= n; i++) {
            graph[i] = new ArrayList<>();
            water[i] = Integer.parseInt(tokenizer.nextToken());
        }
        m = Integer.parseInt(reader.readLine());
        for(int u, v, w; m > 0; m--) {
            tokenizer = new StringTokenizer(reader.readLine());
            u = Integer.parseInt(tokenizer.nextToken());
            v = Integer.parseInt(tokenizer.nextToken());
            w = Integer.parseInt(tokenizer.nextToken());
            graph[u].add(new Edge(v, w));
            graph[v].add(new Edge(u, w));
        }
        tokenizer = new StringTokenizer(reader.readLine());
        s = Integer.parseInt(tokenizer.nextToken());
        t = Integer.parseInt(tokenizer.nextToken());

        maxWater = new long[n + 1];
        dist = new long[n + 1];
        dijk();

        if(dist[t] == INF)
            writer.write("-1");
        else
            writer.write(Long.toString(dist[t]) + " " + Long.toString(maxWater[t]));

        writer.flush();
        writer.close();
        reader.close();
    }

    private static void dijk() {
        PriorityQueue<Node> pq = new PriorityQueue<>();

        Arrays.fill(dist, INF);
        dist[s] = 0;
        maxWater[s] = water[s];
        pq.add(new Node(s, dist[s], maxWater[s]));
        while(!pq.isEmpty()) {
            Node cur = pq.poll();

            if(cur.dist > dist[cur.node] || cur.wSum < maxWater[cur.node])
                continue;
            for(Edge adj: graph[cur.node]) {
                long newDist = cur.dist + adj.cost;
                long newWater = cur.wSum + water[adj.node];
                if(newDist < dist[adj.node]) {
                    dist[adj.node] = newDist;
                    maxWater[adj.node] = newWater;
                    pq.add(new Node(adj.node, newDist, newWater));
                }
                else if(newDist == dist[adj.node] && newWater > maxWater[adj.node]) {
                    maxWater[adj.node] = newWater;
                    pq.add(new Node(adj.node, dist[adj.node], newWater));
                }
            }
        }
    }
}
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.PriorityQueue;

public class Main {
    private static class Edge {
        int adj, time;
        public Edge(int _n, int _t) {
            this.adj = _n;
            this.time = _t;
        }
    }

    private static class Node implements Comparable<Node> {
        int node;
        long dist;
        
        public Node(int _n, long _d) {
            this.node = _n;
            this.dist = _d;
        }

        public int compareTo(Node other) {
            if(this.dist == other.dist) return 0;
            else if(this.dist < other.dist) return -1;
            else return 1;
        }
    };

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static String[] tmp;

    private final static long INF = Long.MAX_VALUE / 2;
    private final static int START = 1;

    private static int n, m;
    private static ArrayList<Edge> graph[] = new ArrayList[100001];
    private static long dist[] = new long[100001];
    private static PriorityQueue<Node> pq = new PriorityQueue<>();

    /**
     * 다익스트라 알고리즘을 통해 최단 시간을 구할 수 있다.
     * 모든 간선의 cost는 1이고 m의 주기로 사용 가능함을 고려해야 한다.
     * 건널 수 있는 가장 빠른 시간을 최단거리로 설정한다.
     * 최단 시간의 범위가 int를 넘어갈 수 있다.
     */
    public static void main(String args[]) throws IOException {
        tmp = reader.readLine().split(" ");
        n = Integer.parseInt(tmp[0]);
        m = Integer.parseInt(tmp[1]);
        for(int i = 1; i <= n; i++) {
            graph[i] = new ArrayList<>();
            dist[i] = INF;
        }
        for(int i = 0, u, v; i < m; i++) {
            tmp = reader.readLine().split(" ");
            u = Integer.parseInt(tmp[0]);
            v = Integer.parseInt(tmp[1]);
            graph[u].add(new Edge(v, i));
            graph[v].add(new Edge(u, i));
        }

        dist[START] = 0;
        pq.add(new Node(START, dist[START]));
        while(!pq.isEmpty()) {
            Node cur = pq.poll();

            if(cur.dist > dist[cur.node])
                continue;
            for(Edge edge: graph[cur.node]) {
                long newDist = cur.dist + edge.time + 1 - (cur.dist % m);
                if(cur.dist % m > edge.time)
                    newDist += m;
                
                if(newDist >= dist[edge.adj])
                    continue;
                dist[edge.adj] = newDist;
                pq.add(new Node(edge.adj, newDist));
            }
        }

        writer.write(Long.toString(dist[n]));

        writer.flush();
        reader.close();
        writer.close();
    }
}

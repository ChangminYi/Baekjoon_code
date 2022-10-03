import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
    private static class Edge {
        private int node = 0, cost = 0;
        Edge(int n, int c) {
            this.node = n;
            this.cost = c;
        }
    }

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer tokenizer;

    private static int ROOT = 1;
    private static int NOT_VISIT = -1;

    private static int t, n, m;
    private static ArrayList<Edge>[] graph = new ArrayList[1001];
    private static ArrayList<Edge>[] child = new ArrayList[1001];
    private static int[] dp = new int[1001];
    private static boolean[] isLeaf = new boolean[1001];

    /**
     * 루트 노드와 연결된 리프 노드가 없도록 하면 된다.
     * 이 때, 다리를 끊는 최소비용은 특정 노드의 자식들에 대하여
     * 자식과 연결된 간선을 끊는 것과 자식을 끊지 않았을 때의 자식의
     * 최소비용 중 더 작은 값을 모두 더한 값과 같다.
     */
    public static void main(String[] args) throws Exception {
        for(int i = 1; i <= 1000; i++) {
            graph[i] = new ArrayList<>();
            child[i] = new ArrayList<>();
        }

        t = Integer.parseInt(reader.readLine());
        do {
            tokenizer = new StringTokenizer(reader.readLine());
            n = Integer.parseInt(tokenizer.nextToken());
            m = Integer.parseInt(tokenizer.nextToken());

            for(int i = 1; i <= n; i++) {
                graph[i].clear();
                child[i].clear();
                dp[i] = NOT_VISIT;
                isLeaf[i] = true;
            }
            for(int u, v, w; m > 0; m--) {
                tokenizer = new StringTokenizer(reader.readLine());
                u = Integer.parseInt(tokenizer.nextToken());
                v = Integer.parseInt(tokenizer.nextToken());
                w = Integer.parseInt(tokenizer.nextToken());
                graph[u].add(new Edge(v, w));
                graph[v].add(new Edge(u, w));
            }

            initTree(ROOT, NOT_VISIT);

            writer.write(Integer.toString(getDp(ROOT)) + "\n");
        } while(--t > 0);

        writer.flush();
        writer.close();
        reader.close();
    }

    private static void initTree(int cur, int par) {
        for(Edge edge: graph[cur]) {
            if(edge.node == par)
                continue;
            isLeaf[cur] = false;
            child[cur].add(edge);
            initTree(edge.node, cur);
        }
    }

    private static int getDp(int cur) {
        if(dp[cur] == NOT_VISIT) {
            dp[cur] = 0;
            for(Edge edge: child[cur]) {
                if(isLeaf[edge.node])
                    dp[cur] += edge.cost;
                else
                    dp[cur] += Math.min(edge.cost, getDp(edge.node));
            }
        }

        return dp[cur];
    }
}
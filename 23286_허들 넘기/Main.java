import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

class PQ_node implements Comparable<PQ_node> {
    public int node, height;
    
    PQ_node(final int node, final int height) {
        this.node = node;
        this.height = height;
    }

    public int compareTo(final PQ_node other) {
        if(this.height < other.height) return 1;
        else if(this.height > other.height) return -1;
        else return 0;
    }
}

public class Main {
    final static int INF = 1000000000;

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringBuilder ans = new StringBuilder();
    private static StringTokenizer parser;

    private static int n, m, t;
    private static ArrayList<ArrayList<Integer>> graph = new ArrayList<>(301);
    private static int[][] weight = new int[301][301];
    private static int[][] max_height = new int[301][301];
    private static PriorityQueue<PQ_node> pq = new PriorityQueue<>(Collections.reverseOrder());

    public static void main(String[] args) throws Exception {
        /**
         * 최단 거리를 두 노드 사이의 구간의 허들의 높이의 최솟값 중 최댓값으로 정의.
         * 다익스트라 알고리즘으로 모든 노드에 대해서 최단 거리를 구하고,
         * 미리 구한 거리를 이용하여 쿼리에 대해서 답을 출력만 하면 된다.
         */

        parser = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(parser.nextToken());
        m = Integer.parseInt(parser.nextToken());
        t = Integer.parseInt(parser.nextToken());

        for(int i = 0; i <= n; i++) {
            graph.add(new ArrayList<Integer>());
            Arrays.fill(max_height[i], INF);
            Arrays.fill(weight[i], INF);
        }

        for(int u, v, h; m > 0; m--) {
            parser = new StringTokenizer(reader.readLine());
            u = Integer.parseInt(parser.nextToken());
            v = Integer.parseInt(parser.nextToken());
            h = Integer.parseInt(parser.nextToken());
            weight[u][v] = Math.min(weight[u][v], h);
            graph.get(u).add(v);
        }

        for(int i = 1; i <= n; i++) {
            dijk(i);
        }

        for(int s, e; t > 0; t--) {
            parser = new StringTokenizer(reader.readLine());
            s = Integer.parseInt(parser.nextToken());
            e = Integer.parseInt(parser.nextToken());
            ans.append(Integer.toString(max_height[s][e]));
            ans.append("\n");
        }


        writer.write(ans.toString());
        writer.flush();
        writer.close();
        reader.close();
    }

    private static void dijk(final int start) {
        max_height[start][start] = 0;
        pq.add(new PQ_node(start, 0));

        while(!pq.isEmpty()) {
            PQ_node cur = pq.poll();

            if(cur.height <= max_height[start][cur.node]) {
                for(final int nxt: graph.get(cur.node)) {
                    int new_height = Math.max(cur.height, weight[cur.node][nxt]);
                    if(new_height < max_height[start][nxt]) {
                        max_height[start][nxt] = new_height;
                        pq.add(new PQ_node(nxt, new_height));
                    }
                }
            }
        }

        for(int i = 1; i <= n; i++) {
            if(max_height[start][i] == INF) max_height[start][i] = -1;
        }
    } 
}

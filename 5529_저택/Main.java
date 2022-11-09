import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.PriorityQueue;
import java.util.StringTokenizer;


public class Main {
    static class Node {
        int row, col, idx;
        boolean isSwitch;

        Node(int row, int col, int idx, boolean isSwitch) {
            this.row = row;
            this.col = col;
            this.idx = idx;
            this.isSwitch = isSwitch;
        }
    }

    static class Edge {
        int adj, cost;

        Edge(int adj, int cost) {
            this.adj = adj;
            this.cost = cost;
        }
    }

    static class Pqn implements Comparable<Pqn> {
        int node, idx;
        long dist;

        Pqn(int node, int idx, long dist) {
            this.node = node;
            this.idx = idx;
            this.dist = dist;
        }

        @Override
        public int compareTo(Pqn other) {
            if(this.dist == other.dist) return 0;
            else return (this.dist < other.dist ? 1 : -1);
        }
    }

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    final static long INF = Long.MAX_VALUE / 2;
    final static int NOT_FOUND = -1;

    static int n, m, k;
    static ArrayList<Node> arg = new ArrayList<>();
    static ArrayList<Edge> graph[][];
    static long dist[][];
    static PriorityQueue<Pqn> pq = new PriorityQueue<>(Collections.reverseOrder());

    /**
     * 문이 상하로 열린 상태와 좌우로 열린 상태를 구분하기 위해
     * 거리 배열을 2차원으로 구성하고, 탐색 시에 인덱스를 같이 저장한다.
     * 스위치가 있는 노드끼리 간선으로 잇고, 해당 그래프를 기준으로
     * 다익스트라 알고리즘을 통해 최단거리를 구한다.
     */
    public static void main(String[] args) throws Exception {
        int startNode = NOT_FOUND, endNode = NOT_FOUND;
        
        tokenizer = new StringTokenizer(reader.readLine());
        m = Integer.parseInt(tokenizer.nextToken());
        n = Integer.parseInt(tokenizer.nextToken());
        k = Integer.parseInt(tokenizer.nextToken());
        for(int i = 0, row, col; i < k; i++) {
            tokenizer = new StringTokenizer(reader.readLine());
            col = Integer.parseInt(tokenizer.nextToken());
            row = Integer.parseInt(tokenizer.nextToken());
            arg.add(new Node(row, col, i, true));

            if(row == 1 && col == 1) startNode = i;
            if(row == n && col == m) endNode = i;
        }
        reader.close();
        if(startNode == NOT_FOUND)
            arg.add(new Node(1, 1, (startNode = arg.size()), false));
        if(endNode == NOT_FOUND)
            arg.add(new Node(n, m, (endNode = arg.size()), true));

        graph = new ArrayList[2][arg.size()];
        for(int i = 0; i < graph[0].length; i++) {
            graph[0][i] = new ArrayList<>();
            graph[1][i] = new ArrayList<>();
        }

        Collections.sort(arg, (Node lhs, Node rhs)->{
            if(lhs.col != rhs.col) return lhs.col - rhs.col;
            else return lhs.row - rhs.row;
        });
        for(int i = 1, n1, n2, edgeLen; i < arg.size(); i++) {
            if(arg.get(i - 1).col == arg.get(i).col) {
                n1 = arg.get(i - 1).idx;
                n2 = arg.get(i).idx;
                edgeLen = arg.get(i).row - arg.get(i - 1).row;
                graph[0][n1].add(new Edge(n2, edgeLen));
                graph[0][n2].add(new Edge(n1, edgeLen));
            }
        }
        Collections.sort(arg, (Node lhs, Node rhs)->{
            if(lhs.row != rhs.row) return lhs.row - rhs.row;
            else return lhs.col - rhs.col;
        });
        for(int i = 1, n1, n2, edgeLen; i < arg.size(); i++) {
            if(arg.get(i - 1).row == arg.get(i).row && arg.get(i - 1).isSwitch && arg.get(i).isSwitch) {
                n1 = arg.get(i - 1).idx;
                n2 = arg.get(i).idx;
                edgeLen = arg.get(i).col - arg.get(i - 1).col;
                graph[1][n1].add(new Edge(n2, edgeLen));
                graph[1][n2].add(new Edge(n1, edgeLen));
            }
        }
        Collections.sort(arg, (Node lhs, Node rhs)->{
            return lhs.idx - rhs.idx;
        });

        dist = new long[2][arg.size()];
        for(long r[]: dist) Arrays.fill(r, INF);

        dist[0][startNode] = 0;
        pq.add(new Pqn(startNode, 0, 0));
        while(!pq.isEmpty()) {
            Pqn cur = pq.poll();

            if(cur.dist <= dist[cur.idx][cur.node]) {
                for(Edge edge: graph[cur.idx][cur.node]) {
                    long newDist = cur.dist + edge.cost;
                    if(newDist < dist[cur.idx][edge.adj]) {
                        dist[cur.idx][edge.adj] = newDist;
                        pq.add(new Pqn(edge.adj, cur.idx, newDist));
                    }
                }
            }
            if(arg.get(cur.idx).isSwitch) {
                int nxtIdx = (cur.idx + 1) % 2;
                if(cur.dist + 1 < dist[nxtIdx][cur.node]) {
                    dist[nxtIdx][cur.node] = cur.dist + 1;
                    pq.add(new Pqn(cur.node, nxtIdx, cur.dist + 1));
                }
            }
        }

        long minDist = Math.min(dist[0][endNode], dist[1][endNode]);
        if(minDist == INF) writer.write("-1");
        else writer.write(Long.toString(minDist));

        writer.flush();
        writer.close();
    }
}

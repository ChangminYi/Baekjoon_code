import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
    final private static int NO_PARENT = -1;

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer parser;

    private static int n, k, a, b;
    private static String[] arg = new String[1000];
    private static ArrayList<ArrayList<Integer>> graph = new ArrayList<>(1000);
    private static boolean[] visit = new boolean[1000];
    private static int[] parent = new int[1000];
    private static Queue<Integer> que = new LinkedList<Integer>();
    private static Stack<Integer> trace = new Stack<>();

    public static void main(String[] args) throws Exception {
    /**
     * 두 문자열의 해밍 거리가 1일 경우 두 노드의 간선을 잇는다.
     * 그래프를 구축한 후, bfs를 하면서 현재 노드의 직전 노드를 기억한다.
     * 도착점부터 경로를 역추적하고, 출력한다.
     */

        parser = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(parser.nextToken());
        k = Integer.parseInt(parser.nextToken());
        Arrays.fill(visit, false);
        Arrays.fill(parent, NO_PARENT);
        for(int i = 0; i < n; i++) {
            arg[i] = reader.readLine();
            graph.add(new ArrayList<Integer>());
        }
        for(int i = 0; i < n - 1; i++) {
            for(int j = i + 1; j < n; j++) {
                if(getHammingDistance(i, j) == 1) {
                    graph.get(i).add(j);
                    graph.get(j).add(i);
                }
            }
        }
        parser = new StringTokenizer(reader.readLine());
        a = Integer.parseInt(parser.nextToken());
        b = Integer.parseInt(parser.nextToken());

        bfs(a - 1);
        if(visit[b - 1]) {
            for(int cur = b - 1; cur != NO_PARENT; cur = parent[cur]) {
                trace.add(cur + 1);
            }

            while(!trace.isEmpty()) {
                writer.write(Integer.toString(trace.pop()) + " ");
            }
        }
        else {
            writer.write(Integer.toString(-1));
        }
        writer.flush();
    }

    private static void bfs(final int start) {
        visit[start] = true;
        que.add(start);
        while(!que.isEmpty()) {
            int cur = que.poll();

            for(final int nxt: graph.get(cur)) {
                if(!visit[nxt]) {
                    visit[nxt] = true;
                    parent[nxt] = cur;
                    que.add(nxt);
                }
            }
        }
    }

    private static int getHammingDistance(final int lhs, final int rhs) {
        int ret = 0;
        for(int i = 0; i < k; i++) {
            if(arg[lhs].charAt(i) != arg[rhs].charAt(i)) {
                ret++;
            }
        }
        return ret;
    }
}

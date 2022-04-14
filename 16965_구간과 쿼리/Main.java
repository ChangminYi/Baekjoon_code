import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
    final private static int MAX_SIZE = 101;

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer parser;
    private static StringBuilder ans = new StringBuilder();

    private static int n;
    private static int nodeCount = 0;
    private static int range[][] = new int[MAX_SIZE][2];
    private static ArrayList<ArrayList<Integer>> graph = new ArrayList<ArrayList<Integer>>(MAX_SIZE);
    private static boolean[] visit = new boolean[101];

    public static void main(String args[]) throws Exception {
        /**
         * 1번 명령이 들어오면 그래프에 노드를 추가하고,
         * 2번 명령이 들어오면 bfs를 실행하여 도달 가능한지를 확인한다.
         * 노드를 추가할 때, 노드 간 인접 검사를 정확히 구현해야 한다.
         */
        for(int i = 1; i < MAX_SIZE; i++) graph.add(new ArrayList<Integer>());

        n = Integer.parseInt(reader.readLine());
        for(int inst, lo, hi; n > 0; n--) {
            parser = new StringTokenizer(reader.readLine());
            inst = Integer.parseInt(parser.nextToken());
            lo = Integer.parseInt(parser.nextToken());
            hi = Integer.parseInt(parser.nextToken());

            if(inst == 1) {
                nodeCount++;
                range[nodeCount][0] = lo;
                range[nodeCount][1] = hi;

                for(int i = 1; i <= nodeCount - 1; i++) {
                    if(isConnected(i, nodeCount)) graph.get(i).add(nodeCount);
                    if(isConnected(nodeCount, i)) graph.get(nodeCount).add(i);
                }
            }
            else {
                if(bfs(lo, hi)) ans.append("1\n");
                else ans.append("0\n");
            }
        }

        writer.write(ans.toString());
        writer.flush();
        writer.close();
        reader.close();
    }

    private static boolean isConnected(final int from, final int to) {
        return (range[to][0] < range[from][0] && range[from][0] < range[to][1]) || (range[to][0] < range[from][1] && range[from][1] < range[to][1]);
    }

    private static boolean bfs(final int start, final int dest) {
        Arrays.fill(visit, false);
        Queue<Integer> que = new LinkedList<Integer>();

        visit[start] = true;
        que.add(start);
        while(!que.isEmpty()) {
            int cur = que.poll();

            if(cur == dest) {
                return true;
            }
            for(final int nxt: graph.get(cur)) {
                if(!visit[nxt]) {
                    visit[nxt] = true;
                    que.add(nxt);
                }
            }
        }

        return false;
    }
}

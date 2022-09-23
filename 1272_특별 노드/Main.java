import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer parser;
    
    private final static int NOT_VISIT = -1;

    private static int n, root;
    private static int[] weight = new int[1001];
    private static int[][] dp = new int[1001][1001];
    private static boolean[] visit = new boolean[1001];
    private static ArrayList<Integer>[] adj = new ArrayList[1001];

    /**
     * 트리를 dfs로 탐색하면서, 현재 노드에서 가장 가까운 특별노드를 기준으로
     * dp 배열에 가중치 합의 최솟값을 채운다. 자식이 일반노드인 것과 특별노드인 것 중
     * 더 작은 가중치를 가지는 것을 반환하면 된다.
     */
    public static void main(String args[]) throws IOException {
        parser = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(parser.nextToken());
        root = Integer.parseInt(parser.nextToken());
        parser = new StringTokenizer(reader.readLine());
        for(int i = 1; i <= n; i++) {
            adj[i] = new ArrayList<>();
            weight[i] = Integer.parseInt(parser.nextToken());
        }
        for(int i = 0, u, v; i < n - 1; i++) {
            parser = new StringTokenizer(reader.readLine());
            u = Integer.parseInt(parser.nextToken());
            v = Integer.parseInt(parser.nextToken());
            adj[u].add(v);
            adj[v].add(u);
        }
        for(int i = 1; i <= n; i++)
            Arrays.fill(dp[i], NOT_VISIT);

        writer.write(Integer.toString(dfs(root, root)));

        writer.flush();
        reader.close();
        writer.close();
    }

    private static int dfs(final int cur, final int lastSp) {
        if(dp[cur][lastSp] != NOT_VISIT)
            return dp[cur][lastSp];
        
        int resNormal = weight[cur] - weight[lastSp];
        int resSp = weight[cur];

        visit[cur] = true;
        for(final int child: adj[cur]) {
            if(visit[child]) continue;
            resSp += dfs(child, cur);
            if(cur != root) resNormal += dfs(child, lastSp);
        }
        visit[cur] = false;

        return dp[cur][lastSp] = (cur == root ? resSp : Math.min(resNormal, resSp));
    }
}

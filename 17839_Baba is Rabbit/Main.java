import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    static int n, cnt = 1;
    static Map<String, Integer> strNum = new HashMap<>();
    static ArrayList<String> strList = new ArrayList<>();
    static ArrayList<ArrayList<Integer>> graph = new ArrayList<>();

    /**
     * 등장하는 이름마다 번호를 설정하여 노드로 간주한다.
     * 사이클이 존재하지 않는 유향 그래프이므로, 루트에서부터 탐색하며
     * 방문한 적 없는 모든 노드의 문자열 값을 정렬하여 출력한다.
     */
    public static void main(String[] args) throws Exception {
        strNum.put("Baba", 0);
        strList.add("Baba");
        graph.add(new ArrayList<>());

        n = Integer.parseInt(reader.readLine());
        for(int i = 0; i < n; i++) {
            String tmp[] = reader.readLine().split(" ");
            Integer from, to;
            if((from = strNum.get(tmp[0])) == null) {
                graph.add(new ArrayList<>());
                strList.add(tmp[0]);
                from = cnt;
                strNum.put(tmp[0], cnt++);
            }
            if((to = strNum.get(tmp[2])) == null) {
                graph.add(new ArrayList<>());
                strList.add(tmp[2]);
                to = cnt;
                strNum.put(tmp[2], cnt++);
            }
            graph.get(from).add(to);
        }

        ArrayList<String> ans = new ArrayList<>();
        Queue<Integer> q = new LinkedList<>();
        boolean visit[] = new boolean[cnt];
        q.add(0);
        visit[0] = true;
        while(!q.isEmpty()) {
            int cur = q.poll();
            for(int nxt: graph.get(cur)) {
                if(!visit[nxt]) {
                    visit[nxt] = true;
                    ans.add(strList.get(nxt));
                    q.add(nxt);
                }
            }
        }

        Collections.sort(ans);
        for(String s: ans) {
            writer.write(s + "\n");
        }

        writer.flush();
        writer.close();
    }
}

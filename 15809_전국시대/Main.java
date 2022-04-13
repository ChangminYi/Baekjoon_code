import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.util.PriorityQueue;
import java.util.StringTokenizer;
import java.io.InputStreamReader;


public class Main {
    final private static int MAX_SIZE = 100001;
    final private static int ALLIANCE = 1;

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer parser;

    private static int n, m, totalNum;
    private static int[] parent = new int[MAX_SIZE];
    private static int[] size = new int[MAX_SIZE];
    private static PriorityQueue<Integer> pq = new PriorityQueue<>();

    public static void main(String[] args) throws Exception {
        /**
         * union-find를 사용하여 동맹/속국의 상태를 관리할 수 있다.
         * 동맹을 하면 전체 집합의 크기를 두 집합의 크기의 합으로 늘려주고,
         * 전쟁을 하면 집합의 크기를 크기의 차로 줄인다. 만약 두 집합 크기가 같다면 둘 다 0이다.
         * 쿼리를 수행하고 남은 집합의 수와 0이 아닌 집합의 크기를 정렬하여 출력하면 된다.
         */

        parser = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(parser.nextToken());
        m = Integer.parseInt(parser.nextToken());

        totalNum = n;
        for(int i = 1; i <= n; i++) {
            size[i] = Integer.parseInt(reader.readLine());
        }
        initParent();
        
        for(int o, p, q; m > 0; m--) {
            parser = new StringTokenizer(reader.readLine());
            o = Integer.parseInt(parser.nextToken());
            p = findParent(Integer.parseInt(parser.nextToken()));
            q = findParent(Integer.parseInt(parser.nextToken()));

            if (o == ALLIANCE) {
                parent[q] = p;
                size[p] += size[q];
                size[q] = 0;
                totalNum--;
            }
            else {
                if(size[p] > size[q]) {
                    parent[q] = p;
                    size[p] -= size[q];
                    size[q] = 0;
                    totalNum--;
                }
                else if(size[p] < size[q]) {
                    parent[p] = q;
                    size[q] -= size[p];
                    size[p] = 0;
                    totalNum--;
                }
                else {
                    size[p] = 0;
                    size[q] = 0;
                    totalNum -= 2;
                }
            }
        }

        for(int i = 1; i <= n; i++) {
            if(size[i] != 0) {
                pq.add(size[i]);
            }
        }

        writer.write(Integer.toString(totalNum) + "\n");
        for(; !pq.isEmpty(); pq.poll()) {
            writer.write(Integer.toString(pq.peek()) + " ");
        }
        writer.flush();
    }

    private static int findParent(final int x) {
        if(parent[x] == x) return x;
        else return parent[x] = findParent(parent[x]);
    }

    private static void initParent() {
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
}

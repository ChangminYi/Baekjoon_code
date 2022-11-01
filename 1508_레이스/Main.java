import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;


public class Main {
    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    final static long UNAVAIL = 0;

    static int n, m, k;
    static int[] dist;

    /**
     * 심판 사이의 거리를 최대로 해야 하므로, 심판 사이의 거리를
     * 매개변수로 하는 이분탐색을 통해 최대 거리를 구한다.
     * 정답이 사전 순으로 가장 늦은 것을 출력해야 하므로,
     * 심판 간 거리가 만족되는 즉시 해당 자리를 선택하여
     * 이진수로 표현하였을 때 값이 가장 큰 조합을 고르면 된다.
     * 비트를 사용할 때, int와 long의 표현 범위를 조심한다.
     */
    public static void main(String[] args) throws Exception {
        tokenizer = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());
        k = Integer.parseInt(tokenizer.nextToken());
        dist = new int[k];
        tokenizer = new StringTokenizer(reader.readLine());
        for(int i = 0; i < k; i++)
            dist[i] = Integer.parseInt(tokenizer.nextToken());
        reader.close();

        int lo = 0, hi = n;
        long visitBit = 0, tmpBit;
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            if((tmpBit = simulate(mid)) == UNAVAIL) {
                hi = mid - 1;
            } else {
                visitBit = tmpBit;
                lo = mid + 1;
            }
        }

        for(int i = 0; i < k; i++) {
            writer.write((visitBit & (1L << i)) == 0 ? "0" : "1");
        }

        writer.flush();
        writer.close();
    }

    static long simulate(int minDist) {
        int lastSelect = dist[0];
        int cnt = 1;
        long visitBit = 1;

        for(int i = 1; i < k && cnt < m; i++) {
            if(dist[i] - lastSelect >= minDist) {
                lastSelect = dist[i];
                visitBit |= (1L << i);
                cnt++;
            }
        }

        return (cnt == m ? visitBit : UNAVAIL);
    }
}

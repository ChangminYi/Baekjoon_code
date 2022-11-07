import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;


public class Main {

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    final static int COL_SIZE = 5;

    static int n;
    static String arg[];
    static int dp[][];

    /**
     * 사용한 단어의 상태와 마지막으로 끝난 알파벳을 알아야 하므로, dp 배열을 2차원으로 관리한다.
     * 모든 가능한 조합의 비트에 대해, 현재 사용한 단어 비트를 기준으로
     * 특정 단어 하나를 사용하지 않은 상태와 사용하지 않은 특정 단어를 이었을 때
     * 만들 수 있는 길이의 최댓값을 갱신하며 최댓값을 찾는다.
     */
    public static void main(String[] args) throws Exception {
        n = Integer.parseInt(reader.readLine());
        arg = new String[n];
        dp = new int[1 << n][COL_SIZE];
        for(int i = 0; i < n; i++) {
            arg[i] = reader.readLine();
        }

        int ans = 0;
        for(int i = 1, prev, lastEnd, curEnd; i < (1 << n); i++) {
            for(int j = 0; j < n; j++) {
                if((i & (1 << j)) == 0) continue;

                prev = i ^ (1 << j);
                lastEnd = charToInt(arg[j].charAt(0));
                curEnd = charToInt(arg[j].charAt(arg[j].length() - 1));
                dp[i][curEnd] = Math.max(dp[i][curEnd], dp[prev][lastEnd] + arg[j].length());
                ans = Math.max(ans, dp[i][curEnd]);
            }
        }

        writer.write(Integer.toString(ans));

        writer.flush();
        writer.close();
    }

    static int charToInt(final char c) {
        switch(c) {
            case 'A': return 0;
            case 'E': return 1;
            case 'I': return 2;
            case 'O': return 3;
            default: return 4;
        }
    }
}

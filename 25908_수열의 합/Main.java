import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;


public class Main {
    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    static int s, t;

    /**
     * 1부터 n까지의 범위에서, 해당 범위 안의 모든 소인수의 수는
     * i는 1부터 n까지일 때, n / i의 총합과 같다.
     * 홀짝을 구분하여 1~t, 1~s-1까지의 소인수의 수를 구하고
     * 앞에서 뒤의 값을 빼면 정답을 구할 수 있다.
     */
    public static void main(String[] args) throws Exception {
        tokenizer = new StringTokenizer(reader.readLine());
        s = Integer.parseInt(tokenizer.nextToken());
        t = Integer.parseInt(tokenizer.nextToken());

        writer.write(Long.toString(getSigma(t) - getSigma(s - 1)));

        reader.close();
        writer.flush();
        writer.close();
    }

    public static long getSigma(int val) {
        long ret = 0;

        for(int i = 1, sign = -1; i <= val; i++) {
            ret += sign * (val / i);
            sign *= -1;
        }

        return ret;
    }
}

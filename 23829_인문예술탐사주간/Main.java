import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer parser;
    
    private static int n, q;
    private static int[] arg;
    private static long[] presum;

    /**
     * 배열이 정렬되었다는 보장이 없으므로, 입력받은 후 정렬한다.
     * 배열의 누적합을 구하여 구간 합을 빠르게 구한다.
     * upperBound를 사용하여 입력받은 값보다 큰 첫번째 값을 찾고,
     * 구간을 나눠서 구간의 거리 합의 절댓값을 구하면 된다.
     * lowerBound를 구현하여 식을 변형해도 된다.
     */
    public static void main(String args[]) throws IOException {
        parser = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(parser.nextToken());
        q = Integer.parseInt(parser.nextToken());

        arg = new int[n];
        presum = new long[n];
        parser = new StringTokenizer(reader.readLine());
        for(int i = 0; i < n; i++)
            arg[i] = Integer.parseInt(parser.nextToken());
        
        Arrays.sort(arg);
        presum[0] = arg[0];
        for(int i = 1; i < n; i++)
            presum[i] = presum[i - 1] + arg[i];

        for(int val, ub; q > 0; q--) {
            val = Integer.parseInt(reader.readLine());
            ub = upperBound(arg, val);
        
            long ans = 0;
            if(ub == 0)
                ans = presum[n - 1] - (long)val * n;
            else
                ans = (long)val * (2 * ub - n) + presum[n - 1] - 2 * presum[ub - 1];
            writer.write(ans + "\n");
        }

        writer.flush();
        reader.close();
        writer.close();
    }

    private static int upperBound(int[] arr, int val) {
        int lo = 0, hi = n, mid = 0;
        while(lo < hi) {
            mid = (lo + hi) / 2;
            if(arr[mid] <= val)
                lo = mid + 1;
            else
                hi = mid;
        }
        return hi;
    }
}

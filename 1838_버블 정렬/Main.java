import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;
import java.util.StringTokenizer;


public class Main {
    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    static int n;
    static int arg[], argSort[];

    /**
     * 버블 정렬에서, 가장 큰 값은 한 번에 자리를 찾아가지만
     * 다른 값들은 한 칸씩 앞으로 이동한다. 따라서 앞으로 이동하는
     * 수들 중에서 이동 횟수가 가장 많을 때를 출력하면 된다.
     */
    public static void main(String[] args) throws Exception {
        n = Integer.parseInt(reader.readLine());
        arg = new int[n];
        argSort = new int[n];
        tokenizer = new StringTokenizer(reader.readLine());
        for(int i = 0; i < n; i++) {
            arg[i] = Integer.parseInt(tokenizer.nextToken());
            argSort[i] = arg[i];
        }
        reader.close();

        Arrays.sort(argSort);

        int ans = 0;
        for(int i = 0; i < n; i++) {
            int sortIdx = Arrays.binarySearch(argSort, arg[i]);
            if(i > sortIdx)
                ans = Math.max(ans, i - sortIdx);
        }

        writer.write(Integer.toString(ans));

        writer.flush();
        writer.close();
    }
}

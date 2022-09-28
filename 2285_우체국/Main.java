import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;

public class Main {
    private static class Pair implements Comparable<Pair> {
        public int first = 0, second = 0;
        Pair(int f, int s) {
            first = f;
            second = s;
        }
        public int compareTo(Pair other) {
            if(first != other.first) return first - other.first;
            else return second - other.second;
        }
    };

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static String[] tmp;

    public static void main(String args[]) throws IOException {
        long totalSum = 0, preSum = 0;
        int n = Integer.parseInt(reader.readLine());
        Pair[] arg = new Pair[n];
        for(int i = 0; i < n; i++) {
            tmp = reader.readLine().split(" ");
            arg[i] = new Pair(Integer.parseInt(tmp[0]), Integer.parseInt(tmp[1]));
            totalSum += arg[i].second;
        }

        Arrays.sort(arg);
        for(int i = 0; i < n; i++) {
            preSum += arg[i].second;
            if(2 * preSum >= totalSum) {
                writer.write(Integer.toString(arg[i].first));
                break;
            }
        }

        
        writer.flush();
        reader.close();
        writer.close();
    }
}

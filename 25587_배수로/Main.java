import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;

public class Main {
    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer parser;

    private static int[] parent = new int[100001];
    private static int[] setSize = new int[100001];
    private static int[] maxFlow = new int[100001];
    private static int[] rain = new int[100001];
    private static int n, m, floodCount = 0;

    /**
     * 유니언-파인드를 사용하여 배수로를 공유하는 도시를 관리할 수 있다.
     * 배수로 용량과 강수량을 입력받을 때, 홍수가 나는 도시의 수를 초기화한다.
     * 유니언을 합치기 전, 홍수가 날 집합의 크기를 카운트에서 뺐다가
     * 유니언 후 합집합이 홍수가 난다면 카운트에 합집합의 크기를 더한다.
     */
    public static void main(String args[]) throws IOException {
        parser = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(parser.nextToken());
        m = Integer.parseInt(parser.nextToken());
        
        parser = new StringTokenizer(reader.readLine());
        for(int i = 1; i <= n; i++)
            maxFlow[i] = Integer.parseInt(parser.nextToken());
        parser = new StringTokenizer(reader.readLine());
        for(int i = 1; i <= n; i++)
            rain[i] = Integer.parseInt(parser.nextToken());
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
            setSize[i] = 1;
            if(rain[i] > maxFlow[i]) floodCount++;
        }

        for(int inst, a, b; m > 0; m--) {
            parser = new StringTokenizer(reader.readLine());
            inst = Integer.parseInt(parser.nextToken());
            if(inst == 1) {
                a = Integer.parseInt(parser.nextToken());
                b = Integer.parseInt(parser.nextToken());
                
                if(findParent(a) != findParent(b)) unionSet(a, b);
            }
            else
                writer.write(Integer.toString(floodCount) + "\n");
        }

        writer.flush();
        writer.close();
        reader.close();
    }

    private static void unionSet(final int x, final int y) {
        int parX = findParent(x), parY = findParent(y);
        if(rain[parX] > maxFlow[parX]) floodCount -= setSize[parX];
        if(rain[parY] > maxFlow[parY]) floodCount -= setSize[parY];

        setSize[parX] += setSize[parY];
        maxFlow[parX] += maxFlow[parY];
        rain[parX] += rain[parY];
        parent[parY] = parX;
        if(rain[parX] > maxFlow[parX]) floodCount += setSize[parX];
    }

    private static int findParent(final int x) {
        if(parent[x] == x) return x;
        else return parent[x] = findParent(parent[x]);
    }
}

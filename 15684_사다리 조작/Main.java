import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;

public class Main {
    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer tokenizer;

    private static int n, m, h;
    private static boolean[][] hasHorizontal = new boolean[32][11];

    /**
     * 가능한 모든 구역에 가로선을 놓아보며 브루트포스로 탐색.
     * 0개를 놓았을 때부터 3개를 놓았을 때까지 만약 답을 찾았다면
     * 탐색을 중단하고 바로 답을 출력한다. 3개를 놓았을 경우에도
     * 답을 찾지 못했다면 -1을 출력한다.
     */
    public static void main(String[] args) throws Exception {
        tokenizer = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());
        h = Integer.parseInt(tokenizer.nextToken());
        for(int row, col; m > 0; m--) {
            tokenizer = new StringTokenizer(reader.readLine());
            row = Integer.parseInt(tokenizer.nextToken());
            col = Integer.parseInt(tokenizer.nextToken());
            hasHorizontal[row][col] = true;
        }

        int ans = -1;
        for(int i = 0; i <= 3; i++) {
            if(dfs(i, 1, 1, 0)) {
                ans = i;
                break;
            }
        }
        writer.write(Integer.toString(ans));

        writer.flush();
        writer.close();
        reader.close();
    }

    private static boolean dfs(int modNum, int row, int col, int depth) {
        if(depth == modNum) {
            for(int i = 1; i <= n; i++)
                if(!hasRightOrder(i, 0, i)) return false;
            return true;
        }
        else if(row == h + 1)
            return false;
        else {
            int nxtRow = (col == n - 1 ? row + 1 : row);
            int nxtCol = (col == n - 1 ? 1 : col + 1);
            if(hasHorizontal[row][col] || hasHorizontal[row][col - 1] || hasHorizontal[row][col + 1])
                return dfs(modNum, nxtRow, nxtCol, depth);
            else {
                hasHorizontal[row][col] = true;
                if(dfs(modNum, nxtRow, nxtCol, depth + 1))
                    return true;
                hasHorizontal[row][col] = false;
                return dfs(modNum, nxtRow, nxtCol, depth);
            }
        }
    }

    private static boolean hasRightOrder(int num, int row, int col) {
        if(row == h + 1)
            return col == num;
        else if(hasHorizontal[row][col])
            return hasRightOrder(num, row + 1, col + 1);
        else if(hasHorizontal[row][col - 1])
            return hasRightOrder(num, row + 1, col - 1);
        else
            return hasRightOrder(num, row + 1, col);
    }
}
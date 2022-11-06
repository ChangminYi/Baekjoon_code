import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.StringTokenizer;


public class Main {
    static class Pos {
        int row, col;

        Pos() {
            this(0, 0);
        }
        Pos(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    static int n, m, t, k;
    static Pos arg[];

    /**
     * 금강석의 수가 최대 100개이므로, 모든 경우의 수를 따져도
     * 시간초과를 받지 않는다. 모든 금강석의 좌표에서 행 좌표와 열 좌표를
     * 일일히 참고하여 굴착할 영역을 만들고, 그 영역 안에 포함되는 금강석의
     * 최대 수를 구한 후, 왼쪽 위 꼭짓점의 좌표를 구하면 된다.
     */
    public static void main(String[] args) throws Exception {
        tokenizer = new StringTokenizer(reader.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());
        t = Integer.parseInt(tokenizer.nextToken());
        k = Integer.parseInt(tokenizer.nextToken());

        arg = new Pos[t];
        for(int i = 0, row, col; i < t; i++) {
            tokenizer = new StringTokenizer(reader.readLine());
            col = Integer.parseInt(tokenizer.nextToken());
            row = Integer.parseInt(tokenizer.nextToken());
            arg[i] = new Pos(row, col);
        }
        reader.close();

        int ans = -1, ansRow = 0, ansCol = 0;
        for(final Pos i: arg) {
            for(final Pos j: arg) {
                int minRow = (j.row + k > m ? m - k : j.row);
                int minCol = (i.col + k > n ? n - k : i.col);
                
                int tmp = inRangeCount(minRow, minCol);
                if(tmp > ans) {
                    ans = tmp;
                    ansRow = minRow + k;
                    ansCol = minCol;
                } 
            }
        }
        
        writer.write(ansCol + " " + ansRow + "\n" + ans);

        writer.flush();
        writer.close();
    }

    static int inRangeCount(final int baseRow, final int baseCol) {
        int ret = 0;
        
        for(final Pos p: arg) {
            if(baseRow <= p.row && p.row <= baseRow + k && baseCol <= p.col && p.col <= baseCol + k)
                ret++;
        }

        return ret;
    }
}

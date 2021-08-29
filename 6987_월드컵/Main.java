import java.util.Scanner;

public class Main {
    static Scanner scanner = new Scanner(System.in);
    static int[][] tournament = {
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4},
            {1, 2, 3, 4, 5, 2, 3, 4, 5, 3, 4, 5, 4, 5, 5} };
    static int[] ans = new int[4];
    static int[][] match = new int[6][3];
    static int[][] result = new int[6][3];

    public static void DFS(int tc, int round) {
        if(round == 15) {
            if(ans[tc] != 0) {
                return;
            }
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < 3; j++) {
                    if(match[i][j] != result[i][j]) {
                        return;
                    }
                }
            }
            ans[tc] = 1;
            return;
        }

        int t1 = tournament[0][round];
        int t2 = tournament[1][round];

        result[t1][0]++; result[t2][2]++;
        DFS(tc, round + 1);
        result[t1][0]--; result[t2][2]--;

        result[t1][1]++; result[t2][1]++;
        DFS(tc, round + 1);
        result[t1][1]--; result[t2][1]--;

        result[t1][2]++; result[t2][0]++;
        DFS(tc, round + 1);
        result[t1][2]--; result[t2][0]--;
    }

    public static void main(String[] args) {
        for(int num = 0; num < 4; num++){
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < 3; j++) {
                    match[i][j] = scanner.nextInt();
                }
            }
            DFS(num, 0);
        }

        System.out.printf("%d %d %d %d", ans[0], ans[1], ans[2], ans[3]);
        scanner.close();
    }
}

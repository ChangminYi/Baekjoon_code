//결과는 맞는데 inputMismatch 에러가 뜬다.

import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    public static Scanner scanner = new Scanner(System.in);
    public static BigInteger arg[][], origin[][];

    public static BigInteger getMult(int row, int col, int N){
        BigInteger totalSum = new BigInteger("0");
        for(int i = 0; i < N; i++){
            totalSum = totalSum.add(arg[row][i].multiply(origin[i][col]));
        }
        return totalSum;
    }

    public static void main(String[] args) {
        int N = scanner.nextInt(), B = scanner.nextInt();

        origin = new BigInteger[N][N];
        arg = new BigInteger[N][N];
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                origin[i][j] = scanner.nextBigInteger();
                arg[i][j] = origin[i][j].add(BigInteger.ZERO);
            }
        }

        for(int k = 1; k < B; k++){
            BigInteger temp[][] = new BigInteger[N][N];
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    temp[i][j] = getMult(i, j, N);
                }
            }
            arg = temp;
        }

        BigInteger thousand = new BigInteger("1000");
        for(int i = 0; i < N; i++){
            System.out.print(arg[i][0].mod(thousand).toString());
            for(int j = 1; j < N; j++){
                System.out.print(" " + arg[i][j].mod(thousand).toString());
            }
            System.out.print("\n");
        }

        scanner.close();
    }
}

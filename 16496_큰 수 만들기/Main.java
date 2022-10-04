import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;

public class Main {
    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    
    private static int n;
    private static String[] arg;

    /**
     * 두 숫자를 이어붙이는 방법은 두 가지이다. 왼쪽+오른쪽, 오른쪽+왼쪽.
     * 만약 이어붙인 결과가 더 큰 값을 가지는 쪽을 앞으로 보내 내림차순 정렬하면,
     * n개의 숫자를 모두 이어붙였을 때의 값은 가능한 조합 중 최대값이 될 것이다.
     */
    public static void main(String[] args) throws Exception {
        n = Integer.parseInt(reader.readLine());
        arg = reader.readLine().split(" ");

        Arrays.sort(arg, (String lhs, String rhs)->{
            String left = lhs + rhs;
            String right = rhs + lhs;
            for(int i = 0; i < left.length(); i++) {
                if(left.charAt(i) != right.charAt(i))
                    return right.charAt(i) - left.charAt(i);
            }
            return 0;
        });

        if(arg[0].equals("0"))
            writer.write("0");
        else {
            for(String str: arg)
                writer.write(str);
        }

        writer.flush();
        writer.close();
        reader.close();
    }
}
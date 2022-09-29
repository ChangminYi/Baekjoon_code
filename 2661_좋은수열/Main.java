import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

public class Main {
    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    
    private static int n;
    private static ArrayList<Integer> ans = new ArrayList<>();

    public static void main(String args[]) throws IOException {
        n = Integer.parseInt(reader.readLine());
        
        dfs(0);

        for(int i: ans)
            writer.write(Integer.toString(i));

        writer.flush();
        reader.close();
        writer.close();
    }

    private static boolean dfs(int cur) {
        if(cur == n)
            return true;
        
        for(int i = 1; i <= 3; i++) {
            ans.add(i);
            if(isBad() || !dfs(cur + 1)) {
                ans.remove(cur);
                continue;
            }

            return true;
        }

        return false;
    }

    private static boolean isBad() {
        for(int i = 1; i <= ans.size() / 2; i++) {
            boolean isSame = true;
            for(int j = ans.size() - 1; j > ans.size() - 1 - i; j--) {
                if(ans.get(j) != ans.get(j - i)) {
                    isSame = false;
                    break;
                }
            }

            if(isSame)
                return true;
        }

        return false;
    }
}

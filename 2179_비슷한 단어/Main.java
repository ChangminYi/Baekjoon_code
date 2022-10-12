import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.HashMap;
import java.util.HashSet;

public class Main {
    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));

    final static int NOT_VISIT = -1;

    static int n;
    static String[] str;
    static HashSet<String> visit = new HashSet<>();
    static HashMap<String, int[]> map = new HashMap<>();

    /**
     * 가장 긴 접두사를 구해야 하므로, 각 문자열의 좌측부터
     * 부분 문자열을 만들며 해당 접두사가 이미 등장했는지를 확인하면 된다.
     * 같은 단어는 지나쳐야 하므로, set을 사용하여 등장 여부를 확인한다.
     * map을 통해 접두사를 관리하는데, 해당 접두사가 두 번 등장하는 순간에
     * 그때까지 등장한 최장 접두사의 길이와 현재 접두사를 비교하면 된다. 
     */
    public static void main(String[] args) throws Exception {
        n = Integer.parseInt(reader.readLine());
        str = new String[n];
        for(int i = 0; i < n; i++)
            str[i] = reader.readLine();

        int maxLen = 0;
        int s = n, t = n;
        for(int i = 0; i < n; i++) {
            if(visit.contains(str[i]))
                continue;
            visit.add(str[i]);
            for(int j = 1; j <= str[i].length(); j++) {
                String subStr = str[i].substring(0, j);
                if(!map.containsKey(subStr)) {
                    int[] val = { i, NOT_VISIT };
                    map.put(subStr, val);
                } else if(map.get(subStr)[1] == NOT_VISIT) {
                    map.get(subStr)[1] = i;
                    if(subStr.length() > maxLen
                    || (subStr.length() == maxLen && map.get(subStr)[0] < s)
                    || (subStr.length() == maxLen && map.get(subStr)[0] == s && map.get(subStr)[1] < t)) {
                        maxLen = subStr.length();
                        s = map.get(subStr)[0];
                        t = map.get(subStr)[1];
                    }
                } else {
                    continue;
                }
            }
        }

        writer.write(str[s] + "\n" + str[t]);

        writer.flush();
        writer.close();
    }
}
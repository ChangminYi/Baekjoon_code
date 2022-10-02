import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.TreeMap;
import java.util.Map.Entry;

public class Main {
    private static class Node {
        private TreeMap<String, Node> child = new TreeMap<>();
    }

    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    
    private static int n;
    private static Node head = new Node();

    /**
     * <String, TreeMap> 쌍으로 하나의 노드를 구성하여 트리 구조를 형성할 수 있다.
     * 문자열의 순차적인 탐색을 위해 HashMap이 아니라 TreeMap으로 구현하였다.
     * 문자열을 \단위로 나눠 트리에 저장하고, 모두 저장한 후 재귀적으로
     * 깊이에 따라서 문자열 앞의 공백을 출력하고 폴더 이름을 출력한다.
     */
    public static void main(String[] args) throws Exception {
        n = Integer.parseInt(reader.readLine());
        for(int i = 0; i < n; i++)
            insertToTree(head, reader.readLine().split("\\\\"), 0);

        printTree(head, 0);

        writer.flush();
        writer.close();
        reader.close();
    }

    private static void insertToTree(Node cur, String[] arg, int depth) {
        if(cur.child.get(arg[depth]) == null)
            cur.child.put(arg[depth], new Node());

        if(depth < arg.length - 1)
            insertToTree(cur.child.get(arg[depth]), arg, depth + 1);
    }

    private static void printTree(Node cur, int depth) throws Exception {
        for(Entry<String, Main.Node> entry: cur.child.entrySet()) {
            for(int i = 0; i < depth; i++)
                writer.write(" ");
            writer.write(entry.getKey() + "\n");
            printTree(entry.getValue(), depth + 1);
        }
    }
}
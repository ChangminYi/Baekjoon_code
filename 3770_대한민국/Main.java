import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.StringTokenizer;

class Node implements Comparable<Node> {
    int idx, val;

    Node(int idx, int val) {
        this.idx = idx;
        this.val = val;
    }

    public int compareTo(Node other) {
        if (this.idx == other.idx) {
            if(this.val == other.val) {
                return 0;
            } else if(this.val < other.val) {
                return -1;
            } else {
                return 1;
            }
        } else if (this.idx < other.idx) {
            return -1;
        } else {
            return 1;
        }
    }
}

public class Main {
    private static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    private static StringTokenizer parser;

    private static int testcase, n, m, k;
    private static ArrayList<Node> arg;
    private static int[] segtree = new int[4005];

    public static void main(String[] args) throws Exception {
        /**
         * 세그먼트 트리를 이용하여 inversion counting을 하면 된다.
         * 다만, 같은 노드에 여러 간선이 이어져 있을 수 있으므로
         * 정렬 기준에 반대편 노드도 포함하여 오름차순 정렬을 해야 한다.
         */

        testcase = Integer.parseInt(reader.readLine());
        for (int tc = 1; tc <= testcase; tc++) {
            Arrays.fill(segtree, 0);

            parser = new StringTokenizer(reader.readLine());
            n = Integer.parseInt(parser.nextToken());
            m = Integer.parseInt(parser.nextToken());
            k = Integer.parseInt(parser.nextToken());

            arg = new ArrayList<>();
            for (int i = 0, a, b; i < k; i++) {
                parser = new StringTokenizer(reader.readLine());
                a = Integer.parseInt(parser.nextToken());
                b = Integer.parseInt(parser.nextToken());
                arg.add(new Node(a, b));
            }

            Collections.sort(arg);

            long ans = 0;
            for (final Node node : arg) {
                ans += getQuery(1, 1, m, node.val, m) - getQuery(1, 1, m, node.val, node.val);
                updateSeg(1, 1, m, node.val, 1);
            }

            writer.write("Test case " + tc + ": " + ans + "\n");
        }

        writer.flush();
        writer.close();
        reader.close();
    }

    private static void updateSeg(int idx, int lo, int hi, int offset, int val) {
        if (lo == hi) {
            segtree[idx] += val;
        } else {
            int mid = (lo + hi) / 2;
            if (offset <= mid) {
                updateSeg(2 * idx, lo, mid, offset, val);
            } else {
                updateSeg(2 * idx + 1, mid + 1, hi, offset, val);
            }
            segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];
        }
    }

    private static int getQuery(int idx, int lo, int hi, int left, int right) {
        if (lo == left && hi == right) {
            return segtree[idx];
        } else {
            int mid = (lo + hi) / 2;
            if (right <= mid) {
                return getQuery(2 * idx, lo, mid, left, right);
            } else if (mid < left) {
                return getQuery(2 * idx + 1, mid + 1, hi, left, right);
            } else {
                return getQuery(2 * idx, lo, mid, left, mid) + getQuery(2 * idx + 1, mid + 1, hi, mid + 1, right);
            }
        }
    }
}

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

class Node{
    public int node_number = 0;
    public int move_count = 0;
    Node(int n, int m){
        this.node_number = n;
        this.move_count = m;
    }
}

public class Main {
    public static Scanner scanner = new Scanner(System.in);
    public static ArrayList<ArrayList<Integer>> graph;
    public static Map<Integer, ArrayList<Integer>> subgraph = new HashMap<>();
    public static int[] parent;
    public static boolean[] visit;
    public static Queue<Node> que = new LinkedList<Node>();
    public static int n, m;

    public static int find(int x){
        return parent[x] == x ? x : (parent[x] = find(parent[x]));
    }

    public static void union(int x, int y){
        int f_x = find(x), f_y = find(y);
        if(f_x > f_y){
            parent[f_x] = f_y;
        }
        else{
            parent[f_y] = f_x;
        }
    }

    public static int bfs(int start){
        int res = 0;
        Arrays.fill(visit, false);

        visit[start] = true;
        que.add(new Node(start, 0));
        while(!que.isEmpty()){
            Node cur = que.poll();
            res = Math.max(res, cur.move_count);

            for(int nxt: graph.get(cur.node_number)){
                if(!visit[nxt]){
                    visit[nxt] = true;
                    que.add(new Node(nxt, cur.move_count + 1));
                }
            }
        }

        return res;
    }

    public static void main(String[] args) {
        n = scanner.nextInt(); m = scanner.nextInt();

        graph = new ArrayList(n + 1);
        parent = new int[n + 1];
        visit = new boolean[n + 1];
        for(int i = 0; i <= n; i++){
            graph.add(new ArrayList<>());
            parent[i] = i;
        }

        for(int i = 0, node1, node2; i < m ; i++){
            node1 = scanner.nextInt(); node2 = scanner.nextInt();
            graph.get(node1).add(node2);
            graph.get(node2).add(node1);
            union(node1, node2);
        }

        for(int i = 1; i <= n; i++){
            if(find(i) == i){
                subgraph.put(i, new ArrayList<>(Arrays.asList(i)));
            }
            else{
                subgraph.get(find(i)).add(i);
            }
        }

        ArrayList<Integer> min_dist = new ArrayList<>();
        for(int key: subgraph.keySet()){
            int min_res = Integer.MAX_VALUE, min_person = 0, tmp_res;

            for(int n: subgraph.get(key)){
                if((tmp_res = bfs(n)) < min_res){
                    min_res = tmp_res;
                    min_person = n;
                }
            }

            min_dist.add(min_person);
        }
        Collections.sort(min_dist);

        System.out.println(min_dist.size());
        for(int i: min_dist){
            System.out.println(i);
        }
    }
}

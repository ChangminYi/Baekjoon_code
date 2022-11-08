import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
import java.util.Map.Entry;


public class Main {
    static class Node {
        HashSet<String> strongEdge, weakEdge;
        Node() {
            this.strongEdge = new HashSet<>();
            this.weakEdge = new HashSet<>();
        }
    }

    static class Edge {
        String from, to;
        Edge(String from, String to) {
            this.from = from;
            this.to = to;
        }
    }

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
    static StringTokenizer tokenizer;

    static int o, e;
    static HashSet<String> rootSet = new HashSet<>();
    static HashMap<String, Node> nodeSet = new HashMap<>();
    static HashMap<String, Edge> strongEdgeSet = new HashMap<>();
    static HashMap<String, Edge> weakEdgeSet = new HashMap<>();
    static HashSet<String> visit = new HashSet<>();
    static Queue<String> q = new LinkedList<>();
    static Queue<String> toRemove = new LinkedList<>();
    static String tmp[];

    /**
     * 문제에서 명세하는 M, m, MADE, ADD, REMOVE를 구현하면 된다.
     * 각 노드는 자신에서 출발하는 연결의 이름을 가지고 있는다.
     * M 혹은 m 명령어는 BFS로 구현하였다. 조건에 맞도록 방문한 노드를 모두 저장하고,
     * 만약 연결 중에서 출발-도착 노드 중 하나라도 방문하지 않았다면
     * 삭제 대상이 된다. 출발 노드가 저장하고 있는 해당 연결의 이름도 제거한다.
     * 그 후 방문하지 않은 노드를 목록에서 지운다. 루트 목록도 같이 갱신한다.
     */
    public static void main(String[] args) throws Exception {
        tokenizer = new StringTokenizer(reader.readLine());
        o = Integer.parseInt(tokenizer.nextToken());
        e = Integer.parseInt(tokenizer.nextToken());
        for(; o > 0; o--) {
            tmp = reader.readLine().split(" ");
            nodeSet.put(tmp[0], new Node());
            if(tmp[1].equals("ROOT")) {
                rootSet.add(tmp[0]);
            }
        }

        for(; e > 0; e--) {
            tmp = reader.readLine().split(" ");
            if(tmp[0].equals("m")) {
                doBFS(true);
                writer.write(Integer.toString(nodeSet.size()) + "\n");
            } else if(tmp[0].equals("M")) {
                doBFS(false);
                writer.write(Integer.toString(nodeSet.size()) + "\n");
            } else if(tmp[0].equals("MADE")) {
                nodeSet.put(tmp[1], new Node());
                if(tmp[2].equals("ROOT")) {
                    rootSet.add(tmp[1]);
                }
            } else if(tmp[0].equals("REMOVE")) {
                if(strongEdgeSet.containsKey(tmp[1])) {
                    String from = strongEdgeSet.get(tmp[1]).from;
                    nodeSet.get(from).strongEdge.remove(tmp[1]);
                    strongEdgeSet.remove(tmp[1]);
                } else {
                    String from = weakEdgeSet.get(tmp[1]).from;
                    nodeSet.get(from).weakEdge.remove(tmp[1]);
                    weakEdgeSet.remove(tmp[1]);
                }
            } else {
                if(tmp[3].equals("=>")) {
                    strongEdgeSet.put(tmp[1], new Edge(tmp[2], tmp[4]));
                    nodeSet.get(tmp[2]).strongEdge.add(tmp[1]);
                } else {
                    weakEdgeSet.put(tmp[1], new Edge(tmp[2], tmp[4]));
                    nodeSet.get(tmp[2]).weakEdge.add(tmp[1]);
                }
            }
        }

        writer.flush();
        writer.close();
    }

    static void doBFS(boolean containsWeak) {
        for(final String r: rootSet) {
            visit.add(r);
            q.add(r);
        }
        while(!q.isEmpty()) {
            String cur = q.poll();
            for(final String se: nodeSet.get(cur).strongEdge) {
                String nxt = strongEdgeSet.get(se).to;
                if(!visit.contains(nxt)) {
                    visit.add(nxt);
                    q.add(nxt);
                }
            }
            if(containsWeak) {
                for(final String we: nodeSet.get(cur).weakEdge) {
                    String nxt = weakEdgeSet.get(we).to;
                    if(!visit.contains(nxt)) {
                        visit.add(nxt);
                        q.add(nxt);
                    }
                }
            }
        }

        for(Entry<String, Edge> entry: strongEdgeSet.entrySet()) {
            Edge edge = entry.getValue();
            if(!visit.contains(edge.to)) {
                nodeSet.get(edge.from).strongEdge.remove(entry.getKey());
            }
            if(!visit.contains(edge.from)) {
                toRemove.add(entry.getKey());
            }
        }
        while(!toRemove.isEmpty()) {
            strongEdgeSet.remove(toRemove.poll());
        }
        for(Entry<String, Edge> entry: weakEdgeSet.entrySet()) {
            Edge edge = entry.getValue();
            if(!visit.contains(edge.to)) {
                nodeSet.get(edge.from).weakEdge.remove(entry.getKey());
            }
            if(!visit.contains(edge.from)) {
                toRemove.add(entry.getKey());
            }
        }
        while(!toRemove.isEmpty()) {
            weakEdgeSet.remove(toRemove.poll());
        }

        for(Entry<String, Node> entry: nodeSet.entrySet()) {
            if(!visit.contains(entry.getKey())) {
                toRemove.add(entry.getKey());
            }
        }
        while(!toRemove.isEmpty()) {
            String cur = toRemove.poll();
            if(rootSet.contains(cur)) {
                rootSet.remove(cur);
            }
            nodeSet.remove(cur);
        }

        visit.clear();
    }
}

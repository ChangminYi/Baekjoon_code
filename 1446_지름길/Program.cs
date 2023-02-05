using System.Text;

class Edge {
    public int adj;
    public int dist;

    public Edge(int adj = 0, int dist = 0) {
        this.adj = adj;
        this.dist = dist;
    }
}

class Pqn {
    public int node;
    public int weight;

    public Pqn(int node, int weight) {
        this.node = node;
        this.weight = weight;
    }
}

public class Program {
    const int INF = int.MaxValue / 2;
    const int START = 0;

    static StreamReader reader = new StreamReader(Console.OpenStandardInput());
    static StreamWriter writer = new StreamWriter(Console.OpenStandardOutput());
    static StringBuilder ans = new StringBuilder();

    /* 다익스트라 알고리즘을 통해 최단거리를 구할 수 있음.
     * 범위 내에 들지 않는 간선은 그래프에서 제외.
     */
    static void Main(string[] args) {
        string[] tmp = reader.ReadLine().Split(' ');
        int n = int.Parse(tmp[0]);
        int d = int.Parse(tmp[1]);
        int[] dist = new int[d + 2];
        List<Edge>[] graph = new List<Edge>[d + 2];
        for(int i = 0; i <= d; i++) {
            dist[i] = INF;
            graph[i] = new List<Edge>();
        }
        for(int start, end, length; n > 0; n--) {
            tmp = reader.ReadLine().Split(' ');
            start = int.Parse(tmp[0]);
            end = int.Parse(tmp[1]);
            length = int.Parse(tmp[2]);
            if(end > d)
                continue;
            graph[start].Add(new Edge(end, length));
        }

        PriorityQueue<Pqn, int> pq = new PriorityQueue<Pqn, int>();
        dist[START] = 0;
        pq.Enqueue(new Pqn(START, dist[START]), dist[START]);
        while(pq.Count > 0) {
            Pqn cur = pq.Dequeue();

            if(cur.weight > dist[cur.node])
                continue;
            foreach(Edge edge in graph[cur.node]) {
                int newDist = cur.weight + edge.dist;
                if(newDist < dist[edge.adj]) {
                    dist[edge.adj] = newDist;
                    pq.Enqueue(new Pqn(edge.adj, newDist), newDist);
                }
            }
            if(cur.weight + 1 < dist[cur.node + 1]) {
                dist[cur.node + 1] = cur.weight + 1;
                pq.Enqueue(new Pqn(cur.node + 1, cur.weight + 1), cur.weight + 1);
            }
        }

        writer.Write(dist[d].ToString());
        writer.Flush();

        writer.Close();
        reader.Close();
    }
}
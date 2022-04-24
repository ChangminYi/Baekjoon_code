package main

import (
	"bufio"
	"os"
	"sort"
	"strconv"
	"strings"
)

type edge struct {
	node1, node2 int
	weight       int64
}

var (
	reader bufio.Reader = *bufio.NewReader(os.Stdin)
	writer bufio.Writer = *bufio.NewWriter(os.Stdout)
	tmp    string

	n, m, cnt int
	ans       int64
	parent    []int
	arg       []edge
)

func main() {
	/**
	 * 최소 스패닝 트리를 구축하면 해결할 수 있다.
	 * 전체 간선의 가중치의 합을 먼저 구하고
	 * 최소 스패닝 트리의 가중치의 합을 전체에서 뺀 값이 정답.
	 */

	tmp, _ = reader.ReadString(' ')
	n, _ = strconv.Atoi(strings.TrimSuffix(tmp, " "))
	tmp, _ = reader.ReadString('\n')
	m, _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))

	InitParent()
	arg = make([]edge, m)
	for i := 0; i < m; i++ {
		tmp, _ = reader.ReadString(' ')
		arg[i].node1, _ = strconv.Atoi(strings.TrimSuffix(tmp, " "))
		tmp, _ = reader.ReadString(' ')
		arg[i].node2, _ = strconv.Atoi(strings.TrimSuffix(tmp, " "))
		tmp, _ = reader.ReadString('\n')
		arg[i].weight, _ = strconv.ParseInt(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"), 10, 64)
		ans += arg[i].weight
	}

	sort.Slice(arg, func(i, j int) bool {
		return arg[i].weight < arg[j].weight
	})

	for i := 0; i < m && cnt < n-1; i++ {
		if FindParent(arg[i].node1) != FindParent(arg[i].node2) {
			cnt++
			ans -= arg[i].weight
			Union(arg[i].node1, arg[i].node2)
		}
	}

	if cnt == n-1 {
		writer.WriteString(strconv.FormatInt(ans, 10))
	} else {
		writer.WriteString(strconv.Itoa(-1))
	}
	writer.Flush()
}

func InitParent() {
	parent = make([]int, n+1)
	for i := 1; i <= n; i++ {
		parent[i] = i
	}
}

func FindParent(x int) int {
	if parent[x] != x {
		parent[x] = FindParent(parent[x])
	}
	return parent[x]
}

func Union(x, y int) {
	parent[FindParent(y)] = FindParent(x)
}

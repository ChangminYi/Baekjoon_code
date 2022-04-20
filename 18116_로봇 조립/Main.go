package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

var (
	reader bufio.Reader = *bufio.NewReader(os.Stdin)
	writer bufio.Writer = *bufio.NewWriter(os.Stdout)

	n          int
	arg1, arg2 int
	inst, tmp  string
	parent     []int = make([]int, 1000001)
	setSize    []int = make([]int, 1000001)
)

func main() {
	/**
	 * union-find를 통해 집합의 상태와 크기를 관리하면 된다.
	 * 집합을 합칠 때, 둘의 parent가 다를 때에만 union을 해야 한다.
	 */

	defer writer.Flush()

	initSet()
	tmp, _ = reader.ReadString('\n')
	n, _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))
	for ; n > 0; n-- {
		tmp, _ = reader.ReadString(' ')
		inst = strings.TrimSuffix(tmp, " ")

		if inst == "I" {
			tmp, _ = reader.ReadString(' ')
			arg1, _ = strconv.Atoi(strings.TrimSuffix(tmp, " "))
			tmp, _ = reader.ReadString('\n')
			arg2, _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))

			if arg1, arg2 = findParent(arg1), findParent(arg2); arg1 != arg2 {
				setSize[arg1] += setSize[arg2]
				setSize[arg2] = 0
				parent[arg2] = arg1
			}
		} else {
			tmp, _ = reader.ReadString('\n')
			arg1, _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))
			writer.WriteString(strconv.Itoa(setSize[findParent(arg1)]) + "\n")
		}
	}
}

func findParent(x int) int {
	if parent[x] == x {
		return x
	} else {
		parent[x] = findParent(parent[x])
		return parent[x]
	}
}

func initSet() {
	for i := 1; i <= 1000000; i++ {
		parent[i] = i
		setSize[i] = 1
	}
}

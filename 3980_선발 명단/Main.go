package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

const (
	SIZE int = 11
)

var (
	reader bufio.Reader = *bufio.NewReader(os.Stdin)
	writer bufio.Writer = *bufio.NewWriter(os.Stdout)
	tmp    string

	testcase int
	arg      [][]int = make([][]int, SIZE)
	ans      int
)

func main() {
	/**
	 * 모든 선수에 대하여 가능한 포지션을 모두 확인하여 최대 합을 구한다.
	 * 이미 다른 선수가 들어간 포시션은 사용할 수 없으므로, 사용한 자리를
	 * 표시하는 visit 변수를 같이 사용한다.
	 */
	defer writer.Flush()

	for i := 0; i < SIZE; i++ {
		arg[i] = make([]int, SIZE)
	}

	tmp, _ = reader.ReadString('\n')
	testcase, _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))
	for ; testcase > 0; testcase-- {
		for i := 0; i < SIZE; i++ {
			for j := 0; j < SIZE-1; j++ {
				tmp, _ = reader.ReadString(' ')
				arg[i][j], _ = strconv.Atoi(strings.TrimSuffix(tmp, " "))
			}
			tmp, _ = reader.ReadString('\n')
			arg[i][SIZE-1], _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))
		}

		ans = 0
		for i := 0; i < SIZE; i++ {
			if arg[0][i] != 0 {
				ans = Max(ans, GetMax(1, arg[0][i], 1<<i))
			}
		}

		writer.WriteString(strconv.Itoa(ans) + "\n")
	}
}

func GetMax(cur, sum, visit int) (ret int) {
	if cur == SIZE {
		ret = sum
	} else {
		ret = 0
		for i := 0; i < SIZE; i++ {
			if arg[cur][i] != 0 && (visit&(1<<i)) == 0 {
				ret = Max(ret, GetMax(cur+1, sum+arg[cur][i], visit|(1<<i)))
			}
		}
	}
	return
}

func Max(i, j int) int {
	if i > j {
		return i
	} else {
		return j
	}
}

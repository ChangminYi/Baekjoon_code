package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

var (
	n      int
	ans    int64        = 0
	arg    []int        = make([]int, 100000)
	visit  []bool       = make([]bool, 100001)
	reader bufio.Reader = *bufio.NewReader(os.Stdin)
	writer bufio.Writer = *bufio.NewWriter(os.Stdout)
)

func main() {
	/*
	 * lo를 기준점으로 하는 연속하는 부분 문자열의 수를 세면 된다.
	 * arg[hi]가 부분 문자열에 포함되지 않으면 계속 hi를 전진시킨다.
	 * 더 이상 hi가 변하지 않으면 그 때가 lo를 기준으로 하는 연속하는
	 * 부분 문자열의 최대 길이이다. hi - lo를 계속 더하면 답을 구할 수 있다.
	 */
	tmp, _ := reader.ReadString('\n')
	n, _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))
	for i := 0; i < n-1; i++ {
		tmp, _ = reader.ReadString(' ')
		arg[i], _ = strconv.Atoi(strings.TrimSuffix(tmp, " "))
	}
	tmp, _ = reader.ReadString('\n')
	arg[n-1], _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))

	for lo, hi := 0, 0; lo < n; lo++ {
		for ; hi < n && !visit[arg[hi]]; hi++ {
			visit[arg[hi]] = true
		}

		ans += int64(hi - lo)
		visit[arg[lo]] = false
	}

	writer.Write([]byte(strconv.FormatInt(ans, 10)))
	writer.Flush()
}

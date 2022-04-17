package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

const (
	MOD int = 100000
)

var (
	reader bufio.Reader = *bufio.NewReader(os.Stdin)
	writer bufio.Writer = *bufio.NewWriter(os.Stdout)

	w  int
	h  int
	dp [][][]int
)

func main() {
	/**
	 * 교차로에서 바로 꺾을 수 없기 때문에 어느 방향에서 오는지까지 고려를 해줘야 한다.
	 * 따라서 dp 배열이 3차원이 되고, i행 j열에서 0~3번째 방향에서 오는 방법을 의미한다.
	 * 정답은 dp[h][w]의 0~3번째 원소를 모두 더해서 100000으로 나눈 값.
	**/

	tmp, _ := reader.ReadString(' ')
	w, _ = strconv.Atoi(strings.TrimSuffix(tmp, " "))
	tmp, _ = reader.ReadString('\n')
	h, _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))

	dp = make([][][]int, h+1)
	for i := 0; i <= h; i++ {
		dp[i] = make([][]int, w+1)
		for j := 0; j <= w; j++ {
			dp[i][j] = make([]int, 4)
		}
	}

	for i := 1; i <= w; i++ {
		dp[1][i][2] = 1
	}
	for i := 1; i <= h; i++ {
		dp[i][1][0] = 1
	}

	for i := 2; i <= h; i++ {
		for j := 2; j <= w; j++ {
			dp[i][j][0] = (dp[i-1][j][1] + dp[i-1][j][0]) % MOD
			dp[i][j][1] = dp[i-1][j][2]
			dp[i][j][2] = (dp[i][j-1][3] + dp[i][j-1][2]) % MOD
			dp[i][j][3] = dp[i][j-1][0]
		}
	}

	ans := (dp[h][w][0] + dp[h][w][1] + dp[h][w][2] + dp[h][w][3]) % MOD
	writer.WriteString(strconv.Itoa(ans))
	writer.Flush()
}

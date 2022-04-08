package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

var (
	n   int
	str string

	reader bufio.Reader = *bufio.NewReader(os.Stdin)
	writer bufio.Writer = *bufio.NewWriter(os.Stdout)

	diffCnt, ans int   = 0, 0
	lo, hi, leng int   = 0, 0, 0
	numCnt       []int = make([]int, 26)
)

/**
 * hi, lo로 각각 문자열의 오른쪽, 왼쪽을 표시한다.
 * 조건을 만족할 때까지 hi를 증가시키고, 최대 길이를 갱신한다.
 * 다음 문자열을 찾기 위해 lo를 증가시킨다.
 * Go에서 bufio.Scanner를 쓰면, 매우 긴 입력이 잘리는 현상이 있다.
 * 따라서, bufio.Reader를 사용하여 특수문자 처리를 한 후 사용하는 게 좋다.
**/
func main() {
	n, str = getInt(), getString()

	for {
		for diffCnt <= n && hi < len(str) {
			if numCnt[str[hi]-'a'] == 0 {
				diffCnt++
			}
			numCnt[str[hi]-'a']++
			hi++

			if diffCnt > n {
				break
			} else {
				ans = Max(ans, hi-lo)
			}
		}

		if hi == len(str) {
			break
		}

		for diffCnt > n {
			numCnt[str[lo]-'a']--
			if numCnt[str[lo]-'a'] == 0 {
				diffCnt--
			}
			lo++
		}
	}

	writer.WriteString(strconv.Itoa(ans))
	writer.Flush()
}

func Max(lhs, rhs int) int {
	if lhs > rhs {
		return lhs
	} else {
		return rhs
	}
}

func getInt() (ret int) {
	ret, _ = strconv.Atoi(getString())
	return
}

func getString() (ret string) {
	ret, _ = reader.ReadString('\n')
	ret = strings.TrimSuffix(strings.TrimSuffix(ret, "\n"), "\r")
	return
}

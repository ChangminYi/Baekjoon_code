package main

import (
	"bufio"
	"os"
	"sort"
	"strconv"
)

var (
	n, k, ans, base, top int
	scanner              bufio.Scanner = *bufio.NewScanner(os.Stdin)
	writer               bufio.Writer  = *bufio.NewWriter(os.Stdout)
	interval             []int         = make([]int, 0)
)

func main() {
	/*
		총 구간의 수가 성냥의 수보다 적다면, 들어온 사람의 수만큼이 불이 켜져 있는 시간이다.
		만약 성냥이 부족하다면, 연속한 구간의 사이 간격들을 이어야 한다.
		오름차순으로 사이 간격을 정렬하고, 부족한 성냥의 수만큼 더하면 된다.
	*/

	defer writer.Flush()
	scanner.Split(bufio.ScanWords)

	n, k, base = scan_int(), scan_int(), scan_int()
	top = base + 1
	for i := 1; i < n; i++ {
		if tmp := scan_int(); top != tmp {
			interval = append(interval, tmp-top)
			base, top = tmp, tmp+1
		} else {
			top = tmp + 1
		}
	}

	sort.Slice(interval, func(i, j int) bool {
		return interval[i] < interval[j]
	})

	ans = n
	if k < len(interval)+1 {
		for i := 0; i < len(interval)-k+1; i++ {
			ans += interval[i]
		}
	}
	writer.WriteString(strconv.Itoa(ans))
}

func scan_int() (ret int) {
	scanner.Scan()
	ret, _ = strconv.Atoi(scanner.Text())
	return
}

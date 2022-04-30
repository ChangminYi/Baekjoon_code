package main

import (
	"bufio"
	"os"
	"sort"
	"strconv"
	"strings"
)

type data struct {
	idx, val int
}

var (
	reader    bufio.Reader = *bufio.NewReader(os.Stdin)
	writer    bufio.Writer = *bufio.NewWriter(os.Stdout)
	tmp       string
	n, m, ans int
	segtree   []int = make([]int, 8005)
	arg       []data
)

func main() {
	tmp, _ = reader.ReadString(' ')
	n, _ = strconv.Atoi(strings.TrimSuffix(tmp, " "))
	tmp, _ = reader.ReadString('\n')
	m, _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))

	arg = make([]data, m)
	for i := 0; i < m; i++ {
		tmp, _ = reader.ReadString(' ')
		arg[i].idx, _ = strconv.Atoi(strings.TrimSuffix(tmp, " "))
		tmp, _ = reader.ReadString('\n')
		arg[i].val, _ = strconv.Atoi(strings.TrimSuffix(strings.TrimSuffix(tmp, "\n"), "\r"))
	}

	sort.Slice(arg, func(i, j int) bool {
		if arg[i].idx == arg[j].idx {
			return arg[i].val < arg[j].val
		} else {
			return arg[i].idx < arg[j].idx
		}
	})

	for i := 0; i < m; i++ {
		ans += GetQuery(1, 1, n, arg[i].val, n) - GetQuery(1, 1, n, arg[i].val, arg[i].val)
		UpdateSeg(1, 1, n, arg[i].val, 1)
	}

	writer.Write([]byte(strconv.Itoa(ans)))
	writer.Flush()
}

func GetQuery(idx, lo, hi, left, right int) int {
	if lo == left && hi == right {
		return segtree[idx]
	} else {
		mid := (lo + hi) / 2
		if right <= mid {
			return GetQuery(2*idx, lo, mid, left, right)
		} else if mid < left {
			return GetQuery(2*idx+1, mid+1, hi, left, right)
		} else {
			return GetQuery(2*idx, lo, mid, left, mid) + GetQuery(2*idx+1, mid+1, hi, mid+1, right)
		}
	}
}

func UpdateSeg(idx, lo, hi, offset, val int) {
	if lo == hi {
		segtree[idx] += val
	} else {
		mid := (lo + hi) / 2
		if offset <= mid {
			UpdateSeg(2*idx, lo, mid, offset, val)
		} else {
			UpdateSeg(2*idx+1, mid+1, hi, offset, val)
		}
		segtree[idx] = segtree[2*idx] + segtree[2*idx+1]
	}
}

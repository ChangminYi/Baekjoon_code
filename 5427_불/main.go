package main

import (
	"bufio"
	"container/list"
	"os"
	"strconv"
)

type dir struct {
	row, col int
}

type qn struct {
	pos  dir
	dist int
}

const (
	INF   int  = 0x7FFFFFFF
	EMPTY byte = '.'
	WALL  byte = '#'
	START byte = '@'
	FIRE  byte = '*'
)

var (
	poss_dir [4]dir = [4]dir{
		{1, 0}, {-1, 0}, {0, 1}, {0, -1},
	}
	tmp                string
	testcase, row, col int
	start              dir
	board              [][]byte
	visit              [1000][1000]bool
	fire_dist          [1000][1000]int
	fire_que           *list.List
	scanner            *bufio.Scanner
	writer             *bufio.Writer
)

func in_range(d *dir) bool {
	return 0 <= d.row && d.row < row && 0 <= d.col && d.col < col
}

func can_exit(d *dir) bool {
	return d.row == 0 || d.row == row-1 || d.col == 0 || d.col == col-1
}

func init_var() {
	board = make([][]byte, row)
	for i := 0; i < row; i++ {
		for j := 0; j < col; j++ {
			visit[i][j] = false
			fire_dist[i][j] = INF
		}
	}
}

func init_fire() {
	for fire_que.Len() > 0 {
		cur := fire_que.Front().Value.(dir)
		fire_que.Remove(fire_que.Front())

		for i := 0; i < 4; i++ {
			nxt := dir{cur.row + poss_dir[i].row, cur.col + poss_dir[i].col}
			if in_range(&nxt) && board[nxt.row][nxt.col] == EMPTY && fire_dist[cur.row][cur.col]+1 < fire_dist[nxt.row][nxt.col] {
				fire_dist[nxt.row][nxt.col] = fire_dist[cur.row][cur.col] + 1
				fire_que.PushBack(nxt)
			}
		}
	}
}

func bfs() (ret int) {
	ret = -1
	que := list.New()

	visit[start.row][start.col] = true
	que.PushBack(qn{start, 0})
	for que.Len() > 0 {
		cur := que.Front().Value.(qn).pos
		cur_dist := que.Front().Value.(qn).dist
		que.Remove(que.Front())

		if can_exit(&cur) {
			ret = cur_dist + 1
			break
		} else {
			for i := 0; i < 4; i++ {
				nxt := dir{cur.row + poss_dir[i].row, cur.col + poss_dir[i].col}
				if in_range(&nxt) && board[nxt.row][nxt.col] == EMPTY && !visit[nxt.row][nxt.col] && cur_dist+1 < fire_dist[nxt.row][nxt.col] {
					visit[nxt.row][nxt.col] = true
					que.PushBack(qn{nxt, cur_dist + 1})
				}
			}
		}
	}

	return
}

func main() {
	/*
		go 연습용 문제풀이.
		로직은 C++로 풀었을 때와 동일. 불의 도착 시간을 먼저 구하고, 시작 지점부터 bfs.
		queue를 구현하기 위해 container/list를 사용했음. 입출력 시간이 길어 bufio 사용.
	*/

	scanner = bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanWords)
	writer = bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	fire_que = list.New()

	testcase := scan_int()
	for ; testcase > 0; testcase-- {
		col, row = scan_int(), scan_int()
		init_var()
		for i := 0; i < row; i++ {
			board[i] = []byte(scan_str())

			for j := 0; j < col; j++ {
				if board[i][j] == START {
					start = dir{i, j}
					board[i][j] = EMPTY
				} else if board[i][j] == FIRE {
					fire_dist[i][j] = 0
					fire_que.PushBack(dir{i, j})

				}
			}
		}

		init_fire()
		if ret := bfs(); ret == -1 {
			writer.WriteString("IMPOSSIBLE\n")
		} else {
			writer.WriteString(strconv.Itoa(ret))
			writer.WriteByte('\n')
		}
	}
}

func scan_int() (ret int) {
	scanner.Scan()
	ret, _ = strconv.Atoi(scanner.Text())
	return
}

func scan_str() string {
	scanner.Scan()
	return scanner.Text()
}

package codenames

import (
	"bufio"
	"context"
	"fmt"
	"math/rand"
	"os"
	"sync"
)

type Game struct {
	lock  sync.Mutex
	games map[string]map[string]*Board
	words map[string]map[int]string
}

func getWords(file string) ([]string, error) {
	words := make([]string, 0)

	fmt.Printf("Loading words from %s\n", file)
	f, err := os.Open(file)
	if err != nil {
		return nil, err
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)

	for scanner.Scan() {
		words = append(words, scanner.Text())
	}

	return words, nil
}

func NewGame(config Config) (*Game, error) {
	wordlists := make(map[string][]string)
	for category, path := range config.WordLists {
		var err error
		wordlists[category], err = getWords(path)
		if err != nil {
			return nil, err
		}
	}
	words := make(map[string]map[int]string)
	games := make(map[string]map[string]*Board)

	for category, wordlist := range wordlists {
		games[category] = make(map[string]*Board)
		words[category] = make(map[int]string)

		for i, word := range wordlist {
			words[category][i] = word
		}
	}

	return &Game{
		games: games,
		words: words,
	}, nil
}

func (r *Game) Categories(ctx context.Context) ([]string, error) {
	r.lock.Lock()
	defer r.lock.Unlock()
	categories := make([]string, 0, len(r.words))
	for category := range r.words {
		categories = append(categories, category)
	}
	return categories, nil
}

func (r *Game) Board(ctx context.Context, category string, code string) (*Board, error) {
	r.lock.Lock()
	defer r.lock.Unlock()
	return r.games[category][code], nil
}

func (r *Game) NewGame(ctx context.Context, category string, code string, x, y int) (bool, error) {
	r.lock.Lock()
	defer r.lock.Unlock()

	board := &Board{}

	r.games[category][code] = board

	board.Tiles = make([][]Tile, x)
	for i := 0; i < x; i++ {
		board.Tiles[i] = make([]Tile, y)
	}

	i := 0
	for _, word := range r.words[category] {
		board.Tiles[i%x][(i/x)%y].Word = word
		i++
		if i == x*y {
			break
		}
	}

	board.Tiles[0][0].Kind = DEATH

	for i := 1; i < (x*y)/3; i++ {
		board.Tiles[i%x][(i/x)%y].Kind = RED
	}

	for i := (x * y) / 3; i < 2*(x*y)/3; i++ {
		board.Tiles[i%x][(i/x)%y].Kind = BLUE
	}

	for i := 2 * (x * y) / 3; i < (x * y); i++ {
		board.Tiles[i%x][(i/x)%y].Kind = NEUTRAL
	}

	rand.Shuffle(x*y, func(i, j int) {
		board.Tiles[i%x][(i/x)%y], board.Tiles[j%x][(j/x)%y] = board.Tiles[j%x][(j/x)%y], board.Tiles[i%x][(i/x)%y]
	})

	return true, nil
}

func (r *Game) HitTile(ctx context.Context, category string, code string, x, y int) (TileType, error) {
	r.lock.Lock()
	defer r.lock.Unlock()
	gameCategory, ok := r.games[category]
	if !ok {
		return 0, fmt.Errorf("Invalid Category %s", category)
	}

	board, ok := gameCategory[code]
	if !ok {
		return 0, fmt.Errorf("Invalid Game %s", code)
	}

	if !(x < len(board.Tiles) && y < len(board.Tiles[y])) {
		return 0, fmt.Errorf("Invalid Bounds %d, %d", x, y)
	}

	board.Tiles[x][y].Revealed = true

	return board.Tiles[x][y].Kind, nil
}

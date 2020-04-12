//go:generate gorunpkg github.com/alvaroloes/enumer -type=TileType

package codenames

import (
	"fmt"
	"io"
)

type Board struct {
	Tiles [][]Tile

	listeners []func() bool
}

func (b *Board) notify() {
	kept := make([]func() bool, 0, len(b.listeners))
	for _, listener := range b.listeners {
		if listener() {
			kept = append(kept, listener)
		}
	}
	b.listeners = kept
}

type Tile struct {
	Kind     TileType
	Word     string
	Revealed bool
}

type TileType byte

const (
	UNKNOWN TileType = 0
	NEUTRAL TileType = 1
	DEATH   TileType = 2
	RED     TileType = 3
	BLUE    TileType = 4
)

func (t TileType) MarshalGQL(w io.Writer) {
	fmt.Fprintf(w, "%q", t.String())
}

func (t *TileType) UnmarshalGQL(v interface{}) error {
	tile, ok := v.(string)
	if !ok {
		return fmt.Errorf("points must be strings")
	}
	var err error
	*t, err = TileTypeString(tile)
	return err
}

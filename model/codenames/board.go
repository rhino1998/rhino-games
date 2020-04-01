package codenames

import (
	"fmt"
	"io"
)

type Board struct {
	Tiles [][]Tile
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

var TileType_name = map[TileType]string{
	0: "UNKNOWN",
	1: "NEUTRAL",
	2: "DEATH",
	3: "RED",
	4: "BLUE",
}
var TileType_value = map[string]TileType{
	"UNKNOWN": 0,
	"NEUTRAL": 1,
	"DEATH":   2,
	"RED":     3,
	"BLUE":    4,
}

func (t TileType) String() string {
	return TileType_name[t]
}

func (t TileType) MarshalGQL(w io.Writer) {
	fmt.Fprintf(w, "%q", t.String())
}

func (t *TileType) UnmarshalGQL(v interface{}) error {
	tile, ok := v.(string)
	if !ok {
		return fmt.Errorf("points must be strings")
	}
	*t = TileType_value[tile]
	return nil
}

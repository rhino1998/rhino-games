//go:generate gorunpkg github.com/alvaroloes/enumer -type=Suit -trimprefix S
//go:generate gorunpkg github.com/alvaroloes/enumer -type=Value -trimprefix V

package playingcard

import (
	"fmt"
	"io"
)

type Card struct {
	Suit  Suit
	Value Value
}

func (c *Card) CompareTo(other *Card, aceHigh bool) int {
	if c.Value != other.Value {
		if aceHigh {
			if c.Value == VACE {
				return 1
			}
			if other.Value == VACE {
				return -1
			}
		}
		return int(c.Value - other.Value)
	}
	return int(c.Suit - other.Suit)
}

func (c *Card) Matches(other *Card) bool {
	return (c.Value == other.Value || c.Value == VWILD) &&
		(c.Suit == other.Suit || c.Suit == SWILD)
}

func (c *Card) String() string {
	return fmt.Sprintf("<%v %v>", c.Value, c.Suit)

}

type Value byte

var Values = [...]Value{
	VWILD,
	VACE,
	VTWO,
	VTHREE,
	VFOUR,
	VFIVE,
	VSIX,
	VSEVEN,
	VEIGHT,
	VNINE,
	VTEN,
	VJACK,
	VQUEEN,
	VKING,
	VACE,
}

const (
	VWILD Value = iota
	VACE
	VTWO
	VTHREE
	VFOUR
	VFIVE
	VSIX
	VSEVEN
	VEIGHT
	VNINE
	VTEN
	VJACK
	VQUEEN
	VKING
)

func (t Value) MarshalGQL(w io.Writer) {
	fmt.Fprintf(w, "%q", t.String())
}

func (t *Value) UnmarshalGQL(v interface{}) error {
	tile, ok := v.(string)
	if !ok {
		return fmt.Errorf("points must be strings")
	}
	var err error
	*t, err = ValueString(tile)
	return err
}

type Suit byte

var Suits = [...]Suit{
	SCLUBS,
	SDIAMONDS,
	SHEARTS,
	SSPADES,
}

const (
	SWILD Suit = iota
	SCLUBS
	SDIAMONDS
	SHEARTS
	SSPADES
)

func (t Suit) MarshalGQL(w io.Writer) {
	fmt.Fprintf(w, "%q", t.String())
}

func (t *Suit) UnmarshalGQL(v interface{}) error {
	tile, ok := v.(string)
	if !ok {
		return fmt.Errorf("points must be strings")
	}
	var err error
	*t, err = SuitString(tile)
	return err
}

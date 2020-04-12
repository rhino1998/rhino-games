//go:generate gorunpkg github.com/alvaroloes/enumer -type=Suit -trimprefix S
//go:generate gorunpkg github.com/alvaroloes/enumer -type=Value -trimprefix V

package liarspoker

import (
	"fmt"
	"io"
)

type Card struct {
	Suit    Suit
	Value   Value
	Present bool
}

func (c *Card) CompareTo(other *Card) int {
	if c.Value != other.Value {
		return int(c.Value) - int(other.Value)
	}
	return int(c.Suit) - int(other.Suit)
}

func (c *Card) Matches(other *Card) bool {
	return (c.Value == other.Value || c.Value == VWILD) &&
		(c.Suit == other.Suit || c.Suit == SWILD)
}

func (c *Card) String() string {
	return fmt.Sprintf("<%v %v>", c.Value, c.Suit)

}

type Value int8

var Values = [...]Value{
	VZERO,
	VONE,
	VTWO,
	VTHREE,
	VFOUR,
	VFIVE,
	VSIX,
	VSEVEN,
	VEIGHT,
	VNINE,
	VTEN,
	VELEVEN,
	VJACK,
	VQUEEN,
	VKING,
	VACE,
}

const (
	VWILD Value = iota
	VZERO
	VONE
	VTWO
	VTHREE
	VFOUR
	VFIVE
	VSIX
	VSEVEN
	VEIGHT
	VNINE
	VTEN
	VELEVEN
	VJACK
	VQUEEN
	VKING
	VACE
)

func (t Value) MarshalGQL(w io.Writer) {
	fmt.Fprintf(w, "%q", t.String())
}

func (t *Value) UnmarshalGQL(v interface{}) error {
	value, ok := v.(string)
	if !ok {
		return fmt.Errorf("points must be strings")
	}
	var err error
	*t, err = ValueString(value)
	return err
}

type Suit int8

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

//go:generate gorunpkg github.com/alvaroloes/enumer -type=HandKind

package liarspoker

import (
	"fmt"
)

type HandKind int8

const (
	UNSPECIFIED HandKind = iota
	HIGH
	PAIR
	TWOPAIR
	THREEOFAKIND
	STRAIGHT
	FULLHOUSE
	FOUROFAKIND
	STRAIGHTFLUSH
	FIVEOFAKIND
	SIXOFAKIND
	SEVENOFAKIND
	EIGHTOFAKIND
)

type CardStatus struct {
	Card    Card
	Present bool
}

func StructureHand(hand []*Card) StructuredHand {
	s := []StructuredHand{}

	i := 0
	for len(hand) > 0 && i < len(handMatchers) {
		var part StructuredHand
		part, hand = handMatchers[i](hand)
		if part != nil {
			s = append(s, part)
		} else {
			i++
		}
	}

	return &CompositeHand{hands: s}
}

type HandMatcher = func(h []*Card) (StructuredHand, []*Card)

type StructuredHand interface {
	kind() HandKind
	Cards() []*Card
	CompareTo(other StructuredHand) int
	String() string
	Size() int
}
type NKind struct {
	cards []*Card
}

func (h *NKind) Cards() []*Card {
	return h.cards
}

func (h *NKind) kind() HandKind {
	switch len(h.cards) {
	case 0:
		return UNSPECIFIED
	case 1:
		return HIGH
	case 2:
		return PAIR
	case 3:
		return THREEOFAKIND
	case 4:
		return FOUROFAKIND
	case 5:
		return FIVEOFAKIND
	case 6:
		return SIXOFAKIND
	case 7:
		return SEVENOFAKIND
	case 8:
		return EIGHTOFAKIND
	default:
		panic("INVALID NKIND HAND")
	}
}

func (h *NKind) CompareTo(other StructuredHand) int {
	cmp := int(h.kind() - other.kind())
	if cmp != 0 {
		return cmp
	}

	o := other.(*NKind)
	for i := range h.cards {
		cmp := h.cards[i].CompareTo(o.cards[i])
		if cmp != 0 {
			return cmp
		}
	}
	return 0
}

func (h *NKind) String() string {
	return fmt.Sprintf("<%d of a kind %s>", len(h.cards), h.cards[0].Value)
}

func (h *NKind) Size() int {
	return len(h.cards)
}

type CompositeHand struct {
	hands []StructuredHand
}

func (h *CompositeHand) kind() HandKind {
	if len(h.hands) == 2 && h.hands[0].kind() == PAIR && h.hands[1].kind() == PAIR {
		return TWOPAIR
	}

	if len(h.hands) == 2 && h.hands[0].kind() == THREEOFAKIND && h.hands[1].kind() == PAIR {
		return FULLHOUSE
	}

	return UNSPECIFIED
}
func (h *CompositeHand) Cards() []*Card {
	hand := []*Card{}

	for _, part := range h.hands {
		hand = append(hand, part.Cards()...)
	}
	return hand
}

func (h *CompositeHand) CompareTo(other StructuredHand) int {
	cmp := int(h.kind() - other.kind())
	if cmp != 0 {
		return cmp
	}

	o := other.(*CompositeHand)
	for i := range h.hands {
		if i >= len(o.hands) {
			break
		}
		cmp = h.hands[i].CompareTo(o.hands[i])
		if cmp != 0 {
			return cmp
		}
	}

	return len(h.hands) - len(o.hands)
}

func (h *CompositeHand) String() string {
	return fmt.Sprintf("<%v>", h.hands)
}

func (h *CompositeHand) Size() int {
	size := 0
	for _, hand := range h.hands {
		size += hand.Size()
	}
	return size
}

type SuitedRunHand struct {
	suit  Suit
	cards []*Card
}

func (h *SuitedRunHand) Cards() []*Card {
	return h.cards
}

func (h *SuitedRunHand) kind() HandKind {

	if len(h.cards) == 5 && h.suit == SWILD {
		return STRAIGHT
	}

	if len(h.cards) == 5 {
		return STRAIGHTFLUSH
	}

	panic("UNKNOWN")
}

func (h *SuitedRunHand) CompareTo(other StructuredHand) int {
	cmp := int(h.kind() - other.kind())
	if cmp != 0 {
		return cmp
	}

	o := other.(*SuitedRunHand)
	for i := range h.cards {
		cmp := h.cards[i].CompareTo(o.cards[i])
		if cmp != 0 {
			return cmp
		}
	}
	return 0
}

func (h *SuitedRunHand) String() string {
	return fmt.Sprintf("<%v from %v>", h.suit, h.cards[0])
}

func (h *SuitedRunHand) Size() int {
	return len(h.cards)
}

package liarspoker

import (
	"testing"
)

func TestExists(t *testing.T) {

	d := NewDeck(1)
	d.Shuffle()
	cards := []*Card{d.Draw(), d.Draw(), d.Draw()}

	if !NewHand(cards).Exists(cards) {
		t.Fail()
	}
}

func TestStraight(t *testing.T) {

	hand := Hand{
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VSIX},
		&Card{Suit: SWILD, Value: VSEVEN},
		&Card{Suit: SWILD, Value: VEIGHT},
		&Card{Suit: SWILD, Value: VNINE},
	}

	s, ok := hand.Structure().(*CompositeHand)

	if !ok || s.hands[0].kind() != STRAIGHT {
		t.Fail()
	}
}

func TestStraightFlush(t *testing.T) {

	hand := Hand{
		&Card{Suit: SHEARTS, Value: VFIVE},
		&Card{Suit: SHEARTS, Value: VSIX},
		&Card{Suit: SHEARTS, Value: VSEVEN},
		&Card{Suit: SHEARTS, Value: VEIGHT},
		&Card{Suit: SSPADES, Value: VEIGHT},
		&Card{Suit: SHEARTS, Value: VNINE},
		&Card{Suit: SHEARTS, Value: VTEN},
		&Card{Suit: SHEARTS, Value: VELEVEN},
		&Card{Suit: SHEARTS, Value: VJACK},
		&Card{Suit: SHEARTS, Value: VQUEEN},
		&Card{Suit: SSPADES, Value: VQUEEN},
		&Card{Suit: SHEARTS, Value: VKING},
		&Card{Suit: SHEARTS, Value: VACE},
	}

	s, ok := hand.Structure().(*CompositeHand)

	if !ok || s.hands[0].kind() != STRAIGHTFLUSH {
		t.Fail()
	}
}

func TestStraightUnordered(t *testing.T) {

	hand := Hand{
		&Card{Suit: SWILD, Value: VSIX},
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VSEVEN},
		&Card{Suit: SWILD, Value: VEIGHT},
		&Card{Suit: SWILD, Value: VNINE},
	}

	s, ok := hand.Structure().(*CompositeHand)

	if !ok || s.hands[0].kind() != STRAIGHT {
		t.Fail()
	}
}

func TestExistsDeck(t *testing.T) {

	d := NewDeck(2)
	d.Shuffle()

	cards := []*Card{}
	for {
		card := d.Draw()
		if card == nil {
			break
		}
		cards = append(cards, card)
	}

	hand := NewHand(cards)

	if !hand.Exists(cards) {
		t.Fail()
	}
}

func TestStructurePair(t *testing.T) {
	hand := Hand{
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFIVE},
	}

	s, ok := hand.Structure().(*CompositeHand)

	if !ok || s.hands[0].kind() != PAIR {
		t.Fail()
	}
}

func TestStructureEightOfAKind(t *testing.T) {
	hand := Hand{
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFIVE},
	}

	s, ok := hand.Structure().(*CompositeHand)

	if !ok || s.hands[0].kind() != EIGHTOFAKIND {
		t.Fail()
	}
}

func TestStructureTwoPair(t *testing.T) {
	hand := Hand{
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFIVE},
		&Card{Suit: SWILD, Value: VFOUR},
		&Card{Suit: SWILD, Value: VFOUR},
		&Card{Suit: SWILD, Value: VSIX},
		&Card{Suit: SWILD, Value: VNINE},
		&Card{Suit: SWILD, Value: VJACK},
		&Card{Suit: SWILD, Value: VQUEEN},
	}

	s, ok := hand.Structure().(*CompositeHand)

	if !ok || s.hands[0].kind() != TWOPAIR {
		t.Fail()
	}
}

package playingcard

import (
	"math/rand"
)

type Deck struct {
	cards []*Card
}

func NewDeck(n int) *Deck {
	d := &Deck{}

	for _, suit := range Suits {
		for _, value := range Values {
			for i := 0; i < n; i++ {
				d.cards = append(d.cards, &Card{Suit: suit, Value: value})
			}
		}
	}

	return d
}

func (d *Deck) Remove() {
}

func (d *Deck) Shuffle() {
	rand.Shuffle(len(d.cards), func(i, j int) { d.cards[i], d.cards[j] = d.cards[j], d.cards[i] })
}

func (d *Deck) Draw() *Card {
	var card *Card
	if len(d.cards) > 1 {
		card = d.cards[0]
		d.cards = d.cards[1:]
	} else if len(d.cards) == 0 {
		card = d.cards[0]
		d.cards = nil
	}
	return card
}

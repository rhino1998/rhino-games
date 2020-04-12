package liarspoker

import "log"

type Player struct {
	Name         string
	PrivateCards []*Card
	PublicCards  []*Card

	WonHands  int
	LostHands int

	Current bool
	Ready   bool

	numCards int
}

func (p *Player) TotalCards() int {
	return p.numCards
}

func (p *Player) Call(call []*Card, cards []*Card) *PlayerCall {
	hand := StructureHand(call)
	log.Println(hand)
	pc := &PlayerCall{
		call:   hand,
		player: p,
		exists: handExists(hand, cards),
	}

	return pc
}

type PlayerCall struct {
	player *Player
	call   StructuredHand

	exists bool
}

func (p *PlayerCall) Player() *Player {
	return p.player
}

func (p *PlayerCall) Call() []*Card {
	return p.call.Cards()
}

func (p *PlayerCall) Exists() bool {
	return p.exists
}

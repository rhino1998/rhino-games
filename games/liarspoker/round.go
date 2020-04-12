package liarspoker

import (
	"fmt"
	"log"
)

type Round struct {
	baseStateNotifier

	callSize int
	numDecks int

	turn int

	players []*Player
	prev    int

	calls []*PlayerCall
}

func (s *Round) deal() {
	deck := NewDeck(s.numDecks)
	deck.Shuffle()

	for _, player := range s.players {
		if player == nil {
			continue
		}
		player.PrivateCards = nil
		player.PublicCards = nil
		for i := 0; i < player.numCards/2; i++ {
			player.PublicCards = append(player.PublicCards, deck.Draw())
		}

		for i := player.numCards / 2; i < player.numCards; i++ {
			player.PrivateCards = append(player.PrivateCards, deck.Draw())
		}
	}
}

func (s *Round) get(player *string) State {
	g := &RoundState{}
	players := make([]*Player, 0, len(s.players))
	pos := 0
	for i, orderedPlayer := range s.players {
		if orderedPlayer == nil {
			continue
		}
		if player != nil && *player == orderedPlayer.Name {
			g.Player = orderedPlayer
			pos = i

		} else {
			players = append(players, orderedPlayer)
		}
	}

	players = append(players[pos:], players[0:pos]...)

	g.CallSize = s.callSize
	g.Others = players
	g.CurrentPlayer = s.currentPlayer()
	g.Calls = s.calls

	return g
}

func (s *Round) mutate(m Mutation) (StateNotifier, error) {
	switch mutation := m.(type) {
	case *CallHandMutation:
		if len(mutation.call) > s.callSize {
			return s, fmt.Errorf("call: invalid call size (%d > %d)", len(mutation.call), s.callSize)
		}
		if mutation.player != s.players[s.turn].Name {
			return s, fmt.Errorf("call: not current player")
		}
		playerCall := s.players[s.turn].Call(mutation.call, s.cards())
		if len(s.calls) > 0 && playerCall.call.CompareTo(s.calls[len(s.calls)-1].call) <= 0 {
			return s, fmt.Errorf("call: call too low")
		}

		s.calls = append(s.calls, playerCall)
		log.Println(s.calls)
		s.nextTurn()
		log.Println(s.turn)
		return s, nil
	case *CallBSMutation:
		if len(s.calls) == 0 {
			return s, fmt.Errorf("call: can't call starting nil call")
		}

		cards := []*Card{}
		for _, player := range s.players {
			cards = append(cards, player.PrivateCards...)
			cards = append(cards, player.PublicCards...)
		}

		var winner, loser *Player

		if s.calls[len(s.calls)-1].Exists() {
			fmt.Println(cards)
			fmt.Println("EXISTS")
			s.players[s.turn%len(s.players)].numCards--
			s.players[s.prev%len(s.players)].LostHands++
			s.players[s.turn%len(s.players)].WonHands++
			winner = s.players[s.prev%len(s.players)]
			loser = s.players[s.turn%len(s.players)]
			s.prevTurn()
		} else {
			s.players[s.prev%len(s.players)].numCards--
			s.players[s.prev%len(s.players)].LostHands++
			s.players[s.turn%len(s.players)].WonHands++
			winner = s.players[s.turn%len(s.players)]
			loser = s.players[s.prev%len(s.players)]
		}

		playersByName := make(map[string]*Player)
		for _, player := range s.players {
			playersByName[player.Name] = player
		}

		return &RoundSummary{
			baseStateNotifier: s.baseStateNotifier,
			numDecks:          s.numDecks,
			callSize:          s.callSize,
			playersByName:     playersByName,
			players:           s.players,
			winner:            winner,
			loser:             loser,
			calls:             s.calls,
			turn:              s.turn,
		}, nil
	}

	return s, fmt.Errorf("round: invalid mutation: %#v", m)
}

func (r *Round) currentPlayer() *Player {
	r.players[r.turn%len(r.players)].Current = true
	return r.players[r.turn%len(r.players)]
}

func (r *Round) nextTurn() {
	r.players[r.turn%len(r.players)].Current = false
	r.prev = r.turn
	r.turn = (r.turn + 1) % len(r.players)
	for r.players[r.turn].numCards <= 0 {
		r.turn = (r.turn + 1) % len(r.players)
	}
	r.players[r.turn%len(r.players)].Current = true
}

func (r *Round) prevTurn() {
	r.players[r.turn%len(r.players)].Current = false
	r.turn = r.prev
	r.players[r.turn%len(r.players)].Current = true
}

func (r *Round) cards() []*Card {
	cards := make([]*Card, 0)
	for _, player := range r.players {
		cards = append(append(cards, player.PublicCards...), player.PrivateCards...)
	}
	return cards
}

type RoundState struct {
	Player        *Player
	Others        []*Player
	CurrentPlayer *Player
	CallSize      int
	Calls         []*PlayerCall
}

func (RoundState) IsLiarsPokerState() {}

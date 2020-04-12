package liarspoker

import (
	"fmt"
	"log"
)

type Lobby struct {
	baseStateNotifier

	callSize int
	numCards int
	numDecks int

	players map[string]*Player
}

var _ State = (*Lobby)(nil)
var _ StateNotifier = (*Lobby)(nil)

func newLobby() *Lobby {
	return &Lobby{
		numDecks: 1,
		numCards: 1,
		callSize: 8,
		players:  make(map[string]*Player),
	}

}

func (Lobby) IsLiarsPokerState() {}

func (l *Lobby) Players() []*Player {
	players := make([]*Player, 0, len(l.players))
	for _, player := range l.players {
		players = append(players, player)
	}

	return players
}

func (l *Lobby) NumCards() int {
	return l.numCards
}

func (l *Lobby) NumDecks() int {
	return l.numDecks
}

func (l *Lobby) CallSize() int {
	return l.callSize
}

func (l *Lobby) setNumCards(numCards int) {
	l.numCards = numCards
	l.notify()
}

func (l *Lobby) setNumDecks(numDecks int) {
	l.numDecks = numDecks
	l.notify()
}

func (l *Lobby) get(player *string) State {
	if player != nil {
		if _, ok := l.players[*player]; !ok {
			l.players[*player] = &Player{Name: *player}
		}
	}
	return l
}

func (l *Lobby) ready() bool {
	ready := true
	for _, player := range l.players {
		ready = ready && player.Ready
	}
	return ready
}

func (l *Lobby) mutate(m Mutation) (StateNotifier, error) {
	switch mutation := m.(type) {
	case *ReadyMutation:
		l.players[mutation.player].Ready = true
		if l.ready() {
			log.Println(l.hooks)
			s := &Round{
				callSize:          l.callSize,
				numDecks:          l.numDecks,
				players:           make([]*Player, 0, len(l.players)),
				baseStateNotifier: l.baseStateNotifier,
			}

			for _, player := range l.players {
				player.numCards = l.numCards
				player.Ready = false
				s.players = append(s.players, player)
			}
			s.deal()
			return s, nil
		} else {
			return l, nil
		}
	case *SetNumCardsMutation:
		l.numCards = mutation.numCards
		return l, nil
	case *SetNumDecksMutation:
		l.numDecks = mutation.numDecks
		return l, nil
	case *SetCallSizeMutation:
		l.callSize = mutation.callSize
		return l, nil
	}

	return l, fmt.Errorf("lobby: invalid mutation: %v", m)
}

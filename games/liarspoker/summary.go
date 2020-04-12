package liarspoker

import (
	"fmt"
	"log"
)

type RoundSummary struct {
	baseStateNotifier

	callSize int
	numDecks int

	calls []*PlayerCall

	playersByName map[string]*Player
	players       []*Player
	winner        *Player
	loser         *Player
	turn          int
}

func (g *RoundSummary) get(player *string) State {
	s := &RoundSummaryState{}
	players := make([]*Player, 0, len(g.players))
	pos := 0
	for i, orderedPlayer := range g.players {
		if orderedPlayer == nil {
			continue
		}
		if player != nil && *player == orderedPlayer.Name {
			s.Player = orderedPlayer
			pos = i

		} else {
			players = append(players, orderedPlayer)
		}
	}

	players = append(players[pos:], players[0:pos]...)

	s.Others = players
	s.Winner = g.winner
	s.Loser = g.loser
	s.Calls = g.calls

	log.Println(s)
	return s
}

func (g *RoundSummary) ready() bool {
	ready := true
	for _, player := range g.players {
		ready = ready && player.Ready
	}
	return ready
}

func (g *RoundSummary) gameOver() bool {
	playersLeft := 0
	for _, player := range g.players {
		if player.numCards > 0 {
			playersLeft++
		}
	}

	return playersLeft <= 1
}

func (g *RoundSummary) mutate(m Mutation) (StateNotifier, error) {
	switch mutation := m.(type) {

	case *ReadyMutation:
		g.playersByName[mutation.player].Ready = true
		if g.ready() {

			if g.gameOver() {
				for _, player := range g.players {
					player.Ready = false
				}
				l := &Lobby{
					baseStateNotifier: g.baseStateNotifier,
					players:           g.playersByName,
					numDecks:          g.numDecks,
					numCards:          1,
					callSize:          g.callSize,
				}

				return l, nil
			} else {
				log.Println(g.hooks)
				s := &Round{
					callSize:          g.callSize,
					numDecks:          g.numDecks,
					players:           make([]*Player, 0, len(g.players)),
					baseStateNotifier: g.baseStateNotifier,
					turn:              g.turn,
				}

				for _, player := range g.players {
					player.Ready = false
					s.players = append(s.players, player)
				}
				s.deal()
				return s, nil
			}
		} else {
			return g, nil
		}
	}

	return g, fmt.Errorf("game_summary: invalid mutation")
}

type RoundSummaryState struct {
	Others []*Player
	Player *Player
	Winner *Player
	Loser  *Player

	Calls []*PlayerCall
}

func (*RoundSummaryState) IsLiarsPokerState() {}

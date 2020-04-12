package liarspoker

import (
	"context"
	"fmt"
	"sync"
)

type State interface {
	IsLiarsPokerState()
}

type Game struct {
	lock sync.Mutex

	games map[string]StateNotifier
}

func New() (*Game, error) {
	return &Game{games: make(map[string]StateNotifier)}, nil
}

func (r *Game) LiarspokerSetNumCards(ctx context.Context, code string, numCards int) (int, error) {
	r.lock.Lock()
	defer r.lock.Unlock()

	state, ok := r.games[code]
	if !ok {
		return 0, fmt.Errorf("Invalid game code: %s", code)
	}

	var err error
	r.games[code], err = state.mutate(&SetNumCardsMutation{numCards: numCards})
	return numCards, err
}

func (r *Game) LiarspokerSetNumDecks(ctx context.Context, code string, numDecks int) (int, error) {

	r.lock.Lock()
	defer r.lock.Unlock()

	state, ok := r.games[code]
	if !ok {
		return 0, fmt.Errorf("Invalid game code: %s", code)
	}

	var err error
	r.games[code], err = state.mutate(&SetNumDecksMutation{numDecks: numDecks})

	return numDecks, err
}

func (r *Game) LiarspokerSetCallSize(ctx context.Context, code string, callSize int) (int, error) {
	r.lock.Lock()
	defer r.lock.Unlock()

	state, ok := r.games[code]
	if !ok {
		return 0, fmt.Errorf("Invalid game code: %s", code)
	}

	var err error
	r.games[code], err = state.mutate(&SetCallSizeMutation{callSize: callSize})
	return callSize, err
}

func (r *Game) LiarspokerReady(ctx context.Context, code string, player string) (bool, error) {

	r.lock.Lock()
	defer r.lock.Unlock()

	state, ok := r.games[code]
	if !ok {
		return false, fmt.Errorf("Invalid game code: %s", code)
	}

	var err error
	r.games[code], err = state.mutate(&ReadyMutation{player: player})
	if err == nil {
		state.notify()
	}

	return err != nil, err

}

func (r *Game) LiarspokerCall(ctx context.Context, code string, player string, call []*Card) (bool, error) {
	r.lock.Lock()
	defer r.lock.Unlock()

	state, ok := r.games[code]
	if !ok {
		return false, fmt.Errorf("Invalid game code: %s", code)
	}

	var err error
	if call == nil {
		r.games[code], err = state.mutate(&CallBSMutation{player: player})
	} else {
		r.games[code], err = state.mutate(&CallHandMutation{call: call, player: player})
	}

	if err == nil {
		state.notify()
	}

	return err != nil, err
}

func (r *Game) LiarspokerState(ctx context.Context, code string, player *string) (<-chan State, error) {
	r.lock.Lock()
	defer r.lock.Unlock()

	state, ok := r.games[code]

	if !ok {
		if player == nil {
			return nil, fmt.Errorf("Cannot spectate empty game")
		}
		state = newLobby()
		r.games[code] = state
	}

	c := make(chan State, 1)

	state.addHook(func() bool {
		state := r.games[code].get(player)
		if state == nil {
			panic(code)
		}
		select {
		case <-ctx.Done():
			return false
		case c <- state:
			return true
		}
	})

	// go func() {
	// 	<-ctx.Done()
	// 	if state.notify() {
	// 		delete(r.games, code)
	// 		log.Printf("Deleted %s", code)
	// 	}
	// 	close(c)
	// 	c = nil
	// }()

	state.notify()
	return c, nil
}

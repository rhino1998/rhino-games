//go:generate gorunpkg github.com/99designs/gqlgen

package games

import (
	"context"

	"github.com/rhino1998/codenames/games/codenames"
	"github.com/rhino1998/codenames/games/liarspoker"
)

type CodeNames = codenames.Game
type LiarsPoker = liarspoker.Game

//Resolver implements the interface defined by the associated GraphQL schema
type Resolver struct {
	*CodeNames
	*LiarsPoker
}

func New(codenames *codenames.Game, liarspoker *LiarsPoker) *Resolver {
	return &Resolver{CodeNames: codenames, LiarsPoker: liarspoker}
}

func (r *Resolver) Query() QueryResolver {
	return r
}

func (r *Resolver) Mutation() MutationResolver {
	return r
}

func (r *Resolver) Subscription() SubscriptionResolver {
	return r
}

func (r *Resolver) StubMutation(ctx context.Context) (bool, error) {
	return true, nil
}

func (r *Resolver) StubQuery(ctx context.Context) (bool, error) {
	return true, nil
}

func (r *Resolver) StubSubscription(ctx context.Context) (<-chan bool, error) {
	return make(chan bool), nil
}

//go:generate gorunpkg github.com/99designs/gqlgen

package resolver

import (
	"context"

	"github.com/rhino1998/codenames/model/codenames"
)

//Resolver implements the interface defined by the associated GraphQL schema
type Resolver struct {
	codenames *codenames.Game
}

func New(codenames *codenames.Game) *Resolver {
	return &Resolver{codenames: codenames}
}

func (r *Resolver) Query() QueryResolver {
	return &queryResolver{r: r}
}

func (r *Resolver) Mutation() MutationResolver {
	return &mutationResolver{r: r}
}

func (r *Resolver) CodeNames() CodeNamesResolver {
	return r.codenames
}

type queryResolver struct {
	r *Resolver
}

func (q *queryResolver) Codenames(ctx context.Context) (*codenames.Game, error) {
	return q.r.codenames, nil
}

type mutationResolver struct {
	r *Resolver
}

func (q *mutationResolver) Codenames(ctx context.Context) (*codenames.Game, error) {
	return q.r.codenames, nil
}

package liarspoker

type StateNotifier interface {
	addHook(hook func() bool)
	notify() bool
	get(player *string) State

	mutate(m Mutation) (StateNotifier, error)
}

type baseStateNotifier struct {
	hooks []func() bool
}

func (b *baseStateNotifier) addHook(hook func() bool) {
	b.hooks = append(b.hooks, hook)
}

func (b *baseStateNotifier) notify() bool {
	kept := make([]func() bool, 0, len(b.hooks))
	for _, hook := range b.hooks {
		if hook() {
			kept = append(kept, hook)
		}
	}
	b.hooks = kept
	return len(b.hooks) == 0
}

package liarspoker

type Mutation interface {
	isMutation()
}

type baseMutation struct {
}

func (baseMutation) isMutation() {}

type SetNumCardsMutation struct {
	baseMutation
	numCards int
}

type SetNumDecksMutation struct {
	baseMutation
	numDecks int
}

type SetCallSizeMutation struct {
	baseMutation
	callSize int
}

type ReadyMutation struct {
	baseMutation
	player string
}

type CallHandMutation struct {
	baseMutation
	player string
	call   []*Card
}

type CallBSMutation struct {
	baseMutation
	player string
}

package liarspoker

import "sort"

var handMatchers = []HandMatcher{
	tryNKind(8),
	tryNKind(7),
	tryNKind(6),
	tryNKind(5),
	trySuitedRunHand(5, SSPADES),
	trySuitedRunHand(5, SHEARTS),
	trySuitedRunHand(5, SDIAMONDS),
	trySuitedRunHand(5, SCLUBS),
	tryNKind(4),
	tryCompositeHand(tryNKind(3), tryNKind(2)), // FULLHOUE
	trySuitedRunHand(5, SWILD),
	tryNKind(3),
	tryNHand(2, tryNKind(2)), // TWO PAIR
	tryNKind(2),
	tryNKind(1),
	tryClean(),
}

func handExists(hand StructuredHand, cards []*Card) bool {
	missing := make(map[Card]int)

	handCards := hand.Cards()
	cards = append([]*Card{}, cards...)
	sort.Slice(cards,
		func(i, j int) bool {
			return cards[i].CompareTo(cards[j]) > 0
		},
	)

	for _, card := range handCards {
		missing[*card]++
	}

	for _, card := range cards {
		for _, target := range handCards {
			if (card.Value == VZERO || target.Matches(card)) && missing[*target] != 0 {
				missing[*target]--
				target.Present = true
				break
			}
		}
	}

	totalMissing := 0
	for _, count := range missing {
		totalMissing += count
	}

	return totalMissing <= 0
}

func tryClean() HandMatcher {
	return func(h []*Card) (StructuredHand, []*Card) {
		return nil, nil
	}
}

func tryNKind(n int) HandMatcher {
	return func(h []*Card) (StructuredHand, []*Card) {
		values := make(map[Value]int)
		for _, card := range h {
			if card.Value != VWILD {
				values[card.Value]++
			}
		}

		for i := len(Values) - 1; i >= 0; i-- {
			value := Values[i]
			num := values[value]
			if num >= n {
				hand := make([]*Card, 0, n)
				rest := make([]*Card, 0, len(h)-n)
				for _, card := range h {
					if card.Value != value || len(hand) == n {
						rest = append(rest, card)
					} else {
						hand = append(hand, card)
					}
				}

				sort.Slice(hand,
					func(i, j int) bool {
						return hand[i].CompareTo(hand[j]) > 0
					},
				)

				return &NKind{cards: hand}, rest
			}
		}

		return nil, h
	}
}

func tryNHand(n int, matcher HandMatcher) HandMatcher {

	matchers := make([]func(h []*Card) (StructuredHand, []*Card), n)
	for i := 0; i < n; i++ {
		matchers[i] = matcher
	}

	return tryCompositeHand(matchers...)
}

func tryCompositeHand(matchers ...HandMatcher) HandMatcher {
	return func(h []*Card) (StructuredHand, []*Card) {
		s := []StructuredHand{}

		hand := h
		for _, matcher := range matchers {
			var part StructuredHand
			part, hand = matcher(hand)
			if part != nil {
				s = append(s, part)
			} else {
				return nil, h
			}
		}

		return &CompositeHand{hands: s}, hand
	}
}

func trySuitedRunHand(n int, suit Suit) HandMatcher {
	return func(h []*Card) (StructuredHand, []*Card) {

		hand := make([]*Card, 0, len(h))
		rest := make([]*Card, 0, len(h))

		for _, card := range h {
			if suit == SWILD || card.Suit == suit {
				hand = append(hand, card)
			} else {
				rest = append(rest, card)
			}
		}

		sort.Slice(hand,
			func(i, j int) bool {
				return hand[i].CompareTo(hand[j]) > 0
			},
		)

		for i, card := range hand {
			if !(n+i <= len(hand)) {
				break
			}

			if suit != SWILD && card.Suit != suit {
				continue
			}

			success := true
			for j := 1; j < n; j++ {
				if hand[i].Value-Value(j) != hand[i+j].Value {
					success = false
					break
				}

				if suit != SWILD && hand[i+j].Suit != suit {
					success = false
					break
				}
			}
			if !success {
				continue
			}

			newHand := make([]*Card, 0, len(hand)-n)
			for k, card := range hand {
				if k < i || k >= i+n {
					newHand = append(newHand, card)
				}
			}

			return &SuitedRunHand{suit: suit, cards: hand[i : i+n]}, append(newHand, rest...)
		}
		return nil, h
	}
}

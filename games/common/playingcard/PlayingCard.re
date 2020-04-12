type value = [
  | `WILD
  | `ACE
  | `EIGHT
  | `FIVE
  | `FOUR
  | `JACK
  | `KING
  | `NINE
  | `QUEEN
  | `SEVEN
  | `SIX
  | `TEN
  | `THREE
  | `TWO
];

type suit = [ | `WILD | `CLUBS | `DIAMONDS | `HEARTS | `SPADES];

type card = {
  value,
  suit,
};

let string_of_suit = suit =>
  switch (suit) {
  | `WILD => {j|*|j}
  | `CLUBS => {j|♣|j}
  | `DIAMONDS => {j|♦|j}
  | `HEARTS => {j|♥|j}
  | `SPADES => {j|♠|j}
  };

let string_of_value = value =>
  switch (value) {
  | `WILD => {j|*|j}
  | `ACE => {j|A|j}
  | `TWO => {j|2|j}
  | `THREE => {j|3|j}
  | `FOUR => {j|4|j}
  | `FIVE => {j|5|j}
  | `SIX => {j|6|j}
  | `SEVEN => {j|7|j}
  | `EIGHT => {j|8|j}
  | `NINE => {j|9|j}
  | `TEN => {j|0|j}
  | `JACK => {j|J|j}
  | `QUEEN => {j|Q|j}
  | `KING => {j|K|j}
  };

let color_of_card = card => {
    switch (card.suit) {
        | `HEARTS | `DIAMONDS => `RED
        | _ => `BLACK
    }
}

let string_of_card = card =>
  switch (card) {
  | {suit: `WILD, value: `WILD} => "*"
  | {suit: `WILD, value} => string_of_value(value)
  | {value: `WILD, suit} => string_of_suit(suit)

  | {suit: `CLUBS, value: `ACE} => {j|🃑|j}
  | {suit: `CLUBS, value: `TWO} => {j|🃒|j}
  | {suit: `CLUBS, value: `THREE} => {j|🃓|j}
  | {suit: `CLUBS, value: `FOUR} => {j|🃔|j}
  | {suit: `CLUBS, value: `FIVE} => {j|🃕|j}
  | {suit: `CLUBS, value: `SIX} => {j|🃖|j}
  | {suit: `CLUBS, value: `SEVEN} => {j|🃗|j}
  | {suit: `CLUBS, value: `EIGHT} => {j|🃘|j}
  | {suit: `CLUBS, value: `NINE} => {j|🃙|j}
  | {suit: `CLUBS, value: `TEN} => {j|🃚|j}
  | {suit: `CLUBS, value: `JACK} => {j|🃛|j}
  | {suit: `CLUBS, value: `QUEEN} => {j|🃝|j}
  | {suit: `CLUBS, value: `KING} => {j|🃞|j}

  | {suit: `DIAMONDS, value: `ACE} => {j|🃁|j}
  | {suit: `DIAMONDS, value: `TWO} => {j|🃂|j}
  | {suit: `DIAMONDS, value: `THREE} => {j|🃃|j}
  | {suit: `DIAMONDS, value: `FOUR} => {j|🃄|j}
  | {suit: `DIAMONDS, value: `FIVE} => {j|🃅|j}
  | {suit: `DIAMONDS, value: `SIX} => {j|🃆|j}
  | {suit: `DIAMONDS, value: `SEVEN} => {j|🃇|j}
  | {suit: `DIAMONDS, value: `EIGHT} => {j|🃈|j}
  | {suit: `DIAMONDS, value: `NINE} => {j|🃉|j}
  | {suit: `DIAMONDS, value: `TEN} => {j|🃊|j}
  | {suit: `DIAMONDS, value: `JACK} => {j|🃋|j}
  | {suit: `DIAMONDS, value: `QUEEN} => {j|🃍|j}
  | {suit: `DIAMONDS, value: `KING} => {j|🃎|j}

  | {suit: `HEARTS, value: `ACE} => {j|🂱|j}
  | {suit: `HEARTS, value: `TWO} => {j|🂲|j}
  | {suit: `HEARTS, value: `THREE} => {j|🂳|j}
  | {suit: `HEARTS, value: `FOUR} => {j|🂴|j}
  | {suit: `HEARTS, value: `FIVE} => {j|🂵|j}
  | {suit: `HEARTS, value: `SIX} => {j|🂶|j}
  | {suit: `HEARTS, value: `SEVEN} => {j|🂷|j}
  | {suit: `HEARTS, value: `EIGHT} => {j|🂸|j}
  | {suit: `HEARTS, value: `NINE} => {j|🂹|j}
  | {suit: `HEARTS, value: `TEN} => {j|🂺|j}
  | {suit: `HEARTS, value: `JACK} => {j|🂻|j}
  | {suit: `HEARTS, value: `QUEEN} => {j|🂽|j}
  | {suit: `HEARTS, value: `KING} => {j|🂾|j}

  | {suit: `SPADES, value: `ACE} => {j|🂡|j}
  | {suit: `SPADES, value: `TWO} => {j|🂢|j}
  | {suit: `SPADES, value: `THREE} => {j|🂣|j}
  | {suit: `SPADES, value: `FOUR} => {j|🂤|j}
  | {suit: `SPADES, value: `FIVE} => {j|🂥|j}
  | {suit: `SPADES, value: `SIX} => {j|🂦|j}
  | {suit: `SPADES, value: `SEVEN} => {j|🂧|j}
  | {suit: `SPADES, value: `EIGHT} => {j|🂨|j}
  | {suit: `SPADES, value: `NINE} => {j|🂩|j}
  | {suit: `SPADES, value: `TEN} => {j|🂪|j}
  | {suit: `SPADES, value: `JACK} => {j|🂫|j}
  | {suit: `SPADES, value: `QUEEN} => {j|🂭|j}
  | {suit: `SPADES, value: `KING} => {j|🂮|j}
  };

module Card = {
  [@react.component]
  let make = (~card) => ReasonReact.string(string_of_card(card));
};

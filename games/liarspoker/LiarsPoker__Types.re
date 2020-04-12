let arr_opt = data => data->Belt.Array.map(item => item->Some);

let player_of_public = player => {
  "name": player##name,
  "publicCards": (player##publicCards: array('a)),
  "privateCards":
	(player##totalCards - player##publicCards->Belt.Array.length)
	->Belt.Array.make(None: 'a),
  "totalCards": player##totalCards,
  "current": player##current,
};

let player_of_private = player => {
  "name": player##name,
  "privateCards": (player##privateCards: array('a)),
  "publicCards":
	(player##totalCards - player##privateCards->Belt.Array.length)
	->Belt.Array.make(None: 'a),
  "totalCards": player##totalCards,
  "current": player##current,
};

let cardStatus_of_card = card => {
  "suit": card##suit,
  "value": card##value,
  "present": (None: option(bool)),
};

let cardStatus_of_cardStatus = card => {
  "suit": card##suit,
  "value": card##value,
  "present": Some(card##present),
};

let players_of_private = player => player->Belt.Option.map(player_of_private);

module Fragments = [%graphql
  {|
	fragment card on LiarsPokerCard @bsDecoder(fn: "cardStatus_of_card") {
	  suit
	  value
	}

	fragment cardStatus on LiarsPokerCardStatus @bsDecoder(fn: "cardStatus_of_cardStatus") {
	  suit
	  value
	  present
	}

	fragment namedPlayer on LiarsPokerPlayer {
	  name
	}

	fragment playerCall on LiarsPokerPlayerCall {
		  call @bsDecoder(fn: "arr_opt") {
			...Card
		  }
		  player {
			...NamedPlayer
		  }
	}

	fragment playerCallStatus on LiarsPokerPlayerCallStatus {
		  call @bsDecoder(fn: "arr_opt") {
			...CardStatus
		  }
		  player {
			...NamedPlayer
		  }
	}

	fragment privatePlayer on LiarsPokerPlayer @bsDecoder(fn: "player_of_private"){
	  name
	  totalCards
	  current

	  privateCards @bsDecoder(fn: "arr_opt") {
		...Card
	  }
	}

	fragment publicPlayer on LiarsPokerPlayer @bsDecoder(fn: "player_of_public"){
	  name
	  totalCards
	  current

	  publicCards @bsDecoder(fn: "arr_opt") {
		...Card
	  }
	}
	fragment player on LiarsPokerPlayer {
	  name
	  totalCards
	  current

	  privateCards @bsDecoder(fn: "arr_opt"){
		...Card
	  }
	  publicCards @bsDecoder(fn: "arr_opt"){
		...Card
	  }
	}

  |}
];
include Fragments;

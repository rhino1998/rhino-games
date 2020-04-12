module Types = LiarsPoker__Types;

module StateS = [%graphql
  {|
	subscription state($code: String!, $player: String){
	  state: liarspoker_state(code: $code, player: $player) {
		... on LiarsPokerRound {
		  callSize
		  calls {
			...Types.PlayerCall
		  }
		  player {
			...Types.PrivatePlayer
		  }
		  others {
			...Types.PublicPlayer
		  }
		  currentPlayer {
			...Types.NamedPlayer
		  }
		}
		... on LiarsPokerLobby {
		  numCards
		  numDecks
		  callSize
		  players {
			  name
			  ready
		  }
		}
		... on LiarsPokerRoundSummary {
		  calls {
			...Types.PlayerCallStatus
		  }
		  player {
			...Types.Player
		  }
		  others {
			...Types.Player
		  }
		  winner {
			...Types.NamedPlayer
		  }
		  loser {
			...Types.NamedPlayer
		  }
		}
	  }
	}
  |}
];

module ReadyM = [%graphql
  {|
	mutation ready($code: String!, $player: String!){
	  ready: liarspoker_ready(code: $code, player: $player)
	}
  |}
];

module SetNumCardsM = [%graphql
  {|
	mutation setNumCards($code: String!, $numCards: Int!){
	  numCards: liarspoker_setNumCards(code: $code, numCards: $numCards)
	}
  |}
];

module SetNumDecksM = [%graphql
  {|
	mutation setNumDecks($code: String!, $numDecks: Int!){
	  numDecks: liarspoker_setNumDecks(code: $code, numDecks: $numDecks)
	}
  |}
];

module SetCallSizeM = [%graphql
  {|
	mutation setCallSize($code: String!, $callSize: Int!){
	  callSize: liarspoker_setCallSize(code: $code, callSize: $callSize)
	}
  |}
];

module CallHandM = [%graphql
  {|
	mutation callHand($code: String!, $player: String!, $call: [LiarsPokerCardInput!]){
	 liarspoker_call(code: $code, player: $player, call: $call)
	}
  |}
];

module CallBSM = [%graphql
  {|
	mutation callBS($code: String!, $player: String!){
	  liarspoker_call(code: $code, player: $player)
	}
  |}
];

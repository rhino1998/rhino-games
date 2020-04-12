type value = [
  | `WILD
  | `ZERO
  | `ONE
  | `TWO
  | `ACE
  | `EIGHT
  | `FIVE
  | `FOUR
  | `ELEVEN
  | `JACK
  | `KING
  | `NINE
  | `QUEEN
  | `SEVEN
  | `SIX
  | `TEN
  | `THREE
];

type suit = [ | `WILD | `CLUBS | `DIAMONDS | `HEARTS | `SPADES];

let string_of_suit = suit =>
  switch (suit) {
  | `WILD => {j|W|j}
  | `CLUBS => {j|C|j}
  | `DIAMONDS => {j|D|j}
  | `HEARTS => {j|H|j}
  | `SPADES => {j|S|j}
  };

let string_of_value = value =>
  switch (value) {
  | `WILD => {j|W|j}
  | `ZERO => {j|0|j}
  | `ONE => {j|1|j}
  | `TWO => {j|2|j}
  | `THREE => {j|3|j}
  | `FOUR => {j|4|j}
  | `FIVE => {j|5|j}
  | `SIX => {j|6|j}
  | `SEVEN => {j|7|j}
  | `EIGHT => {j|8|j}
  | `NINE => {j|9|j}
  | `TEN => {j|T|j}
  | `ELEVEN => {j|E|j}
  | `JACK => {j|J|j}
  | `QUEEN => {j|Q|j}
  | `KING => {j|K|j}
  | `ACE => {j|A|j}
  };

let string_of_card = card =>
  card##value->string_of_value ++ card##suit->string_of_suit;

module CardSVG = {
  [@bs.module] external back: string = "./cards/RB.svg";

  [@bs.module] external ww: string = "./cards/WW.svg";

  [@bs.module] external wc: string = "./cards/WC.svg";
  [@bs.module] external wd: string = "./cards/WD.svg";
  [@bs.module] external wh: string = "./cards/WH.svg";
  [@bs.module] external ws: string = "./cards/WS.svg";

  [@bs.module] external _0w: string = "./cards/0W.svg";
  [@bs.module] external _1w: string = "./cards/1W.svg";
  [@bs.module] external _2w: string = "./cards/2W.svg";
  [@bs.module] external _3w: string = "./cards/3W.svg";
  [@bs.module] external _4w: string = "./cards/4W.svg";
  [@bs.module] external _5w: string = "./cards/5W.svg";
  [@bs.module] external _6w: string = "./cards/6W.svg";
  [@bs.module] external _7w: string = "./cards/7W.svg";
  [@bs.module] external _8w: string = "./cards/8W.svg";
  [@bs.module] external _9w: string = "./cards/9W.svg";
  [@bs.module] external _tw: string = "./cards/TW.svg";
  [@bs.module] external _ew: string = "./cards/EW.svg";
  [@bs.module] external _jw: string = "./cards/JW.svg";
  [@bs.module] external _qw: string = "./cards/QW.svg";
  [@bs.module] external _kw: string = "./cards/KW.svg";
  [@bs.module] external _aw: string = "./cards/AW.svg";

  [@bs.module] external _0c: string = "./cards/0C.svg";
  [@bs.module] external _1c: string = "./cards/1C.svg";
  [@bs.module] external _2c: string = "./cards/2C.svg";
  [@bs.module] external _3c: string = "./cards/3C.svg";
  [@bs.module] external _4c: string = "./cards/4C.svg";
  [@bs.module] external _5c: string = "./cards/5C.svg";
  [@bs.module] external _6c: string = "./cards/6C.svg";
  [@bs.module] external _7c: string = "./cards/7C.svg";
  [@bs.module] external _8c: string = "./cards/8C.svg";
  [@bs.module] external _9c: string = "./cards/9C.svg";
  [@bs.module] external _tc: string = "./cards/TC.svg";
  [@bs.module] external _ec: string = "./cards/EC.svg";
  [@bs.module] external _jc: string = "./cards/JC.svg";
  [@bs.module] external _qc: string = "./cards/QC.svg";
  [@bs.module] external _kc: string = "./cards/KC.svg";
  [@bs.module] external _ac: string = "./cards/AC.svg";

  [@bs.module] external _0d: string = "./cards/0D.svg";
  [@bs.module] external _1d: string = "./cards/1D.svg";
  [@bs.module] external _2d: string = "./cards/2D.svg";
  [@bs.module] external _3d: string = "./cards/3D.svg";
  [@bs.module] external _4d: string = "./cards/4D.svg";
  [@bs.module] external _5d: string = "./cards/5D.svg";
  [@bs.module] external _6d: string = "./cards/6D.svg";
  [@bs.module] external _7d: string = "./cards/7D.svg";
  [@bs.module] external _8d: string = "./cards/8D.svg";
  [@bs.module] external _9d: string = "./cards/9D.svg";
  [@bs.module] external _td: string = "./cards/TD.svg";
  [@bs.module] external _ed: string = "./cards/ED.svg";
  [@bs.module] external _jd: string = "./cards/JD.svg";
  [@bs.module] external _qd: string = "./cards/QD.svg";
  [@bs.module] external _kd: string = "./cards/KD.svg";
  [@bs.module] external _ad: string = "./cards/AD.svg";

  [@bs.module] external _0h: string = "./cards/0H.svg";
  [@bs.module] external _1h: string = "./cards/1H.svg";
  [@bs.module] external _2h: string = "./cards/2H.svg";
  [@bs.module] external _3h: string = "./cards/3H.svg";
  [@bs.module] external _4h: string = "./cards/4H.svg";
  [@bs.module] external _5h: string = "./cards/5H.svg";
  [@bs.module] external _6h: string = "./cards/6H.svg";
  [@bs.module] external _7h: string = "./cards/7H.svg";
  [@bs.module] external _8h: string = "./cards/8H.svg";
  [@bs.module] external _9h: string = "./cards/9H.svg";
  [@bs.module] external _th: string = "./cards/TH.svg";
  [@bs.module] external _eh: string = "./cards/EH.svg";
  [@bs.module] external _jh: string = "./cards/JH.svg";
  [@bs.module] external _qh: string = "./cards/QH.svg";
  [@bs.module] external _kh: string = "./cards/KH.svg";
  [@bs.module] external _ah: string = "./cards/AH.svg";

  [@bs.module] external _0s: string = "./cards/0S.svg";
  [@bs.module] external _1s: string = "./cards/1S.svg";
  [@bs.module] external _2s: string = "./cards/2S.svg";
  [@bs.module] external _3s: string = "./cards/3S.svg";
  [@bs.module] external _4s: string = "./cards/4S.svg";
  [@bs.module] external _5s: string = "./cards/5S.svg";
  [@bs.module] external _6s: string = "./cards/6S.svg";
  [@bs.module] external _7s: string = "./cards/7S.svg";
  [@bs.module] external _8s: string = "./cards/8S.svg";
  [@bs.module] external _9s: string = "./cards/9S.svg";
  [@bs.module] external _ts: string = "./cards/TS.svg";
  [@bs.module] external _es: string = "./cards/ES.svg";
  [@bs.module] external _js: string = "./cards/JS.svg";
  [@bs.module] external _qs: string = "./cards/QS.svg";
  [@bs.module] external _ks: string = "./cards/KS.svg";
  [@bs.module] external _as: string = "./cards/AS.svg";

  let svg_of_card = card =>
	switch (card->string_of_card) {
	| "WW" => ww
	| "WC" => wc
	| "WD" => wd
	| "WH" => wh
	| "WS" => ws

	| "0W" => _0w
	| "1W" => _1w
	| "2W" => _2w
	| "3W" => _3w
	| "4W" => _4w
	| "5W" => _5w
	| "6W" => _6w
	| "7W" => _7w
	| "8W" => _8w
	| "9W" => _9w
	| "TW" => _tw
	| "EW" => _ew
	| "JW" => _jw
	| "QW" => _qw
	| "KW" => _kw
	| "AW" => _aw

	| "0C" => _0c
	| "1C" => _1c
	| "2C" => _2c
	| "3C" => _3c
	| "4C" => _4c
	| "5C" => _5c
	| "6C" => _6c
	| "7C" => _7c
	| "8C" => _8c
	| "9C" => _9c
	| "TC" => _tc
	| "EC" => _ec
	| "JC" => _jc
	| "QC" => _qc
	| "KC" => _kc
	| "AC" => _ac

	| "0D" => _0d
	| "1D" => _1d
	| "2D" => _2d
	| "3D" => _3d
	| "4D" => _4d
	| "5D" => _5d
	| "6D" => _6d
	| "7D" => _7d
	| "8D" => _8d
	| "9D" => _9d
	| "TD" => _td
	| "ED" => _ed
	| "JD" => _jd
	| "QD" => _qd
	| "KD" => _kd
	| "AD" => _ad

	| "0H" => _0h
	| "1H" => _1h
	| "2H" => _2h
	| "3H" => _3h
	| "4H" => _4h
	| "5H" => _5h
	| "6H" => _6h
	| "7H" => _7h
	| "8H" => _8h
	| "9H" => _9h
	| "TH" => _th
	| "EH" => _eh
	| "JH" => _jh
	| "QH" => _qh
	| "KH" => _kh
	| "AH" => _ah

	| "0S" => _0s
	| "1S" => _1s
	| "2S" => _2s
	| "3S" => _3s
	| "4S" => _4s
	| "5S" => _5s
	| "6S" => _6s
	| "7S" => _7s
	| "8S" => _8s
	| "9S" => _9s
	| "TS" => _ts
	| "ES" => _es
	| "JS" => _js
	| "QS" => _qs
	| "KS" => _ks
	| "AS" => _as

	| _ => back
	};

  [@react.component]
  let make = (~card=?) =>
	switch (card) {
	| Some(card) => <InlineSVG src=card->svg_of_card raw=true />
	| None => <InlineSVG src=back raw=true />
	};
};

module Selector = {
  [@react.component]
  let make = (~setCard, ~card) =>
	<div>
	  <div>
		{
		  let _ = ();
		  [|`WILD, `CLUBS, `DIAMONDS, `HEARTS, `SPADES|]
		  ->Belt.Array.map(suit =>
			  <RsuiteUi.Button
				className={
				  "selector-card "
				  ++ Css.(
					   style([
						 important(padding(zero)),
						 width(ch(4.0)),
						 important(borderRadius(pxFloat(3.5))),
					   ])
					 )
				}
				size=`xs
				key=suit->string_of_suit
				appearance={card##suit == suit ? `ghost : `default}
				onClick={
				  _ =>
					setCard({
					  "value": card##value,
					  "suit": suit,
					  "present": None,
					})
				}>
				<CardSVG
				  card={"suit": suit, "value": `WILD, "present": None}
				/>
			  </RsuiteUi.Button>
			)
		  ->React.array;
		}
	  </div>
	  <div>
		{
		  let _ = ();
		  [|
			`WILD,
			`ONE,
			`TWO,
			`THREE,
			`FOUR,
			`FIVE,
			`SIX,
			`SEVEN,
			`EIGHT,
			`NINE,
			`TEN,
			`ELEVEN,
			`JACK,
			`QUEEN,
			`KING,
			`ACE,
		  |]
		  ->Belt.Array.map(value =>
			  <RsuiteUi.Button
				key=value->string_of_value
				size=`xs
				className={
				  "selector-card "
				  ++ Css.(
					   style([important(padding(zero)), width(ch(4.0))])
					 )
				}
				appearance={card##value == value ? `ghost : `default}
				onClick={
				  _ =>
					setCard({
					  "suit": `WILD,
					  "value": value,
					  "present": None,
					})
				}>
				<CardSVG
				  card={"suit": `WILD, "value": value, "present": None}
				/>
			  </RsuiteUi.Button>
			)
		  ->React.array;
		}
	  </div>
	</div>;
};

module Card = {
  [@react.component]
  let make = (~card=?, ~onClick=?) => {
	let presentColor =
	  card
	  ->Belt.Option.mapWithDefault(Css.transparent, card =>
		  switch (card##present) {
		  | None => Css.transparent
		  | Some(true) => Css.rgba(0, 192, 0, 0.50)
		  | Some(false) => Css.rgba(192, 0, 0, 0.50)
		  }
		);
	<RsuiteUi.Button
	  ?onClick
	  size=`xs
	  className=Css.(
		style([
		  important(padding(zero)),
		  width(ch(6.0)),
		  before([
			contentRule(`text("")),
			display(block),
			position(absolute),
			left(zero),
			right(zero),
			bottom(zero),
			top(zero),
			unsafe("mixBlendMode", "darken"),
			backgroundColor(presentColor),
		  ]),
		])
	  )
	  appearance=`default>
	  <CardSVG ?card />
	</RsuiteUi.Button>;
  };
};

module SelectableCard = {
  [@bs.scope "document"] [@bs.val] external html: Dom.element = "html";

  [@react.component]
  let make = (~card, ~setCard, ~container=html) => {
	let speaker = <RsuiteUi.Popover> <Selector card setCard /> </RsuiteUi.Popover>;
	<RsuiteUi.Whisper
	  container trigger=`click placement=`top speaker preventOverflow=true>
	  <Card card />
	</RsuiteUi.Whisper>;
  };
};

module Group = {
  [@react.component]
  let make = (~cards) =>
	cards
	->Belt.Array.mapWithIndex((i, card) =>
		<Card key={string_of_int(i)} ?card />
	  )
	->React.array;
};

module Hand = {
  [@react.component]
  let make = (~topCards, ~bottomCards, ~reverse as reversed=false) =>
	<RsuiteUi.Panel>
	  <div
		className=Css.(
		  style([
			display(grid),
			gridTemplateRows([pct(33.0), pct(33.0), pct(33.0)]),
			justifyContent(center),
		  ])
		)>
		<div
		  className=Css.(
			style([
			  gridRowStart(1),
			  gridRowEnd(2),
			  justifySelf(center),
			  zIndex(reversed ? 1 : 0),
			])
		  )>
		  <Group cards=topCards />
		</div>
		<div
		  className=Css.(
			style([gridRowStart(2), gridRowEnd(3), justifySelf(center)])
		  )>
		  <Group cards=bottomCards />
		</div>
	  </div>
	</RsuiteUi.Panel>;
};

module CallSelector = {
  [@react.component]
  let make = (~call, ~setCall) => {
	let setCard = (i, newCard) =>
	  setCall(_ =>
		call->Belt.Array.mapWithIndex((j, card) => i == j ? newCard : card)
	  );

	let _ = ();
	call
	->Belt.Array.mapWithIndex((i, card) =>
		<SelectableCard
		  key={string_of_int(i)}
		  setCard={card => setCard(i, card)}
		  card
		/>
	  )
	->React.array;
  };
};

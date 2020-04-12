module Card = LiarsPoker__Card;


module Circle = {
  open LiarsPokerTheme;

  [@react.component]
  let make = (~className=?, ~center=?, ~children) => {
	let numChildren = children->React.Children.count;
	<div
	  className=Css.(
		merge([
		  style([
			position(relative),
			overflow(hidden),
			height(pct(100.0)),
			width(pct(100.0)),
			display(grid),
			gridTemplateColumns([fr(1.0)]),
			gridTemplateRows([fr(1.0)]),
			margin(zero),
			unsafe("placeItems", "center"),
		  ]),
		  className->Belt.Option.getWithDefault(style([])),
		])
	  )>
	  <div className=Table.tableStyle>
		(
		  (children->React.Children.toArray: array(React.element))
		  ->Belt.Array.mapWithIndex((i, child) => {
			  let angleStep = 1.0 /. float_of_int(numChildren);
			  <div
				key={string_of_int(i)}
				className={Table.elementContainerStyle(i, angleStep)}>
				<div className=Css.(style([flexGrow(1.0)])) />
				<div className=Table.elementWrapperStyle> child </div>
			  </div>;
			}):
			array(React.element)
		)
		->React.array
	  </div>
	  <div className=Table.centerContainerStyle>
		{
		  let _ = ();
		  center->Belt.Option.mapWithDefault(React.null, center => center);
		}
	  </div>
	</div>;
  };
};

let element_of_player = (~player, ~shift_factor, ~scale_factor) =>
  switch (player) {
  | None => <div />
  | Some(player) =>
	<div
	  className=Css.(
		style([
		  transforms([
			translateY(pct(shift_factor)),
			scale(scale_factor, scale_factor),
		  ]),
		])
	  )>
	  <p
		className=Css.(
		  style([
			position(relative),
			padding(px(4)),
			minWidth(pct(20.0)),
			textAlign(`center),
			borderRadius(px(8)),
			transform(translateY(pct(50.0))),
			backgroundColor(hex("232323")),
		  ])
		)>
		{
		  if (player##current) {
			<RsuiteUi.Icon
			  icon="star"
			  style={ReactDOMRe.Style.make(~color="#FFDF00", ())}
			/>;
		  } else {
			React.null;
		  }
		}
		player##name->React.string
	  </p>
	  <Card.Hand
		bottomCards=player##privateCards
		topCards=player##publicCards
	  />
	</div>
  };

[@react.component]
let make = (~center=?, ~round) => {
  let totalCards =
	round##others
	->Belt.Array.map(player => player##totalCards)
	->Belt.Array.reduce(0, (+))
	+ round##player
	  ->Belt.Option.mapWithDefault(0, player => player##totalCards);
  let numPlayers =
	round##others->Belt.Array.length
	+ round##player->Belt.Option.mapWithDefault(0, _ => 1);
  let scale_factor =
	min(1.0 -. (1.0 /. (4.0 +. numPlayers->float_of_int)) ** 2.0, 1.0);
  let shift_factor =
	(-40.0)
	+. numPlayers->float_of_int
	** 0.25
	*. 10.0
	+. (totalCards / numPlayers)->float_of_int
	*. 5.0;
  <Circle ?center>
	{
	  let _ = ();

	  Belt.Array.concat(
		[|round##player|],
		round##others->Belt.Array.map(player => player->Some),
	  )
	  ->Belt.Array.map(player =>
		  element_of_player(
			~player,
			~shift_factor,
			~scale_factor,
		  )
		)
	  ->React.array;
	}
  </Circle>;
};

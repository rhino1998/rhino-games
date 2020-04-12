[@react.component]
let make = (~className=?, ~children as cols) =>
  <div
	className=Css.(
	  merge([
		style([
		  display(grid),
		  gridTemplateRows([
			`repeat((`num(cols |> React.Children.count), fr(1.))),
		  ]),
		]),
		className->Belt.Option.getWithDefault(style([])),
	  ])
	)>
	cols
  </div>;

[@react.component]
let make = (~active, ~className=?, ~children) => {
  let isActive = active;
  <div
    className=Css.(
      merge([
        style([
          display(isActive ? block : none),
		  zIndex(1),
          position(fixed),
          left(zero),
          right(zero),
          width(pct(100.0)),
          height(pct(100.0)),
        ]),
        className->Belt.Option.getWithDefault(style([])),
      ])
    )>
    children
  </div>;
};

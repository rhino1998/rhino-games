[@react.component]
let make = (~x, ~y, ~className=?, ~children) =>
  <div
    className=Css.(
      merge([
        style([
          display(`grid),
          gridTemplateColumns([`repeat((`num(x), fr(1.)))]),
          gridTemplateRows([`repeat((`num(y), fr(1.)))]),
        ]),
        className->Belt.Option.getWithDefault(style([])),
      ])
    )>
    children
  </div>;

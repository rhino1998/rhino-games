module Menu = {
  [@react.component]
  let make = (~items) =>
    items
    ->Belt.Array.mapWithIndex((index, item) =>
        <button
          onClick={_ => ReasonReactRouter.push("/" ++ item ++ "/")}
          key=index->string_of_int>
          {ReasonReact.string(item)}
        </button>
      )
    |> ReasonReact.array;
};

[@react.component]
let make = () =>
  <div
    className=Css.(
      style([padding2(~h=pct(10.0), ~v=pct(0.0)), marginTop(pct(5.0))])
    )>
    <h1> {React.string("Rhino Games")} </h1>
    <Columns> <Menu items=[|"codenames"|] /> </Columns>
  </div>;

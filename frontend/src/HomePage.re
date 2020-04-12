module Menu = {
  [@react.component]
  let make = (~items) =>
    items
    ->Belt.Array.mapWithIndex((index, item) =>
        <RsuiteUi.Button
          onClick={_ => ReasonReactRouter.push("/" ++ item ++ "/")}
          key=index->string_of_int>
          {ReasonReact.string(item)}
        </RsuiteUi.Button>
      )
    |> ReasonReact.array;
};

[@react.component]
let make = () => <Page> <Menu items=[|"codenames", "liarspoker"|] /> </Page>;

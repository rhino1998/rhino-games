open Util;

type tile = {
  kind: [ | `UNKNOWN | `DEATH | `NEUTRAL | `RED | `BLUE],
  word: string,
  revealed: bool,
};

type board = {tiles: array(array(tile))};

type game = {board: option(board)};

module NewGameM = [%graphql
  {|
    mutation newGame($category: String!, $code: String!, $x: Int!, $y:Int!){
      codenames {
        newGame(category: $category, code: $code, x:$x, y:$y)
      }
    }
  |}
];

module GameQ = [%graphql
  {|
    query game($category: String!, $code: String!){
      game: codenames @bsRecord {
        board(category: $category, code: $code) @bsRecord {
          tiles @bsRecord {
            word
            kind
            revealed
          }
        }
      }
    }
  |}
];

module CategoriesQ = [%graphql
  {|
    query categories @bsRecord {
      codenames {
        categories
      }
    }
  |}
];

module HitTileM = [%graphql
  {|
    mutation hitTile($category: String!, $code: String!, $x:Int!, $y:Int!){
      codenames {
        hitTile(category: $category, code: $code,x: $x, y: $y)
      }
    }
  |}
];

module Board = {
  let kindColor = kind =>
    Css.(
      switch (kind) {
      | `UNKNOWN => white
      | `DEATH => rgba(0, 0, 0, 0.3)
      | `RED => rgba(255, 0, 0, 0.3)
      | `BLUE => rgba(0, 0, 255, 0.3)
      | `NEUTRAL => rgba(240, 200, 0, 0.3)
      }
    );

  [@react.component]
  let make = (~master, ~reset, ~refetch, ~category, ~code, ~hitTile, ~board: board) => {
    let x = board.tiles->Belt.Array.length;
    let y = board.tiles->(Belt.Array.getExn(0))->Belt.Array.length;
    React.useEffect0(()=>{
        let intervalId = Js.Global.setInterval(refetch, 500);
        Some(()=>Js.Global.clearInterval(intervalId))
    });
    <div className=Css.(style([height(pct(100.0))]))>
      <Columns className=Css.(style([height(pct(5.0))]))>
        <button onClick={_ => ReasonReactRouter.push("/")}>
          {ReasonReact.string("Home")}
        </button>
        <button onClick={_ => reset()->ignore}>
          {ReasonReact.string("NEW")}
        </button>
        <button
          onClick={
            _ =>
              master ?
                ReasonReact.Router.push("?") :
                ReasonReact.Router.push("?master")
          }>
          {ReasonReact.string("MASTER")}
        </button>
        <span>
          {ReasonReact.string("RED: ")}
          {
            ReasonReact.string(
              string_of_int(
                board.tiles
                ->Matrix.flat_reduce(0, (acc, tile) =>
                    switch (tile) {
                    | {kind: `RED, revealed: false} => acc + 1
                    | _ => acc
                    }
                  ),
              ),
            )
          }
        </span>
        <span>
          {ReasonReact.string("BLUE: ")}
          {
            ReasonReact.string(
              string_of_int(
                board.tiles
                ->Matrix.flat_reduce(0, (acc, tile) =>
                    switch (tile) {
                    | {kind: `BLUE, revealed: false} => acc + 1
                    | _ => acc
                    }
                  ),
              ),
            )
          }
        </span>
      </Columns>
      <Grid x y className=Css.(style([height(pct(95.0))]))>
        Belt.Array.(
          board.tiles
          ->(reduce([||], (all, row) => concat(all, row)))
          ->(
              mapWithIndex((i, tile) => {
                let yi = i mod x;
                let xi = i / x mod y;
                <div
                  key={tile.word ++ string_of_int(i)}
                  className=Css.(
                    style([
                      textAlign(center),
                      backgroundColor(
                        tile.revealed || master ?
                          kindColor(tile.kind) : kindColor(`UNKNOWN),
                      ),
                      borderColor(black),
                      borderWidth(px(2)),
                      borderStyle(solid),
                    ])
                  )
                  onClick={_ => hitTile(~x=xi, ~y=yi)}>
                  <p
                    className=Css.(
                      style([
                        margin(zero),
                        position(relative),
                        top(pct(50.0)),
                        left(pct(50.0)),
                        transform(translate(pct(-50.0), pct(-50.0))),
                      ])
                    )>
                    {React.string(tile.word)}
                  </p>
                </div>;
              })
            )
        )
        ->React.array
      </Grid>
    </div>;
  };
};

module Game = {
  [@react.component]
  let make = (~category, ~code, ~x, ~y, ~master) => {
    let gameQuery = GameQ.make(~category, ~code, ());
    let (simple, full) =
      ApolloHooks.useQuery(GameQ.definition, ~variables=gameQuery##variables);
    let (newGameMutation, _simple, _full) =
      ApolloHooks.useMutation(
        NewGameM.definition,
        ~refetchQueries=_ => [|gameQuery->ApolloHooks.toQueryObj|],
        ~variables=NewGameM.makeVariables(~category, ~code, ~x, ~y, ()),
      );
    let (hitTileMutation, _simple, _full) =
      ApolloHooks.useMutation(HitTileM.definition, ~refetchQueries=_ =>
        [|gameQuery->ApolloHooks.toQueryObj|]
      );

    let reset = () => newGameMutation()->ignore;

    let refetch = () => full.refetch()->ignore;

    let hitTile = (~x, ~y) =>
      hitTileMutation(
        ~variables=HitTileM.makeVariables(~category, ~code, ~x, ~y, ()),
        (),
      )
      ->ignore;

    switch (simple) {
    | Loading => React.string("Loading")
    | Error(error) =>
      Js.log(error);
      React.string("error");
    | Data(data) =>
      switch (data##game.board) {
      | None => <OnLoad> reset </OnLoad>
      | Some(board) => <Board board category code reset refetch hitTile master />
      }
    };
  };
};

module Menu = {
  [@react.component]
  let make = (~items) =>
    <Columns>
      {
        items
        ->Belt.Array.mapWithIndex((index, item) =>
            <button
              onClick={_ => ReasonReactRouter.push(item ++ "/")}
              key=index->string_of_int>
              {ReasonReact.string(item)}
            </button>
          )
        |> ReasonReact.array
      }
    </Columns>;
};

[@react.component]
let make = (~url: ReasonReactRouter.url) => {
  let (simple, _full) =
    ApolloHooks.useQuery(
      CategoriesQ.definition,
      ~variables=CategoriesQ.makeVariables(),
    );
  switch (url.path) {
  | [] =>
    switch (simple) {
    | Loading => ReasonReact.string("LOADING")
    | Error(_) => ReasonReact.string("ERR")
    | Data(response) =>
      <div
        className=Css.(
          style([
            padding2(~h=pct(10.0), ~v=pct(0.0)),
            marginTop(pct(5.0)),
          ])
        )>
        <h1> {React.string("CodeNames WordList Selection")} </h1>
        <Menu items=response##codenames##categories />
      </div>
    }
  | [_category] =>
    <OnLoad>
      (
        () => {
          let code = Util.gen_code(8);
          ReasonReact.Router.push(code ++ "/");
        }
      )
    </OnLoad>
  | [category, code, ..._] =>
    <div className=Css.(style([margin2(~h=pct(0.0), ~v=pct(0.0))]))>
      <Game category code x=9 y=9 master={url.search == "master"} />
    </div>
  };
};

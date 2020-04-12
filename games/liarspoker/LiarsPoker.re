open Util;

module Table = LiarsPoker__Table;

module Types = LiarsPoker__Types;

module GQL = LiarsPoker__GQL;

module Card = LiarsPoker__Card;

module RoundSummary = {
  module Grid = RsuiteUi.Grid;
  module Col = RsuiteUi.Col;
  module Panel = RsuiteUi.Panel;
  module Form = RsuiteUi.Form;
  module FormGroup = RsuiteUi.FormGroup;
  module Button = RsuiteUi.Button;
  module Avatar = RsuiteUi.Avatar;
  module Icon = RsuiteUi.Icon;
  module Modal = RsuiteUi.Modal;
  module Divider = RsuiteUi.Divider;

  [@react.component]
  let make = (~summary, ~player=?, ~code) => {
    let ready =
      player
      ->Belt.Option.mapWithDefault(
          () => (),
          player => {
            let (ready, _, _) =
              ApolloHooks.useMutation(
                GQL.ReadyM.definition,
                ~variables=GQL.ReadyM.makeVariables(~code, ~player, ()),
              );
            x => x->ready->ignore;
          },
        );
    let players =
      summary##player
      ->Belt.Option.mapWithDefault([||], player => [|player|])
      ->Belt.Array.concat(summary##others);

    <>
      <Modal
        full=true
        show=true
        overflow=true
        dialogClassName=Css.(
          style([
            children([
              important(backgroundColor(rgba(25, 25, 25, 0.5))),
              width(pct(100.0)),
            ]),
          ])
        )>
        <Modal.Body
          style={
            ReactDOMRe.Style.make(
              ~overflow="hidden",
              ~marginTop="0",
              ~paddingBottom="0",
              (),
            )
          }>
          <div className=Css.(style([height(pct(100.0))])) />
          <div
            className=Css.(
              style([
                position(absolute),
                top(zero),
                bottom(zero),
                left(zero),
                right(zero),
              ])
            )>
            <Col sm=12 xs=12>
              <p> "All Calls"->React.string </p>
              <div
                className=Css.(
                  style([
                    overflowY(auto),
                    unsafe("height", "calc(100% - 2em)"),
                  ])
                )>
                {
                  let _ = ();
                  summary##calls
                  ->Belt.Array.mapWithIndex((i, call) => {
                      let exists =
                        call##call
                        ->Belt.Array.every(card =>
                            card
                            ->Belt.Option.mapWithDefault(false, card =>
                                card##present
                                ->Belt.Option.getWithDefault(false)
                              )
                          );
                      <div key=i->string_of_int>
                        <p> call##player##name->React.string </p>
                        <Card.Group cards=call##call />
                        <Avatar
                          size=`xs
                          className=Css.(
                            style([
                              marginLeft(ch(2.0)),
                              important(
                                backgroundColor(exists ? green : red),
                              ),
                            ])
                          )>
                          <Icon icon={exists ? "check" : "close"} />
                        </Avatar>
                      </div>;
                    })
                  ->React.array;
                }
              </div>
            </Col>
            <Col sm=12 xs=12>
              <p> "All Cards"->React.string </p>
              <div
                className=Css.(
                  style([
                    overflowY(auto),
                    unsafe("height", "calc(100% - 2em)"),
                  ])
                )>
                {
                  let _ = ();
                  players
                  ->Belt.Array.map(player =>
                      <div key=player##name>
                        <p> player##name->React.string </p>
                        <div>
                          <Card.Group
                            cards=player##publicCards
                          />
                          <Card.Group
                            cards=player##privateCards
                          />
                        </div>
                      </div>
                    )
                  ->React.array;
                }
              </div>
            </Col>
          </div>
        </Modal.Body>
        <Modal.Footer>
          <Button onClick={_ => ready()->ignore}>
            {ReasonReact.string("Ready")}
          </Button>
        </Modal.Footer>
      </Modal>
      <div
        className=Css.(
          style([
            width(pct(100.0)),
            height(pct(100.0)),
            backgroundColor(hex("232323")),
          ])
        )>
        <div
          className=Css.(
            style([
              width(vmin(100.0)),
              height(vmin(100.0)),
              margin2(~v=zero, ~h=auto),
            ])
          )>
          <Table round=summary />
        </div>
      </div>
    </>;
  };
};

module Round = {
  module Grid = RsuiteUi.Grid;
  module Col = RsuiteUi.Col;
  module Panel = RsuiteUi.Panel;
  module Form = RsuiteUi.Form;
  module FormGroup = RsuiteUi.FormGroup;
  module ControlLabel = RsuiteUi.ControlLabel;
  module Input = RsuiteUi.Input;
  module InputGroup = RsuiteUi.InputGroup;
  module Button = RsuiteUi.Button;
  module ButtonGroup = RsuiteUi.ButtonGroup;
  module Icon = RsuiteUi.Icon;
  module Alert = RsuiteUi.Alert;
  module Drawer = RsuiteUi.Drawer;


  [@react.component]
  let make = (~code, ~round) => {
    let (callHand, _simple, _full) =
      ApolloHooks.useMutation(GQL.CallHandM.definition);
    let (callBS, _simple, _full) =
      ApolloHooks.useMutation(GQL.CallBSM.definition);
    let (call, setCall) =
      React.useState(() =>
        Belt.Array.make(
          round##callSize,
          {"suit": `WILD, "value": `WILD, "present": None},
        )
      );

    let (showCalls, setShowCalls) = React.useState(() => false);

    let isFirstTurn = round##calls->Belt.Array.length == 0;
    let activeCall: array(option(Types.Card.t)) =
      (round##calls: array(Types.PlayerCall.t))
      ->Belt.Array.get(round##calls->Belt.Array.length - 1)
      ->Belt.Option.mapWithDefault([||], playerCall => playerCall##call);
    React.useEffect1(
      () => {
        if (isFirstTurn) {
          setCall(_ =>
            Belt.Array.make(
              round##callSize,
              {"suit": `WILD, "value": `WILD, "present": None},
            )
          );
        } else {
          setCall(_ =>
            Belt.Array.makeBy(round##callSize, i =>
              activeCall
              ->Belt.Array.get(i)
              ->Belt.Option.getWithDefault(None)
              ->Belt.Option.getWithDefault({
                  "suit": `WILD,
                  "value": `WILD,
                  "present": None,
                })
            )
          );
        };
        None;
      },
      [|round##calls->Belt.Array.get(round##calls->Belt.Array.length - 1)|],
    );
    let numPlayers =
      round##others->Belt.Array.length
      + round##player->Belt.Option.mapWithDefault(0, _ => 1);
    let scaleFactor =
      min(1.0 -. (1.0 /. (4.0 +. numPlayers->float_of_int)) ** 2.0, 1.0);
    let isCurrentPlayer =
      switch (round##player) {
      | Some(player) => player##current
      | None => false
      };

    <>
      <div
        className=Css.(
          style([
            width(pct(100.0)),
            height(pct(100.0)),
            backgroundColor(hex("232323")),
          ])
        )>
        <div
          className=Css.(
            style([
              width(vmin(100.0)),
              height(vmin(100.0)),
              margin2(~v=zero, ~h=auto),
            ])
          )>
          <Table
            round
            center={
                     if (isCurrentPlayer || !isFirstTurn) {
                       <Panel
                         bordered=true
                         bodyFill=true
                         className=Css.(
                           style([
                             padding(px(8)),
                             transform(scale(scaleFactor, scaleFactor)),
                             backgroundColor(hex("232323")),
                           ])
                         )>
                         <div
                           className=Css.(
                             style([
                               display(grid),
                               gridTemplateColumns(
                                 isCurrentPlayer ? [auto, auto] : [auto],
                               ),
                               gridTemplateRows([auto, auto]),
                               color(white),
                             ])
                           )>
                           {
                             if (isCurrentPlayer) {
                               <>
                                 <div>
                                   <p> "New Call"->React.string </p>
                                   <Card.CallSelector call setCall />
                                 </div>
                                 <ButtonGroup
                                   vertical=true
                                   className=Css.(
                                     style([
                                       alignSelf(`end_),
                                       borderRadius(px(2)),
                                     ])
                                   )>
                                   <Button
                                     block=true
                                     className=Css.(
                                       style([
                                         width(pct(100.0)),
                                         height(pct(50.0)),
                                       ])
                                     )
                                     color=`green
                                     onClick={
                                       _ =>
                                         callHand(
                                           ~variables=
                                             GQL.CallHandM.makeVariables(
                                               ~code,
                                               ~player=
                                                 round##currentPlayer##name,
                                               ~call,
                                               (),
                                             ),
                                           (),
                                         )
                                         ->Promise.Js.fromBsPromise
                                         ->Promise.Js.catch(_err => {
                                             Alert.error(
                                               ~content="Call too Low",
                                               (),
                                             );
                                             Promise.Js.rejected();
                                           })
                                         ->ignore
                                     }>
                                     <Icon icon="check" />
                                   </Button>
                                   <Button
                                     disabled=isFirstTurn
                                     block=true
                                     className=Css.(
                                       style([
                                         width(pct(100.0)),
                                         height(pct(50.0)),
                                       ])
                                     )
                                     color=`red
                                     onClick={
                                       _ =>
                                         callBS(
                                           ~variables=
                                             GQL.CallBSM.makeVariables(
                                               ~code,
                                               ~player=
                                                 round##currentPlayer##name,
                                               (),
                                             ),
                                           (),
                                         )
                                         ->ignore
                                     }>
                                     <Icon icon="close" />
                                   </Button>
                                 </ButtonGroup>
                               </>;
                             } else {
                               React.null;
                             }
                           }
                           {
                             if (!isFirstTurn) {
                               <div>
                                 <p> "Current Call"->React.string </p>
                                 <Card.Group cards=activeCall />
                               </div>;
                             } else {
                               React.null;
                             }
                           }
                         </div>
                       </Panel>;
                     } else {
                       React.null;
                     }
                   }
          />
        </div>
      </div>
      <Button
        size=`xs
        onClick={_ => setShowCalls(_ => true)}
        className=Css.(
          style([
            height(pct(100.0)),
            important(position(absolute)),
            right(zero),
            top(zero),
          ])
        )>
        "<"->React.string
      </Button>
      <Drawer show=showCalls size=`xs>
        <div
          className=Css.(
            style([
              display(grid),
              gridTemplateColumns([auto, fr(1.0)]),
              height(pct(100.0)),
            ])
          )>
          <Button
            size=`xs
            onClick={_ => setShowCalls(_ => false)}
            className=Css.(style([height(pct(100.0))]))>
            ">"->React.string
          </Button>
          <div
            className=Css.(style([height(pct(100.0)), overflowY(auto)]))>
            {
              let _ = ();
              round##calls
              ->Belt.Array.mapWithIndex((i, call) => {
                  <div key=i->string_of_int>
                    <p> call##player##name->React.string </p>
                    <Card.Group cards=call##call />
                  </div>;
                })
              ->React.array;
            }
          </div>
        </div>
      </Drawer>
    </>;
  };
};
module Lobby = {
  open RsuiteUi;

  [@react.component]
  let make = (~code, ~lobby, ~player=?) => {
    let ready =
      player
      ->Belt.Option.mapWithDefault(
          () => (),
          player => {
            let (ready, _, _) =
              ApolloHooks.useMutation(
                GQL.ReadyM.definition,
                ~variables=GQL.ReadyM.makeVariables(~code, ~player, ()),
              );
            x => x->ready->ignore;
          },
        );

    let (setNumCards, _simple, _full) =
      ApolloHooks.useMutation(GQL.SetNumCardsM.definition);

    let (setNumDecks, _simple, _full) =
      ApolloHooks.useMutation(GQL.SetNumDecksM.definition);

    let (setCallSize, _simple, _full) =
      ApolloHooks.useMutation(GQL.SetCallSizeM.definition);

    let (numCardsLocal, setNumCardsLocal) =
      React.useState(() => lobby##numCards);
    let (numDecksLocal, setNumDecksLocal) =
      React.useState(() => lobby##numDecks);
    let (callSizeLocal, setCallSizeLocal) =
      React.useState(() => lobby##callSize);
    React.useEffect1(
      () => {
        setNumCardsLocal(_ => lobby##numCards);
        setNumDecksLocal(_ => lobby##numDecks);
        setCallSizeLocal(_ => lobby##callSize);
        None;
      },
      [|lobby|],
    );

    <Grid fluid=true>
      <Col lg=4 />
      <Col xs=24 lg=16>
        <Panel bordered=true header={React.string("Lobby")}>
          <Form fluid=true>
            <FormGroup>
              <ControlLabel>
                {React.string("Number of cards per player")}
              </ControlLabel>
              <InputGroup>
                <InputNumber
                  min=1
                  value=numCardsLocal
                  onChange={
                    (numCards, _) => {
                      setNumCardsLocal(_ => numCards);
                      setNumCards(
                        ~variables=
                          GQL.SetNumCardsM.makeVariables(~code, ~numCards, ()),
                        (),
                      )
                      ->ignore;
                    }
                  }
                />
                <InputGroup.Button
                  onClick={
                    _ =>
                      setNumCards(
                        ~variables=
                          GQL.SetNumCardsM.makeVariables(
                            ~code,
                            ~numCards=numCardsLocal,
                            (),
                          ),
                        (),
                      )
                      ->ignore
                  }>
                  {ReasonReact.string("Update")}
                </InputGroup.Button>
              </InputGroup>
            </FormGroup>
            <FormGroup>
              <ControlLabel>
                {React.string("Number of Decks:")}
              </ControlLabel>
              <InputGroup>
                <InputNumber
                  min=1
                  value=numDecksLocal
                  onChange={
                    (numDecks, _) => {
                      setNumDecksLocal(_ => numDecks);
                      setNumDecks(
                        ~variables=
                          GQL.SetNumDecksM.makeVariables(~code, ~numDecks, ()),
                        (),
                      )
                      ->ignore;
                    }
                  }
                />
                <InputGroup.Button
                  onClick={
                    _ =>
                      setNumDecks(
                        ~variables=
                          GQL.SetNumDecksM.makeVariables(
                            ~code,
                            ~numDecks=numDecksLocal,
                            (),
                          ),
                        (),
                      )
                      ->ignore
                  }>
                  {ReasonReact.string("Update")}
                </InputGroup.Button>
              </InputGroup>
            </FormGroup>
            <FormGroup>
              <ControlLabel>
                {React.string("Number of cards per call")}
              </ControlLabel>
              <InputGroup>
                <InputNumber
                  min=1
                  value=callSizeLocal
                  onChange={
                    (callSize, _) => {
                      setCallSizeLocal(_ => callSize);
                      setCallSize(
                        ~variables=
                          GQL.SetCallSizeM.makeVariables(~code, ~callSize, ()),
                        (),
                      )
                      ->ignore;
                    }
                  }
                />
                <InputGroup.Button
                  onClick={
                    _ =>
                      setCallSize(
                        ~variables=
                          GQL.SetCallSizeM.makeVariables(
                            ~code,
                            ~callSize=callSizeLocal,
                            (),
                          ),
                        (),
                      )
                      ->ignore
                  }>
                  {ReasonReact.string("Update")}
                </InputGroup.Button>
              </InputGroup>
            </FormGroup>
            <FormGroup>
              <List>
                {
                  let _ = 5;
                  lobby##players
                  ->Belt.Array.map(p =>
                      <List.Item key=p##name>
                        <FlexboxGrid>
                          <FlexboxGrid.Item colspan=23>
                            <span
                              className=Css.(
                                style([
                                  fontWeight(
                                    player
                                    ->Belt.Option.mapWithDefault(
                                        normal, player =>
                                        player == p##name ? bold : normal
                                      ),
                                  ),
                                ])
                              )>
                              {React.string(p##name)}
                            </span>
                          </FlexboxGrid.Item>
                          <FlexboxGrid.Item>
                            <Avatar
                              size=`xs
                              style={
                                ReactDOMRe.Style.make(
                                  ~backgroundColor=p##ready ? "green" : "red",
                                  (),
                                )
                              }>
                              <Icon icon={p##ready ? "check" : "close"} />
                            </Avatar>
                          </FlexboxGrid.Item>
                        </FlexboxGrid>
                      </List.Item>
                    )
                  ->React.array;
                }
              </List>
            </FormGroup>
            <FormGroup>
              {
                switch (player) {
                | None => <div />
                | Some(_player) =>
                  <Button onClick=(_ => ready()->ignore)>
                    {ReasonReact.string("Ready")}
                  </Button>
                }
              }
            </FormGroup>
          </Form>
        </Panel>
      </Col>
      <Col lg=4 />
    </Grid>;
  };
};

module Switch = {
  [@react.component]
  let make = (~code, ~player=?) => {
    let (simple, _full) =
      ApolloHooks.useSubscription(
        GQL.StateS.definition,
        ~variables=GQL.StateS.makeVariables(~code, ~player?, ()),
      );
    ();

    switch (simple) {
    | NoData => ReasonReact.string("NODATA???")
    | Loading => ReasonReact.string("LOADING")
    | Error(error) =>
      Js.log(error);
      ReasonReact.string("ERR");
    | Data(response) =>
      switch (response##state) {
      | `LiarsPokerRound(round) => <Round code round />
      | `LiarsPokerLobby(lobby) => <Lobby code lobby ?player />
      | `LiarsPokerRoundSummary(summary) =>
        <RoundSummary code ?player summary />
      }
    };
  };
};

module JoinPage = {
  module Grid = RsuiteUi.Grid;
  module Col = RsuiteUi.Col;
  module Panel = RsuiteUi.Panel;
  module Form = RsuiteUi.Form;
  module FormGroup = RsuiteUi.FormGroup;
  module ControlLabel = RsuiteUi.ControlLabel;
  module Input = RsuiteUi.Input;
  module Button = RsuiteUi.Button;

  [@react.component]
  let make = () => {
    let (code, setCode) = React.useState(() => gen_code(8));
    let (player, setPlayer) = React.useState(() => "");
    <Grid fluid=true>
      <Col lg=4 />
      <Col xs=24 lg=16>
        <Panel bordered=true>
          <Form fluid=true>
            <FormGroup>
              <ControlLabel> {React.string("Game Code:")} </ControlLabel>
              <Input value=code onChange={(code, _) => setCode(_ => code)} />
            </FormGroup>
            <FormGroup>
              <ControlLabel> {React.string("Name:")} </ControlLabel>
              <Input
                value=player
                onChange={(player, _) => setPlayer(_ => player)}
              />
            </FormGroup>
            <FormGroup>
              <Button
                onClick={
                  _ => ReasonReact.Router.push(code ++ "?player=" ++ player)
                }>
                {ReasonReact.string("Join")}
              </Button>
            </FormGroup>
          </Form>
        </Panel>
      </Col>
      <Col lg=4 />
    </Grid>;
  };
};

[@react.component]
let make = (~url: ReasonReactRouter.url) =>
  switch (url.path) {
  | [code] =>
    open Webapi.Url;
    let params = URLSearchParams.make(url.search);
    let player = params |> URLSearchParams.get("player");
    <Switch code ?player />;
  | _ => <JoinPage />
  };

Css.(global("body", [margin(px(0))]));

Css.(global("h4", [margin(px(0))]));

Css.(global("h3", [margin(px(0))]));

module Style = {
  open Css;
  open Theme;
  let frame =
    style([
      height(vh(100.0)),
      width(vw(100.0)),
      display(`grid),
      gridTemplateColumns([`px(200), `auto]),
      gridTemplateRows([`auto]),
    ]);
  let bodyFrame =
    style([
      height(pct(100.0)),
      width(pct(100.0)),
      display(`grid),
      gridTemplateColumns([`auto]),
      gridTemplateRows([`px(40), `auto]),
    ]);
  let pageFrame =
    style([
      overflow(`scroll),
      height(Calc.(-)(vh(100.0), px(40))),
      backgroundColor(HomePage.backgroundColor),
    ]);
};

module Router = {
  [@react.component]
  let make = () => {
    let url = ReasonReactRouter.useUrl();
    switch (url.path) {
    | ["codenames", ...rest] => <CodeNames url={...url, path: rest} />
    | _ => <HomePage />
    };
  };
};

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=Client.instance>
    <ApolloHooks.Provider client=Client.instance>
      <Router />
    </ApolloHooks.Provider>
  </ReasonApollo.Provider>,
  "index",
);

/* [%bs.raw {|require('rsuite/lib/styles/index.less')|}]; */
[%bs.raw {|require('rsuite/lib/styles/themes/dark/index.less')|}];
[%bs.raw {|require('rsuite/lib/styles/themes/dark/index.less')|}];

[%bs.raw {|require('./Index.less')|}];

Css.(
  global("html", [margin(px(0)), width(vw(100.0)), height(vh(100.0))])
);

{
  open Css;
  global(
    "*::-webkit-scrollbar-track",
    [
      unsafe("boxShadow", "inset 0 0 6px rgba(0,0,0,0.3)"),
      unsafe("borderRadius", "10px"),
      backgroundColor(rgba(0, 0, 0, 0.2)),
    ],
  );
  global(
    "*::-webkit-scrollbar",
    [width(px(8)), backgroundColor(rgba(0, 0, 0, 0.2))],
  );
  global(
    "*::-webkit-scrollbar-thumb",
    [
      unsafe("boxShadow", "inset 0 0 6px rgba(0,0,0,0.3)"),
      unsafe("borderRadius", "10px"),
      backgroundColor(hex("232323")),
    ],
  );
};

module Router = {
  [@react.component]
  let make = () => {
    let url = ReasonReactRouter.useUrl();
    switch (url.path) {
    | ["codenames", ...rest] => <CodeNames url={...url, path: rest} />
    | ["liarspoker", ...rest] => <LiarsPoker url={...url, path: rest} />
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

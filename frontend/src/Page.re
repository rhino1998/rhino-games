[@react.component]
let make = (~children) =>
  <RsuiteUi.Container>
    <RsuiteUi.Header>
      <h1> {React.string("Rhino Games")} </h1>
    </RsuiteUi.Header>
    <RsuiteUi.Content>
      <RsuiteUi.Grid fluid=true>
        <RsuiteUi.Col lg=4 />
        <RsuiteUi.Col xs=24 lg=16>
          <RsuiteUi.Panel bordered=true> children </RsuiteUi.Panel>
        </RsuiteUi.Col>
        <RsuiteUi.Col lg=4 />
      </RsuiteUi.Grid>
    </RsuiteUi.Content>
  </RsuiteUi.Container>;

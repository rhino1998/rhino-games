/* let fragmentMatcher = ApolloInMemoryCache.createIntrospectionFragmentMatcher(); */

[@bs.module] external fragmentTypes: string = "../fragmentTypes.json";
let fragmentMatcher =
  ApolloInMemoryCache.createIntrospectionFragmentMatcher(~data=fragmentTypes);

let inMemoryCache =
  ApolloInMemoryCache.createInMemoryCache(~fragmentMatcher, ());

/* Create an HTTP Link */
let httpLink =
  ApolloLinks.createHttpLink(
    ~uri=
      "http://"
      ++ (Webapi.Dom.location |> Webapi.Dom.Location.host)
      ++ "/graphql",
    (),
  );

let wsLink =
  ApolloLinks.webSocketLink({
    uri:
      "wss://"
      /* ++"localhost:9000" */
      ++ (Webapi.Dom.location |> Webapi.Dom.Location.host)
      ++ "/graphql",
    options: {
      reconnect: true,
      connectionParams: None,
    },
  });

/* let link = */
/*   ApolloLinks.split( */
/*     (test: ReasonApolloTypes.splitTest) => { */
/*       let def = ApolloUtilities.getMainDefinition(test##query); */
/*       def##kind == "OperationDefinition" && def##operation == "subscription"; */
/*     }, */
/*     wsLink, */
/*     httpLink, */
/*   ); */

let instance =
  ReasonApollo.createApolloClient(
    ~link=wsLink,
    ~cache=inMemoryCache,
    ~queryDeduplication=true,
    (),
  );

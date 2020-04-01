let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

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
  ApolloLinks.webSocketLink(
    ~uri=
      "ws://"
      /* ++"localhost:9000" */
      ++ (Webapi.Dom.location |> Webapi.Dom.Location.host)
      ++ "/graphql",
    ~reconnect=true,
    (),
  );

let link =
  ApolloLinks.split(
    (test: ReasonApolloTypes.splitTest) => {
      let def = ApolloUtilities.getMainDefinition(test##query);
      def##kind == "OperationDefinition" && def##operation == "subscription";
    },
    wsLink,
    httpLink,
  );

let instance =
  ReasonApollo.createApolloClient(
    ~link=wsLink,
    ~cache=inMemoryCache,
    ~queryDeduplication=true,
    (),
  );

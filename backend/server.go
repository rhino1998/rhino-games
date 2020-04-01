package main

import (
	"fmt"
	log "log"
	http "net/http"
	os "os"
	"time"

	handler "github.com/99designs/gqlgen/handler"
	"github.com/kelseyhightower/envconfig"
	"github.com/rhino1998/codenames/games"
	"github.com/rhino1998/codenames/games/codenames"
	"gopkg.in/mcuadros/go-defaults.v1"
	"gopkg.in/yaml.v2"

	"github.com/go-chi/chi"
	"github.com/go-chi/chi/middleware"
	"github.com/gorilla/websocket"
	"github.com/rs/cors"
)

const defaultPort = "9000"

func loadConfig(path string) (*Config, error) {
	var cfg Config
	defaults.SetDefaults(&cfg)

	f, err := os.Open(path)
	if err != nil {
		f2, err2 := os.Create(path)
		if err2 != nil {
			return nil, err
		}
		defer f2.Close()

		encoder := yaml.NewEncoder(f2)
		err = encoder.Encode(&cfg)
		if err != nil {
			return nil, err
		}
	} else {
		defer f.Close()
		decoder := yaml.NewDecoder(f)
		err = decoder.Decode(&cfg)
		if err != nil {
			return nil, err
		}
	}

	err = envconfig.Process("", &cfg)
	if err != nil {
		return nil, err
	}

	return &cfg, nil
}

func main() {
	var configPath string
	if len(os.Args) == 1 {
		configPath = "config.yaml"
	} else {
		configPath = os.Args[1]
	}

	config, err := loadConfig(configPath)
	if err != nil {
		log.Fatalln(err)
	}
	fmt.Printf("%+v\n", config)

	router := chi.NewRouter()
	router.Use(cors.New(cors.Options{
		AllowedOrigins:   []string{"*"},
		AllowCredentials: true,
		Debug:            true,
	}).Handler)

	router.Use(middleware.Logger)

	cn, err := codenames.NewGame(config.CodeNames)
	if err != nil {
		log.Fatalf("codenames: %v", err)
	}

	res := games.New(cn)

	router.Handle("/", handler.Playground("GraphQL playground", "/graphql"))
	router.Handle("/graphql",
		handler.GraphQL(
			games.NewExecutableSchema(games.Config{Resolvers: res}),
			handler.WebsocketUpgrader(websocket.Upgrader{
				CheckOrigin: func(r *http.Request) bool {
					return true
				},
				HandshakeTimeout: 10 * time.Second,
			}),
			handler.WebsocketKeepAliveDuration(1000*time.Millisecond),
		),
	)
	log.Printf("connect to http://localhost:%d/ for GraphQL playground", config.Port)
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%d", config.Port), router))

}

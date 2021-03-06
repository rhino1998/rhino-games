package main

import (
	"github.com/rhino1998/codenames/games/codenames"
)

type Config struct {
	CodeNames codenames.Config `yaml:"codenames"`

	Port int `yaml:"port" default:"9000" envconfig:"PORT"`
}

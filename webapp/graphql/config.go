package main

import (
	"github.com/rhino1998/codenames/model/codenames"
)

type Config struct {
	CodeNames codenames.Config `json:"code_names"`

	Port int `yaml:"port" default:"9000" envconfig:"PORT"`
}

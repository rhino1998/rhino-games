
all: reason

reason: reason_deps
	node generate_schema.js
	# protoc \
	# 	-I=. \
	# 	-I=$(GOPATH)/src \
	# 	-I=$(GOPATH)/src/github.com/gogo/protobuf/protobuf \
	# 	--swagger_out=\
	# Mgoogle/protobuf/empty.proto=github.com/gogo/protobuf/types,\
	# Mgoogle/protobuf/timestamp.proto=github.com/gogo/protobuf/types:.\
	# 	model.proto


 	#Experimental record generation
	# yarn run gql-gen
	# yarn run types-as-schema schema.ts --reason Schema.re
	# sed -i -e '/^$$/d' -e 's/type /and /' -e 's/;//' -e '1s/^and/open Scalars;\ntype/' Schema.re

reason_deps:
	# go get -u github.com/grpc-ecosystem/grpc-gateway/protoc-gen-swagger
	# opam install swagger
	yarn install


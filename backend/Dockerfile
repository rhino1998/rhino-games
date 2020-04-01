FROM golang:1.14.1-alpine3.11 as builder
RUN apk add git build-base protobuf git
ENV GO111MODULE=off
RUN go get \
    github.com/vektah/gorunpkg \
	golang.org/x/net/trace \
	golang.org/x/net/idna
ENV GO111MODULE=on

WORKDIR /codenames
ADD go.mod .
ADD go.sum .
RUN go mod vendor

WORKDIR /codenames/model
ADD model .

WORKDIR /codenames/webapp/graphql
ADD webapp/graphql/gqlgen.yml .

ADD webapp/graphql .
RUN go build -o graphql
CMD "./graphql"

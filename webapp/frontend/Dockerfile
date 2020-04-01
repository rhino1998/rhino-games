FROM node as builder


WORKDIR /go/src/github.com/rhino1998/codenames/model
ADD model .
RUN make reason


WORKDIR /go/src/github.com/rhino1998/codenames/webapp/frontend

ADD webapp/frontend/package.json .
RUN yarn install

ADD webapp/frontend .
RUN yarn run prod

FROM nginx:alpine
RUN mkdir /www
COPY --from=builder /go/src/github.com/rhino1998/codenames/webapp/frontend/build/ /www/
COPY --from=builder /go/src/github.com/rhino1998/codenames/webapp/frontend/index.html /www/
ADD webapp/frontend/nginx.conf /etc/nginx/conf.d/default.conf

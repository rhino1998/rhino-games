FROM nginx:1.15.0-alpine
RUN sed -i -e 's/v3.7/v3.8/' /etc/apk/repositories
RUN apk add --no-cache nginx-mod-http-lua


ADD nginx.conf.add .
RUN cp /etc/nginx/nginx.conf /etc/nginx/nginx.conf.old
RUN cat nginx.conf.add /etc/nginx/nginx.conf.old > /etc/nginx/nginx.conf


ADD www /www
ADD prometheus.lua /lua/
ADD nginx.conf /etc/nginx/conf.d/default.conf

FROM node:18-alpine3.15

# Install packages
RUN apk add --update --no-cache supervisor mariadb mariadb-client

# Copy flag
COPY flag.txt /flag.txt

# Setup app
RUN mkdir -p /app

# Add application
WORKDIR /app
COPY challenge .

# Install dependencies
RUN yarn

# Setup superivsord
COPY config/supervisord.conf /etc/supervisord.conf
COPY config/my.cnf /etc/my.cnf

# Expose the port node-js is reachable on
EXPOSE 1337

# Populate database and start supervisord
COPY --chown=root entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT /entrypoint.sh
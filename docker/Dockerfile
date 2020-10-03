FROM ubuntu:18.04 AS base

RUN apt-get update && apt-get install -y locales && rm -rf /var/lib/apt/lists/* \
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG en_US.utf8


RUN mkdir /code && mkdir /data
WORKDIR /code
RUN apt-get update && apt-get install make && apt-get -y install build-essential  \
    git cmake vim python python-dev swig libncurses5-dev libedit-dev libpthread-stubs0-dev

FROM base AS runner



COPY --from=icalialabs/watchman:4-alpine3.4 /usr/local/bin/watchman* /usr/local/bin/
RUN mkdir -p /usr/local/var/run/watchman \
 && touch /usr/local/var/run/watchman/.not-empty


RUN apt-get update && apt-get -y install cmake git build-essential \
    vim python python-dev swig libncurses5-dev libedit-dev libpthread-stubs0-dev clang-tools-10





FROM ubuntu:24.10

RUN apt-get update
RUN apt-get install -y cmake gcc

COPY scripts/build.sh /build.sh
COPY scripts/run.sh /run.sh

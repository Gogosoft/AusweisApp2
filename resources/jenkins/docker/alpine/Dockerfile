FROM scratch
MAINTAINER Governikus KG <ausweisapp2@governikus.com>

ARG version="3.6.2"
ARG arch="x86_64"
ADD alpine-minirootfs-$version-$arch.tar.gz /

RUN apk --no-cache upgrade

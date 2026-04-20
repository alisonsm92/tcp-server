FROM gcc:latest

RUN apt-get update && apt-get install -y libboost-system-dev

WORKDIR /app
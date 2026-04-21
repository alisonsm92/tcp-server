FROM gcc:latest

RUN apt-get update && apt-get install -y libboost-system-dev cmake

WORKDIR /app

COPY . .

RUN rm -rf build && cmake -B build -S .
RUN cmake --build build
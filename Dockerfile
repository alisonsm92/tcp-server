FROM gcc:latest

RUN apt-get update && apt-get install -y libboost-filesystem-dev cmake

WORKDIR /app

COPY . .

RUN cmake -B build -S .

RUN cmake --build build

CMD ["./build/server"]
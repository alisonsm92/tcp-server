# TCP Server & Client (C++ Boost Asio)

Este projeto implementa um servidor TCP assíncrono e um cliente interativo utilizando a biblioteca Boost.Asio e C++11.

## Estrutura do Projeto

- `server/`: Contém a implementação do servidor TCP.
- `client/`: Contém o cliente TCP interativo que lê do terminal e envia para o servidor.
- `Dockerfile`: Configuração para build da imagem.
- `docker-compose.yml`: Orquestração dos serviços de servidor e cliente.

## Pré-requisitos

- [Docker](https://docs.docker.com/get-docker/)

## Como Executar

Para testar a interação entre o cliente e o servidor, siga os passos abaixo:

### 1. Iniciar o Servidor
Em um terminal, execute o comando para subir o servidor em segundo plano:
```bash
docker-compose up --build server
```

### 2. Executar o Cliente Interativo
Abra um **segundo terminal** e execute o cliente:
```bash
docker-compose run client
```

### 3. Interagir
- No terminal do **cliente**, digite qualquer mensagem e pressione `Enter`.
- No terminal do **servidor**, você verá a mensagem recebida no formato: `Received: <sua mensagem>`.

## Comandos Úteis

- **Parar todos os serviços:**
  ```bash
  docker-compose down
  ```
- **Recompilar após mudanças no código:**
  ```bash
  docker-compose up --build server
  ```

## Tecnologias Utilizadas
- C++11
- Boost.Asio (Networking)
- CMake (Build System)
- Docker (Containerização)

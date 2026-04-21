# TCP Server (C++ Boost Asio Challenge)

Este projeto implementa um servidor TCP que recebe dados e os armazena em arquivos locais, respeitando um limite de tamanho configurável.

## Funcionalidades e Premissas

1. **Configuração via Arquivo:** O servidor carrega `PORT` e `MAX_FILE_SIZE` diretamente do arquivo `server.conf`.
2. **Limite de Tamanho de Arquivo:** O servidor cria um arquivo para cada sessão com o padrão `session_<ip>_<porta>.bin`.
3. **Comunicação TCP:** Utiliza sockets TCP assíncronos para o servidor e síncronos para o cliente.
4. **Integridade de Dados:** Todos os bytes recebidos são persistidos. Se uma mensagem recebida exceder o espaço restante no arquivo atual, ela é dividida entre o arquivo atual e o próximo.

## Estrutura do Projeto

- `server/`: Servidor com lógica de persistência e rotação de arquivos.
- `client/`: Cliente interativo para envio de dados.
- `server.conf`: Arquivo de configuração (Porta e Tamanho Máximo).
- `data/`: Diretório onde os arquivos `.bin` serão salvos.

## Como Configurar

Edite o arquivo `server.conf` na raiz do projeto:

```ini
PORT=8080
MAX_FILE_SIZE=100
```

## Como Executar os Testes

1.**Iniciar o Ambiente:**

  ```bash
    docker-compose up --build server
  ```

2.**Executar o Cliente Interativo:**

  ```bash
    docker-compose run client
  ```

### 3. Interagir

- No terminal do **cliente**, digite qualquer mensagem e pressione `Enter`.
- No terminal do **servidor**, você verá a mensagem recebida no formato: `Received: <sua mensagem>`.

### 4. **Verificar Arquivos:**

  Confira a pasta `data/` local para ver os arquivos gerados.

## Tecnologias e Versões

- **Linguagem:** C++17
- **Biblioteca:** Boost.Asio 1.81+.
- **Build:** CMake 3.10+ / GCC.

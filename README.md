# TCP Server (C++ Boost Asio Challenge)

Este projeto implementa um servidor TCP que recebe dados e os armazena em arquivos locais, respeitando um limite de tamanho configurável.

## Funcionalidades

1. **Configuração via Arquivo:** O servidor carrega `PORT` e `MAX_FILE_SIZE` diretamente nos arquivos `server/server.conf` e `client/client.config`.
2. **Arquivo com dados transmitidos:** O servidor cria um arquivo para cada sessão com o padrão `<FILE_NAME_PREFIX>_<timestamp>.bin` e armazena os dados transmitidos.
3. **Comunicação TCP:** Utiliza sockets TCP assíncronos para o servidor e síncronos para o cliente.
4. **Integridade de Dados:** Todos os bytes recebidos são persistidos. Se uma mensagem recebida exceder o espaço restante no arquivo atual, ela é dividida entre o arquivo atual e o próximo.

## Estrutura do Projeto

- `server/`: Servidor com lógica de persistência e rotação de arquivos.
- `client/`: Cliente interativo para envio de dados.
- `data/`: Diretório onde os arquivos `.bin` serão salvos.
- `common/`: Utilitários em comum entre cliente e servidor.

## Como configurar os parâmetros

Edite os arquivos de configuração:

- Para as configurações do `servidor` edite o arquivo `/server/server.conf`

```ini
PORT=8080
MAX_FILE_SIZE=100
TIMEOUT_IN_SECONDS=10
FILE_NAME_PREFIX=data
```

- Para as configurações do `cliente` edite o arquivo `client/client.conf`:

```ini
PORT=8080
```

### Significado das Configurações:

- **PORT**: Porta TCP utilizada para a comunicação entre cliente e servidor.
- **MAX_FILE_SIZE**: Tamanho máximo, em bytes, de cada arquivo gerado pelo servidor antes de fechar a sessão ou rotacionar o armazenamento.
- **TIMEOUT_IN_SECONDS**: Tempo de inatividade, em segundos, antes do servidor encerrar automaticamente uma sessão.
- **FILE_NAME_PREFIX**: Prefixo utilizado para nomear os arquivos de dados gerados (ex: `data_123456789.bin`).


## Como executar as aplicações

1. **Iniciar o servidor:**

  ```bash
    docker-compose up --build server
  ```

2. **Executar o cliente interativo:**

  ```bash
    docker-compose run client
  ```

3. **Interagir**

- No terminal do **cliente**, digite qualquer mensagem e pressione `Enter`.

> [!NOTE]
> No terminal do **servidor**, você poderá acompanhar em qual arquivo os dados foram salvos. Procure pelo seguinte formato de mensagem: 
> 
> ````
> [session <s>] Saved <b> bytes to file: data/<FILE_NAME_PREFIX>_<TIMESTAMP>.bin`.
> ````

4. **Verificar Arquivos:**

  - Confira a pasta `data/` local para ver os arquivos gerados.

## Tecnologias e Versões

- **Linguagem:** C++17
- **Biblioteca:** Boost.Asio 1.81+.
- **Build:** CMake 3.10+ / GCC.

## Desafios

Durante o desenvolvimento dessa aplicação tive como principal desafio aprender a sintaxe da lingaguem C++, a qual não tive contato prévio. Também entender a API e o funcionando da biblioteca [Boost.Asio](https://www.boost.org/library/latest/asio/).

Dado esse cenário, de não conhecer a linguagem e a biblioteca, utilizei como ponto de partida os exemplos de servidor e cliente TCP da própria documentação da biblioteca Boost.Asio ([examples](https://www.boost.org/doc/libs/latest/doc/html/boost_asio/examples/cpp11_examples.html)).

Utilizei também a documentação no [w3schools](https://www.w3schools.com/cpp/default.asp) para aprender como funcionava estruturas básicas da linguagem C++.

Utilizei o [Google Gemini CLI](https://geminicli.com/) para orquestrar as modificações e refatoração no código, além de tirar dúvidas sobre detalhes da linguagem. A ferramenta foi essencial para que fosse possível implemntar as funcionalidades no tempo disponível.

Infelizmente, por não ter maior conhecimento na linguagem C++, não consegui aplicar Test Drive Development e nem implemntar testes unitários dentro do tempo disponível.

## Tempo gasto

Aproximadamente `12 horas` para realizar o desenvolviemnto e conseguir chegar no resultado final.

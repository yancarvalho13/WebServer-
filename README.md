# Simple C++ WebServer

Servidor web simples feito em C++ com sockets TCP e respostas HTTP montadas manualmente.

## O que ele faz

- escuta conexoes HTTP na porta `8080`
- recebe a requisicao do cliente pelo socket
- faz parse basico do metodo e caminho
- encontra a rota registrada em memoria
- retorna HTML estatico com headers HTTP

## Objetos principais

- `WebServer`: inicia o socket do servidor, aceita conexoes, recebe a requisicao e envia a resposta ao cliente.
- `Route`: representa uma rota HTTP com metodo, caminho e conteudo de resposta.
- `RouteHandler`: registra as rotas e decide qual resposta retornar para cada request.
- `Request`: faz o parse da requisicao HTTP recebida pelo servidor.
- `Response`: encapsula o corpo final enviado ao cliente.
- `RouteEngineHelpers`: contem helpers para converter metodo HTTP e montar resposta HTML.

## Como usar

O uso basico acontece no `Main.cpp`:

```cpp
Route* home = new Route(Methods::GET, "/");
home->setHtmlResponse("html/home.html");

WebServer* webServer = new WebServer(8080, 10);
webServer->start();
webServer->mapRoute(*home);
```

Fluxo:

1. crie uma `Route` com metodo e caminho
2. associe um arquivo HTML com `setHtmlResponse(...)`
3. crie o `WebServer` informando porta e tamanho da fila de conexoes
4. chame `start()` para iniciar o servidor
5. registre as rotas com `mapRoute(...)`

## Rotas atuais

- `GET /` -> `html/home.html`
- `GET /about` -> `html/about.html`
- `GET /portfolio` -> `assets/portfolio.html`

## Estrutura

- `Main.cpp`: configuracao inicial do servidor e mapeamento das rotas
- `WebServer.cpp`: loop de conexao, leitura da request e escrita da response
- `Request.cpp`: parse da requisicao HTTP
- `Response.cpp`: objeto de resposta HTTP
- `Route.cpp`: definicao da rota
- `RouteEngine.cpp`: registro e resolucao de rotas
- `RouteEngineHelpers.cpp`: helpers de metodo HTTP e leitura de HTML
- `html/`: paginas HTML basicas
- `assets/`: arquivos estaticos usados pelas rotas

## Build E Execucao

```bash
cmake -S . -B build && cmake --build build && ./build/server
```

Depois acesse no navegador:

```text
http://localhost:8080
http://localhost:8080/about
http://localhost:8080/portfolio
```

## Observacoes

- projeto didatico e minimalista
- rotas registradas manualmente no codigo
- atualmente serve HTML estatico

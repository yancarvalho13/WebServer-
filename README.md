# Simple C++ WebServer

Servidor web simples feito em C++ usando sockets TCP e respostas HTTP básicas.

## O que ele faz

- Escuta na porta `8080`
- Recebe requisições HTTP simples
- Faz o parse do método, caminho e host
- Mapeia rotas para arquivos HTML
- Retorna o conteúdo com headers HTTP

## Rotas atuais

- `GET /` -> `html/home.html`
- `GET /about` -> `html/about.html`

## Estrutura

- `WebServer.cpp`: ponto de entrada e loop do servidor
- `Request.cpp`: parse da requisição HTTP
- `Response.cpp`: objeto de resposta
- `Route.cpp`: definição de rota
- `RouteEngine.cpp`: registro e busca de rotas
- `RouteEngineHelpers.cpp`: helpers de método e leitura de HTML
- `html/`: páginas HTML servidas pelo servidor

## Compilar

```bash
g++ WebServer.cpp Request.cpp Response.cpp Route.cpp RouteEngine.cpp RouteEngineHelpers.cpp -o main
```

## Executar

```bash
./main
```

Depois acesse no navegador:

```text
http://localhost:8080
http://localhost:8080/about
```

## Observações

- Projeto didático e minimalista
- Suporta rotas simples registradas manualmente no código
- Atualmente serve HTML estático

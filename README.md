# EP de AED: Caminho em Grafo

## Descrição
Neste exercício prático, você deve implementar a função `caminho` em uma estrutura de dados de grafo não direcionado ponderado. O grafo representa um ambiente virtual com salas (vértices) e conexões entre elas (arestas), e cada aresta possui um custo de deslocamento.

### Parâmetros da Função
- `N`: Número de vértices no grafo.
- `A`: Número de arestas no grafo.
- `ijpeso`: Vetor que define as arestas do grafo, representado por triplas (i, j, peso).
- `aberto`: Vetor indicando se as salas estão abertas (1) ou trancadas (0).
- `início`: Sala de partida.
- `fim`: Sala de destino.
- `chave`: Sala que contém a chave de acesso.

### Saída
A função deve retornar um ponteiro do tipo `NO*` representando o caminho de menor custo possível do início até o fim. O caminho não deve incluir acesso inválido a salas trancadas sem que a chave tenha sido previamente obtida.

### Requisitos do Caminho
- A lista de resposta deve seguir o formato especificado no projeto, com um inteiro (`adj`) em cada nó.
- O campo `prox` do último nó da lista deve apontar para NULL.
- Não use nó cabeça, sentinela, circularidade ou encadeamento duplo.
- Se não existe caminho possível, a lista fica vazia (NULL).
- Se a lista não for vazia, o primeiro nó contém o número do vértice de início, e o último nó contém o número do vértice de fim.
- Os elementos da lista representam uma sequência ordenada de vértices adjacentes no grafo, ou seja, o agente não pode "voar" de uma sala para outra que não seja adjacente.
- Uma sala trancada 'i' só pode ser incluída no percurso se a sala chave tiver sido alcançada antes de 'i'.
- A sala chave, por definição, nunca está trancada.
- Uma vez obtida a chave, assume-se que todas as salas que estavam trancadas estão agora acessíveis.

### Como executar?
1. Coloque as informações nos atributos do código seguindo os parâmetros da função já especificados
2. Compile o código utilizando um compilador C++
3. Será gerado uma saída com extensão .txt


## 🤝 Colaborador

A pessoa que contribuiu para o projeto

<table>
  <tr>
    <td align="center">
      <a href="#">
        <img src="https://avatars.githubusercontent.com/u/81971651?s=400&u=548b7cc3deb1bd124ba02dbc2acc865b97138ce3&v=4" width="100px;" alt="Foto do Bruno Friedrich no Github"/><br>
        <sub>
          <b>Bruno Friedrich</b>
        </sub>
      </a>
    </td>
  </tr>
</table>

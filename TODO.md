### TODO's para aprimorar e finalizar o programa

- **Verificações das entradas de cadastro**
    - Garantir que as entradas sejam do tipo correto (ex: evitar caracteres em campos numéricos, e espaços onde nao devem ter)
    - Implementar essas verificações nas entradas de cadastro de Usuários, Eventos e Produtos

####

- **Funções de ativação/desativação**
    - Criar funções para ativar ou desativar Usuários, Eventos e Produtos

####

- **Filtragem de produtos**
    - A função `ListaProdutoVenda()` deve filtrar os produtos exibidos de acordo com o `idEvento` do vendedor

####

- **Relatórios de vendas**
    - Agrupar e somar as quantidades dos itens com o mesmo `id` nos relatórios Geral e Específico de vendas
    - Criar opção de ordenação no relatório geral por:
        - `IdProduto`
        - `MaisVendido`
        - `MenosVendido`
    - No relatório específico de vendas, remover as colunas `cod`, `IdEvento` e `IdVenda`
    - No relatório geral de vendas, remover as colunas `cod`, `IdEvento`

####

- **Gerenciamento de estoque**
    - Adicionar opção no administrativo para ajustes de estoque
    - Implementar evento que, ao gerar uma venda, subtraia a quantidade vendida de cada item
    - Criar variável para atualizar a listagem dos itens, refletindo os valores a cada interação

####

- **Forma de pagamento**
    - Adicionar coluna no arquivo `venda.txt` para um char `formaPgto[8]` com os formatos:
        - "Dinheiro"
        - "Credito"
        - "Debito"
        - "Pix"

####

- **Listagem de eventos**
    - Criar uma função `listarEventosCadastro()` para ser usada ao cadastrar Usuários e Produtos

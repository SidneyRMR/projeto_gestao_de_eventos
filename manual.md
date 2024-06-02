# Documentação do Programa de Gerenciamento de Vendas

## Introdução

O Programa de Gerenciamento de Vendas é uma aplicação desenvolvida em C para auxiliar no registro, organização e análise de vendas. Ele oferece uma variedade de recursos para administradores e vendedores acompanharem o desempenho das vendas de forma eficiente e intuitiva.

## Funcionalidades

### Tela de Login

- **Descrição:** A tela de login permite que os usuários ingressem no sistema usando suas credenciais. Existem dois tipos de usuários: administrador e vendedor.

### Tela de Vendas

- **Descrição:** Permite que os vendedores registrem vendas, selecionando produtos, adicionando itens ao carrinho e finalizando a venda. Após o término da venda, eles retornam à tela de vendas para iniciar uma nova transação.

### Tela Administrativa

- **Descrição:** Oferece opções para administradores gerenciarem usuários, produtos, eventos e acessarem relatórios de vendas. Os administradores também podem fazer logoff ou sair do programa.

### Gerenciamento de Usuários

- **Descrição:** Os administradores podem criar e editar usuários (vendedores) na tela administrativa. 

### Gerenciamento de Produtos e Eventos

- **Descrição:** Os administradores podem criar, editar e excluir produtos e eventos na tela administrativa.

### Relatórios de Vendas

- **Descrição:** Fornece relatórios abrangentes sobre vendas gerais, vendas específicas de eventos e detalhes de produtos vendidos.

### Possíveis Atualizações Futuras

1. **Backup de Dados:** Adicionar uma função para fazer backup dos arquivos e do banco de dados.
2. **Melhoria na Criação de Usuários:** Implementar verificação para evitar a criação de usuários duplicados.
3. **Banco de Dados:** Utilizar uma biblioteca de banco de dados como SQLite para melhorar o armazenamento e gerenciamento de dados.
4. **Interface Gráfica:** Implementar uma interface visual usando bibliotecas como GTK ou Ncurses para facilitar a interação com o usuário.
5. **Otimização de Código:** Reduzir partes repetidas do código encapsulando em funções e ajudando a melhorar a performance.

## Requisitos do Sistema

- **Sistema Operacional:** Windows.
- **Compilador C:** Para compilar e executar o código fonte, se necessário.

## Instalação

1. Faça o download do arquivo executável do programa.
2. Execute o arquivo de instalação e siga as instruções na tela para concluir a instalação.

## Utilização

1. **Tela de Login:** Insira suas credenciais e selecione o tipo de usuário.
2. **Tela de Vendas:** Selecione produtos, adicione ao carrinho e finalize a venda digitando o código 100.
3. **Tela Administrativa:** Acesse as opções disponíveis para gerenciar usuários, produtos, eventos e visualizar relatórios de vendas.

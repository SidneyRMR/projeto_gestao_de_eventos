# Documentação do Programa de Vendas

Este documento fornece uma visão geral do programa de vendas, detalhando suas funcionalidades, instruções de uso e sugestões de melhorias.

## Visão Geral

O programa de vendas é uma aplicação desenvolvida em C que permite aos usuários, especialmente administradores e vendedores, gerenciar vendas, produtos, eventos e relatórios de vendas. Ele oferece uma interface de linha de comando (CLI) intuitiva para facilitar a interação do usuário com as diferentes funcionalidades.

## Funcionalidades Principais

1. **Login de Usuário:** O programa permite que usuários façam login como administradores ou vendedores, com credenciais específicas para cada tipo de usuário.

2. **Vendas:** Na tela de vendas, os usuários podem listar produtos disponíveis, preços e estoques. Eles podem selecionar produtos digitando o código correspondente e adicionar à venda conforme necessário. Ao finalizar a seleção dos produtos, o usuário pode inserir o código especial para prosseguir para as opções de pagamento e finalizar a venda.

3. **Opções de Pagamento:** Após selecionar os produtos, os usuários podem escolher entre diferentes opções de pagamento para finalizar a venda.

4. **Menu Administrativo:** No menu administrativo, os usuários têm acesso a funcionalidades avançadas, incluindo a edição e criação de usuários (apenas vendedores), produtos e eventos. Além disso, eles podem gerar relatórios de vendas, fazer logoff ou sair do programa.

5. **Relatórios de Vendas:** Os usuários podem gerar relatórios detalhados de vendas, permitindo uma análise abrangente do desempenho de vendas ao longo do tempo.

## Instruções de Uso

### 1. Login de Usuário

- Ao iniciar o programa, o usuário será solicitado a fazer login fornecendo suas credenciais de usuário.
- O programa verificará as credenciais e redirecionará o usuário para a tela correspondente (vendas ou menu administrativo).

### 2. Tela de Vendas

- Na tela de vendas, o usuário pode listar os produtos disponíveis e selecionar os produtos desejados digitando o código correspondente.
- Após selecionar os produtos, o usuário pode inserir o código especial para prosseguir para as opções de pagamento e finalizar a venda.
- Após finalizar a venda, o usuário será redirecionado de volta à tela de vendas para iniciar uma nova venda.

### 3. Menu Administrativo

- No menu administrativo, o usuário pode acessar diferentes funcionalidades, incluindo edição e criação de usuários, produtos e eventos.
- Além disso, o usuário pode gerar relatórios de vendas para análises mais detalhadas do desempenho de vendas.

## Sugestões de Melhorias

1. **Backup Automático:** Adicionar uma função de backup automático para salvar os dados do programa periodicamente, garantindo a segurança dos dados em caso de falha do sistema.

2. **Validação de Usuário:** Implementar uma validação mais robusta ao criar novos usuários para garantir que não haja duplicação de credenciais.

3. **Banco de Dados:** Integrar um banco de dados para armazenar e gerenciar os dados do programa de forma mais eficiente e escalável.

4. **Interface Gráfica:** Desenvolver uma interface gráfica usando bibliotecas como GTK ou Qt para proporcionar uma experiência de usuário mais amigável e intuitiva.

5. **Otimização de Código:** Identificar e reduzir partes repetidas do código, passando informações entre funções e otimizando algoritmos para melhorar a performance do programa.

## Conclusão

O programa de vendas oferece uma solução completa para gerenciar vendas, produtos e relatórios de vendas. Com uma interface intuitiva e funcionalidades avançadas, é uma ferramenta poderosa para administradores e vendedores otimizarem suas operações de vendas. As sugestões de melhorias fornecidas podem ajudar a aprimorar ainda mais o programa e oferecer uma experiência ainda melhor aos usuários.

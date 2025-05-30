# ✅ Checklist do Projeto Berê 4 – Profissionalização

## 📆 Cronograma e Entregas
- [ ] Desenvolvimento: 04/06/24 a 28/06/24
- [ ] Entrega final na plataforma até 28/06/24 às 23h59
- [ ] Apresentações: 01/07 (segunda) e 03/07 (quarta)
- [ ] Líder apresenta o grupo; todos devem saber explicar o código

---

## 🔍 Levantamento de Requisitos

### Necessidade 1 – Sistema em C (Terminal)
- [ ] Interface via terminal (Prompt de Comando)
- [ ] Foco na experiência da Dona Berê e sua ajudante

### Necessidade 2 – Menu Profissional
- [ ] Menu Principal com opções:
  - [ ] Cadastros
  - [ ] Vendas
  - [ ] Abertura de Caixa
  - [ ] Fechamento de Caixa
  - [ ] Relatórios
  - [ ] Sair
- [ ] Submenus completos e funcionais
- [ ] Comportamento dinâmico conforme dia da semana

### Necessidade 3 – Structs
- [ ] Structs para usuários, clientes, produtos, vendas e pagamentos

### Necessidade 4 – Ponteiros e Alocação Dinâmica
- [ ] Cadastro dinâmico de clientes, produtos e vendas

### Necessidade 5 – Arquivos
- [ ] Arquivo de usuários
- [ ] Arquivo de clientes
- [ ] Arquivo de produtos
- [ ] Arquivo de vendas
- [ ] Arquivo de pagamentos

---

## 🔐 1. Cadastros
- [ ] Cadastro de usuários (login, senha, tipo)
- [ ] Cadastro de clientes (dados completos e ilimitado)
- [ ] Cadastro de produtos (dados, cálculo da margem, estoque mínimo)
- [ ] Cadastro de categorias

**Regras de Produtos**
- [ ] Alerta para estoque mínimo
- [ ] Alerta para venda acima do estoque
- [ ] Bloqueio de venda com estoque zerado

---

## 🛒 2. Vendas
- [ ] Visualizar lista de produtos
- [ ] Inserir no carrinho por código e quantidade
- [ ] Totalizador por item e por venda
- [ ] Permitir desconto em percentual
- [ ] Estrutura separada para venda e itens da venda

**Pagamentos**
- [ ] Suporte a pagamento em dinheiro, cartão e misto
- [ ] Cálculo de troco
- [ ] Confirmação de operação no cartão
- [ ] Pagamento retroativo para vendas em aberto

**Sangria (Retirada de Caixa)**
- [ ] Totalizar valores pagos em dinheiro
- [ ] Validar administrador
- [ ] Não permitir retirar todo o valor do caixa
- [ ] Restar no mínimo R$ 50,00

---

## 💰 3. Abertura de Caixa
- [ ] Valor ≥ 0
- [ ] Validar se é administrador

---

## 🔐 4. Fechamento de Caixa
- [ ] Validar se é administrador
- [ ] Exibir:
  - [ ] Total de vendas
  - [ ] Faturamento
  - [ ] Valor de abertura
  - [ ] Pagamento em dinheiro e misto
  - [ ] Pagamento em cartão e misto
- [ ] Verificar divergências e ajustar se necessário

---

## 📊 5. Relatórios
- [ ] Listagem alfabética de clientes
- [ ] Clientes que compraram (por período)
- [ ] Produtos ordenados por nome
- [ ] Produtos com estoque mínimo ou zerado
- [ ] Produtos mais vendidos (por período)
- [ ] Listagem de vendas por período
- [ ] Faturamento consolidado por tipo de pagamento
- [ ] Relatórios adicionais criativos

---

## 📁 Documentação e Entregáveis
- [ ] `Bere4.c` documentado
- [ ] Fluxograma por módulos ou requisitos em planilha
- [ ] Manual do Usuário (implantação e uso)
- [ ] Postar na plataforma Blackboard

---

## 🎯 Critérios de Avaliação (14 Itens)
- [ ] Nomenclatura padronizada
- [ ] Comentários no código
- [ ] Uso de passagem e retorno de parâmetros
- [ ] Estruturas de repetição e seleção adequadas
- [ ] `main()` enxuta e bem organizada
- [ ] Vetores e matrizes utilizados
- [ ] Uso de `struct`
- [ ] Ponteiros e alocação dinâmica
- [ ] Arquivos e ordenação de dados
- [ ] Todas as necessidades atendidas
- [ ] Relatórios gerados corretamente
- [ ] Todos os entregáveis concluídos
- [ ] Criatividade no sistema
- [ ] Tratamento de exceções implementado

---

> ⚠️ **Dica para Apresentação**: todos os membros devem estar preparados para explicar o código, as regras de negócio e justificativas das decisões técnicas.

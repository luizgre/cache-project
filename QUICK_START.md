# Guia Rápido - Como Testar o Projeto

## 1. Compilar o Projeto

```bash
make
```

## 2. Testar Modo Interativo

```bash
./ra2_main
```

Depois digite números de 1 a 100 para carregar textos:
- Primeira vez: **MISS** (carrega do disco ~10ms)
- Segunda vez: **HIT** (pega do cache ~0ms)
- Digite **0** para sair
- Digite **-1** para simulação

### Exemplo de Teste:
```
Text: 5      # MISS - carrega do disco
Text: 5      # HIT - pega do cache!
Text: 10     # MISS - outro texto
Text: 5      # HIT - ainda no cache
Text: 0      # Sai
```

## 3. Rodar Simulação Completa

```bash
echo "-1" | ./ra2_main
```

Isso vai:
- Testar os 3 algoritmos (FIFO, LRU, LFU)
- Com 3 padrões de acesso (Random, Poisson, Weighted)
- 3 usuários × 200 requisições cada = 600 por teste
- Salvar resultados em `results.csv`

**Tempo:** ~2 minutos (600 requisições × 9 testes)

## 4. Ver Resultados

```bash
python3 show_results.py
```

Mostra tabela formatada com:
- Taxa de hit de cada algoritmo
- Tempo médio de resposta
- Melhor desempenho geral
- Análise comparativa

### Resultado Esperado:

```
Best Hit Rate: LRU on Poisson pattern (41.50%)
- Random: ~8-10% (padrão mais difícil)
- Poisson: ~35-41% (melhor caso)
- Weighted: ~20-24% (caso médio)
```

## 5. Gerar Gráficos (Opcional)

Se tiver pandas e matplotlib instalados:

```bash
python3 plot_results.py
```

Gera 3 gráficos em `docs/graphs/`:
- `hit_rate.png` - Comparação de hit rate
- `response_time.png` - Comparação de tempo
- `summary_table.png` - Tabela completa

## 6. Limpar Projeto

```bash
make clean
```

Remove arquivos compilados e results.csv

## Comandos Úteis

```bash
# Compilar e rodar
make run

# Ver arquivos de texto
ls texts/ | head -10
wc -w texts/1.txt

# Ver estrutura do projeto
tree -L 2

# Contar linhas de código
find . -name "*.cpp" -o -name "*.h" | xargs wc -l
```

## Análise dos Resultados

### FIFO (First In First Out)
- Mais simples
- Remove o item mais antigo
- Performance moderada (~9% Random, ~35% Poisson)

### LRU (Least Recently Used)
- Remove item menos usado recentemente
- Melhor para padrões com localidade temporal
- **Melhor no geral:** 41.5% no Poisson!

### LFU (Least Frequently Used)
- Remove item menos acessado
- Bom para "hot sets" (itens populares)
- **Melhor no Weighted:** 24% (vs 20% FIFO/LRU)

## Para o Relatório

Use estes pontos:
1. LRU teve melhor desempenho geral (41.5% hit rate)
2. Poisson foi o padrão mais fácil (tem localidade)
3. Random foi o mais difícil (~8-10% todos os algoritmos)
4. LFU se destacou no padrão Weighted (24% vs 20%)
5. Tempo médio inversamente proporcional ao hit rate
6. Cache de 10 itens é limitante para 100 textos

## Dúvidas?

- Todos os logs estão em `DEVELOPMENT_LOG.md`
- Documentação completa em `README.md`
- Código está comentado em inglês

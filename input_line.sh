# head -n $(grep -n 'ss' oi |cut -d ":" -f1) oi |cat - <(echo 123896123) <(tail -n $(($(wc -l oi | awk '{print $1}') - $(grep -n 'ss' oi |cut -d : -f1))) oi) > _ && mv _ oi
  Passo a Passo:
```grep -n 'ss' oi | cut -d: -f1 → pega o número da linha onde ss aparece.
head -n N oi → pega tudo até essa linha (inclusive).
tail -n (total - N) oi → pega tudo depois dessa linha.
cat - <(echo 123896123) <(tail...) → junta: início + a linha nova + o resto.
Escreve num arquivo temporário _ e sobrescreve oi.
```

Problemas:

grep -n 'ss' oi é chamado duas vezes, e o arquivo é lido 4 vezes no total (grep×2, head, wc, tail) — desnecessário.
Se ss aparecer em mais de uma linha, cut devolve vários números separados por quebra de linha, e head -n quebra (head: invalid number of lines).
Não há tratamento se ss não for encontrado (comando quebra silenciosamente ou insere errado).
Estilo difícil de ler/manter.

# -------------------------------------------------------------------------------------------------------------------------------------------------------------------

Forma mais simples com sed (insere depois da primeira ocorrência de ss):

sed -i '0,/ss/{/ss/a\
123896123
}' oi

Se você quiser inserir depois de todas as ocorrências de ss (não só a primeira), fica ainda mais simples:

bash
sed '/ss/a\
123896123' oi > _ && mv _ oi

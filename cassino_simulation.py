'''
import random

def simular_aposta(chance_de_ganho_jogador):
    """Simula uma única aposta e retorna True para vitória, False para derrota."""
    if random.random() < chance_de_ganho_jogador:
        return True  # Jogador ganhou
    else:
        return False # Jogador perdeu

def main():
    """Executa a simulação de apostas e exibe os resultados."""
    total_apostas = 1000000
    chance_de_ganho = 0.497  # 49.7%

    vitorias = 0
    derrotas = 0

    for _ in range(total_apostas):
        if simular_aposta(chance_de_ganho):
            vitorias += 1
        else:
            derrotas += 1

    # Calcula as porcentagens
    porcentagem_vitorias = (vitorias / total_apostas) * 100
    porcentagem_derrotas = (derrotas / total_apostas) * 100

    print("--- Resultados da Simulação do Cassino ---")
    print(f"Total de apostas: {total_apostas}")
    print(f"Chance de ganho definida para o jogador: {chance_de_ganho * 100}%")
    print("-" * 40)
    print(f"Vitórias: {vitorias} ({porcentagem_vitorias:.2f}%)")
    print(f"Derrotas: {derrotas} ({porcentagem_derrotas:.2f}%)")
    print("--- Fim da Simulação ---")

if __name__ == "__main__":
    main()'''

# Versão melhorada

'''
Pontos de melhoria (performance e estilo):
Loop em Python puro é lento para 1M iterações com uma função chamando random.random() a cada vez. Dá pra acelerar bastante:
'''

import random

def main():
    total_apostas = 1_000_000
    chance_de_ganho = 0.497

    vitorias = sum(1 for _ in range(total_apostas) if random.random() < chance_de_ganho)
    derrotas = total_apostas - vitorias

    porcentagem_vitorias = (vitorias / total_apostas) * 100
    porcentagem_derrotas = (derrotas / total_apostas) * 100

    print("--- Resultados da Simulação do Cassino ---")
    print(f"Total de apostas: {total_apostas}")
    print(f"Chance de ganho definida para o jogador: {chance_de_ganho * 100}%")
    print("-" * 40)
    print(f"Vitórias: {vitorias} ({porcentagem_vitorias:.2f}%)")
    print(f"Derrotas: {derrotas} ({porcentagem_derrotas:.2f}%)")
    print("--- Fim da Simulação ---")

if __name__ == "__main__":
    main()

'''
Isso elimina a chamada de função extra por iteração (simular_aposta) e o if/else manual, usando sum() com generator — mais rápido em CPython.
Ainda mais rápido: usar NumPy (se instalado), que vetoriza a geração de números aleatórios:
'''

import numpy as np

def main():
    total_apostas = 1_000_000
    chance_de_ganho = 0.497

    resultados = np.random.random(total_apostas) < chance_de_ganho
    vitorias = int(resultados.sum())
    derrotas = total_apostas - vitorias
    # ... resto igual


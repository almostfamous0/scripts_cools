#!/usr/bin/env python3

from random import randint

def simulacao_ano(init_val, porcentagem_aposta=0.05, acerto=0.5, simulacoes_mes=30):
    meses = 12
    lucro = 0
    inicio = init_val
    break_condition = 0
    trading_times = 0

    while(meses):
        for n in range(simulacoes_mes):
            aposta = init_val*porcentagem_aposta
            win = randint(0,101)
            trading_times+=1

            if win >= acerto*100:
                init_val += aposta*0.8
                lucro += aposta*0.8

            if win < acerto*100:
                init_val -= aposta
                lucro -= aposta

            if init_val <= inicio*0.09:  # Stop Loss
                print(f"\x1b[31mParando pois voce ja perdeu 91% do seu capital com {trading_times} APOSTAS!\x1b[0m")
                break_condition = 1
                break
        if break_condition:
            break

        meses -= 1

    if break_condition:
        print(f'\x1b[31mVoce teve um prejuizo de R${init_val-inicio},00.  E sua banca vale: R${init_val},00 agora!\n\x1b[0m\n >>> [ + ] Isso Ocorreu com {13-meses} Meses!')
        return False
    else:
        if init_val >= inicio:
            print(f'\x1b[32mParabens!  Voce teve um lucro de R${init_val-inicio},00 e banca: {init_val}\n Foram feitas {trading_times} APOSTAS!\n\x1b[0m')
            return True

bom = 0
#for n in range(10000):
for n in range(1000):
    if simulacao_ano(1000):
        bom += 1

print(f"Tiveram apenas {bom}/1000 vezes que voce teve lucro!")

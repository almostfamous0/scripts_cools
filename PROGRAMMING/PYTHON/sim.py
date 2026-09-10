import pandas as pd

# Definindo os valores iniciais
capital_inicial = [200000]
incremento_mensal = 1000
taxa_mensal = 0.015  # Convertendo a taxa de 1.15% para decimal

# Criando a lista de dias
dias = list(range(1, 31))

# Calculando os valores diários e finais
capital_final = []
lucro_diario = []

for dia in dias:
    if dia != 30:
        capital_final_dia = round(capital_inicial[dia-1] + capital_inicial[dia-1] * (1+taxa_mensal) / 30,3)  # 30 dias
#        print(capital_final_dia)
        lucro_dia = round(capital_inicial[dia-1] - (capital_inicial[dia-1] * ((taxa_mensal) / 30)),3)
        capital_inicial.append(capital_final_dia)
        
    capital_final.append(capital_final_dia)
    lucro_diario.append(lucro_dia)
    
#capital_inicial += incremento_mensal

print('\n')
# Criando o DataFrame
data = {'Dia': dias, 'Capital Inicial': capital_inicial, 'Lucro DIA': lucro_diario, 'Capital Final': capital_final}

#print(f'{x}\n' for x in data)

for n in data:
    print(n, end='         ')
print('')

for n in range(30):
    print(f'{data["Dia"][n]}        {" " if n < 10 else ""}   {data["Capital Inicial"][n]}            {data["Lucro DIA"][n]}               {data["Capital Final"][n]}')

import numpy as np
import plotly.graph_objects as go
import json

# 1. Capital inicial
capital_inicial = 1_000_000

# 2. Cenários de retorno em 2 meses
cenarios = {
    "Conservador": 0.02,  # 2%
    "Médio": 0.05,        # 5%
    "Otimista": 0.08      # 8%
}

# 3. Calcular evolução diária
dias = np.arange(0, 61)  # 60 dias ~ 2 meses
resultados = {}
fig = go.Figure()

for nome, retorno_total in cenarios.items():
    retorno_diario = (1 + retorno_total) ** (1/60) - 1
    capital_diario = capital_inicial * (1 + retorno_diario) ** dias

    resultados[nome] = {
        "retorno_percentual": round(retorno_total * 100, 2),
        "capital_final": round(capital_diario[-1], 2),
        "ganho_total": round(capital_diario[-1] - capital_inicial, 2)
    }

    # Adicionar linha ao gráfico interativo
    fig.add_trace(go.Scatter(
        x=dias,
        y=capital_diario-1_000_000,
        mode="lines+markers",
        name=f"{nome} ({retorno_total*100:.0f}%)",
        hovertemplate="Dia %{x}<br>Capital: R$ %{y:.2f}<extra></extra>"
    ))

# 4. Configurar tema escuro
fig.update_layout(
    title="Evolução do Capital em Estratégia com Opções (2 meses)",
    xaxis_title="Dias",
    yaxis_title="Capital (R$)",
    template="plotly_dark",
    hovermode="x unified"
)

# 5. Exibir resultados em JSON
print(json.dumps(resultados, indent=2))

# 6. Mostrar gráfico interativo
fig.show()

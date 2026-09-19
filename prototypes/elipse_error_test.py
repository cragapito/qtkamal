import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import UnivariateSpline

n_simulacoes = 3
theta_dense = np.linspace(0, 2*np.pi, 300)
todas_as_curvas = []

fig, ax = plt.subplots(subplot_kw={'projection': 'polar'}, figsize=(8, 8))

for i in range(n_simulacoes):
    # 1. 4 pontos aleatórios ordenados de 0 a 360°
    angles_deg = np.sort(np.random.uniform(0, 360, 4))
    theta = np.deg2rad(angles_deg)
    r_medido = np.random.uniform(3.0, 7.0, size=4)
    
    # 2. Truque multi-voltas (3 voltas completas: passado, presente e futuro)
    theta_ext = np.concatenate([theta - 2*np.pi, theta, theta + 2*np.pi])
    r_ext = np.concatenate([r_medido, r_medido, r_medido])
    
    sort_idx = np.argsort(theta_ext)
    
    # 3. Usamos UnivariateSpline com k=3 (cúbica) e um leve 's=0.5' 
    # Isso remove qualquer descontinuidade na emenda de 0°/360° sem encolher a curva
    spline = UnivariateSpline(theta_ext[sort_idx], r_ext[sort_idx], k=3, s=0.5)
    
    # Avaliamos estritamente na volta principal (0 a 2*pi)
    r_smooth = spline(theta_dense)
    r_smooth = np.maximum(0.1, r_smooth)
    
    todas_as_curvas.append(r_smooth)
    ax.plot(theta_dense, r_smooth, color='royalblue', alpha=0.04, linewidth=1)

# Estatísticas das 200 simulações
todas_as_curvas = np.array(todas_as_curvas)
curva_media = np.mean(todas_as_curvas, axis=0)
curva_superior = np.percentile(todas_as_curvas, 95, axis=0)
curva_inferior = np.percentile(todas_as_curvas, 5, axis=0)

ax.plot(theta_dense, curva_media, color='darkred', linewidth=3, label='Média Periódica Suavizada')
ax.fill_between(theta_dense, curva_inferior, curva_superior, color='crimson', alpha=0.15, label='Intervalo de Confiança (95%)')

ax.set_theta_zero_location("N")
ax.set_theta_direction(-1)
ax.set_title(f"Teste de incerteza da localização ({n_simulacoes} execuções)", va='bottom', fontsize=12, fontweight='bold', pad=20)
ax.legend(loc='upper right', bbox_to_anchor=(1.4, 1.1))

plt.show()
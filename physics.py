import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.gridspec import GridSpec
import os

figures_dir = os.path.expanduser("~/Desktop/figures")
os.makedirs(figures_dir, exist_ok=True)

# ─────────────────────────────────────────────
# TRANSMISSION COEFFICIENT (WKB approximation)
# T = exp(-2 * kappa * L)
# kappa = sqrt(2m(V0-E)) / hbar
# ─────────────────────────────────────────────

hbar = 1.0545718e-34   # J·s
m    = 9.10938e-31     # electron mass kg
eV   = 1.60218e-19     # 1 eV in Joules

def kappa(V0_eV, E_eV):
    """Decay constant inside barrier"""
    delta = (V0_eV - E_eV) * eV
    return np.sqrt(2 * m * delta) / hbar

def transmission(V0_eV, E_eV, L_nm):
    """WKB tunneling transmission coefficient"""
    if E_eV >= V0_eV:
        return 1.0
    k = kappa(V0_eV, E_eV)
    L = L_nm * 1e-9
    return np.exp(-2 * k * L)

# ─────────────────────────────────────────────
# FIGURE 1: Conceptual diagram — particle + barrier
# ─────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(9, 4))
ax.set_xlim(0, 10)
ax.set_ylim(-0.5, 3)

# Barrier
barrier = mpatches.FancyBboxPatch((4, 0), 2, 2.0,
    boxstyle="square,pad=0", linewidth=1.5,
    edgecolor='#2c3e50', facecolor='#bdc3c7', alpha=0.7)
ax.add_patch(barrier)
ax.text(5, 2.15, r'$V_0$', ha='center', fontsize=13, color='#2c3e50', fontweight='bold')
ax.text(5, 1.0, 'Barrier\n(width L)', ha='center', fontsize=10, color='#2c3e50')

# Incoming wave (left)
x_left = np.linspace(0.3, 3.8, 300)
y_left = 0.5 * np.sin(2 * np.pi * x_left / 0.8) + 1.2
ax.plot(x_left, y_left, color='#2980b9', lw=2, label='Incident wave')

# Reflected wave (smaller amplitude)
x_ref = np.linspace(0.3, 3.5, 300)
y_ref = 0.18 * np.sin(2 * np.pi * x_ref / 0.8 + np.pi) + 0.35
ax.plot(x_ref, y_ref, color='#e74c3c', lw=1.8, linestyle='--', label='Reflected wave')

# Evanescent inside barrier
x_bar = np.linspace(4.05, 5.95, 100)
y_bar = 0.35 * np.exp(-0.9*(x_bar-4)) * np.sin(2*np.pi*x_bar/0.8) + 1.2
ax.plot(x_bar, y_bar, color='#8e44ad', lw=1.5, linestyle=':', label='Evanescent (inside barrier)')

# Transmitted wave (right, smaller)
x_right = np.linspace(6.2, 9.7, 300)
y_right = 0.18 * np.sin(2 * np.pi * x_right / 0.8) + 1.2
ax.plot(x_right, y_right, color='#27ae60', lw=2, label='Transmitted wave')

# Arrow showing direction
ax.annotate('', xy=(3.6, 1.55), xytext=(2.8, 1.55),
    arrowprops=dict(arrowstyle='->', color='#2980b9', lw=1.8))
ax.annotate('', xy=(7.2, 1.55), xytext=(6.4, 1.55),
    arrowprops=dict(arrowstyle='->', color='#27ae60', lw=1.8))

# Energy level
ax.axhline(y=1.2, xmin=0.03, xmax=0.4, color='#f39c12', lw=1.5, linestyle='-.')
ax.axhline(y=1.2, xmin=0.62, xmax=0.97, color='#f39c12', lw=1.5, linestyle='-.')
ax.text(0.15, 1.28, 'E', color='#f39c12', fontsize=12, fontweight='bold')

ax.set_xlabel('Position', fontsize=11)
ax.set_ylabel('Wave Amplitude / Potential', fontsize=11)
ax.set_title('Quantum Tunneling — Wave Behavior at a Potential Barrier', fontsize=12, fontweight='bold')
ax.legend(loc='upper right', fontsize=9)
ax.set_xticks([])
ax.set_yticks([])
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
plt.tight_layout()
plt.savefig(os.path.join(figures_dir, 'fig1_concept.png'), dpi=150, bbox_inches='tight')fil  
plt.close()
print("Fig 1 done")

# ─────────────────────────────────────────────
# FIGURE 2: T vs Barrier Width (varying width)
# ─────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(8, 5))

L_range = np.linspace(0.01, 3.0, 500)   # nm
V0 = 5.0   # eV
energies = [1.0, 2.0, 3.0, 4.0]
colors = ['#e74c3c', '#e67e22', '#2980b9', '#27ae60']

for E, c in zip(energies, colors):
    T_vals = [transmission(V0, E, L) for L in L_range]
    ax.semilogy(L_range, T_vals, color=c, lw=2, label=f'E = {E} eV')

ax.set_xlabel('Barrier Width L (nm)', fontsize=12)
ax.set_ylabel('Transmission Coefficient T (log scale)', fontsize=12)
ax.set_title(f'Effect of Barrier Width on Tunneling Probability\n(Barrier Height V₀ = {V0} eV)', fontsize=12, fontweight='bold')
ax.legend(fontsize=11)
ax.grid(True, which='both', alpha=0.3)
ax.set_xlim(0, 3)
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
plt.tight_layout()
plt.savefig(os.path.join(figures_dir, 'fig2_width.png'), dpi=150, bbox_inches='tight')
plt.close()
print("Fig 2 done")

# ─────────────────────────────────────────────
# FIGURE 3: T vs Barrier Height (varying height)
# ─────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(8, 5))

V0_range = np.linspace(1.01, 10.0, 500)  # eV
E_fixed = 1.0  # eV
widths = [0.3, 0.6, 1.0, 1.5]
colors2 = ['#9b59b6', '#3498db', '#e74c3c', '#2ecc71']

for L, c in zip(widths, colors2):
    T_vals = [transmission(V0, E_fixed, L) for V0 in V0_range]
    ax.semilogy(V0_range, T_vals, color=c, lw=2, label=f'L = {L} nm')

ax.axvline(x=E_fixed, color='gray', linestyle='--', lw=1.5, label=f'E = {E_fixed} eV (particle energy)')
ax.set_xlabel('Barrier Height V₀ (eV)', fontsize=12)
ax.set_ylabel('Transmission Coefficient T (log scale)', fontsize=12)
ax.set_title(f'Effect of Barrier Height on Tunneling Probability\n(Particle Energy E = {E_fixed} eV)', fontsize=12, fontweight='bold')
ax.legend(fontsize=11)
ax.grid(True, which='both', alpha=0.3)
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
plt.tight_layout()
plt.savefig(os.path.join(figures_dir, 'fig3_height.png'), dpi=150, bbox_inches='tight')
plt.close()
print("Fig 3 done")

# ─────────────────────────────────────────────
# FIGURE 4: Heatmap — T as function of both L and V0
# ─────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(8, 6))

L_vals  = np.linspace(0.1, 2.0, 100)
V0_vals = np.linspace(1.5, 8.0, 100)
E_fixed = 1.0

T_matrix = np.zeros((len(V0_vals), len(L_vals)))
for i, V0 in enumerate(V0_vals):
    for j, L in enumerate(L_vals):
        T_matrix[i, j] = transmission(V0, E_fixed, L)

# Log scale for visibility
T_log = np.log10(T_matrix + 1e-300)

im = ax.contourf(L_vals, V0_vals, T_log, levels=40, cmap='plasma')
cbar = fig.colorbar(im, ax=ax)
cbar.set_label('log₁₀(T) — Tunneling Probability', fontsize=10)
ax.set_xlabel('Barrier Width L (nm)', fontsize=12)
ax.set_ylabel('Barrier Height V₀ (eV)', fontsize=12)
ax.set_title(f'Tunneling Probability Map\n(Particle Energy E = {E_fixed} eV)', fontsize=12, fontweight='bold')
plt.tight_layout()
plt.savefig(os.path.join(figures_dir, 'fig4_heatmap.png'), dpi=150, bbox_inches='tight')
plt.close()
print("Fig 4 done")

print(f"All figures saved to {figures_dir}")

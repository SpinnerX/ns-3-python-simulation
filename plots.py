import numpy as np
import matplotlib.pyplot as plt

# Set random seed for reproducibility
np.random.seed(42)

# System Parameters
N = 16            # Number of reflective elements for IRS
num_transmitters = 2        # Tx1 and Tx2
num_receivers = 4        # Rx1, Rx2, Rx3, Rx4

# Generate Rayleigh Fading Channel Matrices (Complex Gaussian)
# Translated from MATLAB's (randn + 1j*randn)/sqrt(2) to Python
h_dir = (np.random.randn(num_transmitters, num_receivers) + 1j * np.random.randn(num_transmitters, num_receivers)) / np.sqrt(2)
H_irs = (np.random.randn(N, num_transmitters) + 1j * np.random.randn(N, num_transmitters)) / np.sqrt(2)
G_irs = (np.random.randn(num_receivers, N) + 1j * np.random.randn(num_receivers, N)) / np.sqrt(2)

# Power allocations and noise variance
p_tx1 = 1.0
p_tx2 = 1.0
sigma2 = 0.001  # Noise power

# Function to compute SINR for each receiver given the IRS phase shifts
def compute_sinr(Phi, p_tx1, p_tx2):
    sinr = np.zeros(num_receivers)
    for k in range(num_receivers):
        # Calculate effective channel values
        h_eff_1 = h_dir[0, k] + np.dot(G_irs[k, :], np.dot(Phi, H_irs[:, 0]))
        h_eff_2 = h_dir[1, k] + np.dot(G_irs[k, :], np.dot(Phi, H_irs[:, 1]))
        
        if k < 2:  # System A (Receivers 1 and 2)
            signal_power = p_tx1 * np.abs(h_eff_1)**2
            interference_power = p_tx2 * np.abs(h_eff_2)**2
        else:      # System B (Receivers 3 and 4)
            signal_power = p_tx2 * np.abs(h_eff_2)**2
            interference_power = p_tx1 * np.abs(h_eff_1)**2
            
        sinr[k] = signal_power / (interference_power + sigma2)
    return sinr

# Creating the simple random phase shifts
theta_init = np.random.uniform(0, 2 * np.pi, N)
Phi_init = np.diag(np.exp(1j * theta_init))
sinr_initial = compute_sinr(Phi_init, p_tx1, p_tx2)

# Performing a simple phase alignment heuristic
# Align the IRS phase shift to match the cascaded path phase for system A 
theta_opt = np.angle(np.conj(G_irs[0, :]) * np.conj(H_irs[:, 0]))
Phi_opt = np.diag(np.exp(1j * theta_opt))
sinr_optimized = compute_sinr(Phi_opt, p_tx1, p_tx2)

# Display Results
print("=" * 50)
print(f"{'Receiver':<12} | {'Initial SINR (dB)':<17} | {'Optimized SINR (dB)':<17}")
print("-" * 50)

# Convert SINR to dB for better readability
for k in range(num_receivers):
    init_db = 10 * np.log10(sinr_initial[k])
    opt_db = 10 * np.log10(sinr_optimized[k])
    print(f"Rx{k+1:<9} | {init_db:>16.2f} dB | {opt_db:>16.2f} dB")
print("=" * 50)

# Plotting the results for the receivers
receivers = ['Rx1 (Sys A)', 'Rx2 (Sys A)', 'Rx3 (Sys B)', 'Rx4 (Sys B)']
x = np.arange(len(receivers))
width = 0.35

# Creating the visual bar plot to compare initial and optimized SINR values
fig, axis = plt.subplots(figsize=(8, 5))
axis.bar(x - width/2, 10 * np.log10(sinr_initial), width, label='Initial (Random Phases)', color='gray')
axis.bar(x + width/2, 10 * np.log10(sinr_optimized), width, label='Optimized (Aligned Phases)', color='#0F52BA')

axis.set_ylabel('SINR (dB)', fontsize=12)
axis.set_title('IRS Coexistence Performance Comparison', fontsize=14)
axis.set_xticks(x)
axis.set_xticklabels(receivers)
axis.legend()
axis.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig('irs_sinr_comparison.png')
plt.show()

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.141592653589793

int main() {
    // Define parameters
    double I = 1;       // Constant input current
    double a = 0.7;     // Positive constant
    double b = 0.1;     // Positive constant
    double c = -0.5;    // Positive constant
    double tau = 30;    // Time constant

    double dt = 0.1;    // Time step (ms)
    double T = 500;     // Total simulation time (ms)

    // Initial conditions
    double V = -0.6;    // Initial membrane voltage
    double W = 0.2;     // Initial recovery variable

    // Calculate integer array size based on simulation parameters
    int array_size = (int)(T / dt + 1);

    // Declare arrays to store V and W values (using dynamic allocation)
    double *V_array = (double *)malloc(array_size * sizeof(double));
    double *W_array = (double *)malloc(array_size * sizeof(double));

    // Check if memory allocation was successful
    if (V_array == NULL || W_array == NULL) {
        printf("Error allocating memory for arrays!\n");
        return 1;
    }

    // Store initial values
    V_array[0] = V;
    W_array[0] = W;

    // Open output file for writing data
    FILE *fp = fopen("fhn_simulation_data1.dat", "w");
    if (fp == NULL) {
        printf("Error opening file for writing data!\n");
        free(V_array);
        free(W_array);
        return 1;
    }

    // (Optional) Write header row
    fprintf(fp, "# Time (ms) \t Voltage \t Recovery Variable\n");

    // Open output file for spike data
    FILE *spike_fp = fopen("spikes.dat", "w");
    if (spike_fp == NULL) {
        printf("Error opening file for writing spike data!\n");
        free(V_array);
        free(W_array);
        fclose(fp);
        return 1;
    }

    // Define threshold voltage for spike detection
    double threshold = 0.1; // Adjust this value as needed

    // Simulation loop
    for (int i = 1; i < array_size; i++) { // iterate until array_size-1 to avoid out-of-bounds access
        double prev_V = V; // Store previous voltage for spike detection

        // Calculate intermediate values (RK4)
        double k1_V = dt * (I - pow(V, 3) / 3 + V * (W - a));
        double k1_W = dt * (b * (V - c) / tau);

        double k2_V = dt * (I - pow(V + k1_V / 2, 3) / 3 + (V + k1_V / 2) * (W - a));
        double k2_W = dt * (b * ((V + k1_V / 2) - c) / tau);

        double k3_V = dt * (I - pow(V + k2_V / 2, 3) / 3 + (V + k2_V / 2) * (W - a));
        double k3_W = dt * (b * ((V + k2_V / 2) - c) / tau);

        double k4_V = dt * (I - pow(V + k3_V, 3) / 3 + (V + k3_V) * (W - a));
        double k4_W = dt * (b * ((V + k3_V) - c) / tau);

        // Update variables
        V = V + (k1_V + 2 * k2_V + 2 * k3_V + k4_V) / 6;
        W = W + (k1_W + 2 * k2_W + 2 * k3_W + k4_W) / 6;

        // Store V and W values
        V_array[i] = V;
        W_array[i] = W;

        // Write data to file
        fprintf(fp, "%lf\t%lf\t%lf\n", i * dt, V, W);

        // Detect spike (optional)
        if (V > threshold && prev_V <= threshold) {
            // Spike detected, write time and voltage to spike data file
            fprintf(spike_fp, "%lf\t%lf\n", i * dt, V);
        }
    }

    // Close output files
    fclose(fp);
    fclose(spike_fp);

    // Free the allocated memory
    free(V_array);
    free(W_array);

    printf("Simulation finished! Data written to 'fhn_simulation_data1.dat' and 'spikes1.dat'\n");
    return 0;
}

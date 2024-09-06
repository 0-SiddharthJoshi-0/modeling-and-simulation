#include <stdio.h>
#include <math.h>

// Function to calculate dopamine level at time t
double update_dopamine(double D1, double k1, double dt) {
    return D1 * exp(-k1 * dt); // Exponential decay
}

// Function to calculate motor symptom severity at time t
double update_symptoms(double D1, double D2, double k2, double dt) {
    return D2 + k2 * dt * (D1 - D2); // Increases when dopamine is below threshold
}

int main() {
    // Define variables and parameters
    double D1_initial, D2_initial, D2_thresh, dt, k1, k2, T;

    // Set initial values
    D1_initial = 100.0;     // Initial dopamine level
    D2_initial = 0.5;       // Initial motor symptom severity
    D2_thresh = 30.0;       // Threshold dopamine level for symptom manifestation
    dt = 0.1;               // Time step for simulation (e.g., 0.1 day)
    k1 = 0.1;               // Rate constant for dopamine loss (1/time)
    k2 = 0.05;              // Rate constant for symptom progression (1/time)
    T = 10.0;               // Total duration of simulation (e.g., 10 days)

    // Open file for writing
    FILE *fp = fopen("parkinson_simulation.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write header to file
    fprintf(fp, "Time,Dopamine,Motor_Symptoms\n");

    // Simulation loop
    double D1 = D1_initial;
    double D2 = D2_initial;
    for (double t = 0; t <= T; t += dt) {
        // Update dopamine level
        D1 = update_dopamine(D1, k1, dt);

        // Update motor symptom severity
        D2 = update_symptoms(D1, D2, k2, dt);

        // Write data to file
        fprintf(fp, "%.1f,%.1f,%.1f\n", t, D1, D2);
    }

    // Close the file
    fclose(fp);

    printf("Simulation data saved to 'parkinson_simulation.csv'\n");

    return 0;
}

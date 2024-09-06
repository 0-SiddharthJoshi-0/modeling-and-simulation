#include <stdio.h>

// FHN parameters
#define c_value 0.7
#define a_value 0.8
#define b_value 0.08
#define epsilon_value 0.01
#define I_value 0.5

// Time parameters
#define dt_value 0.01  // Time step
#define T_value 1000     // Total simulation time
#define num_steps_value (int)(T_value / dt_value)

// Function to calculate the membrane potential derivative
double dv_dt(double v, double w, double I) {
    return c_value * (v - (1.0/3.0) * v * v * v - w + I);
}

// Function to calculate the recovery variable derivative
double dw_dt(double v, double w) {
    return epsilon_value * (v + a_value - b_value * w);
}

// Fourth-order Runge-Kutta method
void rk4(double *v, double *w, double *time) {
    double k1_v, k2_v, k3_v, k4_v;
    double k1_w, k2_w, k3_w, k4_w;
    int i;

    for (i = 0; i < num_steps_value - 1; i++) {
        k1_v = dt_value * dv_dt(v[i], w[i], I_value);
        k1_w = dt_value * dw_dt(v[i], w[i]);

        k2_v = dt_value * dv_dt(v[i] + 0.5 * k1_v, w[i] + 0.5 * k1_w, I_value);
        k2_w = dt_value * dw_dt(v[i] + 0.5 * k1_v, w[i] + 0.5 * k1_w);

        k3_v = dt_value * dv_dt(v[i] + 0.5 * k2_v, w[i] + 0.5 * k2_w, I_value);
        k3_w = dt_value * dw_dt(v[i] + 0.5 * k2_v, w[i] + 0.5 * k2_w);

        k4_v = dt_value * dv_dt(v[i] + k3_v, w[i] + k3_w, I_value);
        k4_w = dt_value * dw_dt(v[i] + k3_v, w[i] + k3_w);

        v[i+1] = v[i] + (1.0/6.0) * (k1_v + 2 * k2_v + 2 * k3_v + k4_v);
        w[i+1] = w[i] + (1.0/6.0) * (k1_w + 2 * k2_w + 2 * k3_w + k4_w);

        time[i+1] = time[i] + dt_value;
    }
}

int main() {
    // Open file for writing
    FILE *file = fopen("fhn_data_rk4.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Arrays to store results
    double v[num_steps_value];
    double w[num_steps_value];
    double time[num_steps_value];

    // Initialize
    v[0] = -1.0;
    w[0] = 0.0;
    time[0] = 0.0;

    // Runge-Kutta integration
    rk4(v, w, time);

    // Write data to file
    int i;
    for (i = 0; i < num_steps_value; i++) {
        fprintf(file, "%.6f %.6f %.6f\n", time[i], v[i], w[i]);
    }

    // Close file
    fclose(file);

    printf("Simulation data saved in 'fhn_data_rk4.txt'.\n");

    return 0;
}

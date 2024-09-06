#include <stdio.h>

void simulate_step(double *healthy, double *amyloid, double *tau, double ka, double kt, double d_n, double dt) {
  double d_healthy, d_amyloid, d_tau;

  // Calculate rates of change
  d_amyloid = ka * *healthy - d_n * *amyloid;
  d_tau = kt * *amyloid - d_n * *tau;
  d_healthy = - (d_amyloid + d_tau); // Assuming all deaths contribute to pathology

  // Update population in each compartment
  *healthy += d_healthy * dt;
  *amyloid += d_amyloid * dt;
  *tau += d_tau * dt;
}

int main() {
  // Set initial conditions (modify as needed)
  double healthy_neurons = 1.0;
  double amyloid_neurons = 0.0;
  double tau_neurons = 0.0;

  // Simulation parameters (modify for different scenarios)
  double ka = 0.01; // Rate of amyloid-β accumulation
  double kt = 0.02; // Rate of tau phosphorylation
  double d_n = 0.001; // Rate of neuronal death
  double dt = 0.1; // Time step (in years, adjust for desired simulation duration)

  // Simulation duration (adjust for desired time frame)
  double simulation_time = 10.0; // Simulation duration (years)

  // Open file for data storage (modify filename if desired)
  FILE *data_file = fopen("simulation_data.dat", "w");

  // Print initial state
  printf("Time: 0.0\n");
  printf("Healthy Neurons: %.2lf\n", healthy_neurons);
  printf("Neurons with Amyloid-β: %.2lf\n", amyloid_neurons);
  printf("Neurons with Tau Tangles: %.2lf\n\n", tau_neurons);

  // Run simulation loop
  for (double t = dt; t <= simulation_time; t += dt) {
    simulate_step(&healthy_neurons, &amyloid_neurons, &tau_neurons, ka, kt, d_n, dt);

    // Store data for visualization
    fprintf(data_file, "%lf %.2lf %.2lf %.2lf\n", t, healthy_neurons, amyloid_neurons, tau_neurons);
  }

  fclose(data_file); // Close the data file

  return 0;
}

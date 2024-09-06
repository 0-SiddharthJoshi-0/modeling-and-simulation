#include <stdio.h>
#include <math.h>

#define dt 0.1  // Time step (adjustable)

double k12, k21, k_prog;  // Model parameters

// Function representing medication input (replace with your function if needed)
double medication(double t) {
  return 0.5;  // Constant medication effect (adjustable)
}

int main() {
  double C1, C2, dC1dt, dC2dt, t;

  // Set model parameters (replace with desired values)
  k12 = 0.1;
  k21 = 0.01;  // Optional feedback (comment out if not used)
  k_prog = 0.02;

  // Initial conditions (replace with desired values)
  C1 = 1.0;  // Initial dopamine level
  C2 = 0.0;  // Initial motor symptom severity
  t = 0.0;

  printf("Time (s), Dopamine (C1), Motor Symptoms (C2)\n");

  // Simulation loop
  while (t < 100) { // Change loop limit for desired simulation duration
    // Calculate rate of change for dopamine
    dC1dt = -k12 * C1 + medication(t);

    // Update dopamine level
    C1 += dC1dt * dt;

    // Calculate rate of change for motor symptoms
    dC2dt = -k21 * C1 + k_prog + rand() / (double)RAND_MAX;  // Include noise

    // Update motor symptoms
    C2 += dC2dt * dt;

    // Print results
    printf("%f, %f, %f\n", t, C1, C2);

    // Update time
    t += dt;
  }

  return 0;
}

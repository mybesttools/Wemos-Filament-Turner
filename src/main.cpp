/*
 * Filament Turner Controller
 * Wemos D1 Clone + 28BYJ-48 Stepper Motor + ULN2003AN Driver
 * 
 * Rotates 180 degrees every 30 minutes in the same direction
 * 
 * Pin Connections (Wemos D1 -> ULN2003AN):
 * D1 (GPIO5)  -> IN1
 * D2 (GPIO4)  -> IN2
 * D3 (GPIO0)  -> IN3
 * D4 (GPIO2)  -> IN4
 * GND -> GND
 * 5V -> 5V (ULN2003AN power)
 * 
 * Motor Specifications (28BYJ-48):
 * - 4076 steps per full rotation (360°)
 * - 2048 steps for 180° rotation
 * - 5-12V operation via ULN2003AN
 */

#include <Arduino.h>

// Stepper motor pin definitions
#define IN1 D1  // GPIO5
#define IN2 D2  // GPIO4
#define IN3 D3  // GPIO0
#define IN4 D4  // GPIO2

// Motor control constants
#define STEPS_PER_ROTATION 4076  // Full rotation
#define STEPS_FOR_180 2048       // 180 degree rotation
#define DELAY_BETWEEN_STEPS 2    // Milliseconds (slower = more torque)

// Timing constants
#define ROTATION_INTERVAL 30 * 60 * 1000  // 30 minutes in milliseconds
unsigned long lastRotationTime = 0;

// Stepper sequence for half-step mode (smoother motion)
int stepSequence[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

int currentStep = 0;

void rotateStepper(int steps);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Configure motor pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initialize all pins to LOW
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
  Serial.println("\nFilament Turner Started");
  Serial.println("Will rotate 180° every 30 minutes");
  
  // Do first rotation immediately on startup
  Serial.println("Performing initial rotation...");
  rotateStepper(STEPS_FOR_180);
  Serial.println("Initial rotation complete");
  
  // Set timer for next rotation
  lastRotationTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Check if 30 minutes have passed
  if (currentTime - lastRotationTime >= ROTATION_INTERVAL) {
    Serial.println("Rotating...");
    rotateStepper(STEPS_FOR_180);
    lastRotationTime = currentTime;
    Serial.println("Rotation complete");
  }
  
  // Optional: Add small delay to prevent overwhelming the loop
  delay(1000);
}

/*
 * Rotates the stepper motor by the specified number of steps
 * Uses half-step mode for smoother motion and better torque
 */
void rotateStepper(int steps) {
  for (int i = 0; i < steps; i++) {
    // Set the coil states for current step
    digitalWrite(IN1, stepSequence[currentStep][0]);
    digitalWrite(IN2, stepSequence[currentStep][1]);
    digitalWrite(IN3, stepSequence[currentStep][2]);
    digitalWrite(IN4, stepSequence[currentStep][3]);
    
    delay(DELAY_BETWEEN_STEPS);
    
    // Move to next step in sequence
    currentStep = (currentStep + 1) % 8;  // Loop through 8 steps
  }
  
  // De-energize coils at the end
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

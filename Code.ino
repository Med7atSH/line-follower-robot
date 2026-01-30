// --- Motor Control Pins (L298N Driver) ---
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;

// --- Speed Control Pins (PWM) ---
int enA = 5;  // Enable Pin for Motor A
int enB = 10; // Enable Pin for Motor B

// --- IR Sensor Pins ---
int L_s = A3; // Left Sensor
int M_s = A2; // Middle Sensor
int R_s = A1; // Right Sensor

// --- Robot Speeds (Adjust as needed) ---
int N_speed = 180; // Normal Speed (Forward)
int R_speed = 235; // Rapid/Sharp Turn Speed
int F_speed = 190; // Fast/Slow Turn Speed

void setup() {
  // Set Motor pins as Outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Set Sensor pins as Inputs
  pinMode(L_s, INPUT);
  pinMode(M_s, INPUT);
  pinMode(R_s, INPUT);
}

void loop() {
  // Read sensor values (1 = Line/Black, 0 = No Line/White - depends on sensor type)
  // Note: Usually IR sensors give 1 on black line and 0 on white surface, or vice versa.
  // Adjust logic below if your sensors logic is inverted.
  bool L = digitalRead(L_s);
  bool M = digitalRead(M_s);
  bool R = digitalRead(R_s);

  // --- Movement Logic ---
  
  // 1. Forward: Middle sensor is on the line
  if (L == 0 && R == 0 && M == 1) {
    forward();
  } 
  // 2. Sharp Left Turn: Left sensor is on the line
  else if (L == 1 && R == 0 && M == 1) {
    left();
  } 
  // 3. Slow Left Turn (Correction)
  else if (L == 1 && R == 0 && M == 0) {
    slowleft();
  } 
  // 4. Sharp Right Turn: Right sensor is on the line
  else if (L == 0 && R == 1 && M == 1) {
    Right();
  } 
  // 5. Slow Right Turn (Correction)
  else if (L == 0 && R == 1 && M == 0) {
    slowRight();
  }
  // 6. Stop: All sensors on the line (Intersection/End)
  else if (L == 1 && R == 1 && M == 1) {
    Stop();
  }
}

// --- Movement Functions ---

void forward() {
  // Left Motor -> Forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // Right Motor -> Forward
  digitalWrite(in3, LOW); 
  digitalWrite(in4,
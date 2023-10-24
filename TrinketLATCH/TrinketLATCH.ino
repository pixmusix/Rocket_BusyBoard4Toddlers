//https://stackoverflow.com/questions/30856751/atmega328p-avrdude-could-not-find-usbtiny-device-0x1781-0xc

const int Q = 3;
const int S = 2;
const int R = 0;
const int B = 4;
bool LATCHED = false;
bool PHASOR = false;

void iamHere() {
  for (byte i = 0; i < 12; i++) {
    digitalWrite(LED_BUILTIN, i % 2);
    delay(125);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  iamHere(); //Feedback to say code started.
}

void loop() {
  // Let's use the BuiltinLED to ensure we are synced
  digitalWrite(LED_BUILTIN, digitalRead(S));

  /* For this SR latch, we only care about the rising edge of the Set Pin. 
  See this timing diagram below for correct behaviour
                    ----
  R                  |  |
  -------------------    -----------------------
          -------------------           --------
  S      |                   |          |
  -------                     ----------
          -----------                    -------
  L      |           |                  |
  -------             ------------------
  We achieve this by basing the Latch, not on the set pin, but on a PHASOR.
  LATCHED is only allowed to check the state of PHASOR while the set pin is HIGH.
  S and R must both be LOW for at least one cycle in order to prime the PHASOR. */


  if (digitalRead(S)) {
    LATCHED = PHASOR;
  } else {
    PHASOR = true;
  }

  if (digitalRead(R)) {
    LATCHED = false;
    PHASOR = false;
  }

  digitalWrite(Q, LATCHED);
}
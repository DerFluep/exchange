const int ledPin = 13;

const double f_min = 1.0 / 1000.0;
const double f_max = 1.0 / 20.0;

class Led {
public:
  unsigned long last_toggle = 0;
  unsigned long last_update = 0;
  int n_steps = 1000;
  double lerp_val = 0.0;
  double change = 1.0 / n_steps;
  void update();
};

void Led::update() {
  unsigned long now = micros();

  if (now - last_update >= 1000) {
    lerp_val += change;
    if (lerp_val >= 1.0) {
      lerp_val = 1.0;
      change *= -1;
    } else if (lerp_val <= 0.0) {
      lerp_val = 0.0;
      change *= -1;
    }
    last_update = micros();
  }

  double freq = f_min + lerp_val * (f_max - f_min);
  unsigned long interval = (unsigned long)(1000.0 / freq);

  if (now - last_toggle >= interval) {
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
    last_toggle = micros();
  }
}

Led led;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  led.update();
}

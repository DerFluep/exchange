const int ledPin = 13;

const double f_min = 1.0 / 1000.0;  // 0.001
const double f_max = 1.0 / 10.0;    // 0.02

long counting = 0;

class Led {
public:
  unsigned long last_toggle = 0;
  unsigned long last_update = 0;
  int n_steps = 500;
  int counting = 0;
  double lerp_val = 0.0;
  double change = 0.001;
  void update();
};

void Led::update() {
  if (n_steps > 0) {
    unsigned long now = micros();

    // excelerate for 1s
    if (now - last_update >= 1000) {
      lerp_val += change;
      if (lerp_val >= 1.0) {
        change = 0.0;
      } else if (lerp_val <= 0.0) {
        lerp_val = 0.0;
      }
      last_update = micros();
    }

    if (n_steps < 50) {
      change = -0.001;
    }

    double freq = f_min + lerp_val * (f_max - f_min);
    unsigned long interval = (unsigned long)(1000.0 / freq);

    if (now - last_toggle >= interval) {
      digitalWrite(ledPin, HIGH);
      delay(10);
      digitalWrite(ledPin, LOW);
      n_steps--;
      counting++;
      last_toggle = micros();
    }
  } else {
    change = 0.001;
    Serial.println(counting);
  }
}

Led led;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() {
  led.update();
}

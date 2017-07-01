// default mode
byte mode;

#define R 0
#define G 1
#define B 2
#define DEBUG 0


byte ledPins[] = { D1, D2, D3 };
word currentColor[] = { 0x0, 0x0, 0x0 };
word desiredColor[] = { 0x0, 0x0, 0x0 };

long timestamp;


void setup() {
  Serial.begin(115200);

  pinMode(ledPins[R], OUTPUT);
  pinMode(ledPins[G], OUTPUT);
  pinMode(ledPins[B], OUTPUT);

  randomSeed(analogRead(0));

  testPattern();

  Serial.print("current mode: ");
  Serial.println(mode);

  timestamp = millis();

  mode = 0;


  initWifi();
}

void loop() {
  switch(mode){
    case 0: {
      if (millis() - timestamp > 5000) {
        do {
          desiredColor[R] = random(1024);
          desiredColor[G] = random(1024);
          desiredColor[B] = random(1024);
        } while((abs(desiredColor[R] - desiredColor[G]) < 300) ||
                (abs(desiredColor[G] - desiredColor[B]) < 300) ||
                (abs(desiredColor[R] - desiredColor[B]) < 300));

        fade_to(desiredColor[R], desiredColor[G], desiredColor[B]);
        timestamp = millis();
      }
      break;
    }
    case 1: {
      int period = 2000;
      int offset = 500;

      timestamp = millis();

      desiredColor[R] = 128+127*cos(2*PI/period*timestamp);
      desiredColor[G] = 128+127*cos(2*PI/period*(offset-timestamp));
      desiredColor[B] = 128+127*cos(2*PI/period*(2*offset-timestamp));

      render(desiredColor[R], desiredColor[G], desiredColor[B]);
      break;
    }
    case 2: {
      render(1024, 1024, 1024);
      delay(1000);
      break;
    }
    case 3: {
      render(desiredColor[R], desiredColor[G], desiredColor[B]);
      delay(10);
      break;
    }
  };
  handleClient();
}

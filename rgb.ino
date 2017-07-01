int cent = 1;

void testPattern(){
  render(512,0,0);
  delay(500);
  render(0,512,0);
  delay(500);
  render(0,0,512);
  delay(500);
  render(0,0,0);
};

void setCurrent(int r, int g, int b) {
  currentColor[R] = r;
  currentColor[G] = g;
  currentColor[B] = b;
}

int move(int target, int destination) {
  if (target < destination) {
    target += cent;
  } else if (target > destination) {
    target -= cent;
  };
  return target;
};

void render(int r, int g, int b) {
  if ((currentColor[R] == r) &&
      (currentColor[G] == g) &&
      (currentColor[B] == b)) return;

  analogWrite(ledPins[R], constrain(r, 0, 1024));
  analogWrite(ledPins[G], constrain(g, 0, 1024));
  analogWrite(ledPins[B], constrain(b, 0, 1024));
  setCurrent(r, g, b);
};

void fade_to(int newR,  int newG, int newB){
  Serial.print("Moving to: ");
  Serial.print("R: ");
  Serial.print(newR);
  Serial.print(", G: ");
  Serial.print(newG);
  Serial.print(", B: ");
  Serial.println(newB);

  while ((newR != currentColor[R] ) &&
        ( newG != currentColor[G] ) &&
        ( newB != currentColor[B] )) {

        render(
          move(currentColor[R], newR),
          move(currentColor[G], newG),
          move(currentColor[B], newB)
        );

        delay(10);
  };
}

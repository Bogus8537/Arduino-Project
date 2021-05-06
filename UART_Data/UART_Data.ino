void setup() {
  Serial.begin(9600);
  Serial.println("==== Arduino -- Pi Connected ====");
}

void loop() {
  int data = random(0, 1000);

  Serial.print("Data : ");
  Serial.println(data);
  delay(2000);
}


int counter;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  counter = 10;

  Serial.print("Counter: ");
  Serial.println(counter);
}

void loop() {
  // put your main code here, to run repeatedly:
  counter++;

  Serial.print("Coutner: ");
  Serial.println(counter);

  delay(1000);

}

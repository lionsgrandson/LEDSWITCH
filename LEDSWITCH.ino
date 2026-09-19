int LED_SWITCH = 7;
int value = 0;
int dataPin = A0;

void setup() {
  pinMode(dataPin, INPUT);
  pinMode(LED_SWITCH, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  value = analogRead(dataPin);
Serial.println(value);
  if (value <= 300){ //check the threshold of mostly dry and check after water + 60 minutes 20% of that top number - bottom number is when to alert
    digitalWrite(LED_SWITCH, HIGH);
  }else{
    digitalWrite(LED_SWITCH, LOW); 
  }
}

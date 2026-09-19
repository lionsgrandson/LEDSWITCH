# Arduino Soil Moisture Sensor

Simple Arduino project that reads an analog soil-moisture sensor and switches an LED/output when the soil becomes too dry.

## Current Setup

- Soil moisture sensor analog output: `A0`
- LED / alert output: pin `7`
- Serial monitor baud rate: `9600`
- Current temporary dry threshold: `300`

## Current Code

```cpp
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

  if (value <= 300) {
    digitalWrite(LED_SWITCH, HIGH);
  } else {
    digitalWrite(LED_SWITCH, LOW);
  }
}
```

## Next Features

### 1. Determine the optimal moisture threshold

First, find the sensor value that represents the point where the plant should actually be watered.

This value will become the real moisture threshold instead of the temporary `300` value currently used in the code.

### 2. Measure the average daily moisture drop

Once the optimal threshold is known, collect sensor readings over several days.

Use those readings to calculate approximately how much the moisture reading drops per day.

For example:

```text
Day 1: 620
Day 2: 590
Day 3: 558
Day 4: 530
```

From multiple days of data, calculate an average daily drop.

This should make it possible to estimate how quickly the soil is drying instead of only knowing whether it is currently dry.

### 3. Estimate how many days remain before watering

Using:

- The current sensor reading
- The calibrated watering threshold
- The average daily moisture drop

Estimate approximately how many days remain before the plant reaches the watering threshold.

Conceptually:

```text
daysRemaining =
    (currentMoisture - moistureThreshold)
    / averageDailyDrop
```

This is only an estimate because soil moisture loss will not always be perfectly linear.

### 4. Add a digit countdown display

When the estimated time remaining falls below 10 days, display the estimated number of days remaining on a digit display.

The display should count:

```text
9
8
7
6
5
4
3
2
1
```

Before the estimate reaches 10 days, the display can remain off.

### 5. Increase the LED warning as watering gets closer

Keep the LED as a visual warning.

As the plant gets closer to needing water, make the warning more noticeable.

Possible behavior:

```text
More than 10 days remaining -> LED off
9-6 days remaining          -> occasional warning
5-3 days remaining          -> more frequent warning
2-1 days remaining          -> strong/frequent warning
Watering threshold reached  -> LED continuously on
```

The exact warning behavior can be adjusted after testing.

### 6. Add Wi-Fi connectivity

Later, connect the project to Wi-Fi using a Wi-Fi-capable microcontroller such as an ESP32 or ESP8266, or another compatible networking module.

This will allow the plant monitor to report its status remotely.

### 7. Send notifications

Once Wi-Fi is available, send a notification when the plant is getting close to needing water.

Possible notifications:

```text
Plant may need water in approximately 5 days.
Plant may need water tomorrow.
Plant needs water now.
```

The notification method can be decided later, such as a phone notification, webhook, Telegram message, email, or another service.

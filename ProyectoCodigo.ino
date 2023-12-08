#include <Servo.h>

#define SENSOR_HUMEDAD_PIN A0  // Cambia al pin analógico correspondiente
#define SERVO_PIN 9  // Cambia al pin correspondiente para el servo
#define TRIGGER_PIN 12  // Cambia al pin correspondiente para el pin de trigger del sensor ultrasónico
#define ECHO_PIN 11  // Cambia al pin correspondiente para el pin de echo del sensor ultrasónico
#define LED_VERDE 5  // Pin del LED verde
#define LED_ROJO 6  // Pin del LED rojo
#define DISTANCIA_MAXIMA 10  // Distancia máxima a la que se desactivará el servo en centímetros

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(SERVO_PIN);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Configura los LED
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
}

void loop() {
  int lecturaHumedad = analogRead(SENSOR_HUMEDAD_PIN);
  int distancia = medirDistancia();

  Serial.print("Lectura de humedad: ");
  Serial.println(lecturaHumedad);

  Serial.print("Distancia al objeto: ");
  Serial.println(distancia);

  // Si la humedad es alta y no hay obstáculos cercanos, activa el servo
  if (lecturaHumedad > 800 && distancia > DISTANCIA_MAXIMA) {
    activarServo();
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ROJO, LOW);
  } else {
    desactivarServo();
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, HIGH);
  }

  delay(1000);  // Ajusta el tiempo entre lecturas según sea necesario
}

void activarServo() {
  Serial.println("Humedad alta y sin obstáculos cercanos, activando servo motor");
  servoMotor.write(180);  // Ajusta el ángulo del servo según tus necesidades
  delay(1000);  // Puedes ajustar el tiempo que el servo se mantiene activado
}

void desactivarServo() {
  Serial.println("Humedad normal o con obstáculos cercanos, desactivando servo motor");
  servoMotor.write(0);  // Ajusta el ángulo del servo según tus necesidades
}

int medirDistancia() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;  // Convierte el tiempo a distancia en centímetros
}
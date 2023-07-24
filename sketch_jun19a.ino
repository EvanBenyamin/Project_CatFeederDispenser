#include <Servo.h>
#include <time.h>


const int trigPin = 10;  //sensor jarak 
const int echoPin = 11;  //sensor jarak echo
const int servoPin = 9;  //Servo
const int buttonPin = 2; // Button
const int buzzerPin = 3; // Piezo 

Servo myservo;

const int feedingDistance = 30; //trigger sensor jarak 

// Batas Interval buka tutup (miliseconds)
  const unsigned long feedingInterval = 120000; 
  const unsigned long dailyLimit = 86400000; // 1 hari
  int limit = 0;
// Variable untuk menyimpan waktu terakhir pemberian makanan
unsigned long lastFedTime = 0;

void playTone(int nada, int durasi) {
  tone(buzzerPin, nada, durasi);
  delay(durasi);
  noTone(buzzerPin);
  delay(50); // Jeda antara catatan musik
}


void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);

  // Inisialisasi pin trigger sebagai output dan echo sebagai input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inisialisasi pin servo
  myservo.attach(servoPin);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Mengirimkan sinyal ultrasonik
  digitalWrite(buzzerPin, LOW);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Menerima waktu pantulan ultrasonik
  long duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak berdasarkan waktu pantulan
  // Kecepatan suara dalam udara adalah 343 meter/detik atau 0.0343 cm/mikrodetik
  float distance = duration * 0.0343 / 2;

  // Menampilkan jarak ke Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Memeriksa apakah jarak memenuhi syarat untuk memberi makan kucing
  if (millis() - lastFedTime >= feedingInterval) {
    waduhMoment();
    feedCat();
    lastFedTime = millis();
  } 
  if (distance <= feedingDistance && limit <= 20){
    feedCat();
    limit++;
    delay(10000);
  } if (millis() == dailyLimit){
    limit=0;
  }

  
  if (millis() - lastFedTime >= dailyLimit) {
    feedCat();
    lastFedTime = millis();
  }

  {
  int buttonState = digitalRead(buttonPin); // Baca status push button
 
  if (buttonState == HIGH) {
    feedCat();
  }
}
}

// Fungsi untuk memberi makan kucing dengan menggerakkan servo
void feedCat() {

  // Menggerakkan servo untuk memberi makan kucing
  myservo.write(0);  // Sudut servo saat memberi makan (misalnya 90 derajat)
  delay(1000);        // Durasi servo bergerak (misalnya 1 detik)
  myservo.write(110);   // Sudut awal servo setelah memberi makan (misalnya 0 derajat)
}
void waduhMoment(){
    //WADUH MOMENT  
  playTone(880, 300); // A
  playTone(784, 300); // G
  playTone(659, 300); // E
  playTone(523, 500); // C
  delay(300);
  playTone(392, 200); // G
  playTone(440, 200); // A
  playTone(523, 250); // C
  playTone(587, 250); // D
  playTone(659, 250); // E
  playTone(587, 500); // D
  delay(100);
  playTone(523, 250); // C
  playTone(392, 175); // G
  playTone(440, 176); // A
  playTone(523, 175); // C
}




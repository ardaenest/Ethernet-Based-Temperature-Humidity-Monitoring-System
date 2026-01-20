#include <DHT.h>
#include <Ethernet.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define BUZZER_PIN 7
#define BUZZER_FREQ 2500
#define SICAKLIK_ESIK 1.0   // DHT11 için mantıklı eşik

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);

EthernetServer server(80);
DHT dht(DHTPIN, DHTTYPE);

float oncekiSicaklik = 0;
bool ilkOlcum = true;
bool alarmAktif = false;

void buzzerOn() {
  tone(BUZZER_PIN, BUZZER_FREQ);
}

void buzzerOff() {
  noTone(BUZZER_PIN);
}

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();

  Ethernet.begin(mac, ip);
  server.begin();

  Serial.print("Web sunucusu basladi: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  float sicaklik = dht.readTemperature();
  float nem = dht.readHumidity();

  if (isnan(sicaklik) || isnan(nem)) {
    delay(2000);
    return;
  }

  if (ilkOlcum) {
    oncekiSicaklik = sicaklik;
    ilkOlcum = false;
    alarmAktif = false;
  } else {
    float fark = abs(sicaklik - oncekiSicaklik);

    if (fark >= SICAKLIK_ESIK) {
      alarmAktif = true;
      buzzerOn();
    } else {
      alarmAktif = false;
      buzzerOff();
    }

    oncekiSicaklik = sicaklik;
  }

  EthernetClient client = server.available();
  if (client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<meta http-equiv='refresh' content='2'>");
    client.println("<title>Ortam Takibi</title>");
    client.println("</head>");
    client.println("<body style='font-family:Arial;'>");

    // SICAKLIK
    client.println("<div style='border:2px solid black; width:220px; padding:10px; margin-bottom:10px;'>");
    client.println("<h2>Sicaklik</h2>");
    client.print("<p style='font-size:24px;'>");
    client.print(sicaklik);
    client.println(" &deg;C</p>");
    client.println("</div>");

    // NEM
    client.println("<div style='border:2px solid black; width:220px; padding:10px; margin-bottom:10px;'>");
    client.println("<h2>Nem</h2>");
    client.print("<p style='font-size:24px;'>");
    client.print(nem);
    client.println(" %</p>");
    client.println("</div>");

    // ALARM DURUMU
    client.println("<div style='border:2px solid black; width:220px; padding:10px;'>");
    client.println("<h2>Alarm Durumu</h2>");

    if (alarmAktif) {
      client.println("<p style='color:red; font-size:20px;'>ALARM AKTIF</p>");
    } else {
      client.println("<p style='color:green; font-size:20px;'>NORMAL</p>");
    }

    client.println("</div>");

    client.println("</body>");
    client.println("</html>");

    client.stop();
  }

  delay(2000);
}

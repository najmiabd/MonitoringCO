#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "sensor"
#endif

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include <SoftwareSerial.h>

#include <math.h>
#define K 3

#define WIFI_SSID "Laboratorium Teknik Kendali"
#define WIFI_PASSWORD "LTK2021"

#define INFLUXDB_URL "https://us-east-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "nF-Z3dhXbfGOAnJmIUIqmUu2DrGoSHKV--ZTPGRnIMKExoLQxlRRpiFyYQdpZbOyh6KRaRsmWex6iSZmphxZXg=="
#define INFLUXDB_ORG "ad674bf36dd49b9a"
#define INFLUXDB_BUCKET "Monitoring Posisi Perokok"

#define TZ_INFO "UTC7"
SoftwareSerial serial(D6, D7);

Point sensor("CO");

double trainingSet[][2] = {
    {1, 11.89}, //Zona 1
    {2, 8.70},
    {3, 9.18},
    {4, 8.91},
    {1, 9.45},  
    {2, 8.76},
    {3, 8.90},
    {4, 8.92},
    {1, 9.18},
    {2, 8.76},
    {3, 8.76},
    {4, 8.92},
    {1, 9.62},
    {2, 8.76},
    {3, 8.13},
    {4, 9.24},                       
    {1, 8.99},  // Zona 2
    {2, 9.32},
    {3, 8.59},
    {4, 8.76},
    {1, 8.29},
    {2, 9.07},
    {3, 8.76},
    {4, 8.61},
    {1, 8.95},
    {2, 9.21},
    {3, 9.18},
    {4, 6.27},
    {1, 7.43},
    {2, 9.47},
    {3, 8.60},
    {4, 7.48},    
    {1, 8.65}, // Zona 3 
    {2, 8.82},
    {3, 9.27}, 
    {4, 8.30},  
    {1, 9.07},
    {2, 8.76},
    {3, 9.42},
    {4, 8.76},    
    {1, 9.07},
    {2, 8.76},
    {3, 9.42},
    {4, 8.76},
    {1, 8.86},
    {2, 9.08},
    {3, 9.25},
    {4, 8.60},
    {1, 7.92},   // Zona 4
    {2, 7.09},
    {3, 8.20},
    {4, 10.02},    
    {1, 8.38},
    {2, 8.05},
    {3, 8.33},
    {4, 8.61},
    {1, 8.55},
    {2, 8.76},
    {3, 8.76},
    {4, 9.09},    
    {1, 8.76},
    {2, 8.97},
    {3, 9.24},
    {4, 9.09},

};

int labels[] = {
    1, //Zona 1
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0, //Zona 2 
    1,
    0,
    0,
    0,
    1,
    0,
    0,  
    0,
    1,
    0,
    0,
    0,
    1,
    0,
    0,    
    0, // Zona 3
    0,
    1,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    1,
    0,    
    0, //Zona 4
    0,
    0,
    1,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    1,
       
};
// Fungsi untuk menghitung jarak Euclidean antara dua data
double euclideanDistance(double* p1, double* p2, int dimensions)
{
    double distance = 0.0;
    for (int i = 0; i < dimensions; i++)
    {
        double diff = p1[i] - p2[i];
        distance += diff * diff;
    }
    return sqrt(distance);
}

// Fungsi untuk mengklasifikasikan data baru menggunakan KNN
int classifyData(double* newData, int dimensions, int dataSize)
{
    // Simpan jarak terdekat ke dalam array
    double nearestDistances[K];
    // Simpan indeks tetangga terdekat ke dalam array
    int nearestIndices[K];

    // Inisialisasi array dengan jarak tak terhingga
    for (int i = 0; i < K; i++)
    {
        nearestDistances[i] = INFINITY;
    }

    // Temukan tetangga terdekat
    for (int i = 0; i < dataSize; i++)
    {
        double distance = euclideanDistance(newData, trainingSet[i], dimensions);

        // Cari posisi yang tepat untuk jarak saat ini
        for (int j = 0; j < K; j++)
        {
            if (distance < nearestDistances[j])
            {
                // Geser jarak dan indeks sebelumnya
                for (int k = K - 1; k > j; k--)
                {
                    nearestDistances[k] = nearestDistances[k - 1];
                    nearestIndices[k] = nearestIndices[k - 1];
                }

                // Simpan jarak dan indeks baru
                nearestDistances[j] = distance;
                nearestIndices[j] = i;

                break;
            }
        }
    }

    // Hitung jumlah tetangga berdasarkan label kelas
    int classCount[2] = {0, 0};
    for (int i = 0; i < K; i++)
    {
        int label = labels[nearestIndices[i]];
        classCount[label]++;
    }

    // Klasifikasikan data baru berdasarkan mayoritas tetangga
    int maxCount = 0;
    int maxClass = 0;
    for (int i = 0; i < 2; i++)
    {
        if (classCount[i] > maxCount)
        {
            maxCount = classCount[i];
            maxClass = i;
        }
    }

    return maxClass;
}


void setup() {
  Serial.begin(19200);
  serial.begin(19200);

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() {
  if (serial.available() > 0) {
    String dataterima = serial.readString();

    int startIdx = dataterima.indexOf("PPM1: ") + 6;  
    int endIdx = dataterima.indexOf(",", startIdx);  
    String ppm1str = dataterima.substring(startIdx, endIdx);  
    float ppm1 = ppm1str.toFloat();  

    startIdx = dataterima.indexOf("PPM2: ") + 6;
    endIdx = dataterima.indexOf(",", startIdx);
    String ppm2str = dataterima.substring(startIdx, endIdx);
    float ppm2 = ppm2str.toFloat();

    startIdx = dataterima.indexOf("PPM3: ") + 6;
    endIdx = dataterima.indexOf(",", startIdx);
    String ppm3str = dataterima.substring(startIdx, endIdx);
    float ppm3 = ppm3str.toFloat();

    startIdx = dataterima.indexOf("PPM4: ") + 6;
    endIdx = dataterima.length();
    String ppm4str = dataterima.substring(startIdx, endIdx);
    float ppm4 = ppm4str.toFloat();    
    
    // Print individual PPM values
    Serial.print("PPM1: ");
    Serial.println(ppm1, 2);
    Serial.print("PPM2: ");
    Serial.println(ppm2, 2);
    Serial.print("PPM3: ");
    Serial.println(ppm3, 2);
    Serial.print("PPM4: ");
    Serial.println(ppm4, 2);

      double newData[][2] = {
    {1, ppm1},
    {2, ppm2},
    {3, ppm3},
    {4, ppm4}
};

int dimensions = sizeof(newData[0]) / sizeof(newData[0][0]); // Hitung dimensi newData
int dataSize = sizeof(trainingSet) / sizeof(trainingSet[0]); // Hitung ukuran data pelatihan

// Klasifikasikan setiap data baru pada setiap zona menggunakan KNN
int classifications[4]; // Array untuk menyimpan hasil klasifikasi

for (int i = 0; i < 4; i++) {
    classifications[i] = classifyData(newData[i], dimensions, dataSize);
}

// Tampilkan hasil klasifikasi pada Serial Monitor
for (int i = 0; i < 4; i++) {
    Serial.print("Zona ");
    Serial.print(String(newData[i][0], 2)); // Tampilkan dengan 2 angka desimal
    Serial.print(" diklasifikasikan sebagai Kelas ");
    Serial.println(classifications[i]);
}
// InfluxDB line protocol
String lineProtocol = "CO PPM1=" + String(ppm1, 2) + ",PPM2=" + String(ppm2, 2) + ",PPM3=" + String(ppm3, 2) + ",PPM4=" + String(ppm4, 2) + ",Zona1=" + String(classifications[0]) + ",Zona2=" + String(classifications[1]) + ",Zona3=" + String(classifications[2]) + ",Zona4=" + String(classifications[3]);
Serial.print("Writing: ");
Serial.println(lineProtocol);

    sensor.clearFields();

    sensor.addField("PPM 1", ppm1);
    sensor.addField("PPM 2", ppm2);
    sensor.addField("PPM 3", ppm3);
    sensor.addField("PPM 4", ppm4);
    sensor.addField("Zona 1", classifications[0]);
    sensor.addField("Zona 2", classifications[1]);
    sensor.addField("Zona 3", classifications[2]);
    sensor.addField("Zona 4", classifications[3]);

    // Check WiFi connection and reconnect if needed
    if (wifiMulti.run() != WL_CONNECTED) {
      Serial.println("Wifi connection lost");
    }

    // Write point
    if (!client.writePoint(sensor)) {
      Serial.print("InfluxDB write failed: ");
      Serial.println(client.getLastErrorMessage());
    }

    delay(10000);
    }
  }

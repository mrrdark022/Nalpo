#include <WiFi.h>
#include <WiFiUdp.h>
#include <driver/i2s.h>

const char* ssid = "your wifi name";
const char* password = "your password";
const char* serverIP = "your server IP ";
const uint16_t serverPort = 5000; // you can change the port 

#define I2S_WS  25
#define I2S_SD  32
#define I2S_SCK 33
#define I2S_PORT I2S_NUM_0

uint8_t buffer[960];
float backgroundNoise = 0;
WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 480  // Each buffer = 960 bytes (30ms audio)
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_set_clk(I2S_PORT, 16000, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
}

float computeSTE(int16_t* samples, size_t numSamples) {
  float energy = 0;
  for (size_t i = 0; i < numSamples; i++) {
    energy += samples[i] * samples[i];
  }
  return energy / numSamples;
}

void loop() {
  size_t bytesRead;
  i2s_read(I2S_PORT, buffer, sizeof(buffer), &bytesRead, portMAX_DELAY);

  // Ensure exactly 960 bytes
  if (bytesRead < sizeof(buffer)) {
    memset(buffer + bytesRead, 0, sizeof(buffer) - bytesRead);
  }

  float currentEnergy = computeSTE((int16_t*)buffer, sizeof(buffer) / 2);
  Serial.print("Energy: ");
  Serial.println(currentEnergy);

  udp.beginPacket(serverIP, serverPort);
  udp.write(buffer, sizeof(buffer));  // Always send 960 bytes
  udp.endPacket();

  backgroundNoise = (backgroundNoise * 0.9) + (currentEnergy * 0.1);
}

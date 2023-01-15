#include "io.h"

String readFile(fs::FS &fs, const char *path) {
    Serial.printf("[READ] Reading file: %s\r\n", path);
    File file = fs.open(path, "r");
    if (!file || file.isDirectory()) {
        Serial.println("[ERRPR] empty file or failed to open file");
        return String();
    }
    String fileContent;
    while (file.available()) {
        fileContent += String((char)file.read());
    }
    file.close();
    return fileContent;
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
    Serial.printf("[WRITE] Writing file: %s\r\n", path);
    File file = fs.open(path, "w");
    if (!file) {
        Serial.println("[ERROR] failed to open file for writing");
        return;
    }
    if (file.print(message)) {
        Serial.println("[WRITE] file written");
    } else {
        Serial.println("[ERRPR] write failed");
    }
    file.close();
}
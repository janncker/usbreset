#include <Arduino.h>
#include <DigiUSB.h>

char recv[10]="";

void setup() {

DigiUSB.begin();
  pinMode(0, OUTPUT); //reset pin on 0
  digitalWrite(0, 1);

  pinMode(2, OUTPUT); //reset pin on 2
  digitalWrite(2, 1);

  pinMode(1, OUTPUT); //LED on Model B

}

void get_input() {
  int lastRead;
  int length=0;

// when there are no characters to read, or the character isn't a newline
  while (true) { // loop forever
    if (DigiUSB.available()) {
      // something to read
      lastRead = DigiUSB.read();
      recv[length] = (char)(lastRead);
      length ++;
     }
      if (lastRead == '\n') {
        DigiUSB.write("cmd recv:");
        DigiUSB.write(recv);
        if (strcmp(recv, "reset0\n")== 0) {
          DigiUSB.write("reset 0\n");
          digitalWrite(0, 0);
          delay(1000);
          digitalWrite(0, 1);
          DigiUSB.write("done");
        }
        if (strcmp(recv, "reset2\n")== 0) {
          DigiUSB.write("reset 2\n");
          digitalWrite(2, 0);
          delay(1000);
          digitalWrite(2, 1);
          DigiUSB.write("done\n");
        }
        memset(recv, 0, 10);
        length=0;
        break; // when we get a newline, break out of loop
      }
    // refresh the usb port for 10 milliseconds
    DigiUSB.delay(10);
  }
}

void loop() {
  // print output
  DigiUSB.println("Waiting for input...");
  // get input
  get_input();
}

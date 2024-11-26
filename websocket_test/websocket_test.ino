#include <WebSocketsServer.h>

static WebSocketsServer webSocket(81);

void setup() {
  // put your setup code here, to run once:

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

}

void loop() {
  // put your main code here, to run repeatedly:

}

#include "Application.h"
#include "receive/ConsoleActionReceiver.h"


int main() {
    ConsoleActionReceiver receiver;
    Application application(&receiver);
    application.run();
    return 0;
}

#include "receive/ConsoleActionReceiver.h"
#include "receive/ConsoleActionParser.h"


ConsoleActionReceiver::ConsoleActionReceiver() : ActionReceiver(ConsoleActionParser()) {
}

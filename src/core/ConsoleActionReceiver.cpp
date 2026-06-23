#include "ConsoleActionReceiver.h"
#include "ConsoleActionParser.h"


ConsoleActionReceiver::ConsoleActionReceiver() : ActionReceiver(ConsoleActionParser()) {
}

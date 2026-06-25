#include "ActionReceiver.h"

#include <cstdlib>
#include <vector>
#include "action/Add.h"
#include "action/Close.h"
#include "action/Exit.h"
#include "action/ListSession.h"
#include "action/Load.h"
#include "action/Paste.h"
#include "action/Redo.h"
#include "action/Save.h"
#include "action/Switch.h"
#include "action/Undo.h"
#include "action/UnknownAction.h"
#include "action/transformation/FlipLeft.h"
#include "action/transformation/FlipTop.h"
#include "action/transformation/Grayscale.h"
#include "action/transformation/Monochrome.h"
#include "action/transformation/Negative.h"
#include "action/transformation/RotateLeft.h"
#include "action/transformation/RotateRight.h"

static bool isSpace(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

static std::vector<std::string> splitTokens(const std::string& line) {
    std::vector<std::string> tokens;
    std::string current;

    for (size_t i = 0; i < line.size(); i++) {
        if (isSpace(line[i])) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else {
            current += line[i];
        }
    }

    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}

bool isValidFormat(const std::string& str) {
    unsigned int len = str.size();
    std::vector<std::string> formats = {".ppm", ".pbm", ".pgm", ".bmp"};

    for (const std::string& format : formats) {
        int equals = true;
        for (unsigned int j = ((len - 1) - 3); j < len; j++ ) {
            if (format[j - (len - 4)] != str[j]) {
                equals = false;
            }
        }
        if (equals) {
            return true;
        }
    }

    return false;
}

Action * ActionReceiver::createAction(std::string parsedAction) {
    std::vector<std::string> tokens = splitTokens(parsedAction);

    if (tokens.empty()) {
        return nullptr;
    }

    if (tokens[0] == "grayscale" && tokens.size() == 1) {
        return new Grayscale();
    }

    if (tokens[0] == "monochrome" && tokens.size() == 1) {
        return new Monochrome();
    }

    if (tokens[0] == "negative" && tokens.size() == 1) {
        return new Negative();
    }

    if (tokens[0] == "rotate" && tokens.size() == 2) {
        if (tokens[1] == "left") {
            return new RotateLeft();
        }
        if (tokens[1] == "right") {
            return new RotateRight();
        }
    }

    if (tokens[0] == "flip" && tokens.size() == 2) {
        if (tokens[1] == "top") {
            return new FlipTop();
        }
        if (tokens[1] == "left") {
            return new FlipLeft();
        }
    }

    if (tokens[0] == "undo" && tokens.size() == 1) {
        return new Undo();
    }

    if (tokens[0] == "redo" && tokens.size() == 1) {
        return new Redo();
    }

    if (tokens[0] == "add" && tokens.size() == 2 && isValidFormat(tokens[1])) {
        return new Add(tokens[1]);
    }

    if (tokens[0] == "paste" && tokens.size() == 5 && isValidFormat(tokens[1]) && isValidFormat(tokens[2])) {
        int posX = std::atoi(tokens[3].c_str());
        int posY = std::atoi(tokens[4].c_str());
        Paste* pt = nullptr;
        try {
            pt = new Paste(tokens[1], tokens[2], posX, posY);
        } catch (const char* ex) {
            std::cout << ex;
        }

        return pt;
    }

    if (tokens[0] == "load" && tokens.size() >= 2 && isValidFormat(tokens[1])) {
        std::vector<std::string> filePaths;
        for (size_t i = 1; i < tokens.size(); i++) {
            filePaths.push_back(tokens[i]);
        }
        return new Load(filePaths);
    }

    if (tokens[0] == "save" && tokens.size() == 1) {
        return new Save();
    }

    if ((tokens[0] == "list" && tokens.size() == 2 && tokens[1] == "session") ||
        (tokens[0] == "session" && tokens.size() == 2 && tokens[1] == "info")) {
        return new ListSession();
    }

    if (tokens[0] == "switch" && tokens.size() == 2) {
        int sessionId = std::atoi(tokens[1].c_str());
        if (sessionId > 0) {
            return new Switch(static_cast<unsigned int>(sessionId));
        }
        return new UnknownAction(parsedAction);
    }

    if (tokens[0] == "close" && tokens.size() == 2) {
        int sessionId = std::atoi(tokens[1].c_str());
        if (sessionId > 0) {
            return new Close(static_cast<unsigned int>(sessionId));
        }
        return new UnknownAction(parsedAction);
    }

    if (tokens[0] == "exit" && tokens.size() == 1) {
        return new Exit();
    }

    return new UnknownAction(parsedAction);
}

ActionReceiver::ActionReceiver(ActionParser parser) : parser(parser) {
}

Action * ActionReceiver::listen() const {
    return createAction(parser.deserializeAction());
}

#include "Plotter.h"
#include "strlib.h"
#include <unordered_map>

using namespace std;

void executeCommand(Vector<string> command);

void runPlotterScript(istream& input) {

    for (string line; getline(input, line); ) {
        Vector<string> command = stringSplit(line, " ");
        executeCommand(command);
    }
}

enum Operation { PenDown, PenUp, MoveAbs, MoveRel, PenColor, PenWidth };

struct Plotter {
    // control by PenDown and PenUp
    bool enabled;
    double X;
    double Y;
    PenStyle style;
};

Plotter plotter = Plotter{false, 0, 0, PenStyle {1.0, "black"} };

unordered_map<string, Operation> umap = {
    {"PENDOWN", PenDown},
    {"PENUP", PenUp},
    {"MOVEABS", MoveAbs},
    {"MOVEREL", MoveRel},
    {"PENCOLOR", PenColor},
    {"PENWIDTH", PenWidth},
};

void executeCommand(Vector<string> command) {
    string operation = toUpperCase(command[0]);

    switch (umap[operation]) {
    case PenDown:
        plotter.enabled = true;
        break;
    case PenUp:
        plotter.enabled = false;
        break;
    case MoveAbs: {
        double xDist = stringToReal(command[1]);
        double yDist = stringToReal(command[2]);
        if (plotter.enabled) {
            drawLine(plotter.X, plotter.Y, xDist, yDist, plotter.style);
        }
        plotter.X = xDist;
        plotter.Y = yDist;
        break;
    }
    case MoveRel: {
        double xDist = stringToReal(command[1]);
        double yDist = stringToReal(command[2]);
        if (plotter.enabled) {
            drawLine(plotter.X, plotter.Y, plotter.X + xDist, plotter.Y + yDist, plotter.style);
        }
        plotter.X += xDist;
        plotter.Y += yDist;
        break;
    }
    case PenColor: {
        string color = command[1];
        plotter.style.color = color;
        break;
    }
    case PenWidth: {
        double widith = stringToReal(command[1]);
        plotter.style.width = widith;
        break;
    }
    default:
        break;
    }
}



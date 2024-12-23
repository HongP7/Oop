#include "Path.h"
#include <sstream>

ClassPath::ClassPath(const std::string& pathData, float fillOpacity, float strokeOpacity, RGB fillRGB, RGB strokeRGB, float strokeWidth, Transform transform, std::string fill, std::string stroke)
    : Shape(fillRGB, strokeRGB, fillOpacity, strokeOpacity, strokeWidth, transform, fill, stroke), pathData(pathData) {
    convertPathToValue();
}

void ClassPath::convertPathToValue() {
    std::istringstream iss(pathData);
    char type;
    float value;
    while (iss >> type) {
        types.push_back(type);
        while (iss >> value) {
            values.push_back(value);
            if (iss.peek() == ' ' || iss.peek() == ',') {
                iss.ignore();
            }
            else {
                break;
            }
        }
    }
}

void ClassPath::Draw(Graphics& graphics, std::vector<Defs*>& defs) {
    GraphicsState state = TransformSVG(graphics, transform);
    GraphicsPath pathToDraw;

    size_t valueIndex = 0;
    for (char type : types) {
        switch (type) {
        case 'M':
        case 'm':
            pathToDraw.StartFigure();
            pathToDraw.AddLine(values[valueIndex], values[valueIndex + 1], values[valueIndex + 2], values[valueIndex + 3]);
            valueIndex += 4;
            break;
        case 'L':
        case 'l':
            pathToDraw.AddLine(values[valueIndex], values[valueIndex + 1], values[valueIndex + 2], values[valueIndex + 3]);
            valueIndex += 4;
            break;
        case 'C':
        case 'c':
            pathToDraw.AddBezier(values[valueIndex], values[valueIndex + 1], values[valueIndex + 2], values[valueIndex + 3], values[valueIndex + 4], values[valueIndex + 5], values[valueIndex + 6], values[valueIndex + 7]);
            valueIndex += 8;
            break;
        case 'Z':
        case 'z':
            pathToDraw.CloseFigure();
            break;
            // Handle other cases like 'H', 'V', 'S', 'Q', etc.
        }
    }

    SolidBrush fillBrush(Color(255 * fillOpacity, fillRGB.r, fillRGB.g, fillRGB.b));
    Pen strokePen(Color(255 * strokeOpacity, strokeRGB.r, strokeRGB.g, strokeRGB.b), strokeWidth);

    if (!fill.empty()) {
        // Handle Gradient fill if necessary
    }
    else {
        graphics.FillPath(&fillBrush, &pathToDraw);
    }
    graphics.DrawPath(&strokePen, &pathToDraw);

    graphics.Restore(state);
}

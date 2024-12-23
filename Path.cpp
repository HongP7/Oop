#include "Path.h"
#include <sstream>
#include <iostream>

ClassPath::ClassPath(const std::string& pathData, const Transform& transform)
    : Shape(), pathData(pathData) {
    this->transform = transform;
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
            if (iss.peek() == ' ' || iss.peek() == ',')
                iss.ignore();
            else
                break;
        }
    }
}

void ClassPath::Draw(Graphics& graphics, std::vector<Defs*>& defs) {
    GraphicsState state = TransformSVG(graphics, transform);
    GraphicsPath pathToDraw;

    size_t valueIndex = 0;
    PointF startPoint, controlPoint1, controlPoint2, endPoint;

    for (char type : types) {
        switch (type) {
        case 'M':
        case 'm':
            pathToDraw.StartFigure();
            startPoint = PointF(values[valueIndex], values[valueIndex + 1]);
            valueIndex += 2;
            break;
        case 'L':
        case 'l':
            pathToDraw.AddLine(startPoint, PointF(values[valueIndex], values[valueIndex + 1]));
            startPoint = PointF(values[valueIndex], values[valueIndex + 1]);
            valueIndex += 2;
            break;
        case 'H':
        case 'h':
            pathToDraw.AddLine(startPoint, PointF(values[valueIndex], startPoint.Y));
            startPoint = PointF(values[valueIndex], startPoint.Y);
            valueIndex += 1;
            break;
        case 'V':
        case 'v':
            pathToDraw.AddLine(startPoint, PointF(startPoint.X, values[valueIndex]));
            startPoint = PointF(startPoint.X, values[valueIndex]);
            valueIndex += 1;
            break;
        case 'C':
        case 'c':
            controlPoint1 = PointF(values[valueIndex], values[valueIndex + 1]);
            controlPoint2 = PointF(values[valueIndex + 2], values[valueIndex + 3]);
            endPoint = PointF(values[valueIndex + 4], values[valueIndex + 5]);
            pathToDraw.AddBezier(startPoint, controlPoint1, controlPoint2, endPoint);
            startPoint = endPoint;
            valueIndex += 6;
            break;
        case 'S':
        case 's':
            controlPoint2 = PointF(values[valueIndex], values[valueIndex + 1]);
            endPoint = PointF(values[valueIndex + 2], values[valueIndex + 3]);
            pathToDraw.AddBezier(startPoint, controlPoint1, controlPoint2, endPoint); // Use last control point as reflection
            startPoint = endPoint;
            valueIndex += 4;
            break;
        case 'Q':
        case 'q':
            controlPoint1 = PointF(values[valueIndex], values[valueIndex + 1]);
            endPoint = PointF(values[valueIndex + 2], values[valueIndex + 3]);
            pathToDraw.AddBezier(startPoint, controlPoint1, endPoint);
            startPoint = endPoint;
            valueIndex += 4;
            break;
        case 'T':
        case 't':
            endPoint = PointF(values[valueIndex], values[valueIndex + 1]);
            pathToDraw.AddLine(startPoint, endPoint);
            startPoint = endPoint;
            valueIndex += 2;
            break;
        case 'Z':
        case 'z':
            pathToDraw.CloseFigure();
            break;
            // Xử lý các loại lệnh khác nếu cần
        }
    }

    // Tạo brush và pen cho fill và stroke
    SolidBrush fillBrush(Color(255 * fillOpacity, fillRGB.r, fillRGB.g, fillRGB.b));
    Pen strokePen(Color(255 * strokeOpacity, strokeRGB.r, strokeRGB.g, strokeRGB.b), strokeWidth);

    if (!fill.empty()) {
        // Tìm kiếm gradient tương ứng trong defs
        for (Defs* def : defs) {
            for (auto& gradient : def->getGradients()) {
                if (gradient->getID() == fill) {
                    // Xử lý LinearGradientBrush hoặc RadialGradientBrush
                    if (auto* linearGradient = dynamic_cast<LinearGradient*>(gradient)) {
                        LinearGradientBrush gradientBrush(linearGradient->getStart(), linearGradient->getEnd(), linearGradient->getStartColor(), linearGradient->getEndColor());
                        gradientBrush.SetInterpolationColors(linearGradient->getColors(), linearGradient->getPositions(), linearGradient->getColorCount());
                        graphics.FillPath(&gradientBrush, &pathToDraw);
                    }
                    else if (auto* radialGradient = dynamic_cast<RadialGradient*>(gradient)) {
                        RadialGradientBrush gradientBrush(PointF(radialGradient->getCx(), radialGradient->getCy()), radialGradient->getR(), PointF(radialGradient->getFx(), radialGradient->getFy()), radialGradient->getColors(), radialGradient->getPositions(), radialGradient->getColorCount());
                        graphics.FillPath(&gradientBrush, &pathToDraw);
                    }
                    break;
                }
            }
        }
    }
    else {
        graphics.FillPath(&fillBrush, &pathToDraw);
    }
    graphics.DrawPath(&strokePen, &pathToDraw);

    graphics.Restore(state);
}

#include "Path.h"
#include <sstream>
#include <iostream>
#include <cmath>

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
    PointF lastPoint(0, 0), controlPoint(0, 0);
    for (char type : types) {
        switch (type) {
        case 'M':
        case 'm':
            pathToDraw.StartFigure();
            lastPoint = PointF(values[valueIndex], values[valueIndex + 1]);
            valueIndex += 2;
            break;
        case 'L':
        case 'l':
            pathToDraw.AddLine(lastPoint, PointF(values[valueIndex], values[valueIndex + 1]));
            lastPoint = PointF(values[valueIndex], values[valueIndex + 1]);
            valueIndex += 2;
            break;
        case 'H':
        case 'h':
            if (type == 'H')
                pathToDraw.AddLine(lastPoint, PointF(values[valueIndex], lastPoint.Y));
            else
                pathToDraw.AddLine(lastPoint, PointF(lastPoint.X + values[valueIndex], lastPoint.Y));
            lastPoint = PointF(values[valueIndex], lastPoint.Y);
            valueIndex += 1;
            break;
        case 'V':
        case 'v':
            if (type == 'V')
                pathToDraw.AddLine(lastPoint, PointF(lastPoint.X, values[valueIndex]));
            else
                pathToDraw.AddLine(lastPoint, PointF(lastPoint.X, lastPoint.Y + values[valueIndex]));
            lastPoint = PointF(lastPoint.X, values[valueIndex]);
            valueIndex += 1;
            break;
        case 'C':
        case 'c':
            pathToDraw.AddBezier(lastPoint, PointF(values[valueIndex], values[valueIndex + 1]), PointF(values[valueIndex + 2], values[valueIndex + 3]), PointF(values[valueIndex + 4], values[valueIndex + 5]));
            lastPoint = PointF(values[valueIndex + 4], values[valueIndex + 5]);
            controlPoint = PointF(values[valueIndex + 2], values[valueIndex + 3]);
            valueIndex += 6;
            break;
        case 'S':
        case 's':
            pathToDraw.AddBezier(lastPoint, PointF(2 * lastPoint.X - controlPoint.X, 2 * lastPoint.Y - controlPoint.Y), PointF(values[valueIndex], values[valueIndex + 1]), PointF(values[valueIndex + 2], values[valueIndex + 3]));
            lastPoint = PointF(values[valueIndex + 2], values[valueIndex + 3]);
            controlPoint = PointF(values[valueIndex], values[valueIndex + 1]);
            valueIndex += 4;
            break;
        case 'Q':
        case 'q':
            pathToDraw.AddBezier(lastPoint, PointF(values[valueIndex], values[valueIndex + 1]), PointF(values[valueIndex + 2], values[valueIndex + 3]));
            lastPoint = PointF(values[valueIndex + 2], values[valueIndex + 3]);
            controlPoint = PointF(values[valueIndex], values[valueIndex + 1]);
            valueIndex += 4;
            break;
        case 'T':
        case 't':
            pathToDraw.AddLine(lastPoint, PointF(values[valueIndex], values[valueIndex + 1]));
            lastPoint = PointF(values[valueIndex], values[valueIndex + 1]);
            valueIndex += 2;
            break;
        case 'A':
        case 'a':
        {
            float rx = values[valueIndex];
            float ry = values[valueIndex + 1];
            float xAxisRotation = values[valueIndex + 2];
            bool largeArcFlag = values[valueIndex + 3] != 0;
            bool sweepFlag = values[valueIndex + 4] != 0;
            PointF endPoint(values[valueIndex + 5], values[valueIndex + 6]);

            if (type == 'a') {
                endPoint.X += lastPoint.X;
                endPoint.Y += lastPoint.Y;
            }

            AddArc(lastPoint, rx, ry, xAxisRotation, largeArcFlag, sweepFlag, endPoint);
            lastPoint = endPoint;
            valueIndex += 7;
            break;
        }
        case 'Z':
        case 'z':
            pathToDraw.CloseFigure();
            break;
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
                        PointF center = radialGradient->getCenter();
                        float radius = radialGradient->getRadius();
                        PathGradientBrush gradientBrush(&pathToDraw);
                        gradientBrush.SetCenterColor(radialGradient->getCenterColor());
                        gradientBrush.SetSurroundColors(radialGradient->getSurroundColors(), radialGradient->getColorCount());
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

void GraphicsPath::AddArc(PointF& lastPoint, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, PointF endPoint) {
    // Chuyển đổi các góc từ độ sang radian
    float phi = xAxisRotation * (M_PI / 180.0);

    // Tính tọa độ điểm giữa giữa
    float x1prime = cos(phi) * (lastPoint.X - endPoint.X) / 2.0 + sin(phi) * (lastPoint.Y - endPoint.Y) / 2.0;
    float y1prime = -sin(phi) * (lastPoint.X - endPoint.X) / 2.0 + cos(phi) * (lastPoint.Y - endPoint.Y) / 2.0;

    // Tính bán kính điều chỉnh
    float rx_sq = rx * rx;
    float ry_sq = ry * ry;
    float x1prime_sq = x1prime * x1prime;
    float y1prime_sq = y1prime * y1prime;

    // Kiểm tra và điều chỉnh bán kính
    float radicant = (rx_sq * ry_sq - rx_sq * y1prime_sq - ry_sq * x1prime_sq) / (rx_sq * y1prime_sq + ry_sq * x1prime_sq);
    radicant = (radicant < 0) ? 0 : radicant;
    float c_prime = sqrt(radicant);
    if (largeArcFlag == sweepFlag) {
        c_prime = -c_prime;
    }

    float cx_prime = c_prime * rx * y1prime / ry;
    float cy_prime = -c_prime * ry * x1prime / rx;

    float cx = cos(phi) * cx_prime - sin(phi) * cy_prime + (lastPoint.X + endPoint.X) / 2.0;
    float cy = sin(phi) * cx_prime + cos(phi) * cy_prime + (lastPoint.Y + endPoint.Y) / 2.0;

    // Tính các góc bắt đầu và độ dài
    float ux = (x1prime - cx_prime) / rx;
    float uy = (y1prime - cy_prime) / ry;
    float vx = (-x1prime - cx_prime) / rx;
    float vy = (-y1prime - cy_prime) / ry;

    float n = sqrt(ux * ux + uy * uy);
    float p = ux; // dot product of (ux, uy) and (1, 0)
    float theta = acos(p / n);

    if (uy < 0) {
        theta = -theta;
    }

    // Distance between (ux, uy) and (vx, vy)
    n = sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy));
    p = ux * vx + uy * vy;
    float d = p / n;
    if (d > 1.0) d = 1.0;
    if (d < -1.0) d = -1.0;
    float deltaTheta = acos(d);

    // Ensure correct direction
    if (ux * vy - uy * vx < 0) {
        deltaTheta = -deltaTheta;
    }

    if (!sweepFlag && deltaTheta > 0) {
        deltaTheta -= 2 * M_PI;
    }
    else if (sweepFlag && deltaTheta < 0) {
        deltaTheta += 2 * M_PI;
    }

    AddArc(cx, cy, rx, ry, theta, deltaTheta, sweepFlag);

    lastPoint = endPoint;
}

void GraphicsPath::AddArc(float cx, float cy, float rx, float ry, float startAngle, float deltaAngle, bool sweepFlag) {
    // Ensure angles are in radians
    if (!sweepFlag) {
        deltaAngle = -deltaAngle;
    }

    GraphicsPath::AddArc(cx - rx, cy - ry, 2 * rx, 2 * ry, startAngle * (180.0 / M_PI), deltaAngle * (180.0 / M_PI));
}

#include "Path.h"
#include <sstream>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

void ClassPath::addValue(float value) {
    values.push_back(value);
}

void ClassPath::addType(char type) {
    types.push_back(type);
}

void ClassPath::clear() {
    values.clear();
    types.clear();
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
            pathToDraw.AddBezier(
                static_cast<REAL>(lastPoint.X), static_cast<REAL>(lastPoint.Y),
                static_cast<REAL>(values[valueIndex]), static_cast<REAL>(values[valueIndex + 1]),
                static_cast<REAL>(values[valueIndex + 2]), static_cast<REAL>(values[valueIndex + 3]),
                static_cast<REAL>(values[valueIndex + 4]), static_cast<REAL>(values[valueIndex + 5])
            );
            lastPoint = PointF(values[valueIndex + 4], values[valueIndex + 5]);
            controlPoint = PointF(values[valueIndex + 2], values[valueIndex + 3]);
            valueIndex += 6;
            break;
        case 'S':
        case 's':
            pathToDraw.AddBezier(
                static_cast<REAL>(lastPoint.X), static_cast<REAL>(lastPoint.Y),
                static_cast<REAL>(2 * lastPoint.X - controlPoint.X), static_cast<REAL>(2 * lastPoint.Y - controlPoint.Y),
                static_cast<REAL>(values[valueIndex]), static_cast<REAL>(values[valueIndex + 1]),
                static_cast<REAL>(values[valueIndex + 2]), static_cast<REAL>(values[valueIndex + 3])
            );
            lastPoint = PointF(values[valueIndex + 2], values[valueIndex + 3]);
            controlPoint = PointF(values[valueIndex], values[valueIndex + 1]);
            valueIndex += 4;
            break;
        case 'Q':
        case 'q':
        {
            // Chuyển đổi quadratic Bezier curve thành cubic Bezier curve
            float x1 = lastPoint.X;
            float y1 = lastPoint.Y;
            float x2 = values[valueIndex];
            float y2 = values[valueIndex + 1];
            float x3 = values[valueIndex + 2];
            float y3 = values[valueIndex + 3];

            float c1x = x1 + 2.0f / 3.0f * (x2 - x1);
            float c1y = y1 + 2.0f / 3.0f * (y2 - y1);
            float c2x = x3 + 2.0f / 3.0f * (x2 - x3);
            float c2y = y3 + 2.0f / 3.0f * (y2 - y3);

            pathToDraw.AddBezier(
                static_cast<REAL>(x1), static_cast<REAL>(y1),
                static_cast<REAL>(c1x), static_cast<REAL>(c1y),
                static_cast<REAL>(c2x), static_cast<REAL>(c2y),
                static_cast<REAL>(x3), static_cast<REAL>(y3)
            );

            lastPoint = PointF(x3, y3);
            controlPoint = PointF(x2, y2);
            valueIndex += 4;
            break;
        }
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

            AddArc(pathToDraw, lastPoint, rx, ry, xAxisRotation, largeArcFlag, sweepFlag, endPoint);
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
    SolidBrush fillBrush(Color(255 * static_cast<int>(fillOpacity), fillRGB.r, fillRGB.g, fillRGB.b));
    Pen strokePen(Color(255 * static_cast<int>(strokeOpacity), strokeRGB.r, strokeRGB.g, strokeRGB.b), strokeWidth);

    if (!fill.empty()) {
        // Tìm kiếm gradient tương ứng trong defs
        for (Defs* def : defs) {
            for (auto& gradient : def->getlinear()) {
                if (gradient->getID() == fill) {
                    LinearGradientBrush gradientBrush(PointF(gradient->getPoint().x1, gradient->getPoint().y1),
                        PointF(gradient->getPoint().x2, gradient->getPoint().y2),
                        Color(255, gradient->getStopList()[0]->getstopColor_red(), gradient->getStopList()[0]->getstopColor_green(), gradient->getStopList()[0]->getstopColor_blue()),
                        Color(255, gradient->getStopList()[1]->getstopColor_red(), gradient->getStopList()[1]->getstopColor_green(), gradient->getStopList()[1]->getstopColor_blue()));
                    graphics.FillPath(&gradientBrush, &pathToDraw);
                }
            }
            for (auto& gradient : def->getradial()) {
                if (gradient->getID() == fill) {
                    PointF center = PointF(gradient->getcx(), gradient->getcy());
                    float radius = gradient->getr();
                    PathGradientBrush gradientBrush(&pathToDraw);
                    gradientBrush.SetCenterColor(Color(255, gradient->getStopList()[0]->getstopColor_red(), gradient->getStopList()[0]->getstopColor_green(), gradient->getStopList()[0]->getstopColor_blue()));
                    int colorCount = gradient->getStopList().size();
                    Color* surroundColors = new Color[colorCount];
                    for (int i = 0; i < colorCount; ++i) {
                        surroundColors[i] = Color(255, gradient->getStopList()[i]->getstopColor_red(), gradient->getStopList()[i]->getstopColor_green(), gradient->getStopList()[i]->getstopColor_blue());
                    }
                    gradientBrush.SetSurroundColors(surroundColors, &colorCount);
                    graphics.FillPath(&gradientBrush, &pathToDraw);
                    delete[] surroundColors;
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

void ClassPath::AddArc(GraphicsPath& pathToDraw, PointF& lastPoint, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, PointF endPoint) {
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

    pathToDraw.AddArc(cx - rx, cy - ry, 2 * rx, 2 * ry, theta * (180.0 / M_PI), deltaTheta * (180.0 / M_PI));
}

void ClassPath::AddArc(GraphicsPath& pathToDraw, float cx, float cy, float rx, float ry, float startAngle, float deltaAngle, bool sweepFlag) {
    // Ensure angles are in radians
    if (!sweepFlag) {
        deltaAngle = -deltaAngle;
    }

    pathToDraw.AddArc(cx - rx, cy - ry, 2 * rx, 2 * ry, startAngle * (180.0 / M_PI), deltaAngle * (180.0 / M_PI));
}

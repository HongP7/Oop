#ifndef TEXT_H
#define TEXT_H

#include "Shapes.h"
#include "Defs.h" // Bao gồm Defs.h
#include "Transform.h" // Bao gồm Transform.h
#include <string>
#include <vector>

class Text_ : public Shape {
private:
    float x, y;
    std::string content;
    float fontSize;
    float fillOpacity;
    float strokeOpacity;
    float strokeWidth;
    std::string fontFamily;
    float dx, dy;
    std::string textAnchor;
    std::string fontStyle;
    bool checkStroke;
    std::string fill, stroke;
    Transform trans; // Sử dụng cấu trúc Transform

public:
    Text_() : x(0), y(0), content(""), fontSize(12.0f), fillOpacity(1.0f), strokeOpacity(1.0f),
        strokeWidth(1.0f), fontFamily("Arial"), dx(0), dy(0), textAnchor("start"), fontStyle("normal"),
        checkStroke(false), fill("black"), stroke("none") {
    }
    Text_(float x, float y, const std::string& content, float fontSize, float fillOpacity, float strokeOpacity,
        float strokeWidth, RGB fillRGB, RGB strokeRGB, Transform trans, const std::string& fontFamily,
        float dx, float dy, const std::string& textAnchor, const std::string& fontStyle, bool checkStroke,
        const std::string& fill, const std::string& stroke, Transform transform);

    float getX() const;
    float getY() const;
    std::string getContent() const;
    float getFontSize() const;
    std::string getFontFamily() const;
    std::string getFill() const;
    std::string getStroke() const;

    void Draw(Graphics&, std::vector<Defs*>&) override;
};

bool IsStringValidForFont(const wchar_t*, HFONT);
std::string normalizeTextContent(std::string);

#endif // TEXT_H

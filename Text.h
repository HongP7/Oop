#ifndef TEXT_H
#define TEXT_H

#include "Shapes.h"
#include <string>
#include <vector>

class Text_ : public Shape {
private:
    float x, y;                     // Tọa độ của văn bản
    std::string content;            // Nội dung văn bản
    float fontSize;                 // Kích thước phông chữ
    float fillOpacity;              // Độ mờ của màu lấp đầy
    float strokeOpacity;            // Độ mờ của nét viền
    float strokeWidth;              // Độ rộng của nét viền
    std::string fontFamily;         // Gia đình phông chữ
    float dx, dy;                   // Dịch chuyển văn bản
    std::string textAnchor;         // Vị trí neo của văn bản
    std::string fontStyle;          // Kiểu phông chữ (thường, nghiêng, đậm)
    bool checkStroke;               // Kiểm tra có nét viền hay không
    std::string fill, stroke;       // Gradient hoặc màu lấp đầy và nét viền

public:
    Text_() : x(0), y(0), content(""), fontSize(12.0f), fillOpacity(1.0f), strokeOpacity(1.0f),
        strokeWidth(1.0f), fontFamily("Arial"), dx(0), dy(0), textAnchor("start"), fontStyle("normal"),
        checkStroke(false), fill("black"), stroke("none") {}
    Text_(float, float, std::string, float, float, float, float, std::string, float, float, 
        std::string, std::string, bool, std::string, std::string);
              

    float getX() const;
    float getY() const;
    std::string getContent() const;
    float getFontSize() const;
    std::string getFontFamily() const;
    std::string getFill() const;
    std::string getStroke() const;

    void Draw(Graphics&, vector<Defs*>&) override;

    void normalizeTextContent();
    bool IsStringValidForFont() const;
};

#endif
#ifndef TEXT_H
#define TEXT_H

#include "Shapes.h"
#include <string>
#include <vector>

class Text : public Shape {
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
    Text(float x = 0, float y = 0, std::string content = "", float fontSize = 12.0f, 
         float fillOpacity = 1.0f, float strokeOpacity = 1.0f, float strokeWidth = 1.0f,
         std::string fontFamily = "Arial", float dx = 0, float dy = 0, 
         std::string textAnchor = "start", std::string fontStyle = "normal", 
         bool checkStroke = false, std::string fill = "black", std::string stroke = "none");

    float getX() const;
    float getY() const;
    std::string getContent() const;
    float getFontSize() const;
    std::string getFontFamily() const;
    std::string getFill() const;
    std::string getStroke() const;

    void Draw();

    void normalizeTextContent();
    bool IsStringValidForFont() const;
};

#endif
#ifndef TEXT_H
#define TEXT_H

#include "Shapes.h" 
#include<string>

class Text : public Shape {
private:
    float x, y;
    std::string content;
    float fontSize;
    std::string color;

public:
    Text(float x = 0, float y = 0, std::string content = "", float fontSize = 12.0f, std::string color = "black");

    float getX() const;
    float getY() const;
    std::string getContent() const;
    float getFontSize() const;
    std::string getColor() const;

    void Draw();

    void normalizeTextContent();
    bool IsStringValidForFont() const;
};

#endif

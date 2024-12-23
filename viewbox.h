#ifndef VIEWBOX_H
#define VIEWBOX_H

class ViewBox {
private:
    float width;
    float height;
    float scale;

public:
    ViewBox(float width, float height, float scale);

    // Getters
    float getWidth() const;
    float getHeight() const;
    float getScale() const;

    // Setters
    void setWidth(float newWidth);
    void setHeight(float newHeight);
    void setScale(float newScale);

    // Drawing function
    void DrawViewBox() const;
};

#endif // VIEWBOX_H

#ifndef VIEWBOX_H
#define VIEWBOX_H

class ViewBox {
private:
    float x, y;                // Tọa độ góc trên trái của hộp nhìn
    float width_in, height_in; // Kích thước vùng nhìn vào
    float width_out, height_out; // Kích thước vùng nhìn ra
    bool check_viewbox;        // Cờ kiểm tra trạng thái của hộp nhìn
    float scale;               // Hệ số tỷ lệ

public:
    ViewBox(float x = 0, float y = 0, 
            float width_in = 100, float height_in = 100, 
            float width_out = 100, float height_out = 100, 
            bool check_viewbox = true, float scale = 1.0f);

    float getScale() const;
    float getWidthOut() const;
    float getHeightOut() const;
    float getWidthIn() const;
    float getHeightIn() const;
    bool getcheck() const;

    void DrawViewBox() const; // Vẽ hộp nhìn
};

#endif
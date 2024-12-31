#include "ReadFile.h"
#include <sstream>
#include <map>
#include <cmath> // Bao gồm thư viện cmath để sử dụng hàm toán học 

bool checkScale = false;

bool isParsingGroup = false;

vector<bool> checkRGB;

string chuanhoa(string input)
{
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ',')
        {
            input[i] = ' ';
        }
    }
    istringstream iss(input);
    ostringstream oss;
    string word;
    bool first = true;

    while (iss >> word)
    {

        if (!first)
        {
            oss << " ";
        }
        oss << word;
        first = false;
    }
    return oss.str();
}
void getNextNumberOfValues(string& s, int& i, int num, ClassPath& path, char curType) {
    istringstream iss(s.substr(i));
    float value;
    int next_pos = 0;
    while (num-- > 0 && iss >> value) {
        path.addValue(value);
        next_pos = iss.tellg(); // Cập nhật vị trí tiếp theo
        if (iss.peek() == ' ' || iss.peek() == ',') {
            iss.ignore();
        }
    }
    i += next_pos; // Cập nhật vị trí i sau khi thêm các giá trị
    path.addType(curType); // Thêm kiểu hiện tại
}

void convertPathToValue(string s, ClassPath& path) {
    char currentCommand = '\0';
    path.clear(); // Xóa các giá trị trong `types` và `values` thông qua phương thức `clear`

    bool passM = false;
    s = chuanhoa(s);
    int i = 0;
    while (i < s.length()) {
        if (isalpha(s[i])) {
            currentCommand = s[i];
            if ((currentCommand == 'M' || currentCommand == 'm') && !passM)
                passM = true;
            i++;

            switch (currentCommand) {
            case 'M':
            case 'm':
                getNextNumberOfValues(s, i, 2, path, currentCommand);
                break;
            case 'L':
            case 'l':
            case 'T':
            case 't':
                getNextNumberOfValues(s, i, 2, path, currentCommand);
                break;
            case 'H':
            case 'h':
            case 'V':
            case 'v':
                getNextNumberOfValues(s, i, 1, path, currentCommand);
                break;
            case 'C':
            case 'c':
                getNextNumberOfValues(s, i, 6, path, currentCommand);
                break;
            case 'Z':
            case 'z':
                getNextNumberOfValues(s, i, 0, path, currentCommand);
                break;
            case 'S':
            case 's':
            case 'Q':
            case 'q':
                getNextNumberOfValues(s, i, 4, path, currentCommand);
                break;
            case 'A':
            case 'a':
                getNextNumberOfValues(s, i, 7, path, currentCommand);
                break;
            }
        }
        else {
            if (currentCommand == 'm' && passM)
                currentCommand = 'l';
            else if (currentCommand == 'M' && passM)
                currentCommand = 'L';
            i++;
            switch (currentCommand) {
            case 'M':
            case 'm':
                getNextNumberOfValues(s, i, 2, path, currentCommand);
                break;
            case 'L':
            case 'l':
            case 'T':
            case 't':
                getNextNumberOfValues(s, i, 2, path, currentCommand);
                break;
            case 'H':
            case 'h':
            case 'V':
            case 'v':
                getNextNumberOfValues(s, i, 1, path, currentCommand);
                break;
            case 'C':
            case 'c':
                getNextNumberOfValues(s, i, 6, path, currentCommand);
                break;
            case 'Z':
            case 'z':
                getNextNumberOfValues(s, i, 0, path, currentCommand);
                break;
            case 'S':
            case 's':
            case 'Q':
            case 'q':
                getNextNumberOfValues(s, i, 4, path, currentCommand);
                break;
            case 'A':
            case 'a':
                getNextNumberOfValues(s, i, 7, path, currentCommand);
                break;
            }
        }
        if (s[i] == ' ')
            i++;
        if ((s[i] >= '0' && s[i] <= '9') || s[i] == '-' || s[i] == '.') {
            i--;
        }
    }
}

string toLower(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
void convert_letters_to_RGB(RGB& rgb, string s)
{
    map<string, RGB> colorMap =
    {
        {"black", {0, 0, 0}},
        {"darkslategray", {47, 79, 79}},
        {"white", {255, 255, 255}},
        {"none", {255, 255, 255}},
        {"red", {255, 0, 0}},
        {"green", {0, 255, 0}},
        {"grey", {128, 128, 128}},
        {"blue", {0, 0, 255}},
        {"yellow", {255, 255, 0}},
        {"cyan", {0, 255, 255}},
        {"magenta", {255, 0, 255}},
        {"grey", {128, 128, 128}},
        {"lightgrey", {192, 192, 192}},
        {"darkgrey", {64, 64, 64}},
        {"maroon", {128, 0, 0}},
        {"olive", {128, 128, 0}},
        {"green", {138, 43, 226}},
        {"navy", {0, 0, 128}},
        {"purple", {128, 0, 128}},
        {"teal", {0, 128, 128}},
        {"orange", {255, 165, 0}},
        {"brown", {165, 42, 42}},
        {"pink", {255, 182, 193}},
        {"salmon", {250, 128, 114}},
        {"gold", {255, 215, 0}},
        {"lime", {0, 255, 0}},
        {"skyblue", {135, 206, 235}},
        {"forestgreen", {34, 139, 34}},
        {"turquoise", {64, 224, 208}},
        {"steelblue", {70, 130, 180}},
        {"dodgerblue", {30, 144, 255}},
        {"royalblue", {65, 105, 225}},
        {"indigo", {75, 0, 130}},
        {"slateblue", {106, 90, 205}},
        {"lavender", {230, 230, 250}},
        {"thistle", {216, 191, 216}},
        {"plum", {221, 160, 221}},
        {"violet", {238, 130, 238}},
        {"orchid", {218, 112, 214}},
        {"mediumpurple", {147, 112, 219}},
        {"darkorchid", {153, 50, 204}},
        {"darkviolet", {148, 0, 211}},
        {"darkmagenta", {139, 0, 139}},
        {"mediumorchid", {186, 85, 211}},
        {"palevioletred", {219, 112, 147}},
        {"cornflowerblue", {100, 149, 237}},
        {"deepskyblue", {0, 191, 255}},
        {"lightskyblue", {135, 206, 250}},
        {"midnightblue", {25, 25, 112}},
        {"mediumaquamarine", {102, 205, 170}},
        {"darkseagreen", {143, 188, 143}},
        {"lightgreen", {144, 238, 144}},
        {"palegreen", {152, 251, 152}},
        {"springgreen", {0, 255, 127}},
        {"mediumspringgreen", {0, 250, 154}},
        {"darkolivegreen", {85, 107, 47}},
        {"olivedrab", {107, 142, 35}},
        {"chartreuse", {127, 255, 0}},
        {"lawngreen", {124, 252, 0}},
        {"darkgreen", {0, 100, 0}},
        {"mediumseagreen", {60, 179, 113}},
        {"seagreen", {46, 139, 87}},
        {"darkslategray", {47, 79, 79}},
        {"dimgray", {105, 105, 105}},
        {"rosybrown", {188, 143, 143}},
        {"indianred", {205, 92, 92}},
        {"blueviolet", {138, 43, 226}},
        {"skyblue", {135, 206, 235}}

    };

    string lowerCaseS = toLower(s);

    auto it = colorMap.find(lowerCaseS);
    if (it != colorMap.end())
    {
        rgb = it->second;
    }
    else
    {
        rgb = { 255, 255, 255 };
    }
}

string convert_String_to_RGB(RGB& rgb, string s, smatch match, regex re)
{
    rgb = { 0, 0, 0 };
    if ((s[0] == 'r' && s[1] == 'g' && s[2] == 'b') && regex_search(s, match, re))
    {
        if (match.size() == 4)
        {
            rgb.r = stoi(match[1]);
            if (rgb.r > 255)
                rgb.r = 255;
            rgb.g = stoi(match[2]);
            if (rgb.g > 255)
                rgb.g = 255;
            rgb.b = stoi(match[3]);
            if (rgb.b > 255)
                rgb.b = 255;
        }
    }
    else if (s != "")
    {
        if (s[0] != '#')
            convert_letters_to_RGB(rgb, s);

        else if (s[0] == '#')
        {
            unsigned int hexValue;
            if (s.length() == 4)
            {
                char a1 = s[1], a2 = s[2], a3 = s[3];
                s = "#" + string(1, a1) + string(1, a1) + string(1, a2) + string(1, a2) + string(1, a3) + string(1, a3);
            }
            istringstream(s.substr(1)) >> hex >> hexValue;

            rgb.r = (hexValue >> 16) & 0xFF;
            rgb.g = (hexValue >> 8) & 0xFF;
            rgb.b = hexValue & 0xFF;
            int alpha = (hexValue >> 24) & 0xFF;
        }
    }
    return "";
}

void convert_String_to_RGB_(RGB& rgb, string s, smatch match, regex re)
{
    rgb = { 0, 0, 0 };
    if ((s[0] == 'r' && s[1] == 'g' && s[2] == 'b') && regex_search(s, match, re))
    {
        if (match.size() == 4)
        {
            rgb.r = stoi(match[1]);
            if (rgb.r > 255)
                rgb.r = 255;
            rgb.g = stoi(match[2]);
            if (rgb.g > 255)
                rgb.g = 255;
            rgb.b = stoi(match[3]);
            if (rgb.b > 255)
                rgb.b = 255;
        }
    }
    else if (s != "")
    {
        if (s[0] != '#')
            convert_letters_to_RGB(rgb, s);

        else if (s[0] == '#')
        {
            unsigned int hexValue;
            if (s.length() == 4)
            {
                char a1 = s[1], a2 = s[2], a3 = s[3];
                s = "#" + string(1, a1) + string(1, a1) + string(1, a2) + string(1, a2) + string(1, a3) + string(1, a3);
            }
            istringstream(s.substr(1)) >> hex >> hexValue;

            rgb.r = (hexValue >> 16) & 0xFF;
            rgb.g = (hexValue >> 8) & 0xFF;
            rgb.b = hexValue & 0xFF;
            int alpha = (hexValue >> 24) & 0xFF;
        }
    }
}

void convertStyle(string styleString, string& fill, string& stroke, RGB& fillRGB, RGB& strokeRGB, float& fillOpacity, float& strokeOpacity, float& strokeWidth) {
    static regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
    int posFill = styleString.find("fill:");
    int posStroke = styleString.find("stroke:");
    int posFillOpa = styleString.find("fill-opacity:");
    int posStrokeOpa = styleString.find("stroke-opacity:");
    int posStrokeWidth = styleString.find("stroke-width:");
    smatch matches;
    if (posFill != string::npos) {
        size_t fillEnd = styleString.find(";", posFill);
        fill = styleString.substr(posFill + 5, fillEnd - posFill - 5);
        if (fill.find("url") == string::npos) {

            fill = convert_String_to_RGB(fillRGB, fill, matches, rgbRegex);
        }
        else {
            int hashtagPos = fill.find("#");
            int stopPos = fill.find(")");
            fill = fill.substr(hashtagPos + 1, stopPos - hashtagPos - 1);
        }
    }
    if (posStroke != string::npos) {
        size_t strokeEnd = styleString.find(";", posStroke);
        stroke = styleString.substr(posStroke + 7, strokeEnd - posStroke - 7);

        if (stroke.find("url") == string::npos) {

            stroke = convert_String_to_RGB(strokeRGB, stroke, matches, rgbRegex);
        }
        else {
            int hashtagPos = stroke.find("#");
            int stopPos = stroke.find(")");
            stroke = stroke.substr(hashtagPos + 1, stopPos - hashtagPos - 1);
        }
    }
    else
    {
        strokeOpacity = strokeWidth = 0;
        strokeRGB = { 255,255,255 };
    }
    if (posFillOpa != string::npos) {
        size_t fillOpaEnd = styleString.find(";", posFillOpa);
        string fillOpaValue = styleString.substr(posFillOpa + 13, fillOpaEnd - posFillOpa - 13);
        fillOpacity = stod(fillOpaValue);
    }
    if (posStrokeOpa != string::npos) {
        size_t strokeOpaEnd = styleString.find(";", posStrokeOpa);
        string strokeOpaValue = styleString.substr(posStrokeOpa + 15, strokeOpaEnd - posStrokeOpa - 15);
        strokeOpacity = stod(strokeOpaValue);
    }
    if (posStrokeWidth != string::npos) {
        size_t strokeWidthEnd = styleString.find(";", posStrokeWidth);
        string strokeWidthValue = styleString.substr(posStrokeWidth + 13, strokeWidthEnd - posStrokeWidth - 13);
        strokeWidth = stod(strokeWidthValue);
    }
}

void convertStyleChild(string styleString, string& fill, string& stroke, RGB& fillRGB, RGB& strokeRGB, float& fillOpacity, float& strokeOpacity, float& strokeWidth, groupChild groupChild) {
    static regex rgbRegex("rgb\\((\\d+),\\s*(\\d+),\\s*(\\d+)\\)");
    int posFill = styleString.find("fill:");
    int posStroke = styleString.find("stroke:");
    int posFillOpa = styleString.find("fill-opacity:");
    int posStrokeOpa = styleString.find("stroke-opacity:");
    int posStrokeWidth = styleString.find("stroke-width:");
    smatch matches;
    if (posFill != string::npos) {
        size_t fillEnd = styleString.find(";", posFill);
        fill = styleString.substr(posFill + 5, fillEnd - posFill - 5);
        if (fill.find("url") == string::npos) {

            fill = convert_String_to_RGB(fillRGB, fill, matches, rgbRegex);
        }
        else {
            int hashtagPos = fill.find("#");
            int stopPos = fill.find(")");
            fill = fill.substr(hashtagPos + 1, stopPos - hashtagPos - 1);
        }
    }
    else {
        fillRGB = groupChild.fillRGB;
    }
    if (posStroke != string::npos) {
        size_t strokeEnd = styleString.find(";", posStroke);
        stroke = styleString.substr(posStroke + 7, strokeEnd - posStroke - 7);
        if (stroke.find("url") == string::npos) {

            stroke = convert_String_to_RGB(strokeRGB, stroke, matches, rgbRegex);
        }
        else {
            int hashtagPos = stroke.find("#");
            int stopPos = stroke.find(")");
            stroke = stroke.substr(hashtagPos + 1, stopPos - hashtagPos - 1);
        }
    }
    else {
        strokeRGB = groupChild.strokeRGB;
    }
    if (posFillOpa != string::npos) {
        size_t fillOpaEnd = styleString.find(";", posFillOpa);
        string fillOpaValue = styleString.substr(posFillOpa + 13, fillOpaEnd - posFillOpa - 13);
        fillOpacity = stod(fillOpaValue);
    }
    else {
        fillOpacity = groupChild.fillOpacity;
    }
    if (posStrokeOpa != string::npos) {
        size_t strokeOpaEnd = styleString.find(";", posStrokeOpa);
        string strokeOpaValue = styleString.substr(posStrokeOpa + 15, strokeOpaEnd - posStrokeOpa - 15);
        strokeOpacity = stod(strokeOpaValue);
    }
    else {
        strokeOpacity = groupChild.strokeOpacity;
    }
    if (posStrokeWidth != string::npos) {
        size_t strokeWidthEnd = styleString.find(";", posStrokeWidth);
        string strokeWidthValue = styleString.substr(posStrokeWidth + 13, strokeWidthEnd - posStrokeWidth - 13);
        strokeWidth = stod(strokeWidthValue);
    }
    else {
        strokeWidth = groupChild.strokeWidth;
    }
}

void convertStyleGradient(string styleString, string& id, string& gradientUnits, string& spreadMethod) {
    int posId = styleString.find("id:");
    int posGradientUnits = styleString.find("gradientUnits:");
    int posSpreadMethod = styleString.find("spreadMethod:");
    if (posId != string::npos) {
        size_t idEnd = styleString.find(";", posId);
        id = styleString.substr(posId + 3, idEnd - posId - 3);
    }
    if (posGradientUnits != string::npos) {
        size_t gradientUnitsEnd = styleString.find(";", posGradientUnits);
        gradientUnits = styleString.substr(posGradientUnits + 14, gradientUnitsEnd - posGradientUnits - 14);
    }
    if (posSpreadMethod != string::npos) {
        size_t spreadMethodEnd = styleString.find(";", posSpreadMethod);
        spreadMethod = styleString.substr(posSpreadMethod + 13, spreadMethodEnd - posSpreadMethod - 13);
    }
}

vector<string> split(string& s, char deli)
{
    vector<string> tokens;
    istringstream tokenStream(s);
    string token;
    while (getline(tokenStream, token, deli))
    {
        tokens.push_back(token);
    }
    return tokens;
}

bool containsKeyword(string& s, string keyword)
{
    return s.find(keyword) != string::npos;
}

string standardize(string transform)
{
    string result;

    int pos = 0;
    while (pos < transform.length())
    {
        int open = transform.find("(", pos);
        if (open == string::npos)
            break;

        int close = transform.find(")", open);
        if (close == string::npos)
            break;

        string content = transform.substr(open + 1, close - open - 1);

        if (content.find(",") == string::npos)
        {
            int space = content.find(" ");
            if (space != string::npos)
            {
                content.insert(space, ",");
            }
        }

        result += transform.substr(pos, open - pos + 1);
        result += content;
        result += ")";

        pos = close + 1;
    }

    result += transform.substr(pos);

    return result;
}

GraphicsState Shape::TransformSVG(Graphics& graphics, Transform transform)
{
    GraphicsState state = graphics.Save();
    Matrix transformMatrix;

    for (const string& operation : transform.transformOrder)
    {
        if (operation == "scale")
            if (checkScale)
                transformMatrix.Scale(transform.scaleX, transform.scaleX);
            else
                transformMatrix.Scale(transform.scaleX, transform.scaleY);
        else if (operation == "translate")
            transformMatrix.Translate(transform.translateX, transform.translateY);
        else if (operation == "rotate")
            transformMatrix.Rotate(transform.rotateAngle);
        else if (operation == "skew")
        {
            float skewX = tan(transform.skewX * static_cast<float>(M_PI) / 180.0f);
            float skewY = tan(transform.skewY * static_cast<float>(M_PI) / 180.0f);

            Matrix skewMatrix(1.0f, skewY, skewX, 1.0f, 0.0f, 0.0f);
            transformMatrix.Multiply(&skewMatrix);
        }
    }
    graphics.MultiplyTransform(&transformMatrix);
    return state;
}



void parseTransform(const string& transformStr, Transform& transform)
{
    transform.transformOrder.clear();
    string transformString = transformStr;
    transformString = standardize(transformString);
    vector<string> transformDeli = split(transformString, ' ');
    for (string& deli : transformDeli)
    {
        if (containsKeyword(deli, "rotate"))
        {
            transform.transformOrder.push_back("rotate");
        }
        else if (containsKeyword(deli, "scale"))
        {
            transform.transformOrder.push_back("scale");
        }
        else if (containsKeyword(deli, "translate"))
        {
            transform.transformOrder.push_back("translate");
        }
    }

    // X? lý translate
    smatch translateMatches;
    regex translateRegex("translate\\(([^,]+),([^)]+)\\)");
    if (regex_search(transformString, translateMatches, translateRegex))
    {
        transform.translateX = stof(translateMatches[1]);
        transform.translateY = stof(translateMatches[2]);
    }
    // X? lý rotate
    regex rotateRegex("rotate\\(([^)]+)\\)");
    smatch rotateMatches;
    if (regex_search(transformString, rotateMatches, rotateRegex))
    {
        transform.rotateAngle = stof(rotateMatches[1]);
    }
    // X? lý scale
    bool check = false;
    regex scaleCheck("scale\\((.*?)\\)");
    smatch scaleCheckMatches;
    regex scaleRegex("scale\\(([^,]+)(?:,([^)]+))?\\)");
    smatch scaleMatches;

    if (regex_search(transformString, scaleCheckMatches, scaleCheck))
    {
        string scalePart = scaleCheckMatches[1];
        if (scalePart.find(",") != string::npos)
            check = true;
    }

    if (regex_search(transformString, scaleMatches, scaleRegex))
    {

        float num1 = stof(scaleMatches[1].str());
        if (check)
        {
            float num2 = stof(scaleMatches[2].str());
            transform.scaleX = num1;
            transform.scaleY = num2;
        }
        else
        {
            checkScale = true;
            transform.scaleY = num1;
            transform.scaleX = num1;
        }
    }
}

void parseTransformMatrix(const string& transformStr, Transform& transform) {
    regex matrixRegex("matrix\\((.*?)\\)");
    smatch matrixMatches;
    if (regex_search(transformStr, matrixMatches, matrixRegex)) {
        string matrixStr = matrixMatches[1].str();
        double skewX, skewY;
        istringstream iss(matrixStr);
        iss >> transform.scaleX >> transform.skewX >> transform.skewY >> transform.scaleY >> transform.translateX >> transform.translateY;
        if (transform.scaleX != 1.0 && transform.scaleY != 1.0)
            transform.transformOrder.push_back("scale");
        if (transform.skewX != 0.0 && transform.skewY != 0.0)
            transform.transformOrder.push_back("skew");
        if (transform.translateX != 0.0 && transform.translateY != 0.0)
            transform.transformOrder.push_back("translate");
    }

}

vector<string> mergeVector(vector<string> v1, vector<string> v2)
{
    vector<string> v3;

    for (string s : v1)
    {
        bool found = false;
        for (string x : v2)
        {
            if (s == x)
            {
                found = true;

                break;
            }
        }

        if (!found)
        {
            v3.push_back(s);
        }
    }

    for (string s : v2)
    {
        v3.push_back(s);
    }
    return v3;
}

                
void parseTransformChild(const string& transformStr, Transform& transform, groupChild& groupChild)
{
    if (transformStr.find("matrix") != string::npos) {
        parseTransformMatrix(transformStr, transform);
    }
    else {
        parseTransform(transformStr, transform);

        if (!transformStr.empty())
        {
            transform.translateX += groupChild.transform.translateX;
            transform.translateY += groupChild.transform.translateY;
            transform.rotateAngle += groupChild.transform.rotateAngle;
            transform.rotateAngle = (transform.rotateAngle > 360) ? (transform.rotateAngle - 360) : transform.rotateAngle;
            transform.scaleX *= groupChild.transform.scaleX;
            transform.scaleY *= groupChild.transform.scaleY;
            transform.transformOrder = mergeVector(groupChild.transform.transformOrder, transform.transformOrder);
        }
        else
        {
            transform = groupChild.transform;
        }
    }

}


void parseTransformChildforText(const string& transformStr, Transform& transform, groupChild& groupChild, Transform& trans)
{
    if (transformStr.find("matrix") != string::npos) {
        parseTransformMatrix(transformStr, transform);
    }
    else {
        parseTransform(transformStr, transform);

        if (!transformStr.empty())
        {
            trans.translateX = transform.translateX;
            trans.translateY = transform.translateY;
            trans.rotateAngle = transform.rotateAngle;
            trans.scaleX = transform.scaleX;
            trans.scaleY = transform.scaleY;

            transform.translateX += groupChild.transform.translateX;
            transform.translateY += groupChild.transform.translateY;
            transform.rotateAngle += groupChild.transform.rotateAngle;
            transform.rotateAngle = (transform.rotateAngle > 360) ? (transform.rotateAngle - 360) : transform.rotateAngle;
            transform.scaleX *= groupChild.transform.scaleX;
            transform.scaleY *= groupChild.transform.scaleY;
            transform.transformOrder = mergeVector(groupChild.transform.transformOrder, transform.transformOrder);
        }
        else
        {
            transform = groupChild.transform;
        }
    }

}

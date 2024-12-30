#include "ReadFile.h"

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

void getNextNumberOfValues(string& s, int& i, int num, Path& path, char curType)
{
    int count = 0;
    for (int j = 0; j < num; ++j)
    {
        if (isdigit(s[i]) || s[i] == '-' || s[i] == '.' || s[i] == ' ')
        {
            size_t next_pos;
            double num_ = stod(s.substr(i), &next_pos);
            path.value.push_back(num_);
            i += next_pos;
        }
    }
    path.type.push_back(curType);
}

void convertPathToValue(string s, Path& path)
{
    char currentCommand = '\0';
    path.type.clear();
    path.value.clear();

    bool passM = false;
    s = chuanhoa(s);
    int i = 0;
    while (i < s.length())
    {
        if (isalpha(s[i]))
        {

            currentCommand = s[i];
            if (currentCommand == 'M' || currentCommand == 'm' && !passM)
                passM = true;
            i++;

            switch (currentCommand)
            {
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
        else
        {
            if (currentCommand == 'm' && passM)
                currentCommand = 'l';
            else if (currentCommand == 'M' && passM)
                currentCommand = 'L';
            i++;
            switch (currentCommand)
            {
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
        if (s[i] >= '0' && s[i] <= '9' || s[i] == '-' || s[i] == '.')
        {
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
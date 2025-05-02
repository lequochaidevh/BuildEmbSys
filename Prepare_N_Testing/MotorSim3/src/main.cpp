#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
// Lớp cha: ParentShape
class ParentShape {
public:
    virtual void draw(sf::RenderWindow& window) = 0; // Hàm vẽ (thuộc tính ảo)
    virtual void rotate(float angle) = 0;  // Hàm xoay (thuộc tính ảo)
    virtual ~ParentShape() {}  // Destructor ảo để đảm bảo hủy đúng loại đối tượng
};

// Lớp đại diện cho hình tròn
class Circle : public ParentShape {
public:
    float radius;
    sf::CircleShape shape;

    sf::Vector2f rotationPoint;
    sf::Vector2f relativePosition;
    // Constructor khởi tạo hình tròn
    Circle(float r, sf::Vector2f center) : radius(r) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(radius, radius);  // Đặt tâm của hình tròn tại (0, 0)
        shape.setPosition(center);
    }

    // Hàm vẽ hình tròn
    void draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    // Hàm xoay hình tròn
    void rotate(float angle) override {
        shape.rotate(angle);
    }
};

// Lớp đại diện cho hình vuông
class Square : public ParentShape {
public:
    float size;
    sf::RectangleShape shape;
    sf::Vector2f m_center;
    sf::Vector2f rotationPoint;
    // Constructor khởi tạo hình vuông
    Square(float s, sf::Vector2f center) : size(s) {
        shape.setSize(sf::Vector2f(size, size));
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(size / 2, size / 2);  // Đặt tâm của hình vuông tại (0, 0) // Goc xoay
        shape.setPosition(center); // Position in window
        m_center = center;
    }

    // Function to rotate the square around a specific point
    void rotateAroundPoint(float angle, sf::Vector2f rotationPoint) {
        // Set the origin to the point around which we want to rotate
        shape.setOrigin(rotationPoint - shape.getPosition());

        // Apply the rotation
        shape.rotate(angle);

        // Reset the origin back to the center of the square after rotation
        shape.setOrigin(size / 2, size / 2);
    }

    // Hàm vẽ hình vuông
    void draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }
    void rotate(float angle) override {
        sf::Vector2f squarePosition = shape.getPosition();
        float offsetX = squarePosition.x - rotationPoint.x;
        float offsetY = squarePosition.y - rotationPoint.y;

        // Rotate the square around the point (using the angle)
        float radians = angle * 3.14159265f / 180.f; // Convert degrees to radians
        float cosAngle = std::cos(radians);
        float sinAngle = std::sin(radians);

        // New position after rotation
        float newX = rotationPoint.x + offsetX * cosAngle - offsetY * sinAngle;
        float newY = rotationPoint.y + offsetX * sinAngle + offsetY * cosAngle;
        shape.rotate(angle);
        // Set the new position of the square
        shape.setPosition(newX, newY);

    }

    // Hàm xoay hình vuông
    //    void rotate(float angle) override {
    //        // Calculate the offset from the rotation point to the square's center
    //        sf::Vector2f squarePosition = shape.getPosition();
    //        float offsetX = squarePosition.x - rotationPoint.x;
    //        float offsetY = squarePosition.y - rotationPoint.y;

    //        // Rotate the square around the point (using the angle)
    //        float radians = angle * 3.14159265f / 180.f; // Convert degrees to radians
    //        float cosAngle = std::cos(radians);
    //        float sinAngle = std::sin(radians);

    //        // New position after rotation
    //        float newX = rotationPoint.x + offsetX * cosAngle - offsetY * sinAngle;
    //        float newY = rotationPoint.y + offsetX * sinAngle + offsetY * cosAngle;

    //        // Set the new position of the square
    //        shape.setPosition(newX, newY);

    //        // Rotate the square around its own center (if needed)
    //        shape.setRotation(angle);
    //    }
    //    void rotate(float angle) override {
    //        //relativePosition = shape.getPosition() - rotationPoint;
    //        //shape.setOrigin(rotationPoint);
    //        shape.rotate(angle);
    //        //shape.setPosition(rotationPoint + relativePosition);
    //    }
};

// Lớp ShapeGround chứa các hình động
class ShapeGround {
public:
    ParentShape* inside;  // Con trỏ đến hình bên trong
    //ParentShape* outside; // Con trỏ đến hình bên ngoài
    std::vector<ParentShape*> outside;
    // Constructor
    ShapeGround(ParentShape* in, std::vector<ParentShape*> out) {
        inside = in;
        outside = out;
    }

    // Hàm vẽ các hình
    void draw(sf::RenderWindow& window) {
        inside->draw(window);
        for (ParentShape* it_shape : outside) {
            it_shape->draw(window);  // Call the draw function of each shape, passing the window
        }
    }

    // Hàm xoay các hình
    void rotate(float angle) {
        inside->rotate(angle);
        for (ParentShape* it_shape : outside) {
            it_shape->rotate(angle);  // Call the draw function of each shape, passing the window
        }
    }
};

// Lớp đại diện cho bộ sưu tập hình và xoay chúng
class ShapeCollection {
public:
    ShapeGround shapeGround;

    // Constructor khởi tạo các hình với tọa độ tâm và kích thước
    // Constructor chỉ khởi tạo ShapeGround và không truyền các hình dạng vào
    ShapeCollection(ShapeGround& shapeGroundObj)
        : shapeGround(shapeGroundObj) {}
    // Hàm vẽ tất cả các hình
    void draw(sf::RenderWindow& window) {
        shapeGround.draw(window);
    }

    // Hàm xoay tất cả các hình
    void rotate(float angle) {
        shapeGround.rotate(angle);
    }
};

sf::Vector2f rotationPointGlobal;

void setSquarePosition(Square &m_square, float x, float y) {
    m_square.rotationPoint = m_square.m_center;
    sf::Vector2f currentPosition = m_square.shape.getPosition();
    m_square.shape.setPosition(currentPosition.x + x, currentPosition.y + y);
}


void setSquarePosition3(Square &m_square, float x, float y) {
    sf::Vector2f currentPosition = m_square.m_center;
    m_square.shape.setPosition(currentPosition.x + x, currentPosition.y );

    m_square.shape.setOrigin(sf::Vector2f(0, 0));
    //sf::Vector2f setOriginVec2f = currentPosition - m_square.shape.getPosition();
    std::cout << "*********" << std::endl;

    std::cout << m_square.shape.getOrigin().x << std::endl;
    std::cout << m_square.shape.getOrigin().y << std::endl;

    std::cout << m_square.shape.getPosition().x << std::endl;
    std::cout << m_square.shape.getPosition().y << std::endl;

    //m_square.rotationPoint = m_square.shape.getOrigin() - sf::Vector2f(x, y);

}
void setSquarePosition2(Square &m_square, float x, float y) {
    //m_square.shape.setOrigin((m_square.size - x), (m_square.size - y));
    sf::Vector2f currentPosition = m_square.shape.getPosition();
    m_square.shape.setPosition(currentPosition.x + x, currentPosition.y + y);
    //m_square.shape.setOrigin((m_square.size+x*2)/2 , m_square.size/2 - y);  // Center of the square
    //sf::Vector2f rotationPoint = m_square.shape.getOrigin() - sf::Vector2f(x/2, y);
    // Set the origin to the point around which we want to rotate
    //m_square.shape.setOrigin(rotationPoint);
    rotationPointGlobal = m_square.shape.getPosition() + m_square.shape.getOrigin() - sf::Vector2f(x, y);
    //sf::Vector2f a(2.0 ,3.0);sf::Vector2f b(2.0 ,3.0);sf::Vector2f c = a + b;
    std::cout << m_square.shape.getPosition().x << std::endl;
    std::cout << m_square.shape.getOrigin().x << std::endl;
    std::cout << x << std::endl;
    std::cout << rotationPointGlobal.x << std::endl;
    m_square.rotationPoint = m_square.shape.getOrigin() - sf::Vector2f(x, y);
    m_square.shape.setOrigin(m_square.rotationPoint);
    // Apply the rotation
    //m_square.shape.rotate(angle);

    // Reset the origin back to the center of the square after rotation
    //m_square.shape.setOrigin(m_square.size / 2, m_square.size / 2);

    //    m_square.shape.setPosition(m_square.shape.getPosition().x + x, m_square.shape.getPosition().y + y);
    //    m_square.shape.setOrigin(m_square.size / 2, m_square.size / 2);
}

int main() {
    // Tạo cửa sổ để hiển thị hình
    sf::RenderWindow window(sf::VideoMode(1200, 1200), "ShapeGround Example");

    Circle circle1(100.0f, sf::Vector2f(400, 300));
    Square square1(200.0f, sf::Vector2f(400, 300));

    Circle circle2(100.0f, sf::Vector2f(650, 500));
    sf::Vector2f shapeCenter;

    sf::CircleShape point(5); // A small circle as the point
    point.setFillColor(sf::Color::Black);
    // Position the point at the center of the shape

    Square square21(50.0f, sf::Vector2f(650, 500));
    Square square22(50.0f, sf::Vector2f(650, 500));
    Square square23(50.0f, sf::Vector2f(650, 500));
    Square square24(50.0f, sf::Vector2f(650, 500));
    setSquarePosition(square21,50.0, 0.0);
    //setSquarePosition(square22,-50.0,0.0);
    //setSquarePosition(square23, 0.0, 50.0);
    //setSquarePosition(square24,0.0,-50.0);

    // Tạo một đối tượng ShapeCollection với các hình động
    //ShapeCollection shapes(100.0f, 100.0f, sf::Vector2f(400, 300));
    // Tạo đối tượng ShapeGround với các hình này
    std::vector<ParentShape*> minorVecShape1, minorVecShape2;
    minorVecShape1.push_back(&circle1);

    minorVecShape2.push_back(&square21);
    //minorVecShape2.push_back(&square22);
    //minorVecShape2.push_back(&square23);
    //minorVecShape2.push_back(&square24);
    shapeCenter = square21.shape.getPosition() - square21.shape.getOrigin();
    point.setPosition(shapeCenter - sf::Vector2f(point.getRadius(), point.getRadius()));
    ShapeGround shapeGround1(&square1, minorVecShape1);
    ShapeGround shapeGround2(&circle2, minorVecShape2);

    // Tạo đối tượng ShapeCollection và truyền ShapeGround vào
    ShapeCollection shapes1(shapeGround1);
    ShapeCollection shapes2(shapeGround2);
    // Biến góc quay
    float rotationSpeed = 0.07f;  // Tốc độ quay (độ/quá trình vẽ)

    // Load a font (make sure you have a valid path to a font file)
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        return -1;  // Error loading font
    }



    // Vòng lặp chính
    while (window.isOpen()) {
        // Xử lý sự kiện
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Xóa màn hình
        window.clear(sf::Color::White);

        // Quay hình
        shapes1.rotate(rotationSpeed);
        shapes2.rotate(rotationSpeed);

        // Vẽ tất cả các hình
        shapes1.draw(window);
        shapes2.draw(window);

        // Create a text object for the asterisk symbol
        sf::Text originSymbol("o", font, 20);  // 20 is the text size
        //originSymbol.setFillColor(sf::Color::Red);  // Set the color of the symbol
        //originSymbol.setPosition(rotationPointGlobal.x, rotationPointGlobal.y);  // Position the symbol at the origin
        //window.draw(originSymbol);
        // Hiển thị các hình đã vẽ
        window.draw(point);

        window.display();
    }

    return 0;
}

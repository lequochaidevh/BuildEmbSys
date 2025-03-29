#include <SFML/Graphics.hpp>
#include <iostream>

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

    // Constructor khởi tạo hình vuông
    Square(float s, sf::Vector2f center) : size(s) {
        shape.setSize(sf::Vector2f(size, size));
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(size / 2, size / 2);  // Đặt tâm của hình vuông tại (0, 0)
        shape.setPosition(center);
    }

    // Hàm vẽ hình vuông
    void draw(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    // Hàm xoay hình vuông
    void rotate(float angle) override {
        shape.rotate(angle);
    }
};

// Lớp ShapeGround chứa các hình động
class ShapeGround {
public:
    ParentShape* inside;  // Con trỏ đến hình bên trong
    ParentShape* outside; // Con trỏ đến hình bên ngoài

    // Constructor
    ShapeGround(ParentShape* in, ParentShape* out) {
        inside = in;
        outside = out;
    }

    // Hàm vẽ các hình
    void draw(sf::RenderWindow& window) {
        inside->draw(window);
        outside->draw(window);
    }

    // Hàm xoay các hình
    void rotate(float angle) {
        inside->rotate(angle);
        outside->rotate(angle);
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

int main() {
    // Tạo cửa sổ để hiển thị hình
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "ShapeGround Example");

    Circle circle(50.0f, sf::Vector2f(400, 300));
    Square square(200.0f, sf::Vector2f(400, 300));


    // Tạo một đối tượng ShapeCollection với các hình động
    //ShapeCollection shapes(100.0f, 100.0f, sf::Vector2f(400, 300));

    // Tạo đối tượng ShapeGround với các hình này
    ShapeGround shapeGround(&square, &circle);

    // Tạo đối tượng ShapeCollection và truyền ShapeGround vào
    ShapeCollection shapes(shapeGround);
    // Biến góc quay
    float rotationSpeed = 0.07f;  // Tốc độ quay (độ/quá trình vẽ)

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
        shapes.rotate(rotationSpeed);

        // Vẽ tất cả các hình
        shapes.draw(window);

        // Hiển thị các hình đã vẽ
        window.display();
    }

    return 0;
}

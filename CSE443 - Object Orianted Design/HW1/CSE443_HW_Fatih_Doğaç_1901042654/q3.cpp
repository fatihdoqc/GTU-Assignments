class LibSquare {
public:
    // Constructors, destructor,
    int32_t getSide();
    void setSide(const int32_t);
private:
    int32_t side;
};


class LibCircle {
public:
    // Constructors, destructor,
    int32_t getRadius();
    void setRadius(const int32_t);
private:
    int32_t radius;
};


class ShapeConcept
{
public:
    virtual ~ShapeConcept() = default;
    virtual void draw() const = 0
}

template< typename ShapeT
    , typename DrawStrategy >
class ShapeModel : public ShapeConcept
{
public:
    explicit ShapeModel( ShapeT shape, DrawStrategy drawer )
    : shape_{ std::move(shape) }
    , drawer_{ std::move(drawer) }
    {}
    
    void draw() const override { drawer_(shape_); }

private:
    ShapeT shape_;
    DrawStrategy drawer_;
};

int main(){

    using Shapes = std::vector<std::unique_ptr<ShapeConcept>>;
    using CircleModel = ShapeModel<Circle,DrawStrategy>;
    using SquareModel = ShapeModel<Square,DrawStrategy>;

    Shapes shapes{};

    shapes.emplace_back(
        std::make_unique<CircleModel>(Circle{2.3}, DrawStrategy(/*...red...*/) ) );
    shapes.emplace_back(
        std::make_unique<SquareModel>(Square{1.2}, DrawStrategy(/*...green...*/) ) );
    shapes.emplace_back(
        std::make_unique<CircleModel>(Circle{4.1}, DrawStrategy(/*...blue...*/) ) );
    
    // Drawing all shapes
    for( auto const& shape : shapes )
    {
        shape->draw();
    }

    return EXIT_SUCCESS;
}
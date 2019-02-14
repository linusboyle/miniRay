#include "vector.hpp"
#include "image.hpp"
#include <cassert>

using namespace graphics;

int main() {

    // test vectors

    Vector3 a = {1, 0, 0};
    Vector3 b = {0, 1, 0};
    Vector3 c = {0, 0, 1};
    
    assert(-(-a) == a);
    assert((a + b + c) == Vector3(1, 1, 1));
    assert(scalarProduct(a, b) == 0);
    assert(a / 2 == Vector3(0.5, 0, 0));

    // right-hand frame
    assert(a * b == c);
    assert(a * c == -b);
    assert(b * c == a);
    assert(b * a == -c);
    assert(c * a == b);
    assert(c * b == -a);

    // cross
    assert(Vector3(2.4,0,0) * Vector3(0, 5.5, 0) == Vector3(0, 0, 13.2)); 

    // color / image
    Image img(Width(512), Height(512));
    img.fillcolor({12, 123, 230});
    img.writeout("pure.png");

    return 0;
}

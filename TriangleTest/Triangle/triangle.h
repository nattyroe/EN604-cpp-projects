
class Triangle
{
public:
    Triangle(int sideLength1, int sideLength2, int sideLength3);
    bool IsValidTriangle();

private:
    int mSideLength1 = 0;
    int mSideLength2 = 0;
    int mSideLength3 = 0;
};

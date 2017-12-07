#include <tuple>

	struct ThreePoints
	{
		double X1, X2, X3, Y1, Y2, Y3;
		ThreePoints(double X1, double Y1, double X2, double Y2, double X3, double Y3)
		{
			this->X1 = X1;
			this->X2 = X2;
			this->X3 = X3;
			this->Y1 = Y1;
			this->Y2 = Y2;
			this->Y3 = Y3;
		}
	};
	
	std::tuple<double, double, double> getCircle(ThreePoints MyPoints)
	{
		double Cx = 0, Cy = 0, r = 0;
		if (((MyPoints.X2 - MyPoints.X1) * (MyPoints.Y3 - MyPoints.Y2) - (MyPoints.Y2 - MyPoints.Y1) * (MyPoints.X3 - MyPoints.X2)) == 0)
			return std::make_tuple(0, 0, 0);
		Cx = ((MyPoints.Y3 - MyPoints.Y1)*((MyPoints.X2 - MyPoints.X1) * (MyPoints.X1 + MyPoints.X2) + (MyPoints.Y2 - MyPoints.Y1) * (MyPoints.Y1 + MyPoints.Y2)) - (MyPoints.Y2 - MyPoints.Y1)*((MyPoints.X3 - MyPoints.X1) * (MyPoints.X1 + MyPoints.X3) + (MyPoints.Y3 - MyPoints.Y1) * (MyPoints.Y1 + MyPoints.Y3))) / (2 * ((MyPoints.X2 - MyPoints.X1) * (MyPoints.Y3 - MyPoints.Y2) - (MyPoints.Y2 - MyPoints.Y1) * (MyPoints.X3 - MyPoints.X2)));
		Cy = ((MyPoints.X2 - MyPoints.X1)*((MyPoints.X3 - MyPoints.X1) * (MyPoints.X1 + MyPoints.X3) + (MyPoints.Y3 - MyPoints.Y1) * (MyPoints.Y1 + MyPoints.Y3)) - (MyPoints.X3 - MyPoints.X1)*((MyPoints.X2 - MyPoints.X1) * (MyPoints.X1 + MyPoints.X2) + (MyPoints.Y2 - MyPoints.Y1) * (MyPoints.Y1 + MyPoints.Y2))) / (2 * ((MyPoints.X2 - MyPoints.X1) * (MyPoints.Y3 - MyPoints.Y2) - (MyPoints.Y2 - MyPoints.Y1) * (MyPoints.X3 - MyPoints.X2)));
		r = sqrtf((MyPoints.X1 - Cx) * (MyPoints.X1 - Cx) + (MyPoints.Y1 - Cy) * (MyPoints.Y1 - Cy));	
		return std::make_tuple(Cx, Cy, r);
	}
	
	static class Angles {
		///Вычисление углов с помощью векторов
	public:
		static double getStartAngle(double X1, double Y1, double Cx, double Cy, double r)
		{
			return  (sqrt(pow(-r, 2)) * sqrt(pow(-(X1 - Cx), 2) + pow(-(Y1 - Cy), 2))) == 0? 
				0:
				acos((r * (Y1 - Cy)) / (sqrt(pow(-r, 2)) * sqrt(pow(-(X1 - Cx), 2) + pow(-(Y1 - Cy), 2)))) / 3.141592653589793 * 180;
		}
		static double getAngle(double X1, double Y1, double X3, double Y3, double Cx, double Cy)
		{
			return (sqrt(pow(-(X1 - Cx), 2) + pow(-(Y1 - Cy), 2)) * sqrt(pow(-(X3 - Cx), 2) + pow(-(Y3 - Cy), 2))) == 0?
				0:
				acos(((X1 - Cx) * (X3 - Cx) + (Y1 - Cy) * (Y3 - Cy)) / (sqrt(pow(-(X1 - Cx), 2) + pow(-(Y1 - Cy), 2)) * sqrt(pow(-(X3 - Cx), 2) + pow(-(Y3 - Cy), 2)))) / 3.141592653589793 * 180;
		}
	};


	std::tuple<double, double, double> getNormal(double First[], double Second[], double Third[]){
		double a, b, c;
		double vec1[] = {First[0] - Second[0], First[1] - Second[1], First[2] - Second[2]}, vec2[] = {Third[0] - Second[0], Third[1] - Second[1], Third[2] - Second[2]};
		a = vec1[1] * vec2[2] - vec1[2] * vec2[1];
		b = vec1[2] * vec2[0] - vec1[0] * vec2[2];
		c = vec1[0] * vec2[1] - vec1[1] * vec2[0];
		a /= sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
		b /= sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
		c /= sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
		return std::make_tuple(a, b, c);
	}

	
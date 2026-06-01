#pragma once
#include <string>
#include <iostream>

namespace KTools
{
	template <typename T>
	class Vector3
	{
	public:
		T x = 0;
		T y = 0;
		T z = 0;


	private:

	public:
		Vector3();
		Vector3(T);
		Vector3(T, T, T);
		//~Vector3();

		std::string ToString();

		const T DotProduct(const Vector3&) const;
		Vector3 CrossProduct(Vector3&);
		Vector3<double> Normalise();
		static Vector3<double> Normalise(const Vector3&);

		Vector3 Invert() const;

		Vector3 operator+(T);
		void operator+=(T);
		Vector3 operator+(const Vector3&) const;
		void operator+=(const Vector3&);

		Vector3* operator-(T);
		void operator-=(T);
		Vector3 operator-(const Vector3&);
		void operator-=(const Vector3&);

		Vector3 operator*(T) const;
		void operator*=(T);

		Vector3 operator*(const Vector3&) const;
		void operator*=(const Vector3&);

		Vector3 operator/(T);
		void operator/=(T);

		bool operator== (Vector3);

		double LengthSquared() const;
		double Magnitude() const;

		static Vector3 Random();
		static Vector3 Random(double min, double max);
		static inline Vector3 RandomUnitVector();
		static inline Vector3 RandomOnHemisphere(const Vector3& normal);
		static inline Vector3 ReflectOnNormal(const Vector3& vec, const Vector3& normal);
		static Vector3 Refract(const Vector3& uv, const Vector3& n, double etaiOverEtat);
		static Vector3 RandomInUnitDisk();

	private:
	};
}

//Defintion
namespace KTools
{
	template <typename T>
	Vector3<T>::Vector3()
	{

	}

	template <typename T>
	Vector3<T>::Vector3(T n)
	{
		x = n;
		y = n;
		z = n;
	}

	template <typename T>
	Vector3<T>::Vector3(T setX, T setY, T setZ)
	{
		x = setX;
		y = setY;
		z = setZ;
	}

	template <typename T>
	const T Vector3<T>::DotProduct(const Vector3& other) const
	{
		T runningSum = 0;
		runningSum += x * other.x;
		runningSum += y * other.y;
		runningSum += z * other.z;
		return runningSum;
	}

	template <typename T>
	Vector3<T> Vector3<T>::CrossProduct(Vector3& other)
	{
		T iComponent = y * other.z - z * other.y;
		T jComponent = z * other.x - x * other.z;
		T kComponent = x * other.y - y * other.x;
		Vector3<T> newVector(iComponent, jComponent, kComponent);
		
		return newVector;
	}

	template <typename T>
	Vector3<double> Vector3<T>::Normalise()
	{
		double mag = Magnitude();
		double xComponent = x / mag;
		double yComponent = y / mag;
		double zComponent = z / mag;
		Vector3<double> normalisedVector(xComponent, yComponent, zComponent);

		return normalisedVector;
	}

	template <typename T>
	Vector3<double> Vector3<T>::Normalise(const Vector3<T>& other)
	{
		double mag = sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
		double xComponent = other.x / mag;
		double yComponent = other.y / mag;
		double zComponent = other.z / mag;
		Vector3<double> normalisedVector(xComponent, yComponent, zComponent);
		return normalisedVector;
	}


	template <typename T>
	Vector3<T> Vector3<T>::Invert() const
	{
		return {x * -1, y * -1, z * -1};
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator+(T scalar)
	{
		return {x + scalar, y + scalar, z + scalar};
	}

	template <typename T>
	void Vector3<T>::operator+=(T scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator+(const Vector3& other) const
	{
		return {x + other.x, y + other.y, z + other.z};
	}

	template <typename T>
	void Vector3<T>::operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	template <typename T>
	Vector3<T>* Vector3<T>::operator-(T scalar)
	{
		Vector3<T> outVector = *new Vector3<T>(x, y, z);
		outVector -= scalar;
		return &outVector;
	}

	template <typename T>
	void Vector3<T>::operator-=(T scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator-(const Vector3& other)
	{
		return {x - other.x, y - other.y, z - other.z};
	}

	template <typename T>
	void Vector3<T>::operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator*(T scalar) const
	{
		return {x * scalar, y * scalar, z * scalar};
	}

	template <typename T>
	void Vector3<T>::operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator*(const Vector3<T>& other) const
	{
		return {x * other.x, y *  other.y, z *  other.z};
	}

	template <typename T>
	void Vector3<T>::operator*=(const Vector3<T>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator/(T scalar)
	{
		return {x / scalar, y / scalar, z / scalar};
	}

	template <typename T>
	void Vector3<T>::operator/=(T scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
	}

	template <typename T>
	bool Vector3<T>::operator==(Vector3<T> other)
	{
		if (x != other.x)
			return false;
		if (y != other.y)
			return false;
		if (z != other.z)
			return false;
		return true;
	}

	template <typename T>
	std::string Vector3<T>::ToString()
	{
		std::string outputString = "( ";
		outputString += std::to_string(x) + ", ";
		outputString += std::to_string(y) + ", ";
		outputString += std::to_string(z);
		outputString += " )";
		return outputString;
	}


	template <typename T>
	double Vector3<T>::LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	template <typename T>
	double Vector3<T>::Magnitude() const
	{
		double magSqrd = x * x + y * y + z * z;
		return sqrt(magSqrd);
	}

	template <typename T>
	Vector3<T> Vector3<T>::Random()
	{
		return Vector3<T>(std::rand() / (RAND_MAX + 1.0), std::rand() / (RAND_MAX + 1.0), std::rand() / (RAND_MAX + 1.0));
	}

	template <typename T>
	Vector3<T> Vector3<T>::Random(double min, double max)
	{
		return Vector3<T>(
			min + (max-min)*std::rand() / (RAND_MAX + 1.0),
			min + (max-min)*std::rand() / (RAND_MAX + 1.0),
			min + (max-min)*std::rand() / (RAND_MAX + 1.0));
	}

	template <typename T>
	Vector3<T> Vector3<T>::RandomUnitVector()
	{
		int attempt = 0;
		while (attempt < 1000000)
		{
			Vector3<double> p = Vector3<double>::Random(-1.0, 1.0);
			double lensq = p.LengthSquared();
			if (1e-160 && lensq <= 1)
			{
				return p / sqrt(lensq);
			}
			attempt++;
		}
	}

	template <typename T>
	Vector3<T> Vector3<T>::RandomOnHemisphere(const Vector3& normal)
	{
		Vector3 onUnitSphere = RandomUnitVector();
		if (onUnitSphere.DotProduct(normal) > 0.0)
			return onUnitSphere;
		else 
			return onUnitSphere * -1;
	}

	template <typename T>
	Vector3<T> Vector3<T>::ReflectOnNormal(const Vector3<T>& vec, const Vector3<T>& normal)
	{
		Vector3<T> intermediary = vec;
		return intermediary - ((normal * 2) * vec.DotProduct(normal));
	}

	template <typename T>
	Vector3<T> Vector3<T>::Refract(const Vector3& uv, const Vector3& n, double etaiOverEtat)
	{
		double cosTheta = std::min((uv * -1).DotProduct(n), 1.0);
		Vector3<T> rOutPerp = (uv + n * cosTheta) * etaiOverEtat;
		Vector3<T> rOutParallel = n * -sqrt(abs(1.0 - rOutPerp.LengthSquared()));
		return rOutPerp + rOutParallel;
	}

	/*
	* Generates vector in XY plane within unit circle
	*/
	template <typename T>
	Vector3<T> Vector3<T>::RandomInUnitDisk()
	{
		// simplifed version of https://stackoverflow.com/questions/5837572/generate-a-random-point-within-a-circle-uniformly
		// as it is known unit circle
		double r = sqrt(randomDouble());
		double theta = randomDouble() * 2 * PI;
		double x = r * cos(theta);
		double y = r * sin(theta);
		return Vector3<T>( x, y, 0);
	}

}
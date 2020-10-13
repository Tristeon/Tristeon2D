#pragma once
#include <cmath>
#include <json.h>
#include <stdexcept>
#include <Standard/String.h>

#include "Serialization/Type.h"

namespace Tristeon
{
	template <typename Type = float>
	struct VectorType
	{
		Type x{};
		Type y{};

#pragma region Constructors
		VectorType() = default;
		~VectorType() = default;

		VectorType(const Type& x, const Type& y) : x(x), y(y) { }

		template<typename T = Type>
		VectorType(const VectorType& copy)
		{
			x = (Type)copy.x;
			y = (Type)copy.y;
		}

		template<typename T = Type>
		VectorType& operator=(const VectorType<T>& copy)
		{
			x = (Type)copy.x;
			y = (Type)copy.y;
			return *this;
		}

		template<typename T>
		explicit operator VectorType<T>() const
		{
			return { (T)x, (T)y };
		}
#pragma endregion

#pragma region Quick Vectors
		/**
		* (0, -1)
		*/
		[[nodiscard]] static VectorType down() { return VectorType(0, -1); }
		/**
		* (0, 1)
		*/
		[[nodiscard]] static VectorType up() { return VectorType(0, 1); }
		/**
		* (1, 0)
		*/
		[[nodiscard]] static VectorType right() { return VectorType(1, 0); }

		/**
		* (-1, 0)
		*/
		[[nodiscard]] static VectorType left() { return VectorType(-1, 0); }

		/**
		* (0, 0)
		*/
		[[nodiscard]] static VectorType zero() { return VectorType(0, 0); }
		/**
		* (1, 1)
		*/
		[[nodiscard]] static VectorType one() { return VectorType(1, 1); }
#pragma endregion
		
#pragma region Operators
		template<typename T = Type>
		[[nodiscard]] bool operator==(const VectorType<T>& other) const
		{
			return x == other.x && y == other.y;
		}

		template<typename T = Type>
		[[nodiscard]] bool operator!=(const VectorType<T>& other) const
		{
			return x != other.x && y != other.y;
		}

		template<typename T = Type>
		void operator*=(const VectorType<T>& other)
		{
			x *= other.x;
			y *= other.y;
		}

		template<typename T = Type>
		[[nodiscard]] VectorType operator*(const VectorType<T>& other) const
		{
			return { x * other.x, y * other.y };
		}

		void operator*=(const Type& multiplier)
		{
			x *= multiplier;
			y *= multiplier;
		}

		[[nodiscard]] VectorType operator*(const Type& multiplier) const
		{
			return { x * multiplier, y * multiplier };
		}

		template<typename T = Type>
		void operator/=(const VectorType<T>& other)
		{
			x /= other.x;
			y /= other.y;
		}

		template<typename T = Type>
		[[nodiscard]] VectorType operator/(const VectorType<T>& other) const
		{
			return { x / other.x, y / other.y };
		}

		void operator/=(const Type& divider)
		{
			x /= divider;
			y /= divider;
		}

		[[nodiscard]] VectorType operator/(const Type& divider) const
		{
			return { x / divider, y / divider };
		}

		template<typename T = Type>
		void operator+=(const VectorType<T>& other)
		{
			x += other.x;
			y += other.y;
		}

		template<typename T = Type>
		[[nodiscard]] VectorType operator+(const VectorType<T>& other) const
		{
			return { x + other.x, y + other.y };
		}

		template<typename T = Type>
		void operator-=(const VectorType<T>& other)
		{
			x -= other.x;
			y -= other.y;
		}

		template<typename T = Type>
		[[nodiscard]] VectorType operator-(const VectorType<T>& other) const
		{
			return { x - other.x, y - other.y };
		}

		[[nodiscard]] VectorType operator-() const
		{
			return { -x, -y };
		}

		[[nodiscard]] Type& operator[](const unsigned int& index)
		{
			if (index == 0)
				return x;
			if (index == 1)
				return y;
			throw std::invalid_argument("index used in Vector::operator[] can't be more than 1!");
		}

		template<typename T = Type>
		[[nodiscard]] bool operator<(const VectorType<T>& other) const
		{
			if (x < other.x)
				return true;
			if (x > other.x)
				return false;
			return y < other.y;
		}

		template<typename T = Type>
		[[nodiscard]] bool operator>(const VectorType<T>& other) const
		{
			if (x > other.x)
				return true;
			if (x < other.x)
				return false;
			return y > other.y;
		}
#pragma endregion

#pragma region Math operations
		[[nodiscard]] Type magnitude() const
		{
			return sqrt(x * x + y * y);
		}

		void normalize()
		{
			if (x == 0 && y == 0)
				return;

			const auto mag = magnitude();

			x /= mag;
			y /= mag;
		}

		[[nodiscard]] VectorType normalized() const
		{
			VectorType vec = *this;
			vec.normalize();
			return vec;
		}

		void floor()
		{
			x = floorf(x);
			y = floorf(y);
		}

		template<typename T = Type>
		[[nodiscard]] static VectorType floor(VectorType<T> vector)
		{
			vector.floor();
			return vector;
		}

		void ceil()
		{
			x = ceilf(x);
			y = ceilf(y);
		}

		template<typename T = Type>
		[[nodiscard]] static VectorType ceil(VectorType<T> vector)
		{
			vector.ceil();
			return vector;
		}

		void round()
		{
			x = roundf(x);
			y = roundf(y);
		}

		template<typename T = Type>
		[[nodiscard]] static VectorType round(VectorType<T> vector)
		{
			vector.round();
			return vector;
		}

		template<typename TA = Type, typename TB = Type>
		static Type dot(const VectorType<TA>& a, const VectorType<TB>& b)
		{
			return a.x * b.x + a.y * b.y;
		}

		template<typename TA = Type, typename TB = Type>
		static Type angleBetween(const VectorType<TA>& a, const VectorType<TB>& b)
		{
			return acos(dot(a, b) / (a.magnitude() * b.magnitude())) * 180.0f / 3.14159265;
		}

		Type angle() const
		{
			return -(atan2(y, x) * 180.0f / 3.14159265);
		}

		template<typename TA = Type, typename TB = Type>
		static Type distance(const VectorType<TA>& a, const VectorType<TB>& b)
		{
			const VectorType diff = b - a;
			return diff.magnitude();
		}

		template<typename TA = Type, typename TB = Type>
		static VectorType lerp(const VectorType<TA>& a, const VectorType<TB>& b, const float& t)
		{
			if (b == a) return b;
			if (t == 0) return a;
			if (t == 1) return b;

			const auto interpolation = distance(a, b) * t;
			const auto linearDirection = (b - a).normalized();
			return linearDirection * interpolation + a;
		}
#pragma endregion

#pragma region Misc
		[[nodiscard]] String toString() const
		{
			return "{ " + std::to_string(x) + ", " + std::to_string(y) + " }";
		}

		/**
		 * Convert to any given type, assuming it has a (float, float) constructor.
		 */
		template<typename T>
		[[nodiscard]] constexpr T convert() const { return T{ x, y }; }

		/**
		 * Convert any given type to a Vector3, assuming it has an x, y, and z field.
		 */
		template<typename T>
		[[nodiscard]] static constexpr VectorType convert(T* vec) { return VectorType{ vec->x, vec->y }; }

		/**
		 * Convert any given type to a Vector3, assuming it has an x, y, and z field.
		 */
		template<typename T>
		[[nodiscard]] static constexpr VectorType convert(const T& vec) { return VectorType{ vec.x, vec.y }; }
#pragma endregion
	};

	template<typename Type = float>
	[[nodiscard]] VectorType<Type> operator*(const float& multiplier, const VectorType<Type>& vector)
	{
		return vector * multiplier;
	}


#pragma region Specializations
	typedef VectorType<float> Vector;
	inline void to_json(nlohmann::json& j, const Vector& p) {
		j["x"] = p.x;
		j["y"] = p.y;
		j["typeID"] = Type<Vector>::fullName();
	}
	inline void from_json(const nlohmann::json& j, Vector& p) {
		p.x = j.value("x", 0.0f);
		p.y = j.value("y", 0.0f);
	}

	typedef VectorType<double> VectorD;
	inline void to_json(nlohmann::json& j, const VectorD& p) {
		j["x"] = p.x;
		j["y"] = p.y;
		j["typeID"] = Type<VectorD>::fullName();
	}
	inline void from_json(const nlohmann::json& j, VectorD& p) {
		p.x = j.value("x", 0.0);
		p.y = j.value("y", 0.0);
	}

	typedef VectorType<int> VectorI;
	inline void to_json(nlohmann::json& j, const VectorI& p) {
		j["x"] = p.x;
		j["y"] = p.y;
		j["typeID"] = Type<VectorI>::fullName();
	}
	inline void from_json(const nlohmann::json& j, VectorI& p) {
		p.x = j.value("x", 0);
		p.y = j.value("y", 0);
	}

	typedef VectorType<unsigned int> VectorU;
	inline void to_json(nlohmann::json& j, const VectorU& p) {
		j["x"] = p.x;
		j["y"] = p.y;
		j["typeID"] = Type<VectorU>::fullName();
	}
	inline void from_json(const nlohmann::json& j, VectorU& p) {
		p.x = j.value("x", 0u);
		p.y = j.value("y", 0u);
	}
#pragma endregion 
}

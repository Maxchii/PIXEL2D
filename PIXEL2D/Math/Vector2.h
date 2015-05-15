#pragma once
#include "MathTypes.h"

namespace PIXL { namespace math {

	class Vector2 final: public glm::vec2
	{
	public:
		Vector2();
		Vector2(Float32 x, Float32 y);
		Vector2(const Vector2& vec);
		Vector2(const glm::vec2& vec);
		~Vector2(){}

		static float Angle(const Vector2& from, const Vector2& to);
		static Vector2 ClampMagnitude(const Vector2& vec, float maxLength);
		static float Distance(const Vector2& from, const Vector2& to);
		static float Dot(const Vector2& from, const Vector2& to);
		static Vector2 Lerp(const Vector2& from, const Vector2& to, float time);

		static Vector2 Reflect(const Vector2& incident, const Vector2& normal);
		static Vector2 Refract(const Vector2& incident, const Vector2& normal, const float& theta);
		static Vector2 FaceForward(const Vector2& normal, const Vector2& incident, const Vector2& normalRef);
		static Vector2 Rotate(const Vector2& vec, const float& angle);

		void Scale(const Vector2& vec);
		void Scale(const float& x, const float& y);
		float GetMagnitude() const;
		float GetSqrMagnitude() const;
		Vector2 Normalized() const;
		void Normalize();

		void Set(Float32 x, Float32 y);
		void Set(const Vector2& vec);

		//Converts the data into raw 16 bit format. (8 bytes)
		glm::vec2 Raw() const;

		inline static Vector2 Up()		{ return Vector2(0.0, 1.0f);  }
		inline static Vector2 Down()	{ return Vector2(0.0, -1.0f); }
		inline static Vector2 Left()	{ return Vector2(-1.0, 0.0f); }
		inline static Vector2 Right()	{ return Vector2(1.0, 0.0f);  }
		inline static Vector2 Zero()	{ return Vector2(0.0f, 0.0f); }
		inline static Vector2 One()		{ return Vector2(1.0f, 1.0f); }

		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);
		std::string ToString();
	};

} }
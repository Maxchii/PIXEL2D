#pragma once
#include "MathTypes.h"

namespace PIXL{ namespace math {

	class Vector3 final: public glm::vec3
	{
	public:
		Vector3(){}
		Vector3(Float32 x, Float32 y, Float32 z);
		Vector3(const Vector3& vec);
		Vector3(const glm::vec3& vec);
		Vector3(const Vector4& vec);
		~Vector3(){}

		static float Angle(const Vector3& from, const Vector3& to);
		static Vector3 ClampMagnitude(const Vector3& vec, float maxLength);
		static float Distance(const Vector3& from, const Vector3& to);
		static float Dot(const Vector3& from, const Vector3& to);
		static Vector3 Cross(const Vector3& x, const Vector3& y);
		static Vector3 Lerp(const Vector3& from, const Vector3& to, float time);

		static Vector3 Reflect(const Vector3& incident, const Vector3& normal);
		static Vector3 Refract(const Vector3& incident, const Vector3& normal, const float& theta);
		static Vector3 FaceForward(const Vector3& normal, const Vector3& incident, const Vector3& normalRef);
		static Vector3 RotateX(const Vector3& vec, float angle);
		static Vector3 RotateY(const Vector3& vec, float angle);
		static Vector3 RotateZ(const Vector3& vec, float angle);

		void Scale(const Vector3& scale);
		void Scale(const float& x, const float& y, const float& z);
		float GetMagnitude() const;
		float GetSqrMagnitude() const;
		Vector3 Normalized() const;
		void Normalize();

		void Set(Float32 x, Float32 y, Float32 z);
		void Set(const Vector3& vec);

		//Converts the data into raw 8 bit format. (12 bytes)
		glm::vec3 Raw() const;

		inline static Vector3 Up()		{ return Vector3(0.0, 1.0f, 0.0f);  }
		inline static Vector3 Down()	{ return Vector3(0.0, -1.0f, 0.0f); }
		inline static Vector3 Left()	{ return Vector3(-1.0, 0.0f, 0.0f); }
		inline static Vector3 Right()	{ return Vector3(1.0, 0.0f, 0.0f);  }
		inline static Vector3 Forward()	{ return Vector3(0.0, 0.0f, 1.0f);  }
		inline static Vector3 Back()	{ return Vector3(0.0, 0.0f, -1.0f); }
		inline static Vector3 Zero()	{ return Vector3(0.0f, 0.0f, 0.0f); }
		inline static Vector3 One()		{ return Vector3(1.0f, 1.0f, 1.0f); }

		friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);
		std::string ToString();
	};

} }
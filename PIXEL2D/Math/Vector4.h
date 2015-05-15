#pragma once
#include "MathTypes.h"

namespace PIXL { namespace math {

	class Vector4 final: public glm::vec4
	{
	public:
		Vector4(){}
		Vector4(Float32 x, Float32 y, Float32 z, Float32 w);
		Vector4(const Vector4& vec);
		Vector4(const glm::vec4& vec);
		~Vector4(){}

		static Float32 Angle(const Vector4& from, const Vector4& to);
		static Vector4 ClampMagnitude(const Vector4& vec, float maxLength);
		static Float32 Distance(const Vector4& from, const Vector4& to);
		static Float32 Dot(const Vector4& from, const Vector4& to);
		static Vector4 Lerp(const Vector4& from, const Vector4& to, float time);

		static Vector4 Reflect(const Vector4& incident, const Vector4& normal);
		static Vector4 Refract(const Vector4& incident, const Vector4& normal, const Float32& theta);
		static Vector4 FaceForward(const Vector4& normal, const Vector4& incident, const Vector4& normalRef);
		static Vector4 RotateX(const Vector4& vec, Float32 angle);
		static Vector4 RotateY(const Vector4& vec, Float32 angle);
		static Vector4 RotateZ(const Vector4& vec, Float32 angle);

		void Scale(const Vector4& scale);
		void Scale(const Float32& x, const Float32& y, const Float32& z, const Float32& w);
		Float32 GetMagnitude() const;
		Float32 GetSqrMagnitude() const;
		Vector4 Normalized() const;
		void Normalize();

		void Set(Float32 x, Float32 y, Float32 z, Float32 w);
		void Set(const Vector4& vec);
		//Converts the data into raw 8 bit format. (12 bytes)
		glm::vec4 Raw() const;

		inline static Vector4 Zero()	{ return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
		inline static Vector4 One()		{ return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }

		friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector);
		std::string ToString();
	};

} }
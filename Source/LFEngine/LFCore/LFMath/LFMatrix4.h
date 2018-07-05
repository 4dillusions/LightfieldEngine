/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	class LFMatrix3;
	class LFVector2D;
	class LFVector3D;
	class LFVector4D;

	/**
		@brief
		4*4 Matrix and math calculations
	*/
	class LFMatrix4 final
	{
	public:
		float m[4][4] = {};

		LFMatrix4() = default;
		LFMatrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		explicit LFMatrix4(const LFMatrix3 &value);
		LFMatrix4(const LFMatrix4 &value) = default;

		LFMatrix4 &operator = (const LFMatrix4 &value);
		void operator = (const LFMatrix3 &value);

		float operator() (int indexX, int indexY) const; //float a = matrix(0, 0);
		float &operator() (int indexX, int indexY); //matrix(0, 0) = 22.12;

		LFMatrix4 operator * (const LFMatrix4 &value) const;
		LFMatrix4 operator + (const LFMatrix4 &value) const;
		LFMatrix4 operator - (const LFMatrix4 &value) const;

		bool operator == (const LFMatrix4 &value) const;
		bool operator != (const LFMatrix4 &value) const;

		LFVector3D operator * (const LFVector3D &vector) const;
		LFVector4D operator * (const LFVector4D &vector) const;
		LFMatrix4 operator * (float scalar) const;

		void SetTranslation(const LFVector2D &vector);
		void SetTranslation(const LFVector3D &vector);
		void SetRotationYaw(float yaw); //Y axis
		void SetRotationPitch(float pitch); //X axis
		void SetRotationRoll(float roll); //Z axis
		LFVector2D GetTranslation2D();
		LFVector3D GetTranslation3D();
		static LFMatrix4 GetTranslation(const LFVector2D &vector);
		static LFMatrix4 GetTranslation(const LFVector3D &vector);
		void MakeTranslation(const LFVector2D &vector);
		void MakeTranslation(const LFVector3D &vector);
		void SetScale(const LFVector3D &vector);
		static LFMatrix4 GetScale(const LFVector3D &vector);
		bool IsHasScale();
		bool IsAffine() const;
		LFMatrix4 InverseAffine() const;
		LFMatrix4 ConcatenateAffine(const LFMatrix4 &value) const;
		LFVector3D TransformAffine(const LFVector3D &vector) const;
		LFVector4D TransformAffine(const LFVector4D &vector) const;

		LFMatrix4 Concatenate(const LFMatrix4 &value) const;
		LFMatrix4 Inverse() const;
		LFMatrix4 Transpose() const;
		float Determinant() const;
		void Zero();
		void Identity();
	};
}}}}

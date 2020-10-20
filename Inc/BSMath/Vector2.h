#pragma once

#include "Utility.h"
#include "VectorBase.h"

namespace BSMath
{
	namespace Detail
	{
		template <class T>
		struct Vector2Base final : public VectorBase<T, 2>
		{
		public:
			using Super = Detail::VectorBase<T, 2>;
			using Super::Super;
			using Super::data;

			const static Vector2Base Right;
			const static Vector2Base Left;
			const static Vector2Base Up;
			const static Vector2Base Down;

		public:
			float& X() noexcept { return data[0][0]; }
			const float& X() const noexcept { return data[0][0]; }

			float& Y() noexcept { return data[0][1]; }
			const float& Y() const noexcept { return data[0][1]; }

			void Set(T inX, T inY) noexcept
			{
				X() = inX; Y() = inY;
			}
		};

		template <class T>
		const Vector2Base<T> Vector2Base<T>::Right{ static_cast<T>(1), static_cast<T>(0) };

		template <class T>
		const Vector2Base<T> Vector2Base<T>::Left{ static_cast<T>(-1), static_cast<T>(0) };

		template <class T>
		const Vector2Base<T> Vector2Base<T>::Up{ static_cast<T>(0), static_cast<T>(1) };

		template <class T>
		const Vector2Base<T> Vector2Base <T>::Down{ static_cast<T>(0), static_cast<T>(-1) };
	}

	using Vector2 = Detail::Vector2Base<float>;
	using IntVector2 = Detail::Vector2Base<int>;

	using UniformIntVector2Random = Detail::UniformMatrixRandom<int, 1, 2>;
	using UniformVector2Random = Detail::UniformMatrixRandom<float, 1, 2>;
	using NormalVector2Random = Detail::NormalMatrixRandom<1, 2>;
}
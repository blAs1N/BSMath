#pragma once

#include "Hash.h"
#include "Random.h"
#include "Utility.h"

namespace BSMath
{
	struct alignas(16) Rotator final
	{
	public:
		const static Rotator Zero;

	public:
		constexpr Rotator() noexcept
			: roll(0.0f), pitch(0.0f), yaw(0.0f) {}

		explicit constexpr Rotator(float angle) noexcept
			: roll(angle), pitch(angle), yaw(angle) {}

		explicit constexpr Rotator(float inRoll, float inPitch, float inYaw) noexcept
			: roll(inRoll), pitch(inPitch), yaw(inYaw) {}

		explicit constexpr Rotator(const float* ptr) noexcept
			: roll(ptr[0]), pitch(ptr[1]), yaw(ptr[2]) {}

		constexpr void Set(float inRoll, float inPitch, float inYaw) noexcept
		{
			roll = inRoll; pitch = inPitch; yaw = inYaw;
		}

		[[nodiscard]] Rotator operator-() const noexcept;

		Rotator& operator+=(const Rotator& other) noexcept;
		Rotator& operator-=(const Rotator& other) noexcept;

		Rotator& operator*=(float scaler) noexcept;
		Rotator& operator/=(float divisor) noexcept;

		[[nodiscard]] constexpr float& operator[](size_t idx) noexcept { return (&roll)[idx]; }
		[[nodiscard]] constexpr float operator[](size_t idx) const noexcept { return (&roll)[idx]; }

	public:
		float roll;
		float pitch;
		float yaw;
	};

	// Global Operators

	[[nodiscard]] NO_ODR bool operator==(const Rotator& lhs, const Rotator& rhs) noexcept
	{
		using namespace SIMD;
		const auto lhsVec = VectorLoadPtr(&lhs.roll, 3);
		const auto rhsVec = VectorLoadPtr(&rhs.roll, 3);
		return VectorMoveMask(VectorEqual(lhsVec, rhsVec)) == 0xF;
	}

	[[nodiscard]] NO_ODR bool operator!=(const Rotator& lhs, const Rotator& rhs) noexcept { return !(lhs == rhs); }

	[[nodiscard]] NO_ODR Rotator operator+(const Rotator& lhs, const Rotator& rhs) noexcept
	{
		return Rotator{ lhs } += rhs;
	}

	[[nodiscard]] NO_ODR Rotator operator-(const Rotator& lhs, const Rotator& rhs) noexcept
	{
		return Rotator{ lhs } -= rhs;
	}

	[[nodiscard]] NO_ODR Rotator operator*(const Rotator& vec, float scaler) noexcept
	{
		return Rotator{ vec } *= scaler;
	}

	[[nodiscard]] NO_ODR Rotator operator*(float scaler, const Rotator& vec) noexcept
	{
		return Rotator{ vec } *= scaler;
	}

	[[nodiscard]] NO_ODR Rotator operator/(const Rotator& vec, float divisor) noexcept
	{
		return Rotator{ vec } /= divisor;
	}

	inline const Rotator Rotator::Zero{};

	NO_ODR Rotator Rotator::operator-() const noexcept
	{
		return Rotator::Zero - *this;
	}

	NO_ODR Rotator& Rotator::operator+=(const Rotator& other) noexcept
	{
		using namespace SIMD;
		const auto lhs = VectorLoadPtr(&roll, 3);
		const auto rhs = VectorLoadPtr(&other.roll, 3);
		VectorStorePtr(VectorAdd(lhs, rhs), &roll, 3);
		return *this;
	}

	NO_ODR Rotator& Rotator::operator-=(const Rotator& other) noexcept
	{
		using namespace SIMD;
		const auto lhs = VectorLoadPtr(&roll, 3);
		const auto rhs = VectorLoadPtr(&other.roll, 3);
		VectorStorePtr(VectorSubtract(lhs, rhs), &roll, 3);
		return *this;
	}

	NO_ODR Rotator& Rotator::operator*=(float scaler) noexcept
	{
		using namespace SIMD;
		const auto lhs = VectorLoadPtr(&roll, 3);
		const auto rhs = VectorLoad1(scaler);
		VectorStorePtr(VectorMultiply(lhs, rhs), &roll, 3);
		return *this;
	}

	NO_ODR Rotator& Rotator::operator/=(float divisor) noexcept
	{
		if (divisor == 0.0f) return *this;

		using namespace SIMD;
		const auto lhs = VectorLoadPtr(&roll, 3);
		const auto rhs = VectorLoad1(divisor);
		VectorStorePtr(VectorDivide(lhs, rhs), &roll, 3);
		return *this;
	}

	// Global

	[[nodiscard]] NO_ODR bool IsNearlyEqual(const Rotator& lhs,
		const Rotator& rhs, float tolerance = Epsilon) noexcept
	{
		using namespace SIMD;
		const auto epsilon = VectorLoad1(tolerance);
		const auto vec = VectorSubtract(VectorLoadPtr(&lhs.roll, 3), VectorLoadPtr(&rhs.roll, 3));
		return VectorMoveMask(VectorLessEqual(vec, epsilon)) == 0xF;
	}

	[[nodiscard]] NO_ODR bool IsNearlyZero(const Rotator& rot, float tolerance = Epsilon) noexcept
	{
		using namespace SIMD;
		const auto epsilon = VectorLoad1(tolerance);
		const auto vec = VectorLoadPtr(&rot.roll, 3);
		return VectorMoveMask(VectorLessEqual(vec, epsilon)) == 0xF;
	}

	// Rotator's Hash
	template <>
	struct Hash<Rotator> final : public HashRange<Rotator, sizeof(float) * 3> {};

	// Rotator's Random
	class RotatorDistribution final
	{
	public:
		using result_type = Rotator;

		template <class Engine>
		[[nodiscard]] result_type operator()(Engine& engine)
		{
			std::uniform_real_distribution<float> dist{ 0.0f, 360.0f };
			return Rotator{ dist(engine), dist(engine), dist(engine) };
		}
	};

	using RotatorRandom = Random<Rotator, std::mt19937, RotatorDistribution>;
}

#pragma once

#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define FORCEINLINE __forceinline
#else
#define NOINLINE __attribute__((noinline))
#define FORCEINLINE __attribute__((always_inline))
#endif

namespace ikakusa {
    template <typename DataType, size_t Len, size_t Count>
    class protected_string {
    public:
        uint32_t data[Len - 1];
		FORCEINLINE consteval size_t size() {
			return Len - 1;
		}
        FORCEINLINE consteval std::uint32_t _time() {
            return (__TIME__[0] - '0') ^ Count
                + (__TIME__[1] - '0') ^ Count * 2
                + (__TIME__[3] - '0') ^ Count * 3
                + (__TIME__[4] - '0') ^ Count * 4
                + (__TIME__[6] - '0') ^ Count * 5
                + (__TIME__[7] - '0') ^ Count * 6;
        }
        NOINLINE constexpr std::uint32_t generate_seed(size_t i) {
            std::uint32_t _1 = size() - Count + (size() * Count * Count) ^ ((_time() * 0x7a2891du + i));
            _1 ^= (_1 << 17) + i + Count;
            _1 ^= (_1 >> 13) + i * Count;
            _1 ^= (_1 << 4) + i + Count;
            return _1;
        }
    public:
        FORCEINLINE consteval explicit protected_string(DataType _data) {
            for (size_t i = 0; i < size(); ++i) {
                data[i] = _data[i] ^ generate_seed(i);
            }
        }
        FORCEINLINE auto reveal() {
            using CharType =
                std::remove_cv_t<
                std::remove_extent_t<
                std::remove_cvref_t<DataType>
                >
                >;
            std::basic_string<CharType> result;
            result.resize(size());

            for (size_t i = 0; i < size(); ++i) {
                result[i] = data[i] ^ generate_seed(i);
            }
            return result;
        }
    };
}

#define protect(str) \
    ikakusa::protected_string<decltype(str), sizeof(str), __COUNTER__>(str).reveal();

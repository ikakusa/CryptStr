#pragma once
#include <intrin.h> 
#include <windows.h>

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
        using CharType =
            std::remove_cv_t<
            std::remove_extent_t<
            std::remove_cvref_t<DataType>
            >
            >;
    public:
        size_t count;
        CharType data[Len / sizeof(CharType) - 1];
        FORCEINLINE consteval size_t size() {
            return Len / sizeof(CharType) - 1;
        }
        FORCEINLINE consteval std::uint32_t _time() {
            return ((__TIME__[0] - '0') ^ Count)
                + ((__TIME__[1] - '0') ^ (Count * 2))
                + ((__TIME__[3] - '0') ^ (Count * 3))
                + ((__TIME__[4] - '0') ^ (Count * 4))
                + ((__TIME__[6] - '0') ^ (Count * 5))
                + ((__TIME__[7] - '0') ^ (Count * 6));
        }
        template <size_t i> 
        NOINLINE constexpr std::uint32_t generate_seed(size_t count) {
            std::uint32_t _1 = (size() - count + (size() * count * count)) ^ ((_time() + 0x7a291du + i));
            _1 ^= (_1 << 11) + i + count;
            _1 ^= (_1 >> 13) + i * count;
            _1 ^= (_1 << 7) + i + count;
            return _1;
        }
    public:
		template <size_t... Is>
        consteval explicit protected_string(DataType _data, std::index_sequence<Is...>) {
            count = Count;
            ((data[Is] = static_cast<CharType>(static_cast<uint32_t>(_data[Is]) ^ generate_seed<Is>(count))), ...);
        }
		template <size_t... Is>
        NOINLINE auto reveal(std::index_sequence<Is...>) {
            using Type = std::basic_string<CharType>;
            Type result{};
			result.resize(size());
            ((result[Is] = static_cast<CharType>(static_cast<uint32_t>(data[Is]) ^ generate_seed<Is>(count))), ...);
            return result;
        }
    };
}

#define _csize(str) (sizeof(str) / sizeof(std::remove_cv_t<std::remove_extent_t<std::remove_cvref_t<decltype(str)>>>) - 1)

#define protect(str) \
ikakusa::protected_string<decltype(str)&, sizeof(str), __COUNTER__>(str, std::make_index_sequence<_csize(str)>{}).reveal(std::make_index_sequence<_csize(str)>{})
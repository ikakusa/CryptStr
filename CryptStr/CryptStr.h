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
    private:
        class scoped_string {
            using CharType =
                std::remove_cv_t<
                std::remove_extent_t<
                std::remove_cvref_t<DataType>
                >
                >;
            using Type = CharType[Len / sizeof(CharType) - 1];
        private:
            Type _buffer{};
        public:
            scoped_string(protected_string* _instance, CharType* d, size_t count, size_t len) {
                for (size_t i = 0; i < len / sizeof(CharType) - 1; ++i) {
                    _buffer[i] = static_cast<CharType>(static_cast<uint32_t>(d[i]) ^ _instance->generate_seed(i, count));
                }
                _buffer[len / sizeof(CharType) - 1] = CharType{};
            }
            ~scoped_string() {
				SecureZeroMemory(_buffer, sizeof(_buffer));
            }
            const CharType* buffer() const {
                return _buffer;
            }
            operator const CharType* () const {
                return _buffer;
            }
        };
    public:
        size_t len;
        size_t count;
        CharType data[Len / sizeof(CharType) - 1];
        FORCEINLINE consteval size_t size() {
            return Len - 1;
        }
        FORCEINLINE consteval std::uint32_t _time() {
            return ((__TIME__[0] - '0') ^ Count)
                + ((__TIME__[1] - '0') ^ (Count * 2))
                + ((__TIME__[3] - '0') ^ (Count * 3))
                + ((__TIME__[4] - '0') ^ (Count * 4))
                + ((__TIME__[6] - '0') ^ (Count * 5))
                + ((__TIME__[7] - '0') ^ (Count * 6));
        }
        NOINLINE constexpr std::uint32_t generate_seed(size_t i, size_t count) {
            volatile std::uint32_t _1 = (size() - count + (size() * count * count)) ^ ((_time() * 0x7a2891du + i));
            _1 ^= (_1 << 17) + i + count;
            _1 ^= (_1 >> 13) + i * count;
            _1 ^= (_1 << 4) + i + count;
            return _1;
        }
    public:
        consteval explicit protected_string(DataType _data) {
            count = Count;
            len = Len;
            for (size_t i = 0; i < len / sizeof(CharType) - 1; ++i) {
                data[i] = static_cast<CharType>(static_cast<uint32_t>(_data[i]) ^ generate_seed(i, count));
            }
        }
        NOINLINE auto reveal() {
            using Type = std::basic_string<CharType>;
            Type result{};
			result.resize(len - 1);
            for (size_t i = 0; i < len / sizeof(CharType) - 1; ++i) {
                result[i] = static_cast<CharType>(static_cast<uint32_t>(data[i]) ^ generate_seed(i, count));
            }
			result[len / sizeof(CharType) - 1] = CharType{};
            return result;
        }
        NOINLINE auto reveal2() {
            auto _result = scoped_string(this, data, count, len);
			return _result;
        }
    };
}

#define protect(str) \
ikakusa::protected_string<decltype(str)&, sizeof(str), __COUNTER__>(str).reveal()

#define protect2(str) \
ikakusa::protected_string<decltype(str)&, sizeof(str), __COUNTER__>(str).reveal2()
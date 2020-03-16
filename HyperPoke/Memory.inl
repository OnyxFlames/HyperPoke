
#include "Common.hpp"
#include <array>
#include "Memory.hpp"

template<typename T>
union ByteBuffer
{
	T value;
	uint8_t bytes[sizeof(T)];
};

template<typename T>
const size_t BufferSize = sizeof(T);

template<typename T>
inline void write(uint8_t* data, T value)
{
	ByteBuffer<T> buffer;

	buffer.value = value;

	for (size_t i = 0; i < BufferSize<T>; ++i)
	{
		data[i] = buffer.bytes[i];
	}
}

template<typename T>
inline void seq_write(uint8_t*& data, T value)
{
	uint8_t* off = data;
	data += sizeof(T);

	return write<T>(off, value);
}

template<typename T, size_t N>
inline void write_n(uint8_t* data, T* values)
{
	for (size_t i = 0; i < N; ++i)
		write(data + sizeof(T) * i, values[i]);
}

template<typename T, size_t N>
inline void seq_write_n(uint8_t*& data, T* values)
{
	for (size_t i = 0; i < N; ++i)
		seq_write(data, values[i]);
}

template<typename T>
inline T read(const uint8_t* data)
{
	ByteBuffer<T> buffer;

	for (size_t i = 0; i < BufferSize<T>; ++i)
	{
		buffer.bytes[i] = data[i];
	}

	return buffer.value;
}

template<typename T, size_t N>
inline std::array<T, N> read(const uint8_t* data)
{
	std::array<T, N> arr;
	
	for (size_t j = 0; j < N; ++j)
	{
		ByteBuffer<T> buffer;
		for (size_t i = 0; i < BufferSize<T>; ++i)
		{
			buffer.bytes[i] = data[i];
		}
		arr[j] = buffer.value;
	}
	return arr;
}

template<typename T>
inline T seq_read(uint8_t*& data)
{
	const uint8_t* old_off = data;
	data += sizeof(T);

	return read<T>(old_off);
}

template<typename T, size_t N>
inline std::array<T, N> seq_read(uint8_t*& data)
{
	std::array<T, N> arr;

	for (size_t i = 0; i < N; ++i)
	{
		arr[i] = seq_read<T>(data);
	}

	return arr;
}

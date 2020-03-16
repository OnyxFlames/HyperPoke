#pragma once

#include "Common.hpp"

#include <vector>

template <typename T>
void write(const uint8_t* data, T value);

template <typename T>
void seq_write(uint8_t*& data, T value);

template <typename T>
T read(const uint8_t* data);

template <typename T, size_t N>
std::array<T, N> read(const uint8_t* data);

// read functions that modify the pointers position after the data was read
template <typename T>
T seq_read(uint8_t*& data);

template <typename T, size_t N>
std::array<T, N> seq_read(uint8_t*& data);

#include "Memory.inl"
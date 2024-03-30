///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2024 IkarusDeveloper. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef __INC_IKD_RAPIDJSON_HELPER_H__
#define __INC_IKD_RAPIDJSON_HELPER_H__
#pragma once

#include <rapidjson/document.h> // dependency
#include <rapidjson/error/en.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <cstdio>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

namespace rapidjsonHelper {
	namespace details {
		inline std::optional<int> getInt(const rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			const rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsInt() == false)
				return std::nullopt;

			// making optional with value
			return std::optional<int>{member.GetInt()};
		}

		inline std::optional<int64_t> getInt64(const rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			const rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsInt64() == false)
				return std::nullopt;

			// making optional with value
			return std::optional<int64_t>{member.GetInt64()};
		}
		
		inline std::optional<unsigned int> getUint(const rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			const rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsUint() == false)
				return std::nullopt;

			// making optional with value
			return std::optional<unsigned int>{member.GetUint()};
		}

		inline std::optional<uint64_t> getUint64(const rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			const rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsUint64() == false)
				return std::nullopt;

			// making optional with value
			return std::optional<uint64_t>{member.GetUint64()};
		}

		inline std::optional<std::string> getString(const rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			const rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsString() == false)
				return std::nullopt;

			// making optional with value
			return std::string{member.GetString()};
		}

		inline std::optional<double> getDouble(const rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			const rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsDouble() == false)
				return std::nullopt;

			// making optional with value
			return member.GetDouble();
		}
		
		inline std::optional<float> getFloat(const rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			const rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsFloat() == false)
				return std::nullopt;

			// making optional with value
			return member.GetFloat();
		}
		
		inline std::optional<bool> getBool(const rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			const rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsBool() == false)
				return std::nullopt;

			// making optional with value
			return member.GetBool();
		}

		template<class T>
		inline std::optional<T> getValue(const rapidjson::Value& value, const std::string& key) {
			if constexpr (std::is_same_v<T, int>)
				return getInt(value, key);
			else if constexpr (std::is_same_v<T, int64_t>)
				return getInt64(value, key);
			else if constexpr (std::is_same_v<T, unsigned int>)
				return getInt(value, key);
			else if constexpr (std::is_same_v<T, uint64_t>)
				return getInt64(value, key);
			else if constexpr (std::is_same_v<T, std::string>)
				return getString(value, key);
			else if constexpr (std::is_same_v<T, double>)
				return getDouble(value, key);
			else if constexpr (std::is_same_v<T, float>)
				return getFloat(value, key);
			else if constexpr (std::is_same_v<T, bool>)
				return getBool(value, key);
			else
				return std::nullopt;
		}
	}

	template<class T>
	inline T getValue(rapidjson::Value& value, const std::string& key) {
		auto ret = details::getValue<T>(value, key);
		if (!ret)
			std::fprintf(stderr, "RAPIDJSON HELPER: FAILED TO OBTAIN VALUE BY KEY %s\n", key.c_str());
		return ret.value_or(T{});
	}

	inline void insertValue(rapidjson::Value& value, const std::string& key, const int& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetInt(insertValue);
		value.AddMember(keyValue, newValue, allocator);
	}

	inline void insertValue(rapidjson::Value& value, const std::string& key, const int64_t& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetInt64(insertValue);
		value.AddMember(keyValue, newValue, allocator);
	}
	
	inline void insertValue(rapidjson::Value& value, const std::string& key, const unsigned int& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetUint(insertValue);
		value.AddMember(keyValue, newValue, allocator);
	}

	inline void insertValue(rapidjson::Value& value, const std::string& key, const uint64_t& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetUint64(insertValue);
		value.AddMember(keyValue, newValue, allocator);
	}
	
	inline void insertValue(rapidjson::Value& value, const std::string& key, const double& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetDouble(insertValue);
		value.AddMember(keyValue, newValue, allocator);
	}
	
	inline void insertValue(rapidjson::Value& value, const std::string& key, const float& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetFloat(insertValue);
		value.AddMember(keyValue, newValue, allocator);
	}
	
	inline void insertValue(rapidjson::Value& value, const std::string& key, const bool& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetBool(insertValue);
		value.AddMember(keyValue, newValue, allocator);
	}

	inline void insertValue(rapidjson::Value& value, const std::string& key, const std::string& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetString(insertValue.c_str(), allocator);
		value.AddMember(keyValue, newValue, allocator);
	}

	inline auto parseFromFile(rapidjson::Document & jsonDoc, const std::string_view& filename) {
		// 1. Open the JSON file
		std::ifstream inFile(filename.data(), std::ios::in | std::ios::binary);
		if (!inFile.is_open()) {
			std::cerr << "Error opening file: " << filename << std::endl;
			return false;
		}

		// 2. Read the entire file content into a string
		rapidjson::IStreamWrapper isw(inFile);

		// 3. Parse the JSON string
		jsonDoc.ParseStream(isw);

		// 4. Checking for parser errors
		if (jsonDoc.HasParseError()) {
			std::fprintf(stderr, "JSON FILE LOAD ERROR %s: [%d] %s\n", filename.data(), (int)jsonDoc.GetParseError(), rapidjson::GetParseError_En(jsonDoc.GetParseError()));
			return false;
		}

		return true;
	}

	inline auto parseFromStream(rapidjson::Document & jsonDoc, const std::string_view& stream) {
		// Parse the JSON string
		jsonDoc.Parse(stream.data());

		// Checking for parser errors
		if (jsonDoc.HasParseError()) {
			std::fprintf(stderr, "JSON DATA LOAD ERROR %s: [%d] %s\n", stream.data(), (int)jsonDoc.GetParseError(), rapidjson::GetParseError_En(jsonDoc.GetParseError()));
			return false;
		}

		return true;
	}

	inline bool writeToFile(rapidjson::Document& jsonDoc, const std::string_view& filename) {
		// opening stream
		std::ofstream stream(filename.data(), std::ios::out | std::ios::binary);
		if (!stream.is_open()) {
			std::fprintf(stderr, "CANNOT SAVE THE FILE %s!", filename.data());
			return false;
		}

		// making json string
		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> StringWriter(buffer);
		jsonDoc.Accept(StringWriter);

		// completing stream data
		stream.write(buffer.GetString(), buffer.GetSize());
		stream.close();
		return true;
	}

	inline std::string writeToStream(rapidjson::Document& jsonDoc) {
		// making json string
		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> StringWriter(buffer);
		jsonDoc.Accept(StringWriter);

		// completing stream data
		return std::string(buffer.GetString(), buffer.GetSize());
	}
}

#endif //__INC_IKD_RAPIDJSON_HELPER_H__

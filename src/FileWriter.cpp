#include "pch.h"
#include "FileWriter.hpp"

struct msfl::RawBytes FileWriter::ReadBytesFromBinFile(std::string path) {
	msfl::RawBytes res;

	if (path != "") {
		std::ifstream _f(path, std::ios::binary);

		if (_f.good() && _f) {
			_f.seekg(0, std::ios::end);

			long len = _f.tellg();
			res.len = len;

			_f.seekg(0, std::ios::beg);

			res.bytes = new unsigned char[len];
			_f.read((char*)res.bytes, len);
		}

		_f.close();
	}

	return res;
}

bool FileWriter::WriteToBinFile(std::string path, unsigned char* bytes, int len) {
	if (path != "") {
		std::ofstream _f(path, std::ios::binary);
		_f.write((char*) bytes, len);

		if (!_f.good()) {
			return false;
		}

		_f.close();
	}
	else {
		return false;
	}

	return true;
}

struct msfl::RawBytes FileWriter::ReadBytesFromBinFileLPCWSTR(LPCWSTR path) {
	msfl::RawBytes res;

	if (path != L"") {
		std::ifstream _f(path, std::ios::binary);

		if (_f.good() && _f) {
			_f.seekg(0, std::ios::end);

			long len = _f.tellg();
			res.len = len;

			_f.seekg(0, std::ios::beg);

			res.bytes = new unsigned char[len];
			_f.read((char*)res.bytes, len);
		}

		_f.close();
	}

	return res;
}

bool FileWriter::WriteToBinFileLPCWSTR(LPCWSTR path, unsigned char* bytes, int len) {
	if (path != L"") {
		std::ofstream _f(path, std::ios::binary);
		_f.write((char*)bytes, len);

		if (!_f.good()) {
			return false;
		}

		_f.close();
	}
	else {
		return false;
	}

	return true;
}
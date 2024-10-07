#include "TextureConverter.h"

TextureConverter::TextureConverter(){}
TextureConverter::~TextureConverter(){}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString) {
	//ワイド文字列に変換した際の文字数
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//ワイド文字列
	std::wstring wString;
	wString.resize(filePathBufferSize);

	//ワイド文字列に変換
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath) {

	//テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath) {

	//ファイルパスをワイド文字列に変換
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

}
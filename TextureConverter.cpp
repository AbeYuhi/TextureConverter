#include "TextureConverter.h"

TextureConverter::TextureConverter(){}
TextureConverter::~TextureConverter(){}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString) {
	std::filesystem::path wString = mString;

	return wString.wstring();
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath) {

	//テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath) {

	//ファイルパスをワイド文字列に変換
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

}
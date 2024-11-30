#pragma once
#include <string>
#include <filesystem>
#include "External/DirectXTex/DirectXTex.h"
#include "External/DirectXTex/d3dx12.h"

using namespace DirectX;

class TextureConverter
{
public:

private:
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

public:
	TextureConverter();
	~TextureConverter();

	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void ConvertTextureWICToDDS(const std::string& filePath);

private:

	/// <summary>
	/// テクスチャファイル読み込み
	/// </summary>
	/// <param name="filePath">ファイルパス/param>
	void LoadWICTextureFromFile(const std::string& filePath);

	/// <summary>
	/// フォルダパスとファイル名を分離する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void SeparateFilePath(const std::wstring& filePath);

	/// <summary>
	/// DDSテクスチャとしてファイル書き出し
	/// </summary>
	void SaveDDSTextureToFIle();

	//画像の情報
	TexMetadata metaData_;
	//画像イメージのコンテナ
	ScratchImage scratchImage_;

	//ディレクトリパス
	std::wstring directoryPath_;
	//ファイル名
	std::wstring fileName_;
	//ファイル拡張子
	std::wstring fileExt_;
};


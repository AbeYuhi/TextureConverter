#pragma once
#include <string>
#include <filesystem>
#include "External/DirectXTex/DirectXTex.h"
#include "External/DirectXTex/d3dx12.h"

using namespace DirectX;

class TextureConverter
{
public:

	/// <summary>
	/// 使用方法を出力(表示)する
	/// </summary>
	static void OutputUsage();

private:
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

public:
	TextureConverter();
	~TextureConverter();

	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	/// <param name="numOptions">オプションの数</param>
	/// <param name="options">オプション配列</param>
	void ConvertTextureWICToDDS(const std::string& filePath,
		int numOptions = 0, char* options[] = nullptr);

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
	/// <param name="numOptions">オプションの数</param>
	/// <param name="options">オプション配列</param>
	void SaveDDSTextureToFIle(int numOptions, char* options[]);

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


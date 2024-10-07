#pragma once
#include <string>
#include <stringapiset.h>

class TextureConverter
{
public:

private:
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

public:
	TextureConverter();
	~TextureConverter();

	/// <summary>
	/// �e�N�X�`����WIC����DDS�ɕϊ�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void ConvertTextureWICToDDS(const std::string& filePath);

private:

	/// <summary>
	/// �e�N�X�`���t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X/param>
	void LoadWICTextureFromFile(const std::string& filePath);
};


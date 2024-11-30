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

	/// <summary>
	/// �t�H���_�p�X�ƃt�@�C�����𕪗�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void SeparateFilePath(const std::wstring& filePath);

	/// <summary>
	/// DDS�e�N�X�`���Ƃ��ăt�@�C�������o��
	/// </summary>
	void SaveDDSTextureToFIle();

	//�摜�̏��
	TexMetadata metaData_;
	//�摜�C���[�W�̃R���e�i
	ScratchImage scratchImage_;

	//�f�B���N�g���p�X
	std::wstring directoryPath_;
	//�t�@�C����
	std::wstring fileName_;
	//�t�@�C���g���q
	std::wstring fileExt_;
};


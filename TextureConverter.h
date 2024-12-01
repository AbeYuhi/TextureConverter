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
	/// �g�p���@���o��(�\��)����
	/// </summary>
	static void OutputUsage();

private:
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

public:
	TextureConverter();
	~TextureConverter();

	/// <summary>
	/// �e�N�X�`����WIC����DDS�ɕϊ�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <param name="numOptions">�I�v�V�����̐�</param>
	/// <param name="options">�I�v�V�����z��</param>
	void ConvertTextureWICToDDS(const std::string& filePath,
		int numOptions = 0, char* options[] = nullptr);

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
	/// <param name="numOptions">�I�v�V�����̐�</param>
	/// <param name="options">�I�v�V�����z��</param>
	void SaveDDSTextureToFIle(int numOptions, char* options[]);

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


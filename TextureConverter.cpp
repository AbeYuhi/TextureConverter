#include "TextureConverter.h"

TextureConverter::TextureConverter(){}
TextureConverter::~TextureConverter(){}

void TextureConverter::OutputUsage() {
	printf("�摜�t�@�C����WIC�`������DDS�`���ɕϊ����܂��B\n");
	printf("\n");
	printf("TextureConverter [�h���C�u:][�p�X][�t�@�C����]\n");
	printf("\n");
	printf(" [�h���C�u:][�p�X][�t�@�C����]: �ϊ�������WIC�`���̉摜�t�@�C�����w�肵�܂��B\n");
	printf(" \n");
	printf(" �w�肵���摜�t�@�C���̌���[-mp][����]: Mip���x���̎w����ł��܂�\n");
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString) {
	std::filesystem::path wString = mString;

	return wString.wstring();
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath,
	int numOptions, char* options[]) {

	//�e�N�X�`���t�@�C����ǂݍ���
	LoadWICTextureFromFile(filePath);

	//DDS�t�@�C���ɕϊ�����
	SaveDDSTextureToFIle(numOptions, options);

}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath) {

	//�t�@�C���p�X�����C�h������ɕϊ�
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

	//WIC�e�N�X�`���̃��[�h
	LRESULT result = LoadFromWICFile(wFilePath.c_str(), WIC_FLAGS_NONE, &metaData_, scratchImage_);
	assert(SUCCEEDED(result));

	//�t�@�C���p�X�ƃt�@�C�����𕪗�����
	SeparateFilePath(wFilePath);
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath) {
	size_t pos1;
	std::wstring exceptExt;

	//��؂蕶��'.'���o�Ă����ԍŌ�̕���������
	pos1 = filePath.rfind('.');
	//�������q�b�g������
	if (pos1 != std::wstring::npos) {
		//��؂蕶���̌����t�@�C���g���q�Ƃ��ĕۑ�
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//��؂蕶���̑O�܂ł������o��
		exceptExt = filePath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}
	
	//��؂蕶��'\\'���o�Ă����ԍŌ�̕���������
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos) {
		//��؂蕶���̑O�܂Ńf�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//��؂蕶���̌����t�@�C���l�[���Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//��؂蕶��'/'���o�Ă����ԍŌ�̕���������
	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		//��؂蕶���̑O�܂Ńf�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//��؂蕶���̌����t�@�C���l�[���Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//��؂蕶�����Ȃ��̂Ńt�@�C�����݂̂Ƃ��Ĉ���
	directoryPath_ = L"";
	fileName_ = exceptExt;
}

void TextureConverter::SaveDDSTextureToFIle(int numOptions, char* options[]) {
	LRESULT result;
	ScratchImage mipChain;
	
	//�~�b�v�̐���
	size_t mipLevels = 0;
	//�~�b�v�}�b�v���x���w�������
	for (int i = 0; i < numOptions; i++) {
		if (std::string(options[i]) == "-ml") {
			//�~�b�v���x���w��
			mipLevels = std::stoi(options[i + 1]);
			break;
		}
	}

	result = GenerateMipMaps(
		scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(),
		TEX_FILTER_DEFAULT, mipLevels, mipChain);
	if (SUCCEEDED(result)) {
		//�C���[�W�ƃ��^�f�[�^���A�~�b�v�}�b�v�łŒu��������
		scratchImage_ = std::move(mipChain);
		metaData_ = scratchImage_.GetMetadata();
	}

	//���k�`���ɕϊ�
	ScratchImage converted;
	result = Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metaData_,
		DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT | TEX_COMPRESS_PARALLEL,
		1.0f, converted);
	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(converted);
		metaData_ = scratchImage_.GetMetadata();
	}

	//�ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	metaData_.format = MakeSRGB(metaData_.format);

	//�o�̓t�@�C������ݒ肷��
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	//DDS�t�@�C�������o��
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metaData_, DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(result));
}
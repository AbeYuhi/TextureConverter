#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <Windows.h>
#include "TextureConverter.h"

enum Argument {
	kApplicationPath,	//�A�v���P�[�V�����̃p�X
	kFilePath,			//�n���ꂽ�t�@�C���p�X

	NumArgument
};

int main(int argc, char* argv[]) {

	if (argc < NumArgument) {
		//�g������\������
		TextureConverter::OutputUsage();
		return 0;
	}

	//Com���C�u�����̏�����
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//�e�N�X�`���R���o�[�^�[
	TextureConverter converter;

	int numOptions = argc - NumArgument;
	char** options = argv + NumArgument;

	//�e�N�X�`���ϊ�
	converter.ConvertTextureWICToDDS(argv[kFilePath], numOptions, options);

	//Com���C�u�����̏I��
	CoUninitialize();

	return 0;
}
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include <cassert>
#include "TextureConverter.h"

enum Argument {
	kApplicationPath,	//�A�v���P�[�V�����̃p�X
	kFilePath,			//�n���ꂽ�t�@�C���p�X

	NumArgument
};

int main(int argc, char* argv[]) {

	assert(argc >= NumArgument);

	//Com���C�u�����̏�����
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//�e�N�X�`���R���o�[�^�[
	TextureConverter converter;

	//�e�N�X�`���ϊ�
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	//Com���C�u�����̏I��
	CoUninitialize();

	system("pause");

	return 0;
}
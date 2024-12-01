#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <Windows.h>
#include "TextureConverter.h"

enum Argument {
	kApplicationPath,	//アプリケーションのパス
	kFilePath,			//渡されたファイルパス

	NumArgument
};

int main(int argc, char* argv[]) {

	if (argc < NumArgument) {
		//使い方を表示する
		TextureConverter::OutputUsage();
		return 0;
	}

	//Comライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコンバーター
	TextureConverter converter;

	int numOptions = argc - NumArgument;
	char** options = argv + NumArgument;

	//テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath], numOptions, options);

	//Comライブラリの終了
	CoUninitialize();

	return 0;
}
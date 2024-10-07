#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include <cassert>
#include "TextureConverter.h"

enum Argument {
	kApplicationPath,	//アプリケーションのパス
	kFilePath,			//渡されたファイルパス

	NumArgument
};

int main(int argc, char* argv[]) {

	assert(argc >= NumArgument);

	//Comライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコンバーター
	TextureConverter converter;

	//テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	//Comライブラリの終了
	CoUninitialize();

	system("pause");

	return 0;
}
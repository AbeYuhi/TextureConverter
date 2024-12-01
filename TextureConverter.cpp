#include "TextureConverter.h"

TextureConverter::TextureConverter(){}
TextureConverter::~TextureConverter(){}

void TextureConverter::OutputUsage() {
	printf("画像ファイルをWIC形式からDDS形式に変換します。\n");
	printf("\n");
	printf("TextureConverter [ドライブ:][パス][ファイル名]\n");
	printf("\n");
	printf(" [ドライブ:][パス][ファイル名]: 変換したいWIC形式の画像ファイルを指定します。\n");
	printf(" \n");
	printf(" 指定した画像ファイルの後ろに[-mp][数字]: Mipレベルの指定をできます\n");
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString) {
	std::filesystem::path wString = mString;

	return wString.wstring();
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath,
	int numOptions, char* options[]) {

	//テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

	//DDSファイルに変換する
	SaveDDSTextureToFIle(numOptions, options);

}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath) {

	//ファイルパスをワイド文字列に変換
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

	//WICテクスチャのロード
	LRESULT result = LoadFromWICFile(wFilePath.c_str(), WIC_FLAGS_NONE, &metaData_, scratchImage_);
	assert(SUCCEEDED(result));

	//ファイルパスとファイル名を分離する
	SeparateFilePath(wFilePath);
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath) {
	size_t pos1;
	std::wstring exceptExt;

	//区切り文字'.'が出てくる一番最後の部分を検索
	pos1 = filePath.rfind('.');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//区切り文字の前までを書き出す
		exceptExt = filePath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}
	
	//区切り文字'\\'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos) {
		//区切り文字の前までディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイルネームとして保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//区切り文字'/'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		//区切り文字の前までディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイルネームとして保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//区切り文字がないのでファイル名のみとして扱う
	directoryPath_ = L"";
	fileName_ = exceptExt;
}

void TextureConverter::SaveDDSTextureToFIle(int numOptions, char* options[]) {
	LRESULT result;
	ScratchImage mipChain;
	
	//ミップの生成
	size_t mipLevels = 0;
	//ミップマップレベル指定を検索
	for (int i = 0; i < numOptions; i++) {
		if (std::string(options[i]) == "-ml") {
			//ミップレベル指定
			mipLevels = std::stoi(options[i + 1]);
			break;
		}
	}

	result = GenerateMipMaps(
		scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(),
		TEX_FILTER_DEFAULT, mipLevels, mipChain);
	if (SUCCEEDED(result)) {
		//イメージとメタデータを、ミップマップ版で置き換える
		scratchImage_ = std::move(mipChain);
		metaData_ = scratchImage_.GetMetadata();
	}

	//圧縮形式に変換
	ScratchImage converted;
	result = Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metaData_,
		DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT | TEX_COMPRESS_PARALLEL,
		1.0f, converted);
	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(converted);
		metaData_ = scratchImage_.GetMetadata();
	}

	//読み込んだテクスチャをSRGBとして扱う
	metaData_.format = MakeSRGB(metaData_.format);

	//出力ファイル名を設定する
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	//DDSファイル書き出し
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metaData_, DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(result));
}
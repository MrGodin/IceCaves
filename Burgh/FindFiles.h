
#pragma once
#include "Utils.h"



class FileFinder
{
protected:
	std::vector<TString>filenames;
public:
	FileFinder(){}


	__inline bool find_files(TString folder,TString ext)
	{
		TString result = folder;
		result += TString("/detected/BioID_*");
		result += ext;
		
		WIN32_FIND_DATA FindFileData;
		//string img = "C:\\opencvAssets/detected/BioID_*.pgm";
		HANDLE hFind = FindFirstFile(result.w_char(), &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE){
			return false;
		}
		else do{
			filenames.push_back(TString(FindFileData.cFileName));
			
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
		return true;
	}
};
//bool find_files(){
//	WIN32_FIND_DATA FindFileData;
//	string img = "C:\\opencvAssets/detected/BioID_*.pgm";
//	HANDLE hFind = FindFirstFile(img.c_str(), &FindFileData);
//	if (hFind == INVALID_HANDLE_VALUE){
//		return false;
//	}
//	else do{
//		cout << FindFileData.cFileName << endl;
//	} while (FindNextFile(hFind, &FindFileData));
//	FindClose(hFind);
//	return true;
//}
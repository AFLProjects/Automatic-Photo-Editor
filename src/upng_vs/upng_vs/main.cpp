#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <lodepng.h>

#include "MSColor.h";

using namespace std;

#pragma warning(disable:4996)

/*SETTINGS*/
bool fileExists(const std::string& name) {
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

struct Settings
{
public:
	/*
	Index - Property
	0 - Color Balance
	1 - White Intensity
	2 - Black Intensity
	3 - Shadow Intensity
	4 - Vividity Min
	5 - Vividity Max
	*/
	float data[6];

	Settings(string path)
	{
		std::ifstream file(path);
		std::string str;
		int k = 0;
		while (std::getline(file, str)) {
			data[k] = std::stof(str);
			k++;
		}
	}
	Settings() { memset(data, -1, sizeof(data)); }

	void DisplaySettings()
	{
		cout << "\nColor Balance : " << data[0] << endl;
		cout << "White Intensity : " << data[1] << endl;
		cout << "Black Intensity : " << data[2] << endl;
		cout << "Shadow Intensity : " << data[3] << endl;
		cout << "Vividity Min : " << data[4] << endl;
		cout << "Vividity Max : " << data[5] << endl << endl;
	}
};
/*SETTINGS END*/


/*IMAGES*/
std::vector<unsigned char> decodeImage(const char* filename) {
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filename);
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	return image;
}

void encodeImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
	unsigned error = lodepng::encode(filename, image, width, height);
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}
/*IMAGES END*/

Settings currentSettings = Settings("settings.ini");
int main() {

	/*<==FAST IO==>*/
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	/*<==TITLE==>*/
	const char *title =
		"     ----     `---.      .---.       .---.      .---`       `-----..`            `--------.            .://:-`          "
		"    `MMMM`    -MMMm      -NMMM:     -NMMM:      hMMM/       oMMMMMMMMNh/`        :MMMMMMMMd         /hNMMMMMMMms-       "
		"    `MMMM`    -MMMm       :MMMN.   `mMMM+       hMMM/       oMMMmssymMMMN:       :MMMNssss+       .dMMMMmhyhNMMMMy      "
		"    `MMMM`    -MMMm        oMMMd`  hMMMs        hMMM/       oMMMs    +MMMN.      :MMMm`````      `mMMMh.     :mMMMy     "
		"    `MMMM`    -MMMm         yMMMy oMMMh         hMMM/       oMMMs     mMMM+      :MMMMMMMMo      /MMMN        :MMMM`    "
		"    `MMMM`    :MMMm          dMMMyMMMd`         hMMM/       oMMMs    `NMMM:      :MMMNyyyy/      -MMMM-       oMMMm     "
		"     mMMMs`  .hMMMy          `mMMMMMN.          hMMM/       oMMMs  .+mMMMh       :MMMm            sMMMNs:.`./hMMMM:     "
		"     -NMMMMNNMMMMy`           .NMMMN-           hMMM/       oMMMMMMMMMMm+        :MMMMMMMMd        /mMMMMMMMMMMMh-      "
		"      `/sdmNmmho.              :hhh:            shhh:       /hhhhhhhs+-          -hhhhhhhhs          -ohdmNmdy+.        ";
	cout << title << "\n by Adrian Fluder" << endl;

	/*<==Commands==>*/
	const char *commands =
		"\nCommands :               "
		"\n\t-settings              //Shows the settings"
		"\n\t-settings -s           //Set setting manually"
		"\n\t-settings -a		    //Set the settings automatically from videos in <dir>"
		"\n\t-edit					//Edits the videos/images in <dir>\n\n";
	cout << commands << endl;

	while (true)
	{
		cout << ">>";
		std::string command;
		std::getline(std::cin, command);

		if (command == "settings")
		{
			if (!fileExists("settings.ini"))
			{
				std::ofstream file("settings.ini");
				file << "1\n100\n0\n50\n50\n70" << std::endl;
				file.close();
				currentSettings = Settings("settings.ini");
			}
			currentSettings.DisplaySettings();
		}
		else if (command == "settings -s")
		{
			string cb, wi, bi, si, vmi, vma;
			cout << "\nColor Balance : " << endl;
			std::getline(std::cin, cb);
			cout << "White Intensity : " << endl;
			std::getline(std::cin, wi);
			cout << "Black Intensity : " << endl;
			std::getline(std::cin, bi);
			cout << "Shadow Intensity : " << endl;
			std::getline(std::cin, si);
			cout << "Vividity Min : " << endl;
			std::getline(std::cin, vmi);
			cout << "Vividity Max : " << endl;
			std::getline(std::cin, vma);
			std::string output = cb + "\n" + wi + "\n" + bi + "\n" + si + "\n" + vmi + "\n" + vma;

			std::ofstream file("settings.ini");
			file << output << std::endl;
			file.close();

			cout << "\nNew Settings" << endl;
			currentSettings = Settings("settings.ini");
			currentSettings.DisplaySettings();
		}
		else if (command == "settings -a")
		{
			cout << "Not implemented!\n\n";
		}
		else if (command == "edit")
		{
			std::string path = "";
			cout << "\File Path : ";
			std::getline(std::cin, path);
			/*Decode*/
			std::vector<unsigned char> image = decodeImage(path.c_str());

			/*Image processing goes here*/

			/*Encode*/
			encodeImage(("updated_" + path).c_str(), image, 1920, 1080);
		}
	}

	std::getchar();
	return 0;

}


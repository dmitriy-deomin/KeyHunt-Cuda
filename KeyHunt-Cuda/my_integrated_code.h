
//
#include "BinSort.cpp"
#include "Bech32.h"
//-------------------------
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iomanip>
#include <array>

//std--------------------------
using std::cout;
using std::string;
using std::vector;
using std::cin;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::endl;
using std::cerr;
using std::setlocale;
using std::chrono::system_clock;
using std::isalpha;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::setw;
using std::setfill;
//---------------------------------------

//�����---------------------------------------
const char zagolovok[] = "\033[33m";//������
const char grey[] = "\033[90m";//�����
const char text_close[] = "\033[37m";//�����
const char text_run_perebor[] = "\033[96m";//�������
const char white[] = "\033[37m";
const char green[] = "\033[32m";//������
const char bluu[] = "\033[34m";//�����
//--------------------------------------------

uint64_t counterPROGRESS = 1000000; // ����� ������� ������ ���������� ���������


void create_bat_Brute(const std::string& text, const std::string& bat_file) {
	FILE* file = fopen(bat_file.c_str(), "w");

	if (file == nullptr) {
		// ��������� ������ �������� �����
		perror("[-] ������ ��� �������� �����");
		return;
	}
	fputs(text.c_str(), file); // ������ ������ � ����
	fclose(file); // �������� �����
}

void printHelp() {
	cout << "\033[37m"; //�����

#ifdef _WIN32 //� ����� ����� ��������� ������� ��� �������
	cout << grey;
	cout << "[+] =====================================================" << endl;
	cout << "[+]" << white << " .bat ����� ��� ������� � ��������������� ��������" << grey << endl;
	create_bat_Brute("KeyHunt-Cuda.exe -g --gpui 0 --coin BTC -m addresses --range 80000000000000000:fffffffffffffffff -i btc.bin -r 10000\npause", "START_BTC_GPU.bat");
	create_bat_Brute("KeyHunt-Cuda.exe -g --gpui 0 --coin BTC -m address --range 80000000000000000:fffffffffffffffff -r 10000 1MVDYgVaSN6iKKEsbzRUAYFrYJadLYZvvZ\npause", "START_BTC_1address_GPU.bat");
	create_bat_Brute("KeyHunt-Cuda.exe -t 1 --coin BTC -m addresses --range 80000000000000000:fffffffffffffffff -i btc.bin -r 10000\npause", "START_BTC_CPU.bat");
	create_bat_Brute("::������� ������ eth.txt ���� ������ ETH ��� TRX �������\nKeyHunt-Cuda.exe -convertFileETH eth.txt\npause", "CONVERT_TXT_ETH_TO_BIN.bat");
	create_bat_Brute("::������� ������ btc.txt ���� ������ BTC �������\nKeyHunt-Cuda.exe -convertFileBTC btc.txt\npause", "CONVERT_TXT_BTC_TO_BIN.bat");
	cout << "[+] =====================================================" << endl << endl;
#endif
	cout << grey;
	cout << "[+] =====================================================" << endl;
	cout << "[+]" << white << " ������ ������� ������ ���� c�������������,������������ � �������� � �������� ���� .bin" << grey << endl;
	cout << "[+]" << white << " �������������� ����� ���������� ����� CONVERT_TXT_TO_BIN.bat" << grey << endl;
	cout << "[+] =====================================================" << endl << endl;

	cout << "[+] =====================================================" << endl;
	cout << "[+]" << white << " ������ ���������� �������" << grey << endl;
	cout << "[+]"<< white <<" -h "<<grey<<"����� ������ �������"<< endl;
	cout << "[+]" << white << " -g " << grey << "����� � ������� ����������" << endl;
	cout << "[+]" << white << " --gpui " << grey << "����� ����������(--gpui 0)���� ����,���� ��������� ����������� ����� �������(--gpui 0,1,2)) " << endl;
	cout << "[+]" << white << " -m " << grey << "����� ������ ��:          " << endl;
	cout << "[+]    -m ADDRESS ������ �������            " << endl;
	cout << "[+]    -m ADDRESSES ������ ��������            " << endl;
	cout << "[+]    -m XPOINT ���������� �����           " << endl;
	cout << "[+]    -m XPOINTS ������ ������            " << endl;
	cout << "[+]" << white << " --coin " << grey << "BTC/ETH ��� �������          " << endl;
	cout << "[+]" << white << " --range " << grey << "�������� ������          " << endl;
	cout << "[+]   --range 80000000000000000:fffffffffffffffff (68 ����)       " << endl;
	cout << "[+]" << white << " -u " << grey << "����� ������ �������� ��������          " << endl;
	cout << "[+]" << white << " -b " << grey << "����� ������ � �������� ��������          " << endl;
	cout << "[+]" << white << " -r " << grey << "��������� ���������� ��������� �� ��������          " << endl;
	cout << "[+]    -r 1000 (��� ������� ����� ������ ��������� � ����� 1000 �������� ��������� �����)          " << endl;
	cout << "[+]" << white << " -t " << grey << "���������� ������� ��� ��� ������ �� ����������" << endl;
	cout << "[+]" << white << " -o " << grey << "���� ���� ����� ����������� ��������" << endl;
	cout << "[+]    (�� ��������� �������� ����� ����� ������������ �� 5 ������ ������ ��������� � �����,���� FOUND[80001_80002].txt )" << endl;
	cout << "[+]" << white << " -convertFileBTC " << grey << "��������������� � ���������� BTC �������� ��������(KeyHunt-Cuda.exe -convertFileBTC btc.txt)" << endl;
	cout << "[+]" << white << " -convertFileETH " << grey << "��������������� � ���������� ETH,TRX ��������(KeyHunt-Cuda.exe -convertFileETH eth.txt)" << endl;
	cout << "[+] =====================================================" << endl << endl;

	
	cout << "[+] =====================================================" << endl;
	cout << "[+]"<<green<<" ��������� ����� ���" << grey << endl;
	cout << "[+]" << bluu << "  https://github.com/iceland2k14/KeyHunt-Cuda" << grey << endl;
	cout << "[+]" << green << " ��� ���������:" << grey<<endl;
	cout << "[+]" << green << " -������� ���������" << grey << endl;
	cout << "[+]" << green << " -������� �����" << grey << endl;
	cout << "[+]" << green << " Github:" << grey << endl;
	cout << "[+]" << bluu << "  https://github.com/dmitriy-deomin/KeyHunt-Cuda" << grey << endl;
	cout << "[+]" << green << " ���������� �� ������� ) " << grey << endl;
	cout << "[+]" << green << " BTC:bc1qmkd9mxvwqhup3tcs9pwx59lnvd59xptp83c4tt" << grey << endl;
	cout << "[+]" << green << " ETH:0x129257C352792F398fdb1Df0A79D4608E0893705" << grey << endl;
	cout << "[+]" << green << " TRX:TBuFpK7NirtgvgMwpPLTtR2C3iFkrwfyj8" << grey << endl;
	cout << "[+] =====================================================" << endl;
}

//��� �� ����� �������� � �������
void enableAnsiCodes() {
#ifdef _WIN32 // ������ ��� ����� � ������ � ��� ������ ��������
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode)) return;

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
#endif
}

//
union hash160_20 {
	uint32_t bits5[5];
	uint8_t bits20[20];
};
//
void readHex(char* buf, const char* txt) {
	char b[3] = "00";
	for (unsigned int i = 0; i < strlen(txt); i += 2) {
		b[0] = *(txt + i);
		b[1] = *(txt + i + 1);
		*(buf + (i >> 1)) = strtoul(b, NULL, 16);
	}
}


int convertBTC(char *in) {

	cout << "\033[92m"; //����-������
	cout << "[+] ********����� ����������� BTC********\n";
	cout << "\033[90m"; //�������
	cout << "[+] ������� ����:\n";
	cout << "[+] BTC(� ����������� ���)\n";
	cout << "[+] 17Xawwqd8bZiXcEKsCEFWVEad3TrmncPsF\n";
	cout << "[+] 3MDDvsiHEKGyyV4XXWbMT7mW5etzvczF3g\n";
	cout << "[+] bc1qfrsxj0g29y08msesvckqcsehanrtvfgkthjgmk\n";
	cout << "\033[96m"; //�������
	string infile = in;

	// ������� ������ �������� ��� �������� ������ ��� ����������
	char outfile[256];
	char convfile[256] = "convfile.tmp";
	strncpy(outfile, infile.c_str(), sizeof(outfile));  // �������� ������ infile � outfile

	// ������ ��������� ����� � ������
	char* dot = strrchr(outfile, '.');

	// ��������, ��� ����� ������� � ��� ������ ".txt"
	if (dot && strcmp(dot, ".txt") == 0) {
		// �������� ���������� .txt �� .bin
		strcpy(dot, ".bin");
	}

	// �������� ���������
	cout << "\n[+] ������� ����: " << white << infile << grey << " -> ����������������+������������: " << white << outfile << grey << endl;

	// �������� �������� �����
	std::ifstream stream(infile.c_str());
	std::cout << "\n[+] ��������� ����: " << white << infile << grey << endl;
	if (!stream) {
		std::cout << "\033[31m"; //�������
		std::cout << "[-] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";
		std::cerr << "[-] ������,�� ������� ������� ����: '" << infile << "'" << endl;
		std::cout << "[-] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";
		std::cin.get();  // ���� ����� ������������
		// ��������� ���������� ���������
		std::abort();
	}

	// �������� ��������� ����� � �������� ������
	FILE* file = fopen(convfile, "wb");
	if (!file) {
		std::perror("������ ��� �������� ��������� �����");
		return false;
	}

	std::string buffer;
	int nr = 0;
	int totalLines = 0;

	// ���������� ���������� ����� ��� ������ ���������
	while (std::getline(stream, buffer)) {
		totalLines++;
	}
	stream.clear(); // ���������� ��������� ������
	stream.seekg(0); // ������������ � ������ �����

	cout << "\n���������������\n" << endl;

	try {
		while (std::getline(stream, buffer)) {
			// ��������, ��� ������ �� ������
			if (buffer.length() == 0) {
				continue;
			}

			hash160_20 h;
			vector<unsigned char> r160;
			if (buffer.length() == 34) {
				if (DecodeBase58(buffer, r160)) {
					for (int i = 1; i <= 20 && i < r160.size(); i++) {
						h.bits20[i - 1] = r160.at(i);
					}
				}
			}
			else if (buffer.at(0) == 'b') {
				size_t data_len = 0;
				uint8_t* data = new uint8_t[64];
				if (bech32_decode_my(data, &data_len, buffer.c_str())) {
					for (int i = 0; i < data_len && i < 20; i++) {
						h.bits20[i] = data[i];
					}
				}
			}

			// ������ ���� � ���� (� �������� ������)
			if (fwrite(h.bits20, 1, 20, file) != 20) {
				std::cerr << "������ ������ � ���� �� ������: " << nr + 1 << endl;
				fclose(file);
				return false;
			}

			// ��������� �������� �����
			nr++;

			// ����� ������������ ��������� ������ 100000 �����
			if (nr % 1000000 == 0 || nr == totalLines) {
				cout << "\r��������: " << nr << "/" << totalLines;
				cout.flush();  // ��������� ������ ��� ����� ������
			}
		}
	}
	catch (...) {
		std::cerr << "��������� ������ ��� ��������� �����." << endl;
		fclose(file);
		return false;
	}

	// �������� ������
	fclose(file);
	stream.close();

	cout << endl; // ������� ������ ����� ���������� ������
	cout << "[+] ������\n" << endl;
	cout << "[+] ����������:" << convfile << endl;


	sort_file(20, convfile, outfile);

	//������� ��������� convfile
	if (remove(convfile) != 0) {
		cout << "\033[31m"; //�������
		cout << "\n[+] ��������� �������:\n" << convfile << " ������� �������" << endl;
	}

	cout << "\n[+] ������:" << outfile << endl;

	// ������� ������� ������� Enter, ����� ��������� �� ����������� �����
	cout << text_close;
	cout << "���� ����� �������";
	cin.get();  // ���� ����� ������������
	return 0;
}

int convertETH(char* in) {

	cout << zagolovok;
	cout << "[+] ********����� ����������� ETH********\n";
	cout << "\033[90m"; //�������
	cout << "[+] ������� ����:\n";
	cout << "[+] ETH\n";
	cout << "[+] 0xbC75b3f4Dc162C7a8aBF885822be0bcAa6FCeeB3\n";
	cout << "[+] bC75b3f4Dc162C7a8aBF885822be0bcAa6FCeeB3\n";
	cout << "[+] TRX\n";
	cout << "[+] TT9h3GV9ePs6CV4jcH4gB3jskb6zh6WC4e\n";
	cout << "\033[96m"; //�������
	string infile = in;

	// ������� ������ �������� ��� �������� ������ ��� ����������
	char outfile[256];
	char convfile[256] = "convfile.tmp";
	strncpy(outfile, infile.c_str(), sizeof(outfile));  // �������� ������ infile � outfile

	// ������ ��������� ����� � ������
	char* dot = strrchr(outfile, '.');

	// ��������, ��� ����� ������� � ��� ������ ".txt"
	if (dot && strcmp(dot, ".txt") == 0) {
		// �������� ���������� .txt �� .bin
		strcpy(dot, ".bin");
	}

	// �������� ���������
	cout << "\n[+] ������� ����: " << white << infile << grey << " -> ����������������+������������: " << white << outfile << grey << endl;

	// �������� �������� �����
	std::ifstream stream(infile.c_str());
	cout << "[+] ��������� ����: " << white << infile << grey << endl;
	if (!stream) {
		cout << "\033[31m"; //�������
		cout << "[-] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cerr << "[-] ������,�� ������� ������� ����: '" << infile << "'" << endl;
		cout << "[-] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cin.get();  // ���� ����� ������������
		// ��������� ���������� ���������
		std::abort();
	}

	// �������� ��������� ����� � �������� ������
	FILE* file = fopen(convfile, "wb");
	if (!file) {
		std::perror("[-] ������ ��� �������� ��������� �����");
		return false;
	}

	string buffer;
	int nr = 0;
	int totalLines = 0;

	// ���������� ���������� ����� ��� ������ ���������
	while (std::getline(stream, buffer)) {
		totalLines++;
	}
	stream.clear(); // ���������� ��������� ������
	stream.seekg(0); // ������������ � ������ �����

	cout << "[+] ���������������" << endl;
	hash160_20 h;
	memset(&h, 0, sizeof(h));
	try {
		while (std::getline(stream, buffer)) {

			// ��������, ��� ������ �� ������
			if (buffer.length() == 0) {
				continue;
			}


			//���� ������ ������ 34(trx) ������� ��� eth
			if (buffer.size() == 34) {
				// ������� ������������� Base58
				vector<unsigned char> binding;
				// ������� ������������� Base58
				if (!DecodeBase58(buffer, binding)) {
					cerr << "[-] ������ ������������� Base58 �� ������: " << nr + 1 << endl;
					continue; // ���������� ���� ����� � ��������� � ����������
				}
				// �������� ����� � ����������� � ������ �������� 20 ����
				if (binding.size() >= 21) {
					std::array<unsigned char, 20> a;
					std::copy(binding.begin() + 1, binding.begin() + 21, a.begin());

					// ����������� 20 ������ � ��������� ����
					for (int i = 0; i < 20; i++) {
						h.bits20[i] = a[i];
					}
				}
			}
			else {
				if (buffer.size() > 2 && (buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X'))) {
					buffer = buffer.substr(2); // ������� "0x"   
				}

				// ��������, ��� ������ ����� ���������� ����� ��� 20 ���� (40 �������� � hex)
				if (buffer.length() != 40) {
					cerr << "[-] ������������ ����� ������: " << buffer << endl;
					continue;
				}

				// ����������� hex ������ � �����
				char buf[20] = { 0 };
				readHex(buf, buffer.c_str());

				// ����������� 20 ������ � ��������� ����
				for (int i = 0; i < 20; i++) {
					h.bits20[i] = buf[i];
				}
			}

			// ������ ���� � ���� (� �������� ������)
			if (fwrite(h.bits20, 1, 20, file) != 20) {
				cerr << "[-] ������ ������ � ���� �� ������: " << nr + 1 << endl;
				fclose(file);
				return false;
			}

			// ��������� �������� �����
			nr++;

			// ����� ������������ ��������� ������ 100000 �����
			if (nr % counterPROGRESS == 0 || nr == totalLines) {
				cout << "\r[+] " << nr << "/" << totalLines;
				cout.flush();  // ��������� ������ ��� ����� ������
			}
		}
	}
	catch (...) {
		cerr << "[-] ��������� ������ ��� ��������� �����." << endl;
		fclose(file);
		return false;
	}

	// �������� ������
	fclose(file);
	stream.close();

	cout << endl; // ������� ������ ����� ���������� ������
	cout << "[+] ������\n" << endl;
	cout << "[+] ����������:" << convfile << endl;


	sort_file(20, convfile, outfile);

	//������� ��������� convfile
	if (remove(convfile) != 0) {
		cout << "\033[31m"; //�������
		cout << "\n[+] ��������� �������:\n" << convfile << " ������� �������" << endl;
	}

	cout << "\n[+] ������:" << outfile << endl;

	// ������� ������� ������� Enter, ����� ��������� �� ����������� �����
	cout << text_close;
	cout << "���� ����� �������";
	cin.get();  // ���� ����� ������������
	return 0;
}

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

//цвета---------------------------------------
const char zagolovok[] = "\033[33m";//желтый
const char grey[] = "\033[90m";//серый
const char text_close[] = "\033[37m";//белый
const char text_run_perebor[] = "\033[96m";//голубой
const char white[] = "\033[37m";
const char green[] = "\033[32m";//зелёный
const char bluu[] = "\033[34m";//синий
//--------------------------------------------

uint64_t counterPROGRESS = 1000000; // через сколько делать обновление прогресса


void create_bat_Brute(const std::string& text, const std::string& bat_file) {
	FILE* file = fopen(bat_file.c_str(), "w");

	if (file == nullptr) {
		// Обработка ошибки открытия файла
		perror("[-] Ошибка при открытии файла");
		return;
	}
	fputs(text.c_str(), file); // Запись строки в файл
	fclose(file); // Закрытие файла
}

void printHelp() {
	cout << "\033[37m"; //белый

#ifdef _WIN32 //в винде будем создавать батники для запуска
	cout << grey;
	cout << "[+] =====================================================" << endl;
	cout << "[+]" << white << " .bat ФАЙЛЫ ДЛЯ ЗАПУСКА И КОНВЕРТИРОВАНИЯ СОЗДАННЫ" << grey << endl;
	create_bat_Brute("KeyHunt-Cuda.exe -g --gpui 0 --coin BTC -m addresses --range 80000000000000000:fffffffffffffffff -i btc.bin -r 10000\npause", "START_BTC_GPU.bat");
	create_bat_Brute("KeyHunt-Cuda.exe -g --gpui 0 --coin BTC -m address --range 80000000000000000:fffffffffffffffff -r 10000 1MVDYgVaSN6iKKEsbzRUAYFrYJadLYZvvZ\npause", "START_BTC_1address_GPU.bat");
	create_bat_Brute("KeyHunt-Cuda.exe -t 1 --coin BTC -m addresses --range 80000000000000000:fffffffffffffffff -i btc.bin -r 10000\npause", "START_BTC_CPU.bat");
	create_bat_Brute("::Укажите вместо eth.txt свой список ETH или TRX адресов\nKeyHunt-Cuda.exe -convertFileETH eth.txt\npause", "CONVERT_TXT_ETH_TO_BIN.bat");
	create_bat_Brute("::Укажите вместо btc.txt свой список BTC адресов\nKeyHunt-Cuda.exe -convertFileBTC btc.txt\npause", "CONVERT_TXT_BTC_TO_BIN.bat");
	cout << "[+] =====================================================" << endl << endl;
#endif
	cout << grey;
	cout << "[+] =====================================================" << endl;
	cout << "[+]" << white << " Список адресов должен быть cконвертирован,отсортирован и сохранен в бинарный файл .bin" << grey << endl;
	cout << "[+]" << white << " Конвертировать можно программой через CONVERT_TXT_TO_BIN.bat" << grey << endl;
	cout << "[+] =====================================================" << endl << endl;

	cout << "[+] =====================================================" << endl;
	cout << "[+]" << white << " Список параметров запуска" << grey << endl;
	cout << "[+]"<< white <<" -h "<<grey<<"Вызов родной справки"<< endl;
	cout << "[+]" << white << " -g " << grey << "Поиск с помощью видеокарты" << endl;
	cout << "[+]" << white << " --gpui " << grey << "Номер видеокарты(--gpui 0)если одна,если несколько перечислить через запятую(--gpui 0,1,2)) " << endl;
	cout << "[+]" << white << " -m " << grey << "Режим поиска по:          " << endl;
	cout << "[+]    -m ADDRESS одному адрессу            " << endl;
	cout << "[+]    -m ADDRESSES списку адрессов            " << endl;
	cout << "[+]    -m XPOINT публичному ключу           " << endl;
	cout << "[+]    -m XPOINTS списку ключей            " << endl;
	cout << "[+]" << white << " --coin " << grey << "BTC/ETH тип адресса          " << endl;
	cout << "[+]" << white << " --range " << grey << "Диапазон поиска          " << endl;
	cout << "[+]   --range 80000000000000000:fffffffffffffffff (68 пазл)       " << endl;
	cout << "[+]" << white << " -u " << grey << "Поиск только несжатых адрессов          " << endl;
	cout << "[+]" << white << " -b " << grey << "Поиск сжатых и несжатых адрессов          " << endl;
	cout << "[+]" << white << " -r " << grey << "Включение рандомного диапазона из заданого          " << endl;
	cout << "[+]    -r 1000 (при запуске будет выбран случайный и через 1000 милионов смениться опять)          " << endl;
	cout << "[+]" << white << " -t " << grey << "Количество потоков цпу при поиске на процессоре" << endl;
	cout << "[+]" << white << " -o " << grey << "Файл куда будет сохраняться найденое" << endl;
	cout << "[+]    (По умолчанию название файла будет сформировано из 5 знаков начала диапазона и конца,вида FOUND[80001_80002].txt )" << endl;
	cout << "[+]" << white << " -convertFileBTC " << grey << "Конвертирование и сотрировка BTC подобных адрессов(KeyHunt-Cuda.exe -convertFileBTC btc.txt)" << endl;
	cout << "[+]" << white << " -convertFileETH " << grey << "Конвертирование и сотрировка ETH,TRX адрессов(KeyHunt-Cuda.exe -convertFileETH eth.txt)" << endl;
	cout << "[+] =====================================================" << endl << endl;

	
	cout << "[+] =====================================================" << endl;
	cout << "[+]"<<green<<" Программа взята тут" << grey << endl;
	cout << "[+]" << bluu << "  https://github.com/iceland2k14/KeyHunt-Cuda" << grey << endl;
	cout << "[+]" << green << " Мои изменения:" << grey<<endl;
	cout << "[+]" << green << " -встроил конвертер" << grey << endl;
	cout << "[+]" << green << " -изменил вывод" << grey << endl;
	cout << "[+]" << green << " Github:" << grey << endl;
	cout << "[+]" << bluu << "  https://github.com/dmitriy-deomin/KeyHunt-Cuda" << grey << endl;
	cout << "[+]" << green << " Задонатить на доширак ) " << grey << endl;
	cout << "[+]" << green << " BTC:bc1qmkd9mxvwqhup3tcs9pwx59lnvd59xptp83c4tt" << grey << endl;
	cout << "[+]" << green << " ETH:0x129257C352792F398fdb1Df0A79D4608E0893705" << grey << endl;
	cout << "[+]" << green << " TRX:TBuFpK7NirtgvgMwpPLTtR2C3iFkrwfyj8" << grey << endl;
	cout << "[+] =====================================================" << endl;
}

//что бы цвета работали в консоли
void enableAnsiCodes() {
#ifdef _WIN32 // только для винды в линукс и так должно работать
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

	cout << "\033[92m"; //ярко-зелёный
	cout << "[+] ********РЕЖИМ КОНВЕРТАЦИИ BTC********\n";
	cout << "\033[90m"; //голубой
	cout << "[+] АДРЕССА ВИДА:\n";
	cout << "[+] BTC(и аналогичные ему)\n";
	cout << "[+] 17Xawwqd8bZiXcEKsCEFWVEad3TrmncPsF\n";
	cout << "[+] 3MDDvsiHEKGyyV4XXWbMT7mW5etzvczF3g\n";
	cout << "[+] bc1qfrsxj0g29y08msesvckqcsehanrtvfgkthjgmk\n";
	cout << "\033[96m"; //голубой
	string infile = in;

	// Создаем массив символов для хранения строки без расширения
	char outfile[256];
	char convfile[256] = "convfile.tmp";
	strncpy(outfile, infile.c_str(), sizeof(outfile));  // Копируем строку infile в outfile

	// Найдем последнюю точку в строке
	char* dot = strrchr(outfile, '.');

	// Проверим, что точка найдена и это именно ".txt"
	if (dot && strcmp(dot, ".txt") == 0) {
		// Заменяем расширение .txt на .bin
		strcpy(dot, ".bin");
	}

	// Печатаем результат
	cout << "\n[+] ВХОДНОЙ ФАЙЛ: " << white << infile << grey << " -> КОНВЕРТИРОВАННЫЙ+СОРТИРОВАНЫЙ: " << white << outfile << grey << endl;

	// Открытие входного файла
	std::ifstream stream(infile.c_str());
	std::cout << "\n[+] ОТКРЫВАЕМ ФАЙЛ: " << white << infile << grey << endl;
	if (!stream) {
		std::cout << "\033[31m"; //красный
		std::cout << "[-] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";
		std::cerr << "[-] ОШИБКА,НЕ УДАЛОСЬ ОТКРЫТЬ ФАЙЛ: '" << infile << "'" << endl;
		std::cout << "[-] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";
		std::cin.get();  // Ждем ввода пользователя
		// Аварийное завершение программы
		std::abort();
	}

	// Открытие выходного файла в бинарном режиме
	FILE* file = fopen(convfile, "wb");
	if (!file) {
		std::perror("Ошибка при открытии выходного файла");
		return false;
	}

	std::string buffer;
	int nr = 0;
	int totalLines = 0;

	// Подсчитаем количество строк для вывода прогресса
	while (std::getline(stream, buffer)) {
		totalLines++;
	}
	stream.clear(); // сбрасываем состояние потока
	stream.seekg(0); // возвращаемся в начало файла

	cout << "\nКОНВЕРТИРОВАНИЕ\n" << endl;

	try {
		while (std::getline(stream, buffer)) {
			// Проверка, что строка не пустая
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

			// Запись хэша в файл (в бинарном режиме)
			if (fwrite(h.bits20, 1, 20, file) != 20) {
				std::cerr << "Ошибка записи в файл на строке: " << nr + 1 << endl;
				fclose(file);
				return false;
			}

			// Инкремент счётчика строк
			nr++;

			// Вывод обновляемого прогресса каждые 100000 строк
			if (nr % 1000000 == 0 || nr == totalLines) {
				cout << "\rПрогресс: " << nr << "/" << totalLines;
				cout.flush();  // обновляем строку без новой строки
			}
		}
	}
	catch (...) {
		std::cerr << "Произошла ошибка при обработке файла." << endl;
		fclose(file);
		return false;
	}

	// Закрытие файлов
	fclose(file);
	stream.close();

	cout << endl; // Перевод строки после завершения работы
	cout << "[+] ГОТОВО\n" << endl;
	cout << "[+] СОРТИРОВКА:" << convfile << endl;


	sort_file(20, convfile, outfile);

	//удаляем временный convfile
	if (remove(convfile) != 0) {
		cout << "\033[31m"; //красный
		cout << "\n[+] НЕУДАЛОСЬ УДАЛИТЬ:\n" << convfile << " УДАЛИТЕ ВРУЧНУЮ" << endl;
	}

	cout << "\n[+] ГОТОВО:" << outfile << endl;

	// Ожидаем нажатия клавиши Enter, чтобы программа не закрывалась сразу
	cout << text_close;
	cout << "окно можно закрыть";
	cin.get();  // Ждем ввода пользователя
	return 0;
}

int convertETH(char* in) {

	cout << zagolovok;
	cout << "[+] ********РЕЖИМ КОНВЕРТАЦИИ ETH********\n";
	cout << "\033[90m"; //голубой
	cout << "[+] АДРЕССА ВИДА:\n";
	cout << "[+] ETH\n";
	cout << "[+] 0xbC75b3f4Dc162C7a8aBF885822be0bcAa6FCeeB3\n";
	cout << "[+] bC75b3f4Dc162C7a8aBF885822be0bcAa6FCeeB3\n";
	cout << "[+] TRX\n";
	cout << "[+] TT9h3GV9ePs6CV4jcH4gB3jskb6zh6WC4e\n";
	cout << "\033[96m"; //голубой
	string infile = in;

	// Создаем массив символов для хранения строки без расширения
	char outfile[256];
	char convfile[256] = "convfile.tmp";
	strncpy(outfile, infile.c_str(), sizeof(outfile));  // Копируем строку infile в outfile

	// Найдем последнюю точку в строке
	char* dot = strrchr(outfile, '.');

	// Проверим, что точка найдена и это именно ".txt"
	if (dot && strcmp(dot, ".txt") == 0) {
		// Заменяем расширение .txt на .bin
		strcpy(dot, ".bin");
	}

	// Печатаем результат
	cout << "\n[+] ВХОДНОЙ ФАЙЛ: " << white << infile << grey << " -> КОНВЕРТИРОВАННЫЙ+СОРТИРОВАНЫЙ: " << white << outfile << grey << endl;

	// Открытие входного файла
	std::ifstream stream(infile.c_str());
	cout << "[+] ОТКРЫВАЕМ ФАЙЛ: " << white << infile << grey << endl;
	if (!stream) {
		cout << "\033[31m"; //красный
		cout << "[-] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cerr << "[-] ОШИБКА,НЕ УДАЛОСЬ ОТКРЫТЬ ФАЙЛ: '" << infile << "'" << endl;
		cout << "[-] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cin.get();  // Ждем ввода пользователя
		// Аварийное завершение программы
		std::abort();
	}

	// Открытие выходного файла в бинарном режиме
	FILE* file = fopen(convfile, "wb");
	if (!file) {
		std::perror("[-] Ошибка при открытии выходного файла");
		return false;
	}

	string buffer;
	int nr = 0;
	int totalLines = 0;

	// Подсчитаем количество строк для вывода прогресса
	while (std::getline(stream, buffer)) {
		totalLines++;
	}
	stream.clear(); // сбрасываем состояние потока
	stream.seekg(0); // возвращаемся в начало файла

	cout << "[+] КОНВЕРТИРОВАНИЕ" << endl;
	hash160_20 h;
	memset(&h, 0, sizeof(h));
	try {
		while (std::getline(stream, buffer)) {

			// Проверка, что строка не пустая
			if (buffer.length() == 0) {
				continue;
			}


			//если строка длинее 34(trx) значить она eth
			if (buffer.size() == 34) {
				// Попытка декодирования Base58
				vector<unsigned char> binding;
				// Попытка декодирования Base58
				if (!DecodeBase58(buffer, binding)) {
					cerr << "[-] Ошибка декодирования Base58 на строке: " << nr + 1 << endl;
					continue; // Пропускаем этот адрес и переходим к следующему
				}
				// Проверка длины и копирование в массив размером 20 байт
				if (binding.size() >= 21) {
					std::array<unsigned char, 20> a;
					std::copy(binding.begin() + 1, binding.begin() + 21, a.begin());

					// Копирование 20 байтов в структуру хэша
					for (int i = 0; i < 20; i++) {
						h.bits20[i] = a[i];
					}
				}
			}
			else {
				if (buffer.size() > 2 && (buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X'))) {
					buffer = buffer.substr(2); // Убираем "0x"   
				}

				// Проверка, что строка имеет корректную длину для 20 байт (40 символов в hex)
				if (buffer.length() != 40) {
					cerr << "[-] Некорректная длина строки: " << buffer << endl;
					continue;
				}

				// Конвертация hex строки в байты
				char buf[20] = { 0 };
				readHex(buf, buffer.c_str());

				// Копирование 20 байтов в структуру хэша
				for (int i = 0; i < 20; i++) {
					h.bits20[i] = buf[i];
				}
			}

			// Запись хэша в файл (в бинарном режиме)
			if (fwrite(h.bits20, 1, 20, file) != 20) {
				cerr << "[-] Ошибка записи в файл на строке: " << nr + 1 << endl;
				fclose(file);
				return false;
			}

			// Инкремент счётчика строк
			nr++;

			// Вывод обновляемого прогресса каждые 100000 строк
			if (nr % counterPROGRESS == 0 || nr == totalLines) {
				cout << "\r[+] " << nr << "/" << totalLines;
				cout.flush();  // обновляем строку без новой строки
			}
		}
	}
	catch (...) {
		cerr << "[-] Произошла ошибка при обработке файла." << endl;
		fclose(file);
		return false;
	}

	// Закрытие файлов
	fclose(file);
	stream.close();

	cout << endl; // Перевод строки после завершения работы
	cout << "[+] ГОТОВО\n" << endl;
	cout << "[+] СОРТИРОВКА:" << convfile << endl;


	sort_file(20, convfile, outfile);

	//удаляем временный convfile
	if (remove(convfile) != 0) {
		cout << "\033[31m"; //красный
		cout << "\n[+] НЕУДАЛОСЬ УДАЛИТЬ:\n" << convfile << " УДАЛИТЕ ВРУЧНУЮ" << endl;
	}

	cout << "\n[+] ГОТОВО:" << outfile << endl;

	// Ожидаем нажатия клавиши Enter, чтобы программа не закрывалась сразу
	cout << text_close;
	cout << "окно можно закрыть";
	cin.get();  // Ждем ввода пользователя
	return 0;
}
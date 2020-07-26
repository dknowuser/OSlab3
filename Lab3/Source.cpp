#include <Windows.h>
#include <iostream>

int main(void)
{
	setlocale(LC_ALL, "Russian");
	char InputChar = '\0';

	while (InputChar != '0')
	{
		std::cout << std::endl << "Меню:" << std::endl << std::endl;
		std::cout << "1 - вывод списка дисков;" << std::endl;
		std::cout << "2 - для одного из выбранных дисков вывод информации о диске и размер свободного пространства;" << std::endl;
		std::cout << "3 - создание и удаление заданных каталогов;" << std::endl;
		std::cout << "4 - создание файлов;" << std::endl;
		std::cout << "5 - копирование и перемещение файлов между каталогами с возможностью выявления\nпопытки работы с файлами, имеющими совпадающие имена;" << std::endl;
		std::cout << "6 - анализ и изменение атрибутов файлов;" << std::endl;
		std::cout << "0 - выход;" << std::endl;
		std::cout << ">> ";

		std::cin >> InputChar;

		int SomeTemp = 0;
		int Counter = 0;
	    char *DiskName = new char[80];
		bool ErrorOccured = false;
		wchar_t* wcDiskName = new wchar_t[80];
		char *cPath = new char[256];
		wchar_t* mPath = new wchar_t[256];
		char *cPath1 = new char[256];
		wchar_t* mPath1 = new wchar_t[256];

		LPTSTR lpVolumeNameBufferm;
		DWORD *lpVolumeSerialNumberm;
		DWORD *lpMaximumComponentLengthm;
		DWORD *lpFileSystemFlagsm;
		wchar_t  *lpFileSystemNameBufferm;

		DWORD *lpSectorsPerClusterm;
		DWORD *lpBytesPerSector;
		DWORD *lpNumberOfFreeClusters;
		DWORD *lpTotalNumberOfClusters;

		switch (InputChar)
		{
		case '1':
			std::cout << "Список дисков:" << std::endl;
			SomeTemp = GetLogicalDrives();

			//В цикле проходим по всем битам полученного числа и выводим найденные диски
			Counter = 0;
			while (SomeTemp)
			{
				if (SomeTemp & 1)
				{
					std::cout << (char)(65 + Counter) << ' ';
				};

				SomeTemp >>= 1;
				Counter++;
			};

			break;
		case '2':
			std::cout << "Введите имя диска, о котором нужно вывести информацию: ";
			std::cin >> DiskName;
			mbstowcs_s(NULL, wcDiskName, 80, DiskName, _TRUNCATE);

			//Определяем тип диска
			switch (GetDriveType(wcDiskName))
			{
			case 0:
				std::cout << "Ошибка! Тип диска не может быть определён." << std::endl;
				ErrorOccured = true;
				break;
			case 1:
				std::cout << "Ошибка! Путь неверен." << std::endl;
				ErrorOccured = true;
				break;
			case 2:
				std::cout << DiskName << " - сменный диск." << std::endl;
				break;
			case 3: 
				std::cout << DiskName << " - жёсткий диск." << std::endl;
				break;
			case 4:
				std::cout << DiskName << " - сетевой диск." << std::endl;
				break;
			case 5:
				std::cout << DiskName << " - CD-ROM." << std::endl;
				break;
			case 6:
				std::cout << DiskName << " - RAM-диск." << std::endl;
				break;
			default:
				std::cout << "Неизвестная ошибка." << std::endl;
				ErrorOccured = true;
				break;
			};

			if (ErrorOccured)
				break;

			//Выводим информацию о диске
			lpVolumeNameBufferm = new wchar_t[MAX_PATH + 1];
			lpVolumeSerialNumberm = new DWORD;
			lpMaximumComponentLengthm = new DWORD;
			lpFileSystemFlagsm = new DWORD;
			lpFileSystemNameBufferm = new wchar_t[MAX_PATH + 1];

			if (!GetVolumeInformation(wcDiskName, lpVolumeNameBufferm, MAX_PATH + 1, lpVolumeSerialNumberm, lpMaximumComponentLengthm, lpFileSystemFlagsm, lpFileSystemNameBufferm, MAX_PATH + 1))
			{
				std::cout << "Неизвестная ошибка." << std::endl;
				ErrorOccured = true;
			}
			else
			{
				//Выводим имя диска
				std::cout << "Имя диска: ";
				char *ptr = (char*)lpVolumeNameBufferm;
				while (*ptr)
				{
					std::cout << *ptr;
					ptr++; ptr++;
				};
				std::cout << std::endl;

				//Выводим серийный номер диска
				std::cout << "Серийный номер диска: " << *lpVolumeSerialNumberm << std::endl;

				//Выводим максимальную длину имени файла
				std::cout << "Максимальная длина имени файла: " << *lpMaximumComponentLengthm << std::endl;

				//Выводим флаги, связанные с файловой системой
				if (*lpFileSystemFlagsm & 0x00000001)
					std::cout << "Поддержка имён файлов с учётом регистра." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000002)
					std::cout << "Поддержка сохранённого регистра имён файлов при размещении на диске." << std::endl;
				
				if (*lpFileSystemFlagsm & 0x20000000)
					std::cout << "Том прямого доступа (DAX)." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000010)
					std::cout << "Поддержка сжатия на основе файлов." << std::endl;

				if (*lpFileSystemFlagsm & 0x00040000)
					std::cout << "Поддержка именованных потоков." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000008)
					std::cout << "Поддержка сохранения и применения списков управления доступом (ACL)." << std::endl;

				if (*lpFileSystemFlagsm & 0x00080000)
					std::cout << "Только для чтения." << std::endl;

				if (*lpFileSystemFlagsm & 0x00100000)
					std::cout << "Поддержка одной последовательной записи." << std::endl;

				if (*lpFileSystemFlagsm & 0x00020000)
					std::cout << "Поддержка зашифрованной файловой системы (EFS)." << std::endl;

				if (*lpFileSystemFlagsm & 0x00800000)
					std::cout << "Поддержка расширенных атрибутов." << std::endl;

				if (*lpFileSystemFlagsm & 0x00400000)
					std::cout << "Поддержка жёстких ссылок." << std::endl;

				if (*lpFileSystemFlagsm & 0x00010000)
					std::cout << "Поддержка идентификаторов объектов." << std::endl;

				if (*lpFileSystemFlagsm & 0x01000000)
					std::cout << "Поддержка открытия по идентификатору файла." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000080)
					std::cout << "Поддержка точек повторной обработки." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000040)
					std::cout << "Поддержка разреженных файлов." << std::endl;

				if (*lpFileSystemFlagsm & 0x00200000)
					std::cout << "Поддержка транзакций." << std::endl;

				if (*lpFileSystemFlagsm & 0x02000000)
					std::cout << "Поддержка журналов порядкового номера обновления (USN)." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000004)
					std::cout << "Поддержка Unicode в именах файлов по мере их появления на диске." << std::endl;

				if (*lpFileSystemFlagsm & 0x00008000)
					std::cout << "Сжатый диск." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000020)
					std::cout << "Поддержка дисковых квот." << std::endl;

				//Выводим имя файловой системы
				std::cout << "Имя файловой системы: ";
				ptr = (char*)lpFileSystemNameBufferm;
				while (*ptr)
				{
					std::cout << *ptr;
					ptr++; ptr++;
				};
				std::cout << std::endl;
			};

			delete[] lpFileSystemNameBufferm;
			delete lpFileSystemFlagsm;
			delete lpMaximumComponentLengthm;
			delete lpVolumeSerialNumberm;
			delete[] lpVolumeNameBufferm;

			if (ErrorOccured)
				break;

			//Получаем размер свободного пространства на диске
			lpSectorsPerClusterm = new DWORD;
			lpBytesPerSector = new DWORD;
			lpNumberOfFreeClusters = new DWORD;
			lpTotalNumberOfClusters = new DWORD;

			if (!GetDiskFreeSpace(wcDiskName, lpSectorsPerClusterm, lpBytesPerSector, lpNumberOfFreeClusters, lpTotalNumberOfClusters))
			{
				std::cout << "Неизвестная ошибка." << std::endl;
				ErrorOccured = true;
			}
			else
			{
				std::cout << "Число секторов в кластере: " << *lpSectorsPerClusterm << std::endl;
				std::cout << "Байт в секторе: " << *lpBytesPerSector << std::endl;
				std::cout << "Число свободных кластеров: " << *lpNumberOfFreeClusters << std::endl;
				std::cout << "Общее число кластеров: " << *lpTotalNumberOfClusters << std::endl;
			};

			delete lpSectorsPerClusterm;
			delete lpBytesPerSector;
			delete lpNumberOfFreeClusters;
			delete lpTotalNumberOfClusters;

			break;
		case '3':
			InputChar = '0';
			std::cout << "Введите \'c\', чтобы создать каталог, или \'d\', чтобы удалить каталог: ";
			std::cin >> InputChar;

			if ((InputChar == 'c') || (InputChar == 'C'))
			{
				std::cout << "Введите имя создаваемого каталога:" << std::endl;
				std::cin >> cPath;
				mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

				if (!CreateDirectory(mPath, NULL))
					std::cout << "Ошибка при создании каталога \'" << cPath << "\"" << std::endl;
				else
					std::cout << "Каталог \"" << cPath << "\" успешно создан." << std::endl;
			}
			else
			{
				if ((InputChar == 'd') || (InputChar == 'D'))
				{
					std::cout << "Введите имя удаляемого каталога:" << std::endl;
					std::cin >> cPath;
					mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

					if (!RemoveDirectory(mPath))
						std::cout << "Ошибка при удалении каталога \"" << cPath << "\"." << std::endl;
					else
						std::cout << "Каталог \"" << cPath << "\" успешно удалён." << std::endl;
				}
				else
				{
					std::cout << "Ошибка! Введён неверный параметр при выборе операции." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};

			break;
		case '4':
			std::cout << "Введите имя файла, который нужно создать:" << std::endl;
			std::cin >> cPath;
			mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

			if(CreateFile(mPath, GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL) == INVALID_HANDLE_VALUE)
				std::cout << "Ошибка при создании файла \"" << cPath << "\"." << std::endl;
			else
				std::cout << "Файл \"" << cPath << "\" успешно создан." << std::endl;
			break;
		case '5':
			InputChar = '0';
			std::cout << "Введите \'c\', чтобы скопировать файл, или \'m\', чтобы переместить файл: ";
			std::cin >> InputChar;

			if ((InputChar == 'c') || (InputChar == 'C'))
			{
				std::cout << "Введите имя файла, который нужно скопировать:" << std::endl;
				std::cin >> cPath;
				mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

				std::cout << "Введите имя нового файла:" << std::endl;
				std::cin >> cPath1;
				mbstowcs_s(NULL, mPath1, 256, cPath1, _TRUNCATE);

				if (CopyFile(mPath, mPath1, TRUE))
					std::cout << "Файл \"" << cPath << "\" успешно скопирован в файл \"" << cPath1 << "\"." << std::endl;
				else
					std::cout << "Ошибка при копировании файла \"" << cPath << "\" в файл \"" << cPath1 << "\"\n - совпадающие имена файлов." << std::endl;
			}
			else
			{
				if ((InputChar == 'm') || (InputChar == 'M'))
				{
					std::cout << "Введите имя файла, который нужно переместить:" << std::endl;
					std::cin >> cPath;
					mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

					std::cout << "Введите путь, куда нужно переместить файл:" << std::endl;
					std::cin >> cPath1;
					mbstowcs_s(NULL, mPath1, 256, cPath1, _TRUNCATE);

					if (MoveFile(mPath, mPath1))
						std::cout << "Файл \"" << cPath << "\" успешно перемещён по пути \"" << cPath1 << "\"." << std::endl;
					else
						std::cout << "Ошибка при перемещении файла \"" << cPath << "\" по пути \"" << cPath1 << "\"\n - совпадающие имена файлов." << std::endl;
				}
				else
				{
					std::cout << "Ошибка! Введён неверный параметр при выборе операции." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};

			break;
		case '6':
			InputChar = '0';
			std::cout << "Введите \'g\', чтобы получить атрибуты файла,\nили \'s\', чтобы установить атрибуты файла: ";
			std::cin >> InputChar;

			if ((InputChar == 'g') || (InputChar == 'G'))
			{
				std::cout << "Введите имя файла, атрибуты которого нужно получить:" << std::endl;
				std::cin >> cPath;
				mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

				DWORD dwTemp = GetFileAttributes(mPath);
				if (dwTemp == INVALID_FILE_ATTRIBUTES)
				{
					std::cout << "Ошибка при получении атрибутов файла \"" << cPath << "\"." << std::endl;
					break;
				};

				//Выводим атрибуты файла
				if(dwTemp & 0x20)
					std::cout << "Архивный файл или каталог." << std::endl;

				if (dwTemp & 0x800)
					std::cout << "Сжатый файл или каталог." << std::endl;

				if (dwTemp & 0x10)
					std::cout << "Дескриптор, идентифицирующий каталог." << std::endl;

				if (dwTemp & 0x4000)
					std::cout << "Зашифрованный файл или каталог." << std::endl;

				if (dwTemp & 0x2)
					std::cout << "Скрытый файл или каталог." << std::endl;

				if (dwTemp & 0x8000)
					std::cout << "Каталог или поток данных пользователя настроен на целостность." << std::endl;

				if (dwTemp & 0x80)
					std::cout << "Файл, у которого нет других атрибутов." << std::endl;

				if (dwTemp & 0x2000)
					std::cout << "Файл или каталог не проиндексирован службой индексирования." << std::endl;

				if (dwTemp & 0x20000)
					std::cout << "Пользовательский поток данных не следует читать в фоновом режиме целостности данных." << std::endl;

				if (dwTemp & 0x1000)
					std::cout << "Данные файла недоступны сразу (данные файла физически перемещаются в автономное хранилище)." << std::endl;

				if (dwTemp & 0x1)
					std::cout << "Файл только для чтения." << std::endl;

				if (dwTemp & 0x400000)
					std::cout << "Файл или каталог не полностью присутствует локально." << std::endl;

				if (dwTemp & 0x40000)
					std::cout << "Файл или каталог не имеет физического представления в локальной системе; элемент является виртуальным." << std::endl;

				if (dwTemp & 0x400)
					std::cout << "Файл или каталог, имеющий связанную точку повторной обработки, или файл, являющийся символической ссылкой." << std::endl;

				if (dwTemp & 0x200)
					std::cout << "Разреженный файл." << std::endl;

				if (dwTemp & 0x4)
					std::cout << "Файл или каталог, который операционная система использует исключительно, или файл или каталог, в котором операционная система использует часть." << std::endl;

				if (dwTemp & 0x100)
					std::cout << "Файл, используемый для временного хранения." << std::endl;

				std::cout << std::endl;

				HANDLE hdl = CreateFile(mPath, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				BY_HANDLE_FILE_INFORMATION FileInfo;
				SYSTEMTIME SysTime;
				if (!GetFileInformationByHandle(hdl, &FileInfo))
				{
					std::cout << "Ошибка при получении атрибутов файла \"" << cPath << "\"." << std::endl;
					break;
				};

				//Выводим данные о файле
				if (!FileTimeToSystemTime(&FileInfo.ftCreationTime, &SysTime))
					std::cout << "Ошибка при получении времени создания файла \"" << cPath << "\"." << std::endl;

				std::cout << "Время создания файла:\nдата: " << SysTime.wDay << '.' << SysTime.wMonth << '.' << SysTime.wYear << "\nвремя: " << SysTime.wHour << ':' << SysTime.wMinute
					<< ':' << SysTime.wSecond << ':' << SysTime.wMilliseconds << "\nдень недели: " << SysTime.wDayOfWeek << std::endl << std::endl;

				if (!FileTimeToSystemTime(&FileInfo.ftLastAccessTime, &SysTime))
					std::cout << "Ошибка при получении времени последнего доступа к файлу \"" << cPath << "\"." << std::endl;

				std::cout << "Время последнего доступа к файлу:\nдата: " << SysTime.wDay << '.' << SysTime.wMonth << '.' << SysTime.wYear << "\nвремя: " << SysTime.wHour << ':' << SysTime.wMinute
					<< ':' << SysTime.wSecond << ':' << SysTime.wMilliseconds << "\nдень недели: " << SysTime.wDayOfWeek << std::endl << std::endl;

				if (!FileTimeToSystemTime(&FileInfo.ftLastWriteTime, &SysTime))
					std::cout << "Ошибка при получении времени последней записи в файл \"" << cPath << "\"." << std::endl;

				std::cout << "Время последней записи в файл:\nдата: " << SysTime.wDay << '.' << SysTime.wMonth << '.' << SysTime.wYear << "\nвремя: " << SysTime.wHour << ':' << SysTime.wMinute
					<< ':' << SysTime.wSecond << ':' << SysTime.wMilliseconds << "\nдень недели: " << SysTime.wDayOfWeek << std::endl << std::endl;

				std::cout << "Серийный номер диска, который содержит файл: " << FileInfo.dwVolumeSerialNumber << std::endl;
				std::cout << "Размер файла: " << FileInfo.nFileSizeLow + (FileInfo.nFileSizeHigh << 32) << std::endl;
				std::cout << "Число ссылок на файл: " << FileInfo.nNumberOfLinks << std::endl;
				std::cout << "Уникальный идентификатор, ассоциированный с файлом: " << FileInfo.nFileIndexLow + (FileInfo.nFileIndexHigh << 32) << std::endl;
			}
			else
			{
				if ((InputChar == 's') || (InputChar == 'S'))
				{
					std::cout << "Введите имя файла, атрибуты которого нужно изменить:" << std::endl;
					std::cin >> cPath;
					mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

					DWORD dwTemp;
					std::cout << "Введите атрибуты файла: ";
					std::cin >> dwTemp;

					if(SetFileAttributes(mPath, dwTemp))
						std::cout << "Атрибуты файла \"" << cPath << "\" успешно изменены." << std::endl;
					else
					{
						std::cout << "Ошибка при изменении атрибутов файла \"" << cPath << "\"." << std::endl;
						break;
					};

					HANDLE hdl = CreateFile(mPath, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					BY_HANDLE_FILE_INFORMATION FileInfo;
					SYSTEMTIME SysTime;

					//Время создания файла
					std::cout << "Введите день создания файла: ";
					std::cin >> SysTime.wDay;

					std::cout << "Введите месяц создания файла: ";
					std::cin >> SysTime.wMonth;

					std::cout << "Введите год создания файла: ";
					std::cin >> SysTime.wYear;

					std::cout << "Введите час создания файла: ";
					std::cin >> SysTime.wHour;

					std::cout << "Введите минуту создания файла: ";
					std::cin >> SysTime.wMinute;

					std::cout << "Введите секунду создания файла: ";
					std::cin >> SysTime.wSecond;

					std::cout << "Введите миллисекунду создания файла: ";
					std::cin >> SysTime.wMilliseconds;

					std::cout << "Введите день недели создания файла: ";
					std::cin >> SysTime.wDayOfWeek;

					if (!SystemTimeToFileTime(&SysTime, &FileInfo.ftCreationTime))
					{
						std::cout << "Ошибка при изменении времени создания файла \"" << cPath << "\"." << std::endl;
						break;
					};

					//Время последнего доступа к файлу
					std::cout << "Введите день последнего доступа к файлу: ";
					std::cin >> SysTime.wDay;

					std::cout << "Введите месяц последнего доступа к файлу: ";
					std::cin >> SysTime.wMonth;

					std::cout << "Введите год последнего доступа к файлу: ";
					std::cin >> SysTime.wYear;

					std::cout << "Введите час последнего доступа к файлу: ";
					std::cin >> SysTime.wHour;

					std::cout << "Введите минуту последнего доступа к файлу: ";
					std::cin >> SysTime.wMinute;

					std::cout << "Введите секунду последнего доступа к файлу: ";
					std::cin >> SysTime.wSecond;

					std::cout << "Введите миллисекунду последнего доступа к файлу: ";
					std::cin >> SysTime.wMilliseconds;

					std::cout << "Введите день недели последнего доступа к файлу: ";
					std::cin >> SysTime.wDayOfWeek;

					if (!SystemTimeToFileTime(&SysTime, &FileInfo.ftLastAccessTime))
					{
						std::cout << "Ошибка при изменении времени последнего доступа к файлу \"" << cPath << "\"." << std::endl;
						break;
					};

					//Время последней записи в файл
					std::cout << "Введите день последней записи в файл: ";
					std::cin >> SysTime.wDay;

					std::cout << "Введите месяц последней записи в файл: ";
					std::cin >> SysTime.wMonth;

					std::cout << "Введите год последней записи в файл: ";
					std::cin >> SysTime.wYear;

					std::cout << "Введите час последней записи в файл: ";
					std::cin >> SysTime.wHour;

					std::cout << "Введите минуту последней записи в файл: ";
					std::cin >> SysTime.wMinute;

					std::cout << "Введите секунду последней записи в файл: ";
					std::cin >> SysTime.wSecond;

					std::cout << "Введите миллисекунду последней записи в файл: ";
					std::cin >> SysTime.wMilliseconds;

					std::cout << "Введите день недели последней записи в файл: ";
					std::cin >> SysTime.wDayOfWeek;

					if (!SystemTimeToFileTime(&SysTime, &FileInfo.ftLastWriteTime))
					{
						std::cout << "Ошибка при изменении времени последней записи в файл \"" << cPath << "\"." << std::endl;
						break;
					};

					if (SetFileTime(hdl, &FileInfo.ftCreationTime, &FileInfo.ftLastAccessTime, &FileInfo.ftLastWriteTime))
						std::cout << "Атрибуты файла \"" << cPath << "\" успешно изменены." << std::endl;
					else
					{
						std::cout << "Ошибка при изменении атрибутов файла \"" << cPath << "\"." << std::endl;
						break;
					};
					

				}
				else
				{
					std::cout << "Ошибка! Введён неверный параметр при выборе операции." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};

			break;
		case '0':
			break;
		default:
			std::cout << "Ошибка! Введён неверный параметр при выборе пункта меню." << std::endl;
			std::cin.clear();
			std::cin.sync();
			break;
		};

		delete[] DiskName;
		delete[] wcDiskName;
		delete[] cPath;
		delete[] mPath;
		delete[] cPath1;
		delete[] mPath1;
	};

	return 0;
};